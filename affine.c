#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* encrypt(const char* msg, int a, int b) {
    char* em = malloc(strlen(msg) + 1);
    int i = 0;
    for (const char* ch = msg; *ch != '\0'; ++ch, ++i) {
        if (isalpha(*ch)) {
            char ec = (a * (toupper(*ch) - 'A') + b) % 26 + 'A';
            em[i] = ec;
        } else {
            em[i] = *ch;
        }
    }
    em[i] = '\0';
    return em;
}

char* decrypt(const char* msg, int a, int b) {
    int Inverse = -1;
    for (int i = 0; i < 26; ++i) {
        if ((a * i) % 26 == 1) {
            Inverse = i;
            break;
        }
    }
    if (Inverse == -1) {
        printf("Invalid value of 'a'. It must be coprime with 26.\n");
        return "";
    }
    char* dm = malloc(strlen(msg) + 1);
    int i = 0;
    for (const char* ch = msg; *ch != '\0'; ++ch, ++i) {
        if (isalpha(*ch)) {
            char dc = (aInverse * (toupper(*ch) - 'A' - b + 26)) % 26 + 'A';
            dm[i] = dc;
        } else {
            dm[i] = *ch;
        }
    }
    dm[i] = '\0';
    return dm;
}

int main() {
    char msg[1000];
    int a, b;
    
    printf("Enter the message: ");
    fgets(msg, 1000, stdin);
    msg[strcspn(msg, "\n")] = '\0';
    
    printf("Enter the value of 'a': ");
    scanf("%d", &a);
    
    printf("Enter the value of 'b': ");
    scanf("%d", &b);
    
    char* em = encrypt(msg, a, b);
    printf("Encrypted message: %s\n", em);
    free(em);
    
    char* dm = decrypt(em, a, b);
    printf("Decrypted message: %s\n", dm);
    free(dm);
    
    return 0;
}
