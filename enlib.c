#include "enlib.h"

static Enlib *el = NULL;

//Initialize the RC4 state using the Key Scheduling Algorithm (KSA).

Enlib *elinit(int8 *key, int16 keylen)
{
    int i;
    int j = 0;
    int8 temp;

    if (key == NULL || keylen == 0)
        return NULL;

    el = malloc(sizeof(Enlib));

    if (el == NULL)
        return NULL;

    for (i = 0; i < 256; i++)
        el->S[i] = (int8)i;

    //Key Scheduling Algorithm (KSA)
    for (i = 0; i < 256; i++) {
        j = (j + el->S[i] + key[i % keylen]) & 0xff;

        temp = el->S[i];
        el->S[i] = el->S[j];
        el->S[j] = temp;
    }

    el->i = 0;
    el->j = 0;

    return el;
}

/*
  Generate one byte of RC4 keystream.
 
  This is the PRGA:
 
  i = i + 1
  j = j + S[i]
  swap(S[i], S[j])
  output = S[(S[i] + S[j]) % 256]
 */
int8 elbyte(void)
{
    int8 temp;
    int8 k;

    if (el == NULL)
        return 0;

    el->i = (el->i + 1) & 0xff;
    el->j = (el->j + el->S[el->i]) & 0xff;

    temp = el->S[el->i];
    el->S[el->i] = el->S[el->j];
    el->S[el->j] = temp;

    k = (el->S[el->i] + el->S[el->j]) & 0xff;

    return el->S[k];
}

/*
  RC4 encryption.
 
  RC4 encryption and decryption are identical:
  ciphertext = plaintext XOR keystream
  plaintext  = ciphertext XOR keystream
 */
int8 *elencrypt(int8 *input, int16 len)
{
    int16 i;
    int8 *output;

    if (input == NULL || len == 0)
        return NULL;

    output = malloc(len);

    if (output == NULL)
        return NULL;

    for (i = 0; i < len; i++)
        output[i] = input[i] ^ elbyte();

    return output;
}