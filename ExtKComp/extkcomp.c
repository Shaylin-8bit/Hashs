/////////////////////////////////////////////////////////////////////
// ExtKComp Hash
//
// A ""stacking sector" based hash function, built on top of the 
// "Mulit" hash function.
//
// Designed for my Cryptic program, as a second improved hash 
// 
// Written by Malakai "Shaylin" C.
/////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

// Mulit
//  multiplication based hash function, with subtraction to make character order matter
unsigned long long int subhash(char* str) {
    unsigned long long int result = 1;       // result storage
    while (*str) {                           // loop through array
        if (result * *str) result *= *str;   // mutiply result by current byte
        if (result - *++str) result -= *str; // subtract next byte
    }
    return result;                           // return result
}

// main stacking sector based hash
unsigned long long int hash(char* key, unsigned long long int factor) {
    if (!strlen(key) || !factor) return 0; // check that hashing can be done

    // set up variables
    unsigned long long int result;                         // store the result
    unsigned long k_sze = strlen(key);                     // size of users key
    unsigned long u_sze = sizeof(result);                  // size of result
    unsigned long sze = k_sze + (u_sze - (k_sze % u_sze)); // starting size used to create extended key
    unsigned long i;                                       // for iteration
    if (sze < u_sze*8) sze += u_sze*8 - sze;               // expand size used to create extended key
    unsigned long sectors = sze / u_sze;                   // number of sectors in extended key
    
    char* ext_key;                                         // extended key
    char** sec_div;                                        // container to divide sector elements
    char* sub_result;                                      // sub result          
     
    // array memory allocation
    if ((ext_key = (char*)malloc(sze+1)) == NULL) {
        fprintf(stderr, "Failed to allocate %lu bytes at %p for hash function.", sze+1, ext_key);
        exit(EXIT_FAILURE);
    }

    if ((sub_result = (char*)malloc(u_sze)) == NULL) {
        fprintf(stderr, "Failed to allocate %lu bytes at %p for hash function.", u_sze, sub_result);
        exit(EXIT_FAILURE);
    }

    if ((sec_div = malloc(sizeof(char*) * u_sze)) == NULL) {
        fprintf(stderr, "Failed to allocate %lu bytes at %p for hash function.", sizeof(char*) * u_sze, sec_div);
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < u_sze; i++) {
        if ((sec_div[i] = malloc(sectors+1)) == NULL) {
            fprintf(stderr, "Failed to allocate %lu bytes at %p for hash function.", sectors+1, sec_div[i]);
            exit(EXIT_FAILURE);
        }
    }

    // prepare extended key for population 
    for (i = k_sze; i < sze+1; i++) ext_key[i] = '\0';
    strcpy(ext_key, key);

    // populate key and organize sectors
    for (i = k_sze; i < sze; i++) ext_key[i] = log(subhash(ext_key)) * 1000;
    for (i = 0; i < sze; i++) sec_div[i%u_sze][i/u_sze] = ext_key[i];
    
    // generate sub result and convert to result
    for (i = 0; i < u_sze; i++) {                                                 
        sec_div[i][sectors] = 0;
        sub_result[i] = subhash(sec_div[i]);
    }
    memcpy(&result, sub_result, u_sze);
    printf("%llu\n", result);
    
    // free up memory
    for (i = 0; i < u_sze; i++) free(sec_div[i]);
    free(sec_div);
    free(sub_result);
    free(ext_key);
    
    // return result shortened with modulo and factor
    return result % factor;
}