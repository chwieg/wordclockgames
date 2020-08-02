package main

import (
	"fmt"
	. "golang.org/x/sys/unix"
	"time"
)

func main() {
	fd, _ := Socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)
	fmt.Println("Connecting")
	_ = Connect(fd, &SockaddrRFCOMM{
		Channel: 1,
		// Addr:    [6]byte{0x11, 0x22, 0x33, 0xaa, 0xbb, 0xcc}, // CC:BB:AA:33:22:11
		Addr: [6]byte{0x8c, 0xbc, 0x00, 0xaa, 0x13, 0x00}, // 00:13:AA:00:BC:8C
	})

	fmt.Println("Waiting...")
	time.Sleep(10 * time.Second)
	fmt.Println("done")
	Write(fd, []byte{0xff, 0x20, 0xdf})
	Close(fd)
}
