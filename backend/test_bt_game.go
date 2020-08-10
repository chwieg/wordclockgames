package main

func main() {

	g := newGame()

	g.move(0)
	g.updateState()
	g.updateAllowedMoves()
	g.switchActivePlayer()

	g.move(1)
	g.updateState()
	g.updateAllowedMoves()
	g.switchActivePlayer()

	g.move(0)
	g.updateState()
	g.updateAllowedMoves()
	g.switchActivePlayer()

	g.move(6)
	g.updateState()
	g.updateAllowedMoves()
	g.switchActivePlayer()

	g.ColorPlayer1 = "FF0000"

	sendBtGame(g)
/*
	type game struct {
		State        state
		ActivePlayer int
		ColorPlayer1 string
		ColorPlayer2 string
		AllowedMoves [nCols]bool
		Board        [nRows][nCols]int // bord[0][0] is upper left corner
	} */
}