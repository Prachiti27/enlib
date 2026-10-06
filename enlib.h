#ifndef ENLIB_H
#define ENLIB_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#define eldecrypt(x, y) elencrypt(x, y)

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

typedef struct s_enlib {
    int8 S[256];
    int8 i;
    int8 j;
} Enlib;

//Initialize RC4 with the given key.
Enlib *elinit(int8 *key, int16 keylen);


//Generate the next byte of the RC4 keystream.

int8 elbyte(void);


//Encrypt/decrypt data.

int8 *elencrypt(int8 *input, int16 len);

#endif