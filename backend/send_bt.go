package main

import (
	"encoding/hex"
	"fmt"
	"os/exec"
	"strconv"
)

// converts input hex str to str of hex ascii codes representing the decimal value of the hex input
func hex2decAscii(hexStr string) string {

	//fmt.Printf("Input: %v\n", hexStr)

	decInt, _ := strconv.ParseUint(hexStr, 0, 64)
	//fmt.Printf("%T, %v\n", decInt, decInt)

	decStr := strconv.Itoa(int(decInt))
	//fmt.Printf("%T, %v\n", decStr, decStr)

	decAsciiuint8_ts := []uint8_t(decStr)
	//fmt.Printf("%T, %v\n", decAsciiuint8_ts, decAsciiuint8_ts)

	decAsciiStr := hex.EncodeToString(decAsciiuint8_ts)
	//fmt.Printf("%T, %v\n", decAsciiStr, decAsciiStr)

	return decAsciiStr
}

func sendBtButtonCode(buttonCode string) {
	//gattCmd := "gatttool -i hci0 -b 00:13:AA:00:BC:8C --char-write-req -a 0x0025 -n "+
		//hex2decAscii(buttonCode)
	cmd := exec.Command("gatttool", "-i", "hci0", "-b", "00:13:AA:00:BC:8C", "--char-write-req", "-a", "0x0025", "-n",
		hex2decAscii(buttonCode))
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
