# RC4 Encryption Library

A small C implementation of the **RC4 (Rivest Cipher 4 / ARCFOUR) stream cipher**, built from scratch as a learning project.

The library implements the core RC4 algorithm without relying on an external cryptography library.

## What I Implemented

### 1. Key Scheduling Algorithm (KSA)

Implemented RC4's **Key Scheduling Algorithm** in `elinit()`.

The algorithm:

- Initializes the 256-byte state array `S`
- Fills it with values `0–255`
- Uses the provided key to permute the state array
- Initializes the RC4 indices `i` and `j`

```text
S = [0, 1, 2, ..., 255]

        +
        │
       Key
        │
        ▼
   Key Scheduling
      (KSA)
        │
        ▼
  Permuted S[256]
```

### 2. Pseudo-Random Generation Algorithm (PRGA)

Implemented RC4's keystream generation in `elbyte()`.

For every byte requested, the implementation:

1. Updates `i`
2. Updates `j`
3. Swaps `S[i]` and `S[j]`
4. Generates the next keystream byte

```text
S[256]
  │
  ▼
 PRGA
  │
  ▼
Keystream byte
```

### 3. Encryption

Implemented encryption in `elencrypt()`.

RC4 uses XOR between the input data and generated keystream:

```text
ciphertext = plaintext XOR keystream
```

Each byte is processed independently:

```c
output[i] = input[i] ^ elbyte();
```

### 4. Decryption

RC4 uses the same operation for decryption:

```text
plaintext = ciphertext XOR keystream
```

Therefore:

```c
#define eldecrypt(x, y) elencrypt(x, y)
```

The RC4 state must be initialized again with the same key before decrypting so that the same keystream is generated.

## Project Structure

```text
.
├── enlib.h       # Library interface and data structures
├── enlib.c       # RC4 implementation
├── example.c     # Example program demonstrating encryption/decryption
├── Makefile      # Build configuration
└── README.md
```

## API

### `elinit()`

Initializes the RC4 state using the supplied key.

```c
Enlib *elinit(int8 *key, int16 keylen);
```

### `elbyte()`

Generates one byte of the RC4 keystream.

```c
int8 elbyte(void);
```

### `elencrypt()`

Encrypts data using the generated RC4 keystream.

```c
int8 *elencrypt(int8 *input, int16 len);
```

### `eldecrypt()`

Decryption uses the same operation as encryption.

```c
#define eldecrypt(x, y) elencrypt(x, y)
```

## Building

Build the library and example program with:

```bash
make
```

This produces:

```text
enlib.so
example
```

Run the example:

```bash
./example
```

Clean build artifacts:

```bash
make clean
```