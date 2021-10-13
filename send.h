//
// Created by sergio on 09/10/21.
//

#ifndef DISTRIBUTED_SYSTEM_SEND_H
#define DISTRIBUTED_SYSTEM_SEND_H

#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void send_conexions(int, int, int);

#endif //DISTRIBUTED_SYSTEM_SEND_H
