//
//  socket.h
//  p²-server
//
//  Created by James Carter on 3/1/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#pragma once

#include <netinet/in.h>

namespace App {
    struct datagram_socket {
        int file_descriptor;
        struct sockaddr_in address;
    };
}
