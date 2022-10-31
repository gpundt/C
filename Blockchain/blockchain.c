/*
 * CSEC-201
 * Authors: CSEC-201 Instructors
 * Semester: 2221
 * Purpose: Blockchain implementation
 */

#include "blockchain.h"
#include <stdbool.h>

 /*
  * Name: initialize
  * Purpose: Creates and returns a pointer to an empty blockchain
  * Parameters: None
  * Returns: pointer to Blockchain
  */
struct Blockchain* initialize()
{
    struct Blockchain* chain = (struct Blockchain*)malloc(sizeof(struct Blockchain));
    chain->size = 0;
    chain->head = NULL;
    return chain;
}

/*
 * Name: print_blockchain
 * Purpose: Prints blockchain
 * Parameters: Pointer to Blockchain
 * Returns: None
 */
void print_blockchain(struct Blockchain* blockchain)
{
    printf("Printing...\n");
    struct Block* current = blockchain->head;
    while (current) {
        printf("{height: %d, data: %d, prev_hash: %d %d %d %d %d}\n",
            current->height, current->data, current->prev_hash.hash0, current->prev_hash.hash1,
            current->prev_hash.hash2, current->prev_hash.hash3, current->prev_hash.hash4);
        current = current->prev_block;
    }
}

//Sets digest to the SHA_40 digest of block
void set_digest(struct Digest digest, struct Block* prevBlock, struct Block* currentBlock) {
    unsigned char* hash = SHA_40((unsigned char*) prevBlock, BLOCK_SIZE);
    digest.hash0 = hash[0];
    digest.hash1 = hash[1];
    digest.hash2 = hash[2];
    digest.hash3 = hash[3];
    digest.hash4 = hash[4];

    currentBlock->prev_hash = digest;

}

//Adds a block to a blockchain
void add(struct Blockchain* chain, int data) {
    //creates a new block on the heap
    struct Block* new_block = (struct Block*)malloc(BLOCK_SIZE);

    //sets block's prev_hash
    if (chain->size == 0) {
        new_block->prev_hash.hash0 = 0;
        new_block->prev_hash.hash1 = 0;
        new_block->prev_hash.hash2 = 0;
        new_block->prev_hash.hash3 = 0;
        new_block->prev_hash.hash4 = 0;

        //assigns new_block as head
        chain->head = new_block;
        new_block->prev_block = NULL;

        //sets new block's data
        new_block->data = data;

        //sets new block's height
        //printf("%d", chain->size);
        new_block->height = chain->size;

        //increments chain size
        chain->size = (chain->size + 1);
    }else {
        struct Block* old_head = chain->head;
        new_block->prev_block = old_head;
        chain->head = new_block;

        //sets prev_hash to SHA-40 of prev_block
        struct Digest d1 = new_block->prev_hash;
        set_digest(d1, old_head, new_block);
        
        //sets new block's data
        new_block->data = data;

        //sets new block's height
        new_block->height = chain->size;

        //increments chain size
        chain->size = (chain->size + 1);
    }


}

//verifies integrity of blockchain
//iterates through every block in the chain and compares
//its assigned prev_hash value with the actual hash value of
//its prev_block
void verify(struct Blockchain* chain) {
    printf("Verifying...\n");
    struct Block* current = chain->head;
    while (current) {
        printf("Testing Block %d...\n", current->height);
        if (current->height == 0) {
            printf("Block 0 passed\n");
            printf("All blocks have been verified\n\n");
            break;
        }
        unsigned char* actual = SHA_40((unsigned char*)current->prev_block, BLOCK_SIZE);
        struct Digest actualDigest;
        actualDigest.hash0 = actual[0];
        actualDigest.hash1 = actual[1];
        actualDigest.hash2 = actual[2];
        actualDigest.hash3 = actual[3];
        actualDigest.hash4 = actual[4];

        if(actualDigest.hash0 == current->prev_hash.hash0 &&
            actualDigest.hash1 == current->prev_hash.hash1 &&
            actualDigest.hash2 == current->prev_hash.hash2 &&
            actualDigest.hash3 == current->prev_hash.hash3 &&
            actualDigest.hash4 == current->prev_hash.hash4)
{
                
            printf("Block %d Passed\n", current->height);
            current = current->prev_block;
        }
        else {
            printf("Block %d Failed\n", current->height);
            current = NULL;
        }


        
    }
    
}

//deletes a block at given height
void delete_at(struct Blockchain* chain, int height) {
    printf("Deleting block at height %d...\n", height);
    struct Block* current = chain->head;
    if (current->height == height) {
        chain->head = current->prev_block;
    }
    else {
        current = current->prev_block;
        while (current) {
            if (current->height == height) {
                struct Block* newTop = chain->head;
                while (newTop) {
                    if (newTop->height == height + 1) {
                        newTop->prev_block = current->prev_block;
                        newTop = NULL;
                    }
                    else {
                        newTop = newTop->prev_block;
                    }
                }
                
            }
            current = current->prev_block;

        }
    }



    printf("Block at height %d has been deleted\n", height);
}

//changes the data of a block at given height
void alter_block(struct Blockchain* chain, int height, int data) {
    printf("Altering a block...\nBlock %d altered containing now %d\n", height, data);
    struct Block* current = chain->head;
    while (current) {
        if (current->height == height) {
            current->data = data;
            current = NULL;
        }
        else {
            current = current->prev_block;
        }
    }
}

//changes the data of a block at a given height, as well as the 
//next block's prev_hash value
void alter_2_blocks(struct Blockchain* chain, int height, int data) {
    bool sentinel1 = true;
    bool sentinel2 = true;
    printf("Altering blocks at height %d and height %d...\n", height, height + 1);
    struct Block* current = chain->head;
    while (sentinel1) {
        if (current->height == height) {
            struct Block* priorBlock = chain->head;
            while (sentinel2) {
                if (priorBlock->prev_block == current) {
                    struct Digest digest = priorBlock->prev_hash;
                    current->data = data;
                    set_digest(digest, current, priorBlock);
                    sentinel2 = false;
                }
                else {
                    priorBlock = priorBlock->prev_block;
                }
            }
            sentinel1 = false;
        }
        else {
            current = current->prev_block;
        }
    }
    printf("Blocks at height %d and %d have been altered\n", height, height + 1);
}

/*
 * Name: main
 * Purpose: Test functions above
 * Parameters: int argc, char* argv[]
 * Returns: integer
 */
int main(int argc, char* argv[])
{
    //Test cases
    //Test 1
    //Create, print, and verify blockchain
    struct Blockchain* blockchain = initialize();
    for (int i = 1; i <= 5; i++)
    {
        add(blockchain, 10 * i);
       
    }
    print_blockchain(blockchain);
    verify(blockchain);
    

    //Test 2
    //Alter the value in a block, print, and verify blockchain
    //alter_block(blockchain, 2, 300);
    //print_blockchain(blockchain);
    //verify(blockchain);

    //Test 3
    //Comment out Test 2, and uncomment the following three code lines
    //Alter the value in a block and the hash value tracked for
    //that altered block
    //alter_2_blocks(blockchain, 1, 200);
    //print_blockchain(blockchain);
    //verify(blockchain);

    //Test 4
    //Comment out Test 2 and 3, and uncomment the following three code lines
    delete_at(blockchain, 1);
    print_blockchain(blockchain);
    verify(blockchain);

    return 0;
}