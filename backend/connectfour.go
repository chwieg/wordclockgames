package main

import (
	"fmt"
	//	"math/rand"
	//"os"
	//"time"
)

const nRows = 10
const nCols = 11

type state int

const (
	stRunning state = iota
	stStopWinner
	stStopDraw
)

type game struct {
	Board        [nRows][nCols]int // bord[0][0] is upper left corner
	AllowedMoves []int
	ActivePlayer int
	State        state
}

func newGame() game {
	g := game{
		State:        stRunning,
		ActivePlayer: 1,
	}
	g.updateAllowedMoves()
	return g
}

func (g *game) showBoard() {
	fmt.Println()
	fmt.Println("Board:")
	for i := 0; i < nRows; i++ {
		for j := 0; j < nCols; j++ {
			if g.Board[i][j] == 0 {
				fmt.Print(".")
			} else {
				fmt.Print(g.Board[i][j])
			}
			fmt.Print(" ")
		}
		fmt.Println()
	}
	fmt.Println()
}

func (g *game) updateAllowedMoves() {
	g.AllowedMoves = nil
	for i := 0; i < nCols; i++ {
		if g.Board[0][i] == 0 {
			g.AllowedMoves = append(g.AllowedMoves, i)
		}
	}
}

func (g *game) isAllowedMove(col int) bool {
	if col < 0 || col >= nCols {
		return false
	} else {
		for _, allowedCol := range g.AllowedMoves {
			if allowedCol == col {
				return true
			}
		}
		return false
	}
}

func (g *game) move(col int) {
	for i := nRows - 1; i >= 0; i-- {
		if g.Board[i][col] == 0 {
			g.Board[i][col] = g.ActivePlayer
			g.updateAllowedMoves()
			break
		}
	}
}

func (g *game) checkBoard() state {

	// check vertical
	for j := 0; j < nCols; j++ {
		cntFields := 0
		for i := 0; i < nRows; i++ {
			if g.Board[i][j] == g.ActivePlayer {
				cntFields += 1
				if cntFields == 4 {
					return stStopWinner
				}
			} else {
				cntFields = 0
			}
		}
	}
	// check horizontal
	for i := 0; i < nRows; i++ {
		cntFields := 0
		for j := 0; j < nCols; j++ {
			if g.Board[i][j] == g.ActivePlayer {
				cntFields += 1
				if cntFields == 4 {
					return stStopWinner
				}
			} else {
				cntFields = 0
			}
		}
	}

	// check diagonal southeast
	for i := 0 - (nCols - 4); i < nRows-3; i++ {
		cntFields := 0
		for j := 0; j < nCols && i+j < nRows; j++ {
			if i+j < 0 {
				continue
			}
			if g.Board[i+j][j] == g.ActivePlayer {
				cntFields += 1
				if cntFields == 4 {
					return stStopWinner
				}
			} else {
				cntFields = 0
			}
		}
	}

	// check diagonal northeast
	for i := nRows - 1 + (nCols - 4); i >= 3; i-- {
		cntFields := 0
		for j := 0; j < nCols && i-j >= 0; j++ {
			if i-j >= nRows {
				continue
			}
			if g.Board[i-j][j] == g.ActivePlayer {
				cntFields += 1
				if cntFields == 4 {
					return stStopWinner
				}
			} else {
				cntFields = 0
			}
		}
	}

	// check if draw
	for j := 0; j < nCols; j++ {
		for i := 0; i < nRows; i++ {
			if g.Board[i][j] == 0 {
				return stRunning
			}
		}
	}
	return stStopDraw

}
func (g *game) switchActivePlayer() {
if g.State == stRunning {
		if g.ActivePlayer == 1 {
			g.ActivePlayer = 2
		} else {
			g.ActivePlayer = 1
		}
}
}
/*
func main() {
	g := newGame()

	col := 0

	for i := 0; i < nRows*nCols+10; i++ {
		/*
			// simple vertical strategy
			if i==2 && g.ActivePlayer==1 {
				col = 3 // fatal mistakte by player 1
			} else {
				col = g.ActivePlayer
			}
		* /
		// random Strategy
		src := rand.NewSource(time.Now().UnixNano())
		randSeeded := rand.New(src)
		col = g.AllowedMoves[randSeeded.Intn(len(g.AllowedMoves))]

		if !g.isAllowedMove(col) {
			fmt.Println("Invalid move")
			os.Exit(-1)
		}
		g.move(col)
		g.State = g.checkBoard()
		switch g.State {
		case stStopWinner:
			fmt.Println()
			fmt.Println("Winner: Player ", g.ActivePlayer)
			g.showBoard()
			os.Exit(g.ActivePlayer)
		case stStopDraw:
			fmt.Println()
			fmt.Println("No winner.")
			g.showBoard()
			os.Exit(0)
		}
		// simple horizontal strategy
		if g.ActivePlayer == 1 {
			col += 1
		}
	}
}
*/
