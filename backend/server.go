package main

import (
	"encoding/json"
	"fmt"
	"net/http"
)

type dummyGame struct {
	Name         string
	State        int
	ActivePlayer int
}

func connectFourHandler(w http.ResponseWriter, r *http.Request) {
	game := dummyGame{"test", 0, 1}
	json, err := json.Marshal(game)
/* print for debugging
	fmt.Println(game)
	fmt.Println("err:  ", err)
	fmt.Println("json: ", json)
*/
	w.Write(json)
}

func main() {

	http.HandleFunc("/wordclock/connectfour", connectFourHandler)
	http.ListenAndServe(":8080", nil)

}
