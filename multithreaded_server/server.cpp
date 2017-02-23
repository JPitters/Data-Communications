#include "oop_winsock.h"

extern int const MAX_SOCKETS;

int main() {

	winsock_server server(27000, "127.0.0.1"); //receiver
	winsock_server server2(27001, "127.0.0.1"); //transmitter - added
	int socket_number;

	while (true) {
		socket_number = server.accept_connection();
		if ( socket_number < MAX_SOCKETS) {
			
			std::thread(&winsock_server::rec_mode, &server, socket_number).detach(); //added
			
			server2.accept_connection(); //added
			std::thread(&winsock_server::send_mode, &server2).detach(); //changed to send_mode from echo_mode
		}
	}

	WSACleanup();
	exit(0);
}
