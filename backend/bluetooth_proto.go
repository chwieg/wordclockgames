package main

// import "cmd/vendor/golang.org/x/sys/unix"
import "net"


type SockaddrRFCOMM struct {

	// Addr represents a bluetooth address, byte ordering is little-endian.

	Addr [6]uint8


	// Channel is a designated bluetooth channel, only 1-30 are available for use.

	// Since Linux 2.6.7 and further zero value is the first available channel.

	Channel uint8


	raw RawSockaddrRFCOMM

}


func (sa *SockaddrRFCOMM) sockaddr() (unsafe.Pointer, _Socklen, error) {

	sa.raw.Family = AF_BLUETOOTH

	sa.raw.Channel = sa.Channel

	sa.raw.Bdaddr = sa.Addr

}




func main() {
	fd, _ := Socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)
	_ = Connect(fd, &SockaddrRFCOMM{
		Channel: 1,
		// Addr:    [6]byte{0x11, 0x22, 0x33, 0xaa, 0xbb, 0xcc}, // CC:BB:AA:33:22:11
		Addr:    [6]byte{0x8c, 0xbc, 0x00, 0xaa, 0x13, 0x00}, // 00:13:AA:00:BC:8C
	})
	Write(fd, [3]byte(0xff, 0x20, 0xdf))
	Close(fd)
}
