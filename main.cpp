//
//  main.cpp
//  CPSC441-Assignment2_Client
//
//  Created by Nathan Godard on 2018-10-19.
//  Copyright © 2018 Nathan Godard. All rights reserved.
//
#include "Client.hpp"
#include <iostream>

int main(int argc, const char * argv[]) {
    Client* client = new Client();
    client -> run_client(8543);
    return 0;
}
