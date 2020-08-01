package main

import (
	"encoding/json"
	"fmt"
	"net/http"
)

type clientData struct {
	Column int
}

var g game

func setupResponse(w *http.ResponseWriter, req *http.Request) {
	(*w).Header().Set("Access-Control-Allow-Origin", "*")
	//  (*w).Header().Set("Access-Control-Allow-Methods", "POST, GET, OPTIONS, PUT, DELETE")
	(*w).Header().Set("Access-Control-Allow-Methods", "GET, OPTIONS, PUT")
	(*w).Header().Set("Access-Control-Allow-Headers", "Accept, Content-Type, Content-Length, Accept-Encoding, X-CSRF-Token, Authorization")
}

func hiHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Entering Hi-Handler!")
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(http.StatusOK)
	w.Write([]byte("Hi!"))
}

func conFourNewGameHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Entering ConFourNewGame-Handler!")
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(http.StatusOK)

	fmt.Println("Creating new Game...")
	g = newGame()
	fmt.Println("done.")
	fmt.Println("Writing...")
	json, _ := json.Marshal(g)
	w.Write(json)
	fmt.Println("done.")
}
func conFourHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("Entering ConFour-Handler!")
	setupResponse(&w, r)
	fmt.Println("Request Method: ", r.Method)
	if (*r).Method == "OPTIONS" {
		return
	}
	switch r.Method {
	case http.MethodGet:	// Serve the resource.
		w.Header().Set("Content-Type", "application/json")
		w.WriteHeader(http.StatusOK)
		json, _ := json.Marshal(g)
		w.Write(json)
	case http.MethodPut:	// Update an existing record.
		w.Header().Set("Content-Type", "application/json")

		var d clientData
		err := json.NewDecoder(r.Body).Decode(&d)
		if err != nil {
			http.Error(w, err.Error(), http.StatusBadRequest)
			return
		}

		if g.State != stRunning {
			http.Error(w, "Game is already over", http.StatusBadRequest)
			return
		}

		if !g.isAllowedMove(d.Column) {
			http.Error(w, "Invalid value for Column", http.StatusBadRequest)
			return
		}

		w.WriteHeader(http.StatusOK)

		g.move(d.Column)
		g.State = g.checkBoard()
		g.switchActivePlayer()

		json, _ := json.Marshal(g)
		w.Write(json)
	}
	/*	// debugging
		json, err := json.Marshal(g)
		fmt.Println(g)
		fmt.Println("err:  ", err)
		fmt.Println("json: ", json)
	*/
}

func main() {
	g = newGame()
//	g.showBoard()
	fmt.Println("Server running at localhost:8080/wordclock/connectfour")
	http.HandleFunc("/hi", hiHandler)
	http.HandleFunc("/wordclock/connectfour", conFourHandler)
	http.HandleFunc("/wordclock/connectfour/newgame", conFourNewGameHandler)
	http.ListenAndServe(":8080", nil)

}
