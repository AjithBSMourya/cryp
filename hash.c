#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int hash(const char* msg) {
    srand((unsigned int)msg);
    unsigned int hv = rand() % (1 << 16);
    return hv;
}

int main() {
    char msg[100];
    printf("Enter a message: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = '\0'; 
    unsigned int hv = hash(msg);

    printf("Message: %s\n", msg);
    printf("Hash value: %u\n", hv);

    char rmsg[100];
    printf("Received message: ");
    fgets(rmsg, sizeof(rmsg), stdin);
    rmsg[strcspn(rmsg, "\n")] = '\0';
    unsigned int rhv = hash(rmsg);
    printf("Hash value: %u\n", rhv);

    if (rhv == hv) {
        printf("The message is not modified.\n");
    }
    else {
        printf("The message is modified.\n");
    }

    return 0;
}
