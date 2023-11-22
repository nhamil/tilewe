#pragma once 

#include "Bits.h" 
#include "Tile.h" 
#include "Types.h"

#define Tw_RotPcConSet_NumBitsetInts 5
#define Tw_NumRotPcCons 309

/**
 * Piece. Contains tiles that can be rotated and placed on the board. 
 */
typedef enum Tw_Pc 
{
    Tw_Pc_First, 
    Tw_Pc_O1 = Tw_Pc_First, 
    Tw_Pc_I2, 
    Tw_Pc_I3, 
    Tw_Pc_L3, 
    Tw_Pc_O4, 
    Tw_Pc_I4, 
    Tw_Pc_L4, 
    Tw_Pc_Z4, 
    Tw_Pc_T4, 
    Tw_Pc_F5, 
    Tw_Pc_I5, 
    Tw_Pc_L5, 
    Tw_Pc_N5, 
    Tw_Pc_P5, 
    Tw_Pc_T5, 
    Tw_Pc_U5, 
    Tw_Pc_V5, 
    Tw_Pc_W5, 
    Tw_Pc_X5, 
    Tw_Pc_Y5, 
    Tw_Pc_Z5, 

    /**
     * Total number of pieces. 
     */
    Tw_NumPcs, 

    Tw_Pc_None = Tw_NumPcs
} Tw_Pc; 

/**
 * Piece string. 
 * 
 * @param pc Piece
 * @return Notation
 */
static const char* Tw_Pc_Str(Tw_Pc pc) 
{
    static const char* Names[] = 
    {
        "O1", 
        "I2", 
        "I3", 
        "L3", 
        "O4", 
        "I4", 
        "L4", 
        "Z4", 
        "T4", 
        "F5", 
        "I5", 
        "L5", 
        "N5", 
        "P5", 
        "T5", 
        "U5", 
        "V5", 
        "W5", 
        "X5", 
        "Y5", 
        "Z5", 
        "(none)"
    };

    return Names[pc]; 
}

/**
 * Rotated piece. Represents a piece rotated by the specified amount. 
 */
typedef enum Tw_RotPc 
{
    Tw_RotPc_O1n, Tw_RotPc_O1e, Tw_RotPc_O1s, Tw_RotPc_O1w, Tw_RotPc_O1nf, Tw_RotPc_O1ef, Tw_RotPc_O1sf, Tw_RotPc_O1wf, 
    Tw_RotPc_I2n, Tw_RotPc_I2e, Tw_RotPc_I2s, Tw_RotPc_I2w, Tw_RotPc_I2nf, Tw_RotPc_I2ef, Tw_RotPc_I2sf, Tw_RotPc_I2wf, 
    Tw_RotPc_I3n, Tw_RotPc_I3e, Tw_RotPc_I3s, Tw_RotPc_I3w, Tw_RotPc_I3nf, Tw_RotPc_I3ef, Tw_RotPc_I3sf, Tw_RotPc_I3wf, 
    Tw_RotPc_L3n, Tw_RotPc_L3e, Tw_RotPc_L3s, Tw_RotPc_L3w, Tw_RotPc_L3nf, Tw_RotPc_L3ef, Tw_RotPc_L3sf, Tw_RotPc_L3wf, 
    Tw_RotPc_O4n, Tw_RotPc_O4e, Tw_RotPc_O4s, Tw_RotPc_O4w, Tw_RotPc_O4nf, Tw_RotPc_O4ef, Tw_RotPc_O4sf, Tw_RotPc_O4wf, 
    Tw_RotPc_I4n, Tw_RotPc_I4e, Tw_RotPc_I4s, Tw_RotPc_I4w, Tw_RotPc_I4nf, Tw_RotPc_I4ef, Tw_RotPc_I4sf, Tw_RotPc_I4wf, 
    Tw_RotPc_L4n, Tw_RotPc_L4e, Tw_RotPc_L4s, Tw_RotPc_L4w, Tw_RotPc_L4nf, Tw_RotPc_L4ef, Tw_RotPc_L4sf, Tw_RotPc_L4wf, 
    Tw_RotPc_Z4n, Tw_RotPc_Z4e, Tw_RotPc_Z4s, Tw_RotPc_Z4w, Tw_RotPc_Z4nf, Tw_RotPc_Z4ef, Tw_RotPc_Z4sf, Tw_RotPc_Z4wf, 
    Tw_RotPc_T4n, Tw_RotPc_T4e, Tw_RotPc_T4s, Tw_RotPc_T4w, Tw_RotPc_T4nf, Tw_RotPc_T4ef, Tw_RotPc_T4sf, Tw_RotPc_T4wf, 
    Tw_RotPc_F5n, Tw_RotPc_F5e, Tw_RotPc_F5s, Tw_RotPc_F5w, Tw_RotPc_F5nf, Tw_RotPc_F5ef, Tw_RotPc_F5sf, Tw_RotPc_F5wf, 
    Tw_RotPc_I5n, Tw_RotPc_I5e, Tw_RotPc_I5s, Tw_RotPc_I5w, Tw_RotPc_I5nf, Tw_RotPc_I5ef, Tw_RotPc_I5sf, Tw_RotPc_I5wf, 
    Tw_RotPc_L5n, Tw_RotPc_L5e, Tw_RotPc_L5s, Tw_RotPc_L5w, Tw_RotPc_L5nf, Tw_RotPc_L5ef, Tw_RotPc_L5sf, Tw_RotPc_L5wf, 
    Tw_RotPc_N5n, Tw_RotPc_N5e, Tw_RotPc_N5s, Tw_RotPc_N5w, Tw_RotPc_N5nf, Tw_RotPc_N5ef, Tw_RotPc_N5sf, Tw_RotPc_N5wf, 
    Tw_RotPc_P5n, Tw_RotPc_P5e, Tw_RotPc_P5s, Tw_RotPc_P5w, Tw_RotPc_P5nf, Tw_RotPc_P5ef, Tw_RotPc_P5sf, Tw_RotPc_P5wf, 
    Tw_RotPc_T5n, Tw_RotPc_T5e, Tw_RotPc_T5s, Tw_RotPc_T5w, Tw_RotPc_T5nf, Tw_RotPc_T5ef, Tw_RotPc_T5sf, Tw_RotPc_T5wf, 
    Tw_RotPc_U5n, Tw_RotPc_U5e, Tw_RotPc_U5s, Tw_RotPc_U5w, Tw_RotPc_U5nf, Tw_RotPc_U5ef, Tw_RotPc_U5sf, Tw_RotPc_U5wf, 
    Tw_RotPc_V5n, Tw_RotPc_V5e, Tw_RotPc_V5s, Tw_RotPc_V5w, Tw_RotPc_V5nf, Tw_RotPc_V5ef, Tw_RotPc_V5sf, Tw_RotPc_V5wf, 
    Tw_RotPc_W5n, Tw_RotPc_W5e, Tw_RotPc_W5s, Tw_RotPc_W5w, Tw_RotPc_W5nf, Tw_RotPc_W5ef, Tw_RotPc_W5sf, Tw_RotPc_W5wf, 
    Tw_RotPc_X5n, Tw_RotPc_X5e, Tw_RotPc_X5s, Tw_RotPc_X5w, Tw_RotPc_X5nf, Tw_RotPc_X5ef, Tw_RotPc_X5sf, Tw_RotPc_X5wf, 
    Tw_RotPc_Y5n, Tw_RotPc_Y5e, Tw_RotPc_Y5s, Tw_RotPc_Y5w, Tw_RotPc_Y5nf, Tw_RotPc_Y5ef, Tw_RotPc_Y5sf, Tw_RotPc_Y5wf, 
    Tw_RotPc_Z5n, Tw_RotPc_Z5e, Tw_RotPc_Z5s, Tw_RotPc_Z5w, Tw_RotPc_Z5nf, Tw_RotPc_Z5ef, Tw_RotPc_Z5sf, Tw_RotPc_Z5wf, 
    Tw_NumRotPcs
} Tw_RotPc; 

/**
 * Rotation-Piece-Contact. Represents a rotated piece where the tile origin is
 * located at a certain contact. Excluding rotations that not unique for each
 * piece, there are 309 total. 
 */
typedef Tw_UInt16 Tw_RotPcCon; 

/**
 * A set that can contain all possible rotation-piece-contacts. 
 */
Tw_DEFINE_BITSET(RotPcConSet, Tw_RotPcConSet_NumBitsetInts, 0x1FFFFFFFFFFFFFULL)

/**
 * Loops over all rotation-piece-contacts in a set. 
 */
#define Tw_RotPcConSet_FOR_EACH(rpcSet, rpcVar, action) \
    { \
        Tw_RotPcConSet _forEachRotPcConSet##rpcVar = rpcSet; \
        Tw_RotPcCon rpcVar; \
        while ((rpcVar = Tw_RotPcConSet_RemoveFirst(&_forEachRotPcConSet##rpcVar)) != (Tw_RotPcCon) -1) \
        { \
            action; \
        } \
    } while (0); 

/**
 * Contains a rotation-piece-contact set for each tile on the board. 
 * 
 * In practice this is used to keep track of how pieces can be played at each
 * open corner for a player. 
 */
typedef struct Tw_RotPcConSetMap Tw_RotPcConSetMap; 

struct Tw_RotPcConSetMap 
{
    Tw_RotPcConSet Sets[Tw_NumTiles]; 
    Tw_TileSet Keys; 
};

/**
 * Per-piece information. 
 */
typedef struct Tw_PcInfo Tw_PcInfo; 

struct Tw_PcInfo 
{
    /**
     * Which rotation-piece-contacts use this piece. 
     */
    Tw_RotPcConSet RotPcCons; 
};

/**
 * Per-rotated piece information. 
 */
typedef struct Tw_RotPcInfo Tw_RotPcInfo; 

struct Tw_RotPcInfo 
{
    /**
     * Get the rotation-piece-contact of a rotated piece at the specified 
     * contact. 
     */
    Tw_RotPcCon ToRotPcCon[Tw_NumTiles]; 
    /**
     * Which tiles are part of the rotated piece. 
     */
    Tw_TileSet Tiles; 
    /**
     * Which tiles of the rotated piece are contacts. 
     * 
     * Only tiles set here may be used in `ToRotPcCon`. 
     */
    Tw_TileSet Contacts; 
    /**
     * Which tiles are adjacent to the rotated piece. 
     * 
     * These tiles are relative to the bottom-left corner of the piece. 
     */
    Tw_TileSet RelAdjacents; 
    /**
     * Which tiles are corners to the rotated piece. 
     * 
     * These tiles are relative to the bottom-left corner of the piece. 
     */
    Tw_TileSet RelCorners; 
    /**
     * Which rotation-piece-contacts use this rotated piece. 
     */
    Tw_RotPcConSet RotPcCons; 
};

/**
 * Per-rotated-piece-contact information. 
 */
typedef struct Tw_RotPcConInfo Tw_RotPcConInfo; 

struct Tw_RotPcConInfo 
{
    /**
     * The piece used for the rotated-piece-contact. 
     */
    Tw_Pc Pc; 
    /**
     * The rotation used for the rotated-piece-contact. 
     */
    Tw_Rot Rot; 
    /**
     * The rotated piece used for the rotated-piece-contact. 
     */
    Tw_RotPc RotPc; 
    /**
     * The contact coordinate of the rotated piece. 
     */
    Tw_Tile Offset; 
};

typedef struct Tw_RelTileInfo Tw_RelTileInfo; 

/**
 * Contains sets of rotation-piece-contacts that are affected at each tile 
 * relative to an open corner.  
 */
struct Tw_RelTileInfo 
{
    /**
     * Rotation-piece-contacts that cannot be played if the relative tile is 
     * claimed by any color. 
     */
    Tw_RotPcConSet RotPcConsWithRelTile; 
    /**
     * Rotation-piece-contacts that cannot be played if the relative tile is 
     * claimed by the player's color. 
     */
    Tw_RotPcConSet RotPcConsWithAdjRelTile; 
};

/**
 * Information for each piece. 
 */
extern Tw_PcInfo Tw_PcInfos[Tw_NumPcs]; 
/**
 * Information for each rotated piece. 
 */
extern Tw_RotPcInfo Tw_RotPcInfos[Tw_NumRotPcs]; 
/**
 * Information for each rotation-piece-contact. 
 */
extern Tw_RotPcConInfo Tw_RotPcConInfos[Tw_NumRotPcCons]; 
/**
 * Affected rotation-piece-contacts for each relative tile. 
 */
extern Tw_RelTileInfo Tw_RelTileInfos[Tw_NumTiles]; 
/**
 * List of relative tiles that affect any rotation-piece-contacts. 
 */
extern Tw_TileList Tw_RelTilesWithRotPcCons; 

/**
 * Remove all rotation-piece-contacts from all tiles. 
 * 
 * @param map Rotation-piece-contact sets mapped to each tile
 */
static inline void Tw_RotPcConSetMap_Clear(Tw_RotPcConSetMap* map) 
{
    Tw_TileSet_Clear(&map->Keys); 
    for (int i = 0; i < Tw_NumTiles; i++) 
    {
        Tw_RotPcConSet_Clear(&map->Sets[i]); 
    }
}

/**
 * Initialize the map. It does not have to be deinitialized. 
 * 
 * @param map Rotation-piece-contact sets mapped to each tile
 */
static inline void Tw_InitRotPcConSetMap(Tw_RotPcConSetMap* map) 
{
    Tw_RotPcConSetMap_Clear(map); 
}

/**
 * Clear the set associated with a tile. 
 * 
 * @param map Rotation-piece-contact sets mapped to each tile
 * @param t Tile to clear
 */
static inline void Tw_RotPcConSetMap_ClearFromTile(Tw_RotPcConSetMap* map, Tw_Tile t) 
{
    Tw_TileSet_Remove(&map->Keys, t); 
    Tw_RotPcConSet_Clear(&map->Sets[t]); 
}

/**
 * Remove elements from all tiles' sets. 
 * 
 * @param map Rotation-piece-contact sets mapped to each tile
 * @param remove Elements to remove
 */
static inline void Tw_RotPcConSetMap_DifferenceFromAll(Tw_RotPcConSetMap* map, const Tw_RotPcConSet* remove) 
{
    Tw_TileSet_FOR_EACH(map->Keys, tile, 
    {
        Tw_RotPcConSet_Difference(&map->Sets[tile], remove); 
        if (!Tw_RotPcConSet_Any(&map->Sets[tile])) 
        {
            Tw_TileSet_Remove(&map->Keys, tile); 
        }
    });
}

/**
 * Remove elements from the set associated with a tile. 
 * 
 * @param map Rotation-piece-contact sets mapped to each tile
 * @param t Tile to clear
 * @param remove Elements to remove
 */
static inline void Tw_RotPcConSetMap_DifferenceFromTile(Tw_RotPcConSetMap* map, Tw_Tile t, const Tw_RotPcConSet* remove) 
{
    Tw_RotPcConSet_Difference(&map->Sets[t], remove); 
    if (!Tw_RotPcConSet_Any(&map->Sets[t])) 
    {
        Tw_TileSet_Remove(&map->Keys, t); 
    }
}

/**
 * Add elements to the set associated with a tile. 
 * 
 * @param map Rotation-piece-contact sets mapped to each tile
 * @param t Tile to add elements to
 * @param add Elements to add
 */
static inline void Tw_RotPcConSetMap_AddToTile(Tw_RotPcConSetMap* map, Tw_Tile t, const Tw_RotPcConSet* add) 
{
    if (!Tw_RotPcConSet_Any(add)) return; 

    Tw_TileSet_Add(&map->Keys, t); 
    Tw_RotPcConSet_Union(&map->Sets[t], add); 
}

/**
 * Set elements to the set associated with a tile. This overrides any existing
 * elements. 
 * 
 * @param map Rotation-piece-contact sets mapped to each tile
 * @param t Tile to set elements to
 * @param add Elements to set
 */
static inline void Tw_RotPcConSetMap_SetToTile(Tw_RotPcConSetMap* map, Tw_Tile t, const Tw_RotPcConSet* add) 
{
    map->Sets[t] = *add; 

    if (Tw_RotPcConSet_Any(add)) 
    {
        Tw_TileSet_Add(&map->Keys, t); 
    }
    else 
    {
        Tw_TileSet_Remove(&map->Keys, t); 
    }
}

/**
 * Checks if there are any elements set at a tile. 
 * 
 * @param map Rotation-piece-contact sets mapped to each tile
 * @param t Tile to check 
 * @return Whether any elements are set at the tile
 */
static inline bool Tw_RotPcConSetMap_TileHasValues(const Tw_RotPcConSetMap* map, Tw_Tile t) 
{
    return Tw_TileSet_Has(&map->Keys, t); 
}

/**
 * Checks if there are any elements set at any tile. 
 * 
 * @param map Rotation-piece-contact sets mapped to each tile
 * @return Whether any elements are set
 */
static inline bool Tw_RotPcConSetMap_AnyTileHasValues(const Tw_RotPcConSetMap* map) 
{
    return Tw_TileSet_Any(&map->Keys); 
}

/**
 * @param pc Piece
 * @param rot Rotation
 * @return Rotated piece
 */
static inline Tw_RotPc Tw_ToRotPc(Tw_Pc pc, Tw_Rot rot) 
{
    return pc * Tw_NumRots + rot; 
}

/**
 * @param rp Rotated piece 
 * @return Piece
 */
static inline Tw_Pc Tw_UnrotPc(Tw_RotPc rp) 
{
    return rp / Tw_NumRots; 
}

/**
 * @param rp Rotated piece 
 * @return Rotation
 */
static inline Tw_Rot Tw_PcRot(Tw_RotPc rp) 
{
    return rp % Tw_NumRots; 
}
