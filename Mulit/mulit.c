///////////////////////////////////////////////////////////////////
// Mulit Hash
//
// A simplistic multiplication based hash, with subtraction to
//  ensure importance of character order.
//
// Written by Malakai "Shaylin" C.
///////////////////////////////////////////////////////////////////

unsigned long long int hash(char* str, unsigned long long int factor) {
    unsigned long long int result = 1;       // result storage
    while (*str) {                           // loop through array
        if (result * *str) result *= *str;   // mutiply result by current byte
        if (result - *++str) result -= *str; // subtract next byte
    }
    return result % factor;                  // return result shortened with modulo and factor
}