#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Digest* SHA_40(const unsigned char* data, size_t size) {
	int seed[] = {11, 22, 33, 44, 55};
	struct Digest top_digest;
	top_digest.hash0 = seed[0];
	top_digest.hash1 = seed[1];
	top_digest.hash2 = seed[2];
	top_digest.hash3 = seed[3];
	top_digest.hash4 = seed[4];

	for (int i = 0; i < size; i++) {
		unsigned char block = data[i];
		//printf("%c", block);
		for (int round = 0; round < 12; round++) {
			struct Digest bottom_digest;

			//remapps each hash value
			// bottom B = top A 
			bottom_digest.hash1 = top_digest.hash0;

			//bottom C = top B << 1
			bottom_digest.hash2 = top_digest.hash1 << 1;

			//bottom D = top C
			bottom_digest.hash3 = top_digest.hash2;

			//bottom E = top D
			bottom_digest.hash4 = top_digest.hash3;

			
			//bottom A = top E + (top B & top C) ^ top D + top A >> 3 + block chunk + round
			unsigned char temp = top_digest.hash4 + ((top_digest.hash1 & top_digest.hash2) ^ top_digest.hash3);
			temp += (top_digest.hash0 >> 3);
			temp += (int)block;
			temp += round;
			bottom_digest.hash0 = temp;


			//matches each hash value for next iteration
			top_digest.hash0 = bottom_digest.hash0;
			top_digest.hash1 = bottom_digest.hash1;
			top_digest.hash2 = bottom_digest.hash2;
			top_digest.hash3 = bottom_digest.hash3;
			top_digest.hash4 = bottom_digest.hash4;
		}

	}

	printf("%d ", top_digest.hash0);
	printf("%d ", top_digest.hash1);
	printf("%d ", top_digest.hash2);
	printf("%d ", top_digest.hash3);
	printf("%d\n", top_digest.hash4);


	struct Digest* final = (struct Digest*)malloc(sizeof(DIGEST_SIZE));
	final->hash0 = top_digest.hash0;
	final->hash1 = top_digest.hash1;
	final->hash2 = top_digest.hash2;
	final->hash3 = top_digest.hash3;
	final->hash4 = top_digest.hash4;

	return final;
}

//Compares every hash segment of the SHA_40 output to another SHA_40 output
int digest_equal(struct Digest* digest1, struct Digest* digest2) {
	if (digest1->hash0 == digest2->hash0) {
		if (digest1->hash1 == digest2->hash1) {
			if (digest1->hash2 == digest2->hash2) {
				if (digest1->hash3 == digest2->hash3) {
					if (digest1->hash4 == digest2->hash4) {
						return 1;
					}
				}
			}
		}
	}
	else {
		return 0;
	}
}

int main() {
	printf("Hashing 'Rob'...\t");
	unsigned char* rob = SHA_40("Rob", sizeof("Rob"));
	printf("\n\nHashing 'James'...\t");
	unsigned char* james = SHA_40("James", sizeof("James"));
	printf("\n\nHashing 'Ahmed'...\t");
	unsigned char* ahmed = SHA_40("Ahmed", sizeof("Ahmed"));
	printf("\n\nHashing 'CSEC'...\t");
	unsigned char* csec = SHA_40("CSEC", sizeof("CSEC"));
	printf("\n\nHashing 'Griffin'...\t");
	unsigned char* griffin = SHA_40("Griffin", sizeof("Griffin"));

	printf("\n\nTesting equality of 'Rob' and 'Rob'...\t");
	printf("%d\n", digest_equal(rob, rob));
	

	printf("\n\nTesting equality of 'Rob' and 'Ahmed'...\t");
	printf("%d", digest_equal(rob, ahmed));
	
	

	
	

}