#pragma once 

#include <stdbool.h> 
#include <stdint.h> 

typedef uint64_t Tw_UInt64; 
typedef uint32_t Tw_UInt32; 
typedef uint16_t Tw_UInt16; 
typedef uint8_t Tw_UInt8; 

typedef int64_t Tw_Int64; 
typedef int32_t Tw_Int32; 
typedef int16_t Tw_Int16; 
typedef int8_t Tw_Int8; 

/**
 * Piece rotation. Possible values are: 
 *
 * - north (default)
 * - east (clockwise) 
 * - south (180 degrees)
 * - west (counterclockwise)
 *
 * and horizontally flipped variants of each. 
 */
typedef enum Tw_Rot
{
    Tw_Rot_N, 
    Tw_Rot_E, 
    Tw_Rot_S, 
    Tw_Rot_W, 
    Tw_Rot_NF, 
    Tw_Rot_EF, 
    Tw_Rot_SF, 
    Tw_Rot_WF, 
    Tw_NumRots 
} Tw_Rot; 

/**
 * Rotation string. 
 * 
 * @param r Rotation
 * @return String notation
 */
static inline const char* Tw_Rot_Str(Tw_Rot r) 
{
    static const char* Names[] = 
    {
        "n", "e", "s", "w", "nf", "ef", "sf", "wf"
    };

    return Names[r]; 
}

/**
 * Piece/player color. 
 */
typedef enum Tw_Color 
{
    Tw_Color_First, 
    Tw_Color_Blue = Tw_Color_First, 
    Tw_Color_Yellow, 
    Tw_Color_Red, 
    Tw_Color_Green, 
    Tw_Color_None, 
    Tw_NumColors = Tw_Color_None
} Tw_Color; 

/**
 * Color string. 
 * 
 * @param c Color
 * @return Name of color
 */
static inline const char* Tw_Color_Str(Tw_Color c) 
{
    static const char* Names[] = 
    {
        "blue", "yellow", "red", "green", "(none)"
    };

    return Names[c]; 
}
