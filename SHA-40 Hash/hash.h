#pragma once
/*
 * CSEC-201
 * Authors: CSEC-201 Instructors
 * Semester: 2221
 * Purpose: Header file for SHA_40
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIGEST_SIZE 5 //Size of SHA_40 hash in bytes
#define BYTE unsigned char //Allows using BYTE in place of unsigned char

 //SHA_40 digest structure definition
struct Digest {
    BYTE hash0, hash1, hash2, hash3, hash4;
};

//Function Prototypes
struct Digest* SHA_40(const unsigned char* data, size_t size); //SHA_40 hash function 
int digest_equal(struct Digest* digest1, struct Digest* digest2); //Returns 1 (true) or 0 (false)