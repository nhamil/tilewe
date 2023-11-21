#pragma once 

#include "Bits.h" 
#include "StackList.h"
#include "Types.h" 

#define Tw_BoardWidth 20 
#define Tw_BoardHeight 20 

#define Tw_RelCoordOffset 10

#define Tw_TileSet_NumBitsetInts 7

/**
 * Represents a tile on the board or a piece, where letters increase to the right and numbers increase upwards. 
 * 
 * A01 is the bottom-left of the board and T20 is the top-right. 
 */
typedef enum Tw_Tile 
{
    Tw_Tile_A01, Tw_Tile_B01, Tw_Tile_C01, Tw_Tile_D01, Tw_Tile_E01, Tw_Tile_F01, Tw_Tile_G01, Tw_Tile_H01, Tw_Tile_I01, Tw_Tile_J01, 
    Tw_Tile_K01, Tw_Tile_L01, Tw_Tile_M01, Tw_Tile_N01, Tw_Tile_O01, Tw_Tile_P01, Tw_Tile_Q01, Tw_Tile_R01, Tw_Tile_S01, Tw_Tile_T01, 
    Tw_Tile_A02, Tw_Tile_B02, Tw_Tile_C02, Tw_Tile_D02, Tw_Tile_E02, Tw_Tile_F02, Tw_Tile_G02, Tw_Tile_H02, Tw_Tile_I02, Tw_Tile_J02, 
    Tw_Tile_K02, Tw_Tile_L02, Tw_Tile_M02, Tw_Tile_N02, Tw_Tile_O02, Tw_Tile_P02, Tw_Tile_Q02, Tw_Tile_R02, Tw_Tile_S02, Tw_Tile_T02, 
    Tw_Tile_A03, Tw_Tile_B03, Tw_Tile_C03, Tw_Tile_D03, Tw_Tile_E03, Tw_Tile_F03, Tw_Tile_G03, Tw_Tile_H03, Tw_Tile_I03, Tw_Tile_J03, 
    Tw_Tile_K03, Tw_Tile_L03, Tw_Tile_M03, Tw_Tile_N03, Tw_Tile_O03, Tw_Tile_P03, Tw_Tile_Q03, Tw_Tile_R03, Tw_Tile_S03, Tw_Tile_T03, 
    Tw_Tile_A04, Tw_Tile_B04, Tw_Tile_C04, Tw_Tile_D04, Tw_Tile_E04, Tw_Tile_F04, Tw_Tile_G04, Tw_Tile_H04, Tw_Tile_I04, Tw_Tile_J04, 
    Tw_Tile_K04, Tw_Tile_L04, Tw_Tile_M04, Tw_Tile_N04, Tw_Tile_O04, Tw_Tile_P04, Tw_Tile_Q04, Tw_Tile_R04, Tw_Tile_S04, Tw_Tile_T04, 
    Tw_Tile_A05, Tw_Tile_B05, Tw_Tile_C05, Tw_Tile_D05, Tw_Tile_E05, Tw_Tile_F05, Tw_Tile_G05, Tw_Tile_H05, Tw_Tile_I05, Tw_Tile_J05, 
    Tw_Tile_K05, Tw_Tile_L05, Tw_Tile_M05, Tw_Tile_N05, Tw_Tile_O05, Tw_Tile_P05, Tw_Tile_Q05, Tw_Tile_R05, Tw_Tile_S05, Tw_Tile_T05, 
    Tw_Tile_A06, Tw_Tile_B06, Tw_Tile_C06, Tw_Tile_D06, Tw_Tile_E06, Tw_Tile_F06, Tw_Tile_G06, Tw_Tile_H06, Tw_Tile_I06, Tw_Tile_J06, 
    Tw_Tile_K06, Tw_Tile_L06, Tw_Tile_M06, Tw_Tile_N06, Tw_Tile_O06, Tw_Tile_P06, Tw_Tile_Q06, Tw_Tile_R06, Tw_Tile_S06, Tw_Tile_T06, 
    Tw_Tile_A07, Tw_Tile_B07, Tw_Tile_C07, Tw_Tile_D07, Tw_Tile_E07, Tw_Tile_F07, Tw_Tile_G07, Tw_Tile_H07, Tw_Tile_I07, Tw_Tile_J07, 
    Tw_Tile_K07, Tw_Tile_L07, Tw_Tile_M07, Tw_Tile_N07, Tw_Tile_O07, Tw_Tile_P07, Tw_Tile_Q07, Tw_Tile_R07, Tw_Tile_S07, Tw_Tile_T07, 
    Tw_Tile_A08, Tw_Tile_B08, Tw_Tile_C08, Tw_Tile_D08, Tw_Tile_E08, Tw_Tile_F08, Tw_Tile_G08, Tw_Tile_H08, Tw_Tile_I08, Tw_Tile_J08, 
    Tw_Tile_K08, Tw_Tile_L08, Tw_Tile_M08, Tw_Tile_N08, Tw_Tile_O08, Tw_Tile_P08, Tw_Tile_Q08, Tw_Tile_R08, Tw_Tile_S08, Tw_Tile_T08, 
    Tw_Tile_A09, Tw_Tile_B09, Tw_Tile_C09, Tw_Tile_D09, Tw_Tile_E09, Tw_Tile_F09, Tw_Tile_G09, Tw_Tile_H09, Tw_Tile_I09, Tw_Tile_J09, 
    Tw_Tile_K09, Tw_Tile_L09, Tw_Tile_M09, Tw_Tile_N09, Tw_Tile_O09, Tw_Tile_P09, Tw_Tile_Q09, Tw_Tile_R09, Tw_Tile_S09, Tw_Tile_T09, 
    Tw_Tile_A10, Tw_Tile_B10, Tw_Tile_C10, Tw_Tile_D10, Tw_Tile_E10, Tw_Tile_F10, Tw_Tile_G10, Tw_Tile_H10, Tw_Tile_I10, Tw_Tile_J10, 
    Tw_Tile_K10, Tw_Tile_L10, Tw_Tile_M10, Tw_Tile_N10, Tw_Tile_O10, Tw_Tile_P10, Tw_Tile_Q10, Tw_Tile_R10, Tw_Tile_S10, Tw_Tile_T10, 
    Tw_Tile_A11, Tw_Tile_B11, Tw_Tile_C11, Tw_Tile_D11, Tw_Tile_E11, Tw_Tile_F11, Tw_Tile_G11, Tw_Tile_H11, Tw_Tile_I11, Tw_Tile_J11, 
    Tw_Tile_K11, Tw_Tile_L11, Tw_Tile_M11, Tw_Tile_N11, Tw_Tile_O11, Tw_Tile_P11, Tw_Tile_Q11, Tw_Tile_R11, Tw_Tile_S11, Tw_Tile_T11, 
    Tw_Tile_A12, Tw_Tile_B12, Tw_Tile_C12, Tw_Tile_D12, Tw_Tile_E12, Tw_Tile_F12, Tw_Tile_G12, Tw_Tile_H12, Tw_Tile_I12, Tw_Tile_J12, 
    Tw_Tile_K12, Tw_Tile_L12, Tw_Tile_M12, Tw_Tile_N12, Tw_Tile_O12, Tw_Tile_P12, Tw_Tile_Q12, Tw_Tile_R12, Tw_Tile_S12, Tw_Tile_T12, 
    Tw_Tile_A13, Tw_Tile_B13, Tw_Tile_C13, Tw_Tile_D13, Tw_Tile_E13, Tw_Tile_F13, Tw_Tile_G13, Tw_Tile_H13, Tw_Tile_I13, Tw_Tile_J13, 
    Tw_Tile_K13, Tw_Tile_L13, Tw_Tile_M13, Tw_Tile_N13, Tw_Tile_O13, Tw_Tile_P13, Tw_Tile_Q13, Tw_Tile_R13, Tw_Tile_S13, Tw_Tile_T13, 
    Tw_Tile_A14, Tw_Tile_B14, Tw_Tile_C14, Tw_Tile_D14, Tw_Tile_E14, Tw_Tile_F14, Tw_Tile_G14, Tw_Tile_H14, Tw_Tile_I14, Tw_Tile_J14, 
    Tw_Tile_K14, Tw_Tile_L14, Tw_Tile_M14, Tw_Tile_N14, Tw_Tile_O14, Tw_Tile_P14, Tw_Tile_Q14, Tw_Tile_R14, Tw_Tile_S14, Tw_Tile_T14, 
    Tw_Tile_A15, Tw_Tile_B15, Tw_Tile_C15, Tw_Tile_D15, Tw_Tile_E15, Tw_Tile_F15, Tw_Tile_G15, Tw_Tile_H15, Tw_Tile_I15, Tw_Tile_J15, 
    Tw_Tile_K15, Tw_Tile_L15, Tw_Tile_M15, Tw_Tile_N15, Tw_Tile_O15, Tw_Tile_P15, Tw_Tile_Q15, Tw_Tile_R15, Tw_Tile_S15, Tw_Tile_T15, 
    Tw_Tile_A16, Tw_Tile_B16, Tw_Tile_C16, Tw_Tile_D16, Tw_Tile_E16, Tw_Tile_F16, Tw_Tile_G16, Tw_Tile_H16, Tw_Tile_I16, Tw_Tile_J16, 
    Tw_Tile_K16, Tw_Tile_L16, Tw_Tile_M16, Tw_Tile_N16, Tw_Tile_O16, Tw_Tile_P16, Tw_Tile_Q16, Tw_Tile_R16, Tw_Tile_S16, Tw_Tile_T16, 
    Tw_Tile_A17, Tw_Tile_B17, Tw_Tile_C17, Tw_Tile_D17, Tw_Tile_E17, Tw_Tile_F17, Tw_Tile_G17, Tw_Tile_H17, Tw_Tile_I17, Tw_Tile_J17, 
    Tw_Tile_K17, Tw_Tile_L17, Tw_Tile_M17, Tw_Tile_N17, Tw_Tile_O17, Tw_Tile_P17, Tw_Tile_Q17, Tw_Tile_R17, Tw_Tile_S17, Tw_Tile_T17, 
    Tw_Tile_A18, Tw_Tile_B18, Tw_Tile_C18, Tw_Tile_D18, Tw_Tile_E18, Tw_Tile_F18, Tw_Tile_G18, Tw_Tile_H18, Tw_Tile_I18, Tw_Tile_J18, 
    Tw_Tile_K18, Tw_Tile_L18, Tw_Tile_M18, Tw_Tile_N18, Tw_Tile_O18, Tw_Tile_P18, Tw_Tile_Q18, Tw_Tile_R18, Tw_Tile_S18, Tw_Tile_T18, 
    Tw_Tile_A19, Tw_Tile_B19, Tw_Tile_C19, Tw_Tile_D19, Tw_Tile_E19, Tw_Tile_F19, Tw_Tile_G19, Tw_Tile_H19, Tw_Tile_I19, Tw_Tile_J19, 
    Tw_Tile_K19, Tw_Tile_L19, Tw_Tile_M19, Tw_Tile_N19, Tw_Tile_O19, Tw_Tile_P19, Tw_Tile_Q19, Tw_Tile_R19, Tw_Tile_S19, Tw_Tile_T19, 
    Tw_Tile_A20, Tw_Tile_B20, Tw_Tile_C20, Tw_Tile_D20, Tw_Tile_E20, Tw_Tile_F20, Tw_Tile_G20, Tw_Tile_H20, Tw_Tile_I20, Tw_Tile_J20, 
    Tw_Tile_K20, Tw_Tile_L20, Tw_Tile_M20, Tw_Tile_N20, Tw_Tile_O20, Tw_Tile_P20, Tw_Tile_Q20, Tw_Tile_R20, Tw_Tile_S20, Tw_Tile_T20, 

    /**
     * Total number of tiles on the board. 
     */
    Tw_NumTiles, 
    Tw_Tile_None = Tw_NumTiles, 

    Tw_RelTile_Offset = Tw_RelCoordOffset + Tw_RelCoordOffset * Tw_BoardWidth
} Tw_Tile;

/**
 * Holds a list of up to 400 tiles. 
 */
Tw_DEFINE_STACK_LIST(TileList, Tw_Tile, Tw_NumTiles)

/**
 * Keeps track of what tiles are in a set. 
 */
Tw_DEFINE_BITSET(TileSet, Tw_TileSet_NumBitsetInts, 0xFFFFULL)

/**
 * Iterates over every tile in the set. 
 */
#define Tw_TileSet_FOR_EACH(tileSet, action) \
    { \
        Tw_TileSet _forEachTileTmp = tileSet; \
        Tw_Tile tile; \
        while ((tile = Tw_TileSet_RemoveFirst(&_forEachTileTmp)) != (Tw_Tile) -1) \
        { \
            action; \
        } \
    } while (0); 

/**
 * Tile string. 
 * 
 * @param t Tile
 * @return Notation
 */
static inline const char* Tw_Tile_Str(Tw_Tile t) 
{
    static const char* Names[] = 
    {
        "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "i1", "j1", "k1", "l1", "m1", "n1", "o1", "p1", "q1", "r1", "s1", "t1", 
        "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "i2", "j2", "k2", "l2", "m2", "n2", "o2", "p2", "q2", "r2", "s2", "t2", 
        "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "i3", "j3", "k3", "l3", "m3", "n3", "o3", "p3", "q3", "r3", "s3", "t3", 
        "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "i4", "j4", "k4", "l4", "m4", "n4", "o4", "p4", "q4", "r4", "s4", "t4", 
        "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "i5", "j5", "k5", "l5", "m5", "n5", "o5", "p5", "q5", "r5", "s5", "t5", 
        "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", "i6", "j6", "k6", "l6", "m6", "n6", "o6", "p6", "q6", "r6", "s6", "t6", 
        "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", "i7", "j7", "k7", "l7", "m7", "n7", "o7", "p7", "q7", "r7", "s7", "t7", 
        "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", "i8", "j8", "k8", "l8", "m8", "n8", "o8", "p8", "q8", "r8", "s8", "t8", 
        "a9", "b9", "c9", "d9", "e9", "f9", "g9", "h9", "i9", "j9", "k9", "l9", "m9", "n9", "o9", "p9", "q9", "r9", "s9", "t9", 
        "a10", "b10", "c10", "d10", "e10", "f10", "g10", "h10", "i10", "j10", "k10", "l10", "m10", "n10", "o10", "p10", "q10", "r10", "s10", "t10", 
        "a11", "b11", "c11", "d11", "e11", "f11", "g11", "h11", "i11", "j11", "k11", "l11", "m11", "n11", "o11", "p11", "q11", "r11", "s11", "t11", 
        "a12", "b12", "c12", "d12", "e12", "f12", "g12", "h12", "i12", "j12", "k12", "l12", "m12", "n12", "o12", "p12", "q12", "r12", "s12", "t12", 
        "a13", "b13", "c13", "d13", "e13", "f13", "g13", "h13", "i13", "j13", "k13", "l13", "m13", "n13", "o13", "p13", "q13", "r13", "s13", "t13", 
        "a14", "b14", "c14", "d14", "e14", "f14", "g14", "h14", "i14", "j14", "k14", "l14", "m14", "n14", "o14", "p14", "q14", "r14", "s14", "t14", 
        "a15", "b15", "c15", "d15", "e15", "f15", "g15", "h15", "i15", "j15", "k15", "l15", "m15", "n15", "o15", "p15", "q15", "r15", "s15", "t15", 
        "a16", "b16", "c16", "d16", "e16", "f16", "g16", "h16", "i16", "j16", "k16", "l16", "m16", "n16", "o16", "p16", "q16", "r16", "s16", "t16", 
        "a17", "b17", "c17", "d17", "e17", "f17", "g17", "h17", "i17", "j17", "k17", "l17", "m17", "n17", "o17", "p17", "q17", "r17", "s17", "t17", 
        "a18", "b18", "c18", "d18", "e18", "f18", "g18", "h18", "i18", "j18", "k18", "l18", "m18", "n18", "o18", "p18", "q18", "r18", "s18", "t18", 
        "a19", "b19", "c19", "d19", "e19", "f19", "g19", "h19", "i19", "j19", "k19", "l19", "m19", "n19", "o19", "p19", "q19", "r19", "s19", "t19", 
        "a20", "b20", "c20", "d20", "e20", "f20", "g20", "h20", "i20", "j20", "k20", "l20", "m20", "n20", "o20", "p20", "q20", "r20", "s20", "t20"
    };

    return Names[t]; 
}

/**
 * @param t Tile
 * @return X coordinate (0 to 19)
 */
static inline int Tw_Tile_X(Tw_Tile t) 
{
    return t % Tw_BoardWidth; 
}

/**
 * @param t Tile
 * @return Y coordinate (0 to 19)
 */
static inline int Tw_Tile_Y(Tw_Tile t) 
{
    return t / Tw_BoardWidth; 
}

/**
 * Gets the coordinates of a valid tile. 
 * 
 * @param t Tile
 * @param x Output X coordinate (0 to 19)
 * @param y Output Y coordinate (0 to 19)
 */
static inline void Tw_Tile_ToCoords(Tw_Tile t, int* x, int* y) 
{
    *x = Tw_Tile_X(t); 
    *y = Tw_Tile_Y(t); 
}

/**
 * Gets the coordinates of a valid relative tile. 
 * 
 * @param t Relative tile
 * @param x Output X coordinate (-10 to 9)
 * @param y Output Y coordinate (-10 to 9)
 */
static inline void Tw_Tile_ToRelCoords(Tw_Tile t, int* x, int* y) 
{
    *x = Tw_Tile_X(t) - Tw_RelCoordOffset; 
    *y = Tw_Tile_Y(t) - Tw_RelCoordOffset; 
}

/**
 * Creates a tile from valid coordinates. 
 * 
 * @param x X coordinate (0 to 19)
 * @param y Y coordinate (0 to 19)
 * @return Tile
 */
static inline Tw_Tile Tw_MakeTile(int x, int y) 
{
    return (Tw_Tile) (x + y * Tw_BoardWidth); 
}

/**
 * Creates a relative tile from valid coordinates. 
 * 
 * @param x X coordinate (-10 to 9)
 * @param y Y coordinate (-10 to 9)
 * @return Tile
 */
static inline Tw_Tile Tw_MakeRelTile(int x, int y) 
{
    return (Tw_Tile) ((x + Tw_RelCoordOffset) + (y + Tw_RelCoordOffset) * Tw_BoardWidth); 
}

/**
 * Checks if a tile is valid. Note that if the coordinates used to make this 
 * tile were invalid, this may still return true. 
 * 
 * @param t Tile
 * @return Whether tile is valid
 */
static inline bool Tw_Tile_InBounds(Tw_Tile t) 
{
    return (t >= 0) & (t < Tw_NumTiles); 
}

/**
 * Checks if coordinates are able to create a tile. 
 * 
 * @param x X coordinate
 * @param y Y coordinate
 * @return Whether coordinates would create a valid tile
 */
static inline bool Tw_CoordsInBounds(int x, int y) 
{
    if (x < 0 || x >= Tw_BoardWidth) return false; 
    if (y < 0 || y >= Tw_BoardHeight) return false; 

    return true; 
}

/**
 * Checks if coordinates are able to create a relative tile. 
 * 
 * @param x X coordinate
 * @param y Y coordinate
 * @return Whether coordinates would create a valid relative tile
 */
static inline bool Tw_RelCoordsInBounds(int x, int y) 
{
    if (x < -Tw_RelCoordOffset || x >= (Tw_BoardWidth - Tw_RelCoordOffset)) return false; 
    if (y < -Tw_RelCoordOffset || y >= (Tw_BoardHeight - Tw_RelCoordOffset)) return false; 

    return true; 
}

/**
 * Appends all set tiles to an existing list. 
 * 
 * @param set Tile set
 * @param list Tile list 
 */
static inline void Tw_TileSet_AddToTileList(const Tw_TileSet* set, Tw_TileList* list) 
{
    Tw_TileSet_FOR_EACH(*set, 
    {
        Tw_TileList_Push(list, tile); 
    }); 
}

/**
 * Prints a tile set as a 2D grid. 
 * 
 * @param set Tile set
 */
static inline void Tw_TileSet_PrintFmt(const Tw_TileSet* set) 
{
    for (int y = Tw_BoardHeight - 1; y >= 0; y--) 
    {
        for (int x = 0; x < Tw_BoardWidth; x++) 
        {
            printf("%s ", Tw_TileSet_Has(set, Tw_MakeTile(x, y)) ? "X" : "."); 
        }
        printf("\n"); 
    }
}

/**
 * Prints a tile set as a 2D grid with a width and height of the farthest set 
 * tile. Useful for printing piece shapes. 
 * 
 * @param set Tile set
 */
static inline void Tw_TileSet_PrintFmtToFarthest(const Tw_TileSet* set) 
{
    int farthestX = 0, farthestY = 0; 

    for (int y = Tw_BoardHeight - 1; y >= 0; y--) 
    {
        for (int x = 0; x < Tw_BoardWidth; x++) 
        {
            if (Tw_TileSet_Has(set, Tw_MakeTile(x, y))) 
            {
                if (x > farthestX) farthestX = x; 
                if (y > farthestY) farthestY = y; 
            }
        }
    }

    for (int y = farthestY; y >= 0; y--) 
    {
        for (int x = 0; x <= farthestX; x++) 
        {
            printf("%s ", Tw_TileSet_Has(set, Tw_MakeTile(x, y)) ? "X" : "."); 
        }
        printf("\n"); 
    }
}
