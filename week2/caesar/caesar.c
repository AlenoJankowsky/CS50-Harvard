#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int i);

int main(int argc, string argv[]) {

    bool isNotValidInput = argc != 2;

    if (isNotValidInput) {
        printf("Usage: Please enter a single number as a key. Like this: ./caesar key\n");

        return 1;
    }
    if (only_digits(argv[1])) {

        int key = atoi(argv[1]) % 26;
        string plain = get_string("plaintext: ");
        
        printf("ciphertext: ");
        for (int i = 0; i < strlen(plain); i++) {
            printf("%c", rotate(plain[i], key));
        }
        printf("\n");

        return 0;
    }
    else {
        printf("Usage: ./caesar key\n");

        return 1;
    }
}

bool only_digits(string s) {
    bool hasOnlyDigits = false;

    for (int i = 0; i < strlen(s); i++) {

        hasOnlyDigits = s[i] >= '0' && s[i] <= '9';
        return hasOnlyDigits;

    }
    return hasOnlyDigits;
}

char rotate(char c, int i) {

    bool isInLowerAlphabet = c >= 'a' && c <= 'z';
    bool isInUpperAlphabet = c >= 'A' && c <= 'Z';
    
    if (isInLowerAlphabet || isInUpperAlphabet) {
        for (int j = 1; j <= i; j++) {
            c = c + 1;

            if (isInLowerAlphabet) {
                bool isOutOfAlphabet = c == 'z' + 1;

                if (isOutOfAlphabet) {
                    c = 'a' + (i - j);

                    return c;
                }
            }

            if (isInUpperAlphabet) {
                bool isOutOfAlphabet = c == 'Z' + 1;

                if(isOutOfAlphabet) {
                    c = 'A' + (i - j);

                    return c;
                }
            }
        }   
    }
    return c;
}
