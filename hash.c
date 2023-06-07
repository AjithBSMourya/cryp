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
    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; 
    unsigned int hash_value = custom_hash(message);

    printf("Original Message: %s\n", message);
    printf("Hash value: %u\n", hash_value);

    char received_message[100];
    printf("Enter the received message: ");
    fgets(received_message, sizeof(received_message), stdin);
    received_message[strcspn(received_message, "\n")] = '\0';
    unsigned int received_hash_value = custom_hash(received_message);

    printf("Received Message: %s\n", received_message);
    printf("Received Hash value: %u\n", received_hash_value);

    if (received_hash_value == hash_value) {
        printf("Integrity: The message has not been modified.\n");
    }
    else {
        printf("Integrity: The message has been modified.\n");
    }

    return 0;
}
