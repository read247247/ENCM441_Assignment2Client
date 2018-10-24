//
//  Client.cpp
//  CPSC441 Assignment2

// TCP-based client example of socket programming.
// This client interacts with the Assignment2 server,
// which needs to be running first.
//
//  Created by Nathan Godard on 2018-10-12.
//  Adapted from code given by Dr. Carey Williamson at http://pages.cpsc.ucalgary.ca/~carey/CPSC441/examples/wordlengthclient.c (Retrieved Oct. 19, 2018)
//

#include "Client.hpp"

#define DEBUG 0

int Client::run_client(const int PORTNUMBER) {
    int selection;
    char c;
    int tweet_length = 0;
    size_t num_bytes_rcvd;
    
    // Set up  socket
    initialize_address(PORTNUMBER);
    sock = create_socket();
    if(sock < 0){ exit(1); }    //Failed to create socket

    // Connect to server
    status = connect_TCP();
    if(status < 0) { exit(1); } //Failed to connect to server
    
    // Begin interaction
    std::cout << "Welcome!\n";
    print_menu();
    
    scanf("%d", &selection);
    
    while(selection != 0){     //Run until user selects exit from main menu
        if(selection == 1){    //User chose to run the main program (from main menu)
            c = getchar();      // get rid of newline after the (integer) menu choice given
            
            std::cout << "Enter the tweet you wish to encode: ";
            tweet_length = 0;
            while( (c = getchar()) != '\n' ){
                message[tweet_length] = c;
                tweet_length++;
            }
            
            if(tweet_length > MAXMESSAGELENGTH){
                std::cout << "That tweet is toooooo long. Sorry! Try again";
                print_menu();
                scanf("%d", &selection);
                continue;
            }
            
            message[tweet_length] = '\0';
            
            send_data(tweet_length);
            num_bytes_rcvd = rcv_data();
            
            if(num_bytes_rcvd > 0){
                std::cout << "Answer received from server: ";
                std::cout << rcv_message;
            } else{
                std::cout << "THE SERVER HAS DESERTED US!! WE ARE ALOOOONE\n";
                close(sock);
                exit(1);
            }
        }
        else printf("Invalid menu selection. Please try again.\n");
        
        print_menu();
        
        scanf("%d", &selection);
    }
    strcpy(message, "CLOSE CONNECTION");
    send_data(17);
    std::cout << "Goodbye!\n";
    close(sock);
    return 0;
}

void Client::initialize_address(const int portnumber){
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(portnumber);
    //server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
}

int Client::create_socket(){
    sock = socket(PF_INET, SOCK_STREAM, 0);
#if DEBUG
    if (sock < 0) {
        std::cout << "Error in socket() while creating lstn_sock\n";
    } else { std::cout << "socket() run successfully\n"; }
#endif
    return sock;
}

int Client::connect_TCP(){
    status = connect(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_in));
#if DEBUG
    if (status < 0) {
        printf("Error in connect()\n");
    } else {
        printf("Connected.\n");
    }
#endif
    return status;
}

size_t Client::send_data(size_t length_of_message){
    size_t count;
    count = send(sock, message, length_of_message, 0);
#if DEBUG
    if (count <= 0) {
        std::cout << "Error in send()\n";
    } else { std::cout << "Send successful\n"; }
#endif
    return count;
}

size_t Client::rcv_data(){
    size_t count;
    count = recv(sock, rcv_message, sizeof(rcv_message), 0);
    rcv_message[count] = '\0';
#if DEBUG
    if (count < 0) {
        printf("Error in recv()\n");
    } else {
        printf("Server says: %s\n", rcv_message);
    }
#endif
    return count;
}

void Client::print_menu()
{
    std::cout << "\n";
    std::cout << "Please choose from the following selections:\n";
    std::cout << "  1 - Enter a word\n";
    std::cout << "  0 - Exit program\n";
    std::cout << "Your desired menu selection? ";
}
