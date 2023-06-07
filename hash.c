#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int custom_hash(const char* message) {
    srand((unsigned int)message);
    unsigned int hash_value = rand() % (1 << 16);
    return hash_value;
}

int main() {
    char message[100];
    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; 
    unsigned int hash_value = custom_hash(message);

    printf("Message: %s\n", message);
    printf("Hash value: %u\n", hash_value);

    char received_message[100];
    printf("Received message: ");
    fgets(received_message, sizeof(received_message), stdin);
    received_message[strcspn(received_message, "\n")] = '\0';
    unsigned int received_hash_value = custom_hash(received_message);
    printf("Hash value: %u\n", received_hash_value);

    if (received_hash_value == hash_value) {
        printf("Integrity: The message is not modified.\n");
    }
    else {
        printf("Integrity: The message is modified.\n");
    }

    return 0;
}
