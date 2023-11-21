#pragma once 

#include <stdio.h> 
#include <string.h> 

#include "Types.h"

extern const Tw_UInt8 Tw_PopCount16[]; 

/**
 * Get total number of 1 bits. 
 * 
 * @see https://github.com/nhamil/halcyon/blob/master/Source/Bitboard.h
 * 
 * @param x 64-bit int 
 * @return Population count
 */
static inline int Tw_PopCount64(Tw_UInt64 x) 
{
    return Tw_PopCount16[((x >>  0) & 65535)]
         + Tw_PopCount16[((x >> 16) & 65535)]
         + Tw_PopCount16[((x >> 32) & 65535)]
         + Tw_PopCount16[((x >> 48) & 65535)];
}

/**
 * Finds the least significant bit of a nonzero value. 
 * 
 * Note: the value must be nonzero or the result is undefined. 
 * 
 * @see https://github.com/nhamil/halcyon/blob/master/Source/Bitboard.h
 * 
 * @param x 64-bit int 
 * @return Least significant bit index
 */
static inline int Tw_Lsb64(Tw_UInt64 x) 
{
    // pre-calculated hash results  
    static const int Positions[] = 
    {
        63,  0,  1, 28,  2,  6, 29, 54, 
         3, 18, 13,  7, 50, 30, 21, 55, 
        26,  4, 16, 19, 14, 42,  8, 44, 
        51, 10, 39, 31, 46, 22, 34, 56, 
        62, 27,  5, 53, 17, 12, 49, 20, 
        25, 15, 41, 43,  9, 38, 45, 33, 
        61, 52, 11, 48, 24, 40, 37, 32, 
        60, 47, 23, 36, 59, 35, 58, 57 
    };

    // x & -x isolates the least significant bit: 
    // -x first flips all bits, so the bits before the LSB are all 1. 
    // After flipping all bits, 1 is added to the result to make 
    // 2's complement -x. This reverts all bits before LSB back to 0, 
    // and the LSB bit to 1. x & -x therefore produces a number with 
    // a single 1 bit as all bits before LSB must be zero and all bits 
    // after are flipped so they are zero as well. 
    
    // multiply (x & -x) by a pre-generated constant to perfect 
    // hash all possible nonzero values to unique 6-bit indices in a 
    // lookup table
    return Positions[(x & -x) * 0x45949D0DED5CC7EULL >> 58]; 
}

#define Tw_DEFINE_BITSET(name, numInts, finalBits) \
    typedef struct Tw_##name Tw_##name; \
    \
    struct Tw_##name \
    { \
        Tw_UInt64 Elements[numInts]; \
    }; \
    \
    static inline bool Tw_##name##_Has(const Tw_##name* set, int index) \
    { \
        return (set->Elements[index / 64] >> (index & 63)) & 1; \
    } \
    \
    static inline void Tw_##name##_Add(Tw_##name* set, int index) \
    { \
        set->Elements[index / 64] |= 1ULL << (index & 63); \
    } \
    \
    static inline void Tw_##name##_Remove(Tw_##name* set, int index) \
    { \
        set->Elements[index / 64] &= ~(1ULL << (index & 63)); \
    } \
    \
    static inline void Tw_##name##_Clear(Tw_##name* set) \
    { \
        for (int i = 0; i < numInts; i++) \
        { \
            set->Elements[i] = 0; \
        } \
    } \
    \
    static inline void Tw_Init##name(Tw_##name* set) \
    { \
        Tw_##name##_Clear(set); \
    } \
    \
    static inline void Tw_##name##_Copy(Tw_##name* set, const Tw_##name* from) \
    { \
        for (int i = 0; i < numInts; i++) \
        { \
            set->Elements[i] = from->Elements[i]; \
        } \
    } \
    \
    static inline void Tw_##name##_Fill(Tw_##name* set) \
    { \
        for (int i = 0; i < numInts - 1; i++) \
        { \
            set->Elements[i] = 0xFFFFFFFFFFFFFFFFULL; \
        } \
        set->Elements[numInts - 1] = finalBits; \
    } \
    \
    static inline void Tw_Init##name##_Filled(Tw_##name* set) \
    { \
        Tw_##name##_Fill(set); \
    } \
    \
    static inline void Tw_##name##_Validate(Tw_##name* set) \
    { \
        set->Elements[numInts - 1] &= finalBits; \
    } \
    \
    static inline bool Tw_##name##_Equals(const Tw_##name* set, const Tw_##name* other) \
    { \
        return memcmp(set, other, sizeof(Tw_##name)) == 0; \
    } \
    \
    static inline bool Tw_##name##_Any(const Tw_##name* set) \
    { \
        for (int i = 0; i < numInts; i++) \
        { \
            if (set->Elements[i]) return true; \
        } \
        \
        return false; \
    } \
    \
    static inline bool Tw_##name##_HasAny(const Tw_##name* set, const Tw_##name* targets) \
    { \
        for (int i = 0; i < numInts; i++) \
        { \
            if (set->Elements[i] & targets->Elements[i]) return true; \
        } \
        \
        return false; \
    } \
    \
    static inline bool Tw_##name##_HasAll(const Tw_##name* set, const Tw_##name* targets) \
    { \
        for (int i = 0; i < numInts; i++) \
        { \
            if ((set->Elements[i] & targets->Elements[i]) != targets->Elements[i]) return false; \
        } \
        \
        return true; \
    } \
    \
    static inline void Tw_##name##_Union(Tw_##name* set, const Tw_##name* other) \
    { \
        for (int i = 0; i < numInts; i++) \
        { \
            set->Elements[i] |= other->Elements[i]; \
        } \
    } \
    \
    static inline void Tw_##name##_Intersection(Tw_##name* set, const Tw_##name* other) \
    { \
        for (int i = 0; i < numInts; i++) \
        { \
            set->Elements[i] &= other->Elements[i]; \
        } \
    } \
    \
    static inline void Tw_##name##_Difference(Tw_##name* set, const Tw_##name* other) \
    { \
        for (int i = 0; i < numInts; i++) \
        { \
            set->Elements[i] &= ~other->Elements[i]; \
        } \
    } \
    \
    static inline int Tw_##name##_First(const Tw_##name* set) \
    { \
        int prev = 0; \
        \
        for (int i = 0; i < numInts; i++) \
        { \
            Tw_UInt64 b = set->Elements[i]; \
            if (b) \
            { \
                return Tw_Lsb64(b) + prev; \
            } \
            else \
            { \
                prev += 64; \
            } \
        } \
        \
        return -1; \
    } \
    \
    static inline int Tw_##name##_RemoveFirst(Tw_##name* set) \
    { \
        int index = Tw_##name##_First(set); \
        Tw_##name##_Remove(set, index); \
        return index; \
    } \
    \
    static inline int Tw_##name##_Count(const Tw_##name* set) \
    { \
        int total = 0; \
        \
        for (int i = 0; i < numInts; i++) \
        { \
            total += Tw_PopCount64(set->Elements[i]); \
        } \
        \
        return total; \
    } \
    \
    static inline void Tw_##name##_LShift64(Tw_##name* set) \
    { \
        for (int i = numInts - 1; i >= 1; i--) \
        { \
            set->Elements[i] = set->Elements[i - 1]; \
        } \
        set->Elements[0] = 0; \
    } \
    \
    static inline void Tw_##name##_LShift(Tw_##name* set, int amt) \
    { \
        while (amt >= 64) \
        { \
            Tw_##name##_LShift64(set); \
            amt -= 64; \
        } \
        \
        if (amt > 0) \
        { \
            int revAmt = 64 - amt; \
            \
            for (int i = numInts - 1; i >= 1; i--) \
            { \
                set->Elements[i] = set->Elements[i] << amt | set->Elements[i - 1] >> revAmt; \
            } \
            set->Elements[0] <<= amt; \
            Tw_##name##_Validate(set); \
        } \
    } \
    \
    static inline void Tw_##name##_RShift64(Tw_##name* set) \
    { \
        for (int i = 0; i < numInts - 1; i--) \
        { \
            set->Elements[i] = set->Elements[i + 1]; \
        } \
        set->Elements[numInts - 1] = 0; \
    } \
    \
    static inline void Tw_##name##_RShift(Tw_##name* set, int amt) \
    { \
        while (amt >= 64) \
        { \
            Tw_##name##_RShift64(set); \
            amt -= 64; \
        } \
        \
        if (amt > 0) \
        { \
            int revAmt = 64 - amt; \
            \
            for (int i = 0; i < numInts - 1; i++) \
            { \
                set->Elements[i] = set->Elements[i] >> amt | set->Elements[i + 1] << revAmt; \
            } \
            set->Elements[numInts - 1] >>= amt; \
        } \
    } \
    \
    static inline void Tw_##name##_Print(const Tw_##name* set) \
    { \
        printf("["); \
        Tw_##name all; \
        Tw_Init##name##_Filled(&all); \
        for (int i = 0; i < numInts * 64; i++) \
        { \
            if (!Tw_##name##_Has(&all, i)) break; \
            printf("%d", Tw_##name##_Has(set, i)); \
        } \
        printf("] count=%d", Tw_##name##_Count(set)); \
    }
