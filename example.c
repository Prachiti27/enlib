#include "enlib.h"

#define F fflush(stdout)

void printbin(int8 *input, const int16 size)
{
    int16 i;
    int8 *p;

    assert(size > 0);

    for (i = size, p = input; i; i--, p++) {
        if (!((i + 1) % 2))
            printf(" ");

        printf("%.02x", *p);
    }

    printf("\n");
}

int main(void)
{
    Enlib *el;
    int16 skey, stext;
    int8 *key, *from, *encrypted, *decrypted;

    key = (int8 *)"tomatoes";
    skey = strlen((char *)key);

    from = (int8 *)"Shall I compare thee to a summer's day?";
    stext = strlen((char *)from);

    printf("Initializing encryption...");
    F;

    el = elinit(key, skey);

    if (el == NULL) {
        fprintf(stderr, "Failed to initialize encryption\n");
        return 1;
    }

    printf("done\n");

    printf("'%s'\n", from);

    encrypted = elencrypt(from, stext);

    if (encrypted == NULL) {
        fprintf(stderr, "Encryption failed\n");
        return 1;
    }

    printf("Encrypted:\n");
    printbin(encrypted, stext);

    el = elinit(key, skey);

    if (el == NULL) {
        fprintf(stderr, "Failed to reinitialize encryption\n");
        free(encrypted);
        return 1;
    }

    decrypted = eldecrypt(encrypted, stext);

    if (decrypted == NULL) {
        fprintf(stderr, "Decryption failed\n");
        free(encrypted);
        return 1;
    }

    printf("Decrypted:\n");
    printf("'%.*s'\n", stext, decrypted);

    free(encrypted);
    free(decrypted);

    return 0;
}