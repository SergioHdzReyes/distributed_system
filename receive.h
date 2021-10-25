//
// Created by sergio on 10/10/21.
//

#ifndef DISTRIBUTED_SYSTEM_RECEIVE_H
#define DISTRIBUTED_SYSTEM_RECEIVE_H

#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

void receive_conexions(int, int, int**);

#endif //DISTRIBUTED_SYSTEM_RECEIVE_H
