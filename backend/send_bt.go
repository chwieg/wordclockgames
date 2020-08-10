package main

import (
	"encoding/hex"
	"fmt"
	"os/exec"
	"strconv"
)

const btGameBufferLen = 49 // number of Bytes to transmit for game state


// converts input hex str to str of hex ascii codes representing the decimal value of the hex input
func hex2decAscii(hexStr string) string {

	decInt, _ := strconv.ParseUint(hexStr, 0, 64)
	decStr := strconv.Itoa(int(decInt))
	decAsciiBytes := []byte(decStr)
	decAsciiStr := hex.EncodeToString(decAsciiBytes)

	return decAsciiStr
}

func getBtGameBuffer(g game) [btGameBufferLen]byte {

	var (
		buffer [49]byte
		ixBeg int
		ixEnd int
	)

	h, _ :=  hex.DecodeString(g.ColorPlayer1)
	copy(buffer[:3],h)

	h, _ =  hex.DecodeString(g.ColorPlayer2)
	copy(buffer[3:6],h)

	for i := 0; i < nRows; i++ {
		ixBeg = 6+(i*nCols)
		ixEnd = ixBeg+nCols
		copy(buffer[ixBeg:ixEnd], g.Board[i][:])
	}

	if g.State == stRunning {
		buffer[ixEnd] = g.ActivePlayer
	} else {
		buffer[ixEnd] = 0
	}

	return buffer
}


func sendBtButtonCode(buttonCode string) {

	sendBtCommand(hex2decAscii(buttonCode))
}

func sendBtGame(g game) {

	buffer := getBtGameBuffer(g)
	sendBtCommand(hex.EncodeToString(buffer[:]))
}

func sendBtCommand(btCommand string) {
	cmd := exec.Command("gatttool", "-i", "hci0", "-b", "00:13:AA:00:BC:8C", "--char-write-req", "-a", "0x0025", "-n",
		btCommand)
	out, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Printf("cmd.Run() failed with %s\n", err)
	}
	fmt.Printf("combined out:\n%s\n", string(out))
}



/*
func main() {
	// hex2decAscii("0xff")
	gattCmd := "sudo gatttool -i hci0 -b 00:13:AA:00:BC:8C --char-write-req -a 0x0025 -n "+
		//hex2decAscii("0xFF906F") // red
		hex2decAscii("0xFF609F") // seconds

	fmt.Println("\ncommand to execute:\n")
	fmt.Println(gattCmd)

	// cmd := exec.Command("/bin/sh", "-c", "sudo find . -name \"*.go\"")
	cmd := exec.Command("/bin/sh", "-c", gattCmd)
	out, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Printf("cmd.Run() failed with %s\n", err)
	}
	fmt.Printf("combined out:\n%s\n", string(out))
}
*/
