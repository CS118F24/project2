#pragma once

#include <arpa/inet.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Maximum payload size
#define MAX_PAYLOAD 1012

// Retransmission time
#define TV_DIFF(end, start)                                                    \
    (end.tv_sec * 1000000) - (start.tv_sec * 1000000) + end.tv_usec -          \
        start.tv_usec
#define RTO 1000000

// Window size
#define MAX_WINDOW 20 * MAX_PAYLOAD
#define DUP_ACKS 3

// States
#define SERVER_AWAIT 0
#define CLIENT_START 1
#define SERVER_SYN 2
#define ClIENT_AWAIT 3
#define SERVER_AWAIT_2 4
#define CLIENT_AWAIT_2 5
#define NORMAL 6

// Diagnostic messages
#define RECV 0
#define SEND 1
#define RTOD 2
#define DUPA 3

// Structs
typedef struct {
    uint32_t ack;
    uint32_t seq;
    uint16_t length;
    uint8_t flags; // LSb 0 SYN, LSb 1 ACK
    uint8_t unused;
    uint8_t payload[0];
} packet;

struct buffer_node {
    struct buffer_node* next;
    packet pkt;
} typedef buffer_node;

// Helpers
static inline void print(char* txt) {
    fprintf(stderr, "%s\n", txt);
}

static inline void print_diag(packet* pkt, int diag) {
    switch (diag) {
    case RECV:
        fprintf(stderr, "RECV");
        break;
    case SEND:
        fprintf(stderr, "SEND");
        break;
    case RTOD:
        fprintf(stderr, "RTOS");
        break;
    case DUPA:
        fprintf(stderr, "DUPS");
        break;
    }

    bool syn = pkt->flags & 0b01;
    bool ack = pkt->flags & 0b10;
    fprintf(stderr, " %u ACK %u SIZE %hu FLAGS ", ntohl(pkt->seq),
            ntohl(pkt->ack), ntohs(pkt->length));
    if (!syn && !ack) {
        fprintf(stderr, "NONE");
    } else {
        if (syn) {
            fprintf(stderr, "SYN ");
        }
        if (ack) {
            fprintf(stderr, "ACK ");
        }
    }
    fprintf(stderr, "\n");
}

static inline void print_buf(buffer_node* node) {
    fprintf(stderr, "BUF ");

    while (node != NULL) {
        fprintf(stderr, "%u ", htonl(node->pkt.seq));
        node = node->next;
    }
    fprintf(stderr, "\n");
}
