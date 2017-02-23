#include "oop_winsock.h"
#include <iostream>
#include <thread>

int main() {

	winsock_client client(27000, "127.0.0.1"); //transmitter
	winsock_client client2(27001, "127.0.0.1"); //receiver
	char rx_message[128] = "", tx_message[128] = "Hello";
	

	client.connect_to_tcp_server_loop();

	
	
	if (strcmp(rx_message, "Server Full") == 0) {
		std::cout << "Could not connect to server" << std::endl;
		std::cin.get();
	} else if (strcmp(rx_message, "Welcome") == 0) {
		client2.connect_to_tcp_server_loop(); //added
		strcpy(rx_message, client2.receive_message()); //added
		std::cout << "Start sending (and receiving) messages:" << rx_message << std::endl << std::endl; //added
		std::thread(&winsock_client::get_message, &client2).detach(); //added
		
		while (true) {
			std::cout << "Enter message to send: " << std::endl;
			std::cin.getline(tx_message, sizeof(tx_message));
			client.send_message(tx_message);
			strcpy(rx_message, client.receive_message());
			std::cout << "server ack:" << rx_message << std::endl << std::endl;
			
			if (strcmp(tx_message, "quit") == 0) {
				break;
			}
		}
	}

	WSACleanup();
	exit(0);
}