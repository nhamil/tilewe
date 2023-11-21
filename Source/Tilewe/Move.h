#pragma once 

#include "Piece.h" 
#include "StackList.h"
#include "Tile.h" 
#include "Types.h" 

/**
 * Move. Stores a rotation-piece-contact and a target tile for that contact. 
 */
typedef Tw_UInt32 Tw_Move; 

#define Tw_Move_None ((Tw_Move) -1)

/**
 * @param rpc Rotation-piece-contact
 * @param toTile Target tile 
 * @return Move
 */
static inline Tw_Move Tw_MakeMoveFromRotPcCon(Tw_RotPcCon rpc, Tw_Tile toTile) 
{
    return (Tw_Move) ((((Tw_Move) rpc) << 9) | ((Tw_Move) toTile)); 
}

/**
 * Convenience constructor to build move from a piece, rotation, contact, and
 * target tile. 
 * 
 * @param pc Piece
 * @param rot Rotation
 * @param con Contact
 * @param toTile Target tile
 * @return 
 */
static inline Tw_Move Tw_MakeMove(Tw_Pc pc, Tw_Rot rot, Tw_Tile con, Tw_Tile toTile) 
{
    return Tw_MakeMoveFromRotPcCon(Tw_RotPcInfos[Tw_ToRotPc(pc, rot)].ToRotPcCon[con], toTile); 
}

/**
 * @param move Move
 * @return Rotation-piece-contact
 */
static inline Tw_RotPcCon Tw_Move_RotPcCon(Tw_Move move) 
{
    return (Tw_RotPcCon) (move >> 9); 
}

/**
 * @param move Move
 * @return Target tile
 */
static inline Tw_Tile Tw_Move_ToTile(Tw_Move move) 
{
    return (Tw_Tile) (move & 511); 
}

/**
 * @param move Move 
 * @return Piece
 */
static inline Tw_Pc Tw_Move_Pc(Tw_Move move) 
{
    return Tw_RotPcConInfos[Tw_Move_RotPcCon(move)].Pc; 
}

/**
 * @param move Move
 * @return Rotation
 */
static inline Tw_Rot Tw_Move_Rot(Tw_Move move) 
{
    return Tw_RotPcConInfos[Tw_Move_RotPcCon(move)].Rot; 
}

/**
 * @param move Move 
 * @return Rotated piece
 */
static inline Tw_RotPc Tw_Move_RotPc(Tw_Move move) 
{
    return Tw_RotPcConInfos[Tw_Move_RotPcCon(move)].RotPc; 
}

/**
 * @param move Move
 * @return Contact
 */
static inline Tw_Tile Tw_Move_Con(Tw_Move move) 
{
    return Tw_RotPcConInfos[Tw_Move_RotPcCon(move)].Offset; 
}

/**
 * Prints a move. 
 * 
 * @param move Move 
 */
static inline void Tw_Move_Print(Tw_Move move) 
{
    printf("%s%s-%s%s", 
        Tw_Pc_Str(Tw_Move_Pc(move)), 
        Tw_Rot_Str(Tw_Move_Rot(move)), 
        Tw_Tile_Str(Tw_Move_Con(move)), 
        Tw_Tile_Str(Tw_Move_ToTile(move))
    );
}

/**
 * Upper bound on the maximum number of moves possible in a single turn. 
 */
#define Tw_MaxMoveListCount 28336

/**
 * Contains a list of moves for a single turn. 
 */
Tw_DEFINE_STACK_LIST(MoveList, Tw_Move, Tw_MaxMoveListCount) 
