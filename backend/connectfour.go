package main

import (
	"fmt"
	"math/rand"
	"os"
	"time"
)

const nRows = 10
const nCols = 11

type State int

const (
	stateWinner State = iota
	stateDraw
	stateContinue
)

type Game struct {
	board        [nRows][nCols]int // bord[0][0] is upper left corner
	allowedMoves []int
	activePlayer int
	state        State
}

func (g *Game) showBoard() {
	fmt.Println()
	fmt.Println("Board:")
	for i := 0; i < nRows; i++ {
		for j := 0; j < nCols; j++ {
			if g.board[i][j] == 0 {
				fmt.Print(".")
			} else {
				fmt.Print(g.board[i][j])
			}
			fmt.Print(" ")
		}
		fmt.Println()
	}
	fmt.Println()
}

func (g *Game) updateAllowedMoves() {
	g.allowedMoves = nil
	for i := 0; i < nCols; i++ {
		if g.board[0][i] == 0 {
			g.allowedMoves = append(g.allowedMoves, i)
		}
	}
}

func (g *Game) isAllowedMove(col int) bool {
	if col < 0 || col >= nCols {
		return false
	} else {
		for _, allowedCol := range g.allowedMoves {
			if allowedCol == col {
				return true
			}
		}
		return false
	}
}

func (g *Game) move(col int) {
	for i := nRows - 1; i >= 0; i-- {
		if g.board[i][col] == 0 {
			g.board[i][col] = g.activePlayer
			g.updateAllowedMoves()
			break
		}
	}
}

func (g *Game) checkBoard() State {

	// check vertical
	for j := 0; j < nCols; j++ {
		cntFields := 0
		for i := 0; i < nRows; i++ {
			if g.board[i][j] == g.activePlayer {
				cntFields += 1
				if cntFields == 4 {
					return stateWinner
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
			if g.board[i][j] == g.activePlayer {
				cntFields += 1
				if cntFields == 4 {
					return stateWinner
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
			if g.board[i+j][j] == g.activePlayer {
				cntFields += 1
				if cntFields == 4 {
					return stateWinner
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
			if g.board[i-j][j] == g.activePlayer {
				cntFields += 1
				if cntFields == 4 {
					return stateWinner
				}
			} else {
				cntFields = 0
			}
		}
	}

	// check if draw
	for j := 0; j < nCols; j++ {
		for i := 0; i < nRows; i++ {
			if g.board[i][j] == 0 {
				return stateContinue
			}
		}
	}
	return stateDraw

}

func main() {

	g := Game{
		state:        stateContinue,
		activePlayer: 1,
	}
	g.updateAllowedMoves()

	col := 0
	for i := 0; i < nRows*nCols+10; i++ {
		/*
			// simple vertical strategy
			if i==2 && g.activePlayer==1 {
				col = 3 // fatal mistakte by player 1
			} else {
				col = g.activePlayer
			}
		*/
		// random Strategy
		src := rand.NewSource(time.Now().UnixNano())
		randSeeded := rand.New(src)
		col = g.allowedMoves[randSeeded.Intn(len(g.allowedMoves))]

		if !g.isAllowedMove(col) {
			fmt.Println("Invalid move")
			os.Exit(-1)
		}
		g.move(col)
		g.state = g.checkBoard()
		switch g.state {
		case stateWinner:
			fmt.Println()
			fmt.Println("Winner: Player ", g.activePlayer)
			g.showBoard()
			os.Exit(g.activePlayer)
		case stateDraw:
			fmt.Println()
			fmt.Println("No winner.")
			g.showBoard()
			os.Exit(0)
		}
		if g.activePlayer == 1 {
			g.activePlayer = 2
		} else {
			g.activePlayer = 1
		}

		// simple horizontal strategy
		if g.activePlayer == 1 {
			col += 1
		}
	}
}
