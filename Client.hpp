//
//  Client.hpp
//  CPSC441 Assignment2
//
//  Created by Nathan Godard on 2018-10-12.
//  Copyright © 2018 Nathan Godard. All rights reserved.
//

#ifndef Client_hpp
#define Client_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <string.h>

#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <strings.h>
#include <netdb.h>

#define MAXMESSAGELENGTH 280
#define SERVER_IP "192.168.1.69"

class Client{
public:
    static void print_menu();
    int run_client(const int PORTNUMBER);
    void initialize_address(const int portnumber);
    int create_socket();
    int connect_TCP();
    size_t send_data(size_t length_of_message);
    size_t rcv_data();
private:
    sockaddr_in server;
    int status;
    int sock;
    char message[MAXMESSAGELENGTH];
    char rcv_message[MAXMESSAGELENGTH];
};


#endif /* Client_hpp */
