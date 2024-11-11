#import "security.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {
    load_private_key(argv[1]);
    derive_public_key();

    load_private_key(argv[2]);

    uint8_t sig[255];
    size_t sig_size = sign(public_key, pub_key_size, sig);

    uint8_t cert[255];
    uint8_t* buf = cert;
    *buf = 0xA0;
    buf += 1;
    *((uint16_t*) buf) = htons(6 + pub_key_size + sig_size);
    buf += 2;

    *buf = 0xA1;
    buf += 1;
    *((uint16_t*) buf) = htons(pub_key_size);
    buf += 2;
    memcpy(buf, public_key, pub_key_size);
    buf += pub_key_size;

    *buf = 0xA2;
    buf += 1;
    *((uint16_t*) buf) = htons(sig_size);
    buf += 2;
    memcpy(buf, sig, sig_size);
    buf += sig_size;

    FILE* fp = fopen(argv[3], "w");
    fwrite(cert, buf - cert, 1, fp);
    fclose(fp);

    return 0;
}
