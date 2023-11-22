#pragma once 

#include "Bits.h" 
#include "Move.h" 
#include "Piece.h" 
#include "Tile.h" 
#include "Types.h" 

/**
 * Must be called before any other tilewe function. 
 */
void Tw_Init(void); 

#define Tw_MaxBoardDepth 84

#define Tw_BoardStrSize 8192

Tw_DEFINE_STACK_LIST(ChangedCornerList, Tw_RotPcConSet, 128)
Tw_DEFINE_STACK_LIST(ChangedCornerTileList, Tw_Tile, 128)

/**
 * INTERNAL. 
 * 
 * Historical player state. 
 */
typedef struct Tw_PlayerState Tw_PlayerState; 

struct Tw_PlayerState 
{
    Tw_ChangedCornerList Corners; 
    Tw_ChangedCornerTileList CornerTiles; 
    Tw_TileSet Claimed; 
    Tw_RotPcConSet RotPcCons; 
    int Score; 
    bool HasPlayed; 
    bool CanPlay; 
};

/**
 * INTERNAL. 
 * 
 * Player data. 
 */
typedef struct Tw_Player Tw_Player; 

struct Tw_Player 
{
    Tw_PlayerState History[Tw_MaxBoardDepth + 2]; 
    Tw_RotPcConSetMap OpenCorners; 
    Tw_RotPcConSet RotPcCons; 
    Tw_TileSet Claimed; 
    int Score; 
    bool HasPlayed; 
    bool CanPlay; 
    int Depth; 
    Tw_Color Color; 
};

typedef struct Tw_BoardState Tw_BoardState; 

/**
 * INTERNAL. 
 * 
 * Historical board state. 
 */
struct Tw_BoardState 
{
    Tw_TileSet All; 
    Tw_Color CurTurn; 
    Tw_Move Move; 
};

typedef struct Tw_Board Tw_Board; 

/**
 * Contains data used for a tilewe game. 
 */
struct Tw_Board 
{
    /**
     * Historical data used for undoing moves. 
     */
    Tw_BoardState History[Tw_MaxBoardDepth + 2]; 
    /**
     * Player-specific data. 
     */
    Tw_Player Players[Tw_NumColors]; 
    /**
     * Set of tiles claimed by any player. 
     */
    Tw_TileSet All; 
    /**
     * Current ply of the game. 
     */
    int Ply; 
    /**
     * Number of players in the game (including players who can no longer play)
     */
    int NumPlayers; 
    /**
     * Color of the current player. 
     */
    Tw_Color CurTurn; 
    /**
     * Whether moves can still be played. 
     */
    bool Finished; 
};

/**
 * INTERNAL 
 * 
 * @param state 
 * @param player 
 */
static inline void Tw_InitPlayerState(Tw_PlayerState* state, const Tw_Player* player) 
{
    Tw_InitChangedCornerList(&state->Corners); 
    Tw_InitChangedCornerTileList(&state->CornerTiles); 
    state->Claimed = player->Claimed; 
    state->Score = player->Score; 
    state->HasPlayed = player->HasPlayed; 
    state->CanPlay = player->CanPlay; 
    state->RotPcCons = player->RotPcCons; 

    // save available pieces for open tiles 
    Tw_TileSet_FOR_EACH(player->OpenCorners.Keys, tile, 
    {
        Tw_ChangedCornerList_PushPtr(&state->Corners, &player->OpenCorners.Sets[tile]); 
        Tw_ChangedCornerTileList_Push(&state->CornerTiles, tile); 
    });
}

/**
 * INTERNAL 
 * 
 * @param player 
 * @param color 
 * @param inGame 
 */
static inline void Tw_InitPlayer(Tw_Player* player, Tw_Color color, bool inGame) 
{
    Tw_InitRotPcConSetMap(&player->OpenCorners); 
    Tw_InitRotPcConSet_Filled(&player->RotPcCons); 
    Tw_InitTileSet(&player->Claimed); 
    player->Score = 0; 
    player->HasPlayed = false; 
    player->CanPlay = inGame; 
    player->Depth = 0; 
    player->Color = color; 
    Tw_InitPlayerState(&player->History[0], player); 
}

/**
 * INTERNAL 
 * 
 * @param player 
 */
static inline void Tw_Player_PushState(Tw_Player* player) 
{
    Tw_InitPlayerState(&player->History[++player->Depth], player); 
}

/**
 * INTERNAL 
 * 
 * @param player 
 */
static inline void Tw_Player_PopState(Tw_Player* player) 
{
    Tw_PlayerState* state = &player->History[player->Depth--]; 

    player->Claimed = state->Claimed; 
    player->Score = state->Score; 
    player->HasPlayed = state->HasPlayed; 
    player->CanPlay = state->CanPlay; 
    player->RotPcCons = state->RotPcCons; 

    Tw_RotPcConSetMap_Clear(&player->OpenCorners); 

    for (int i = 0; i < state->Corners.Count; i++) 
    {
        Tw_RotPcConSetMap_SetToTile(&player->OpenCorners, state->CornerTiles.Elements[i], &state->Corners.Elements[i]); 
    }
}

/**
 * INTERNAL 
 * 
 * @param player 
 * @param pc 
 */
static inline void Tw_Player_RemovePc(Tw_Player* player, Tw_Pc pc) 
{
    const Tw_RotPcConSet* pcRpcs = &Tw_PcInfos[pc].RotPcCons; 

    // remove possible RotPcCons from all possible moves 
    Tw_RotPcConSet_Difference(&player->RotPcCons, pcRpcs); 

    // remove possible RotPcCons from each corner 
    Tw_RotPcConSetMap_DifferenceFromAll(&player->OpenCorners, pcRpcs); 

    player->CanPlay &= Tw_RotPcConSetMap_AnyTileHasValues(&player->OpenCorners); 
}

/**
 * INTERNAL 
 * 
 * Update valid open corners and pieces that can be placed. 
 * 
 * @param player 
 * @param tiles 
 */
static inline void Tw_Player_OnTilesFilled(Tw_Player* player, const Tw_TileList* tiles) 
{
    Tw_RotPcConSet invalid; 
    int cx, cy, fx, fy, dx, dy; 
    Tw_TileSet_FOR_EACH(player->OpenCorners.Keys, tile, 
    {
        Tw_Tile_ToCoords(tile, &cx, &cy); 
        Tw_InitRotPcConSet(&invalid); 

        // the tiles being filled might affect which RotPcCons can be played at this corner
        for (int i = 0; i < tiles->Count; i++) 
        {
            Tw_Tile_ToCoords(tiles->Elements[i], &fx, &fy); 
            dx = fx - cx; 
            dy = fy - cy; 
            if (Tw_RelCoordsInBounds(dx, dy)) 
            {
                // any RotPcCons that need this tile, relative to their contact point, can no longer be played at this corner
                Tw_RotPcConSet_Union(&invalid, &Tw_RelTileInfos[Tw_MakeRelTile(dx, dy)].RotPcConsWithRelTile); 
            }
        }

        Tw_RotPcConSetMap_DifferenceFromTile(&player->OpenCorners, tile, &invalid); 
    });

    player->CanPlay &= Tw_RotPcConSetMap_AnyTileHasValues(&player->OpenCorners); 
}

/**
 * @param board Board
 * @param tile Tile
 * @return Whether the tile is claimed by any player
 */
static inline bool Tw_Board_IsClaimed(const Tw_Board* board, Tw_Tile tile) 
{
    return Tw_TileSet_Has(&board->All, tile); 
}

/**
 * @param board Board
 * @param tile Tile
 * @param col Player color
 * @return Whether the tile is claimed by the player
 */
static inline bool Tw_Board_IsClaimedBy(const Tw_Board* board, Tw_Tile tile, Tw_Color col) 
{
    return Tw_TileSet_Has(&board->Players[col].Claimed, tile); 
}

/**
 * @param board Board
 * @param tile Tile
 * @return Color of the tile (can be none)
 */
static inline Tw_Color Tw_Board_ColorAt(const Tw_Board* board, Tw_Tile tile) 
{
    if (Tw_Board_IsClaimed(board, tile)) 
    {
        for (Tw_Color col = Tw_Color_First; col < (Tw_Color) board->NumPlayers; col++) 
        {
            if (Tw_Board_IsClaimedBy(board, tile, col)) 
            {
                return col; 
            }
        }
    }
    
    return Tw_Color_None; 
}

/**
 * INTERNAL 
 * 
 * Add a playable corner to the player and determines which pieces can be 
 * placed there. 
 * 
 * @param player 
 * @param t 
 * @param board 
 * @param playerColor 
 */
static inline void Tw_Player_AddCorner(Tw_Player* player, Tw_Tile t, const Tw_Board* board, Tw_Color playerColor) 
{
    if (Tw_RotPcConSetMap_TileHasValues(&player->OpenCorners, t)) 
    {
        return;
    }

    Tw_RotPcConSet invalid; 
    Tw_InitRotPcConSet(&invalid); 

    int x, y, rx, ry, nx, ny; 
    Tw_Tile rel, n; 
    Tw_Color col; 
    Tw_Tile_ToCoords(t, &x, &y); 

    for (int i = 0; i < Tw_RelTilesWithRotPcCons.Count; i++) 
    {
        rel = Tw_RelTilesWithRotPcCons.Elements[i]; 
        Tw_Tile_ToRelCoords(rel, &rx, &ry); 

        // absolute coords of corner + rel tile 
        nx = x + rx; 
        ny = y + ry; 

        if (Tw_CoordsInBounds(nx, ny)) 
        {
            n = Tw_MakeTile(nx, ny); 
            if ((col = Tw_Board_ColorAt(board, n)) != Tw_Color_None) 
            {
                Tw_RotPcConSet_Union(&invalid, &Tw_RelTileInfos[rel].RotPcConsWithRelTile); 
                if (col == playerColor) 
                {
                    Tw_RotPcConSet_Union(&invalid, &Tw_RelTileInfos[rel].RotPcConsWithAdjRelTile); 
                }
            }
        }
        else 
        {
            Tw_RotPcConSet_Union(&invalid, &Tw_RelTileInfos[rel].RotPcConsWithRelTile); 
        }
    }

    Tw_RotPcConSet valid = player->RotPcCons; 
    Tw_RotPcConSet_Difference(&valid, &invalid); 
    Tw_RotPcConSetMap_AddToTile(&player->OpenCorners, t, &valid); 
}

/**
 * INTERNAL 
 * 
 * Moves to the next player on the board. 
 * 
 * @param board Board
 * @return Color of the last player 
 */
static inline Tw_Color Tw_Board_IncrPlayer(Tw_Board* board) 
{
    board->Ply++; 
    Tw_Color curTurn = board->CurTurn; 

    while (true) 
    {
        board->CurTurn = (board->CurTurn + 1) % (Tw_Color) board->NumPlayers; 

        if (board->Players[board->CurTurn].CanPlay) 
        {
            break; 
        }

        if (curTurn == board->CurTurn) 
        {
            board->Finished = true; 
            break; 
        }
    }

    // last player 
    return curTurn; 
}

/**
 * Undo the last-played move. 
 * 
 * There must have been at least one move played to call this. 
 * 
 * @param board Board
 */
static inline void Tw_Board_Pop(Tw_Board* board) 
{
    for (Tw_Color col = Tw_Color_First; col < (Tw_Color) board->NumPlayers; col++) 
    {
        Tw_Player_PopState(&board->Players[col]); 
    }

    board->Finished = false; 
    board->Ply--; 
    board->All = board->History[board->Ply].All; 
    board->CurTurn = board->History[board->Ply].CurTurn; 
}

/**
 * Play a move. Legality is not checked. 
 * 
 * @param board Board
 * @param move Move
 */
static inline void Tw_Board_Push(Tw_Board* board, Tw_Move move) 
{
    for (Tw_Color col = Tw_Color_First; col < (Tw_Color) board->NumPlayers; col++) 
    {
        Tw_Player_PushState(&board->Players[col]); 
    }

    board->History[board->Ply] = (Tw_BoardState) 
    {
        .All = board->All, 
        .CurTurn = board->CurTurn, 
        .Move = move
    };

    Tw_RotPcCon rpc = Tw_Move_RotPcCon(move); 
    Tw_Tile toTile = Tw_Move_ToTile(move); 
    Tw_Color col = board->CurTurn; 
    Tw_Player* player = &board->Players[col]; 

    Tw_RotPcConInfo* rpcInfo = &Tw_RotPcConInfos[rpc]; 
    Tw_RotPcInfo* rotInfo = &Tw_RotPcInfos[rpcInfo->RotPc]; 
    int tx, ty, rx, ry, ox, oy, cx, cy; 

    Tw_Tile_ToCoords(toTile, &tx, &ty); 
    Tw_Tile_ToCoords(rpcInfo->Offset, &ox, &oy); 

    // add new possible corners to current player 
    Tw_TileSet_FOR_EACH(rotInfo->RelCorners, tile, 
    {
        Tw_Tile_ToRelCoords(tile, &rx, &ry); 
        
        cx = tx + rx - ox; 
        cy = ty + ry - oy; 
        if (Tw_CoordsInBounds(cx, cy)) 
        {
            Tw_Player_AddCorner(player, Tw_MakeTile(cx, cy), board, col); 
        }
    });

    // move piece tiles to target positions
    Tw_TileSet tiles = rotInfo->Tiles; 
    Tw_TileSet_LShift(&tiles, toTile - rpcInfo->Offset); 

    // add tiles to board 
    Tw_TileSet_Union(&board->All, &tiles); 
    Tw_TileSet_Union(&board->Players[col].Claimed, &tiles); 

    // update valid piece moves for players 
    Tw_TileList tilesFilled; 
    Tw_InitTileList(&tilesFilled); 
    Tw_TileSet_AddToTileList(&tiles, &tilesFilled); 
    for (Tw_Color c = Tw_Color_First; c < (Tw_Color) board->NumPlayers; c++) 
    {
        Tw_Player_OnTilesFilled(&board->Players[c], &tilesFilled); 
    }

    // player can't place tiles adjacent to their own color 
    Tw_InitTileList(&tilesFilled); 
    Tw_TileSet_FOR_EACH(rotInfo->RelAdjacents, tile, 
    {
        Tw_Tile_ToRelCoords(tile, &rx, &ry); 
        
        cx = tx + rx - ox; 
        cy = ty + ry - oy; 
        if (Tw_CoordsInBounds(cx, cy)) 
        {
            Tw_TileList_Push(&tilesFilled, Tw_MakeTile(cx, cy)); 
        }
    });
    Tw_Player_OnTilesFilled(player, &tilesFilled); 
    Tw_Player_RemovePc(player, rpcInfo->Pc); 

    if (!player->HasPlayed) 
    {
        Tw_RotPcConSetMap_ClearFromTile(&player->OpenCorners, Tw_Tile_A01); 
        Tw_RotPcConSetMap_ClearFromTile(&player->OpenCorners, Tw_Tile_A20); 
        Tw_RotPcConSetMap_ClearFromTile(&player->OpenCorners, Tw_Tile_T01); 
        Tw_RotPcConSetMap_ClearFromTile(&player->OpenCorners, Tw_Tile_T20); 
    }

    player->HasPlayed = true; 
    player->Score += Tw_TileSet_Count(&rotInfo->Tiles); 

    Tw_Board_IncrPlayer(board); 
}

/**
 * Get number of legal moves as if the specified player is up to play. 
 * 
 * @param board Board
 * @param forPlayer Player to generate moves for
 * @return Number of legal moves 
 */
static inline int Tw_Board_NumMovesForPlayer(const Tw_Board* board, Tw_Color forPlayer) 
{
    const Tw_Player* player = &board->Players[forPlayer]; 
    int total = 0; 

    Tw_TileSet_FOR_EACH(player->OpenCorners.Keys, tile, 
    {
        Tw_RotPcConSet_FOR_EACH(player->OpenCorners.Sets[tile], rpc, 
        {
            total++; 
        });
    });

    return total; 
}

/**
 * Get number of legal moves for the current player. 
 * 
 * @param board Board
 * @return Number of legal moves 
 */
static inline int Tw_Board_NumMoves(const Tw_Board* board) 
{
    return Tw_Board_NumMovesForPlayer(board, board->CurTurn); 
}

/**
 * Get all legal moves as if the specified player is up to play. 
 * 
 * @param board Board
 * @param forPlayer Player to generate moves for
 * @param moves Initialized list of moves
 */
static inline void Tw_Board_GenMovesForPlayer(const Tw_Board* board, Tw_Color forPlayer, Tw_MoveList* moves) 
{
    const Tw_Player* player = &board->Players[forPlayer]; 

    Tw_TileSet_FOR_EACH(player->OpenCorners.Keys, tile, 
    {
        Tw_RotPcConSet_FOR_EACH(player->OpenCorners.Sets[tile], rpc, 
        {
            Tw_MoveList_Push(moves, Tw_MakeMoveFromRotPcCon(rpc, tile)); 
        });
    });
}

/**
 * Generate all legal moves for the current player. 
 * 
 * @param board Board
 * @param moves Initialized list of moves
 */
static inline void Tw_Board_GenMoves(const Tw_Board* board, Tw_MoveList* moves) 
{
    Tw_Board_GenMovesForPlayer(board, board->CurTurn, moves); 
}

/**
 * Gets the string representation of a board. 
 * 
 * Note that the buffer must hold at least `Tw_BoardStrSize` bytes. 
 * 
 * @param board Board
 * @param out Output buffer
 */
static inline void Tw_Board_ToStr(const Tw_Board* board, char* out) 
{
    static const char* Chars[] = 
    {
        "\033[94mB\033[0m", 
        "\033[93mY\033[0m", 
        "\033[91mR\033[0m", 
        "\033[92mG\033[0m", 
        "."
    };

    int len = 0; 

    for (int y = Tw_BoardHeight - 1; y >= 0; y--) 
    {
        len += sprintf(out + len, "%2d ", y + 1); 
        for (int x = 0; x < Tw_BoardWidth; x++) 
        {
            len += sprintf(out + len, "%s ", Chars[Tw_Board_ColorAt(board, Tw_MakeTile(x, y))]); 
        }
        len += sprintf(out + len, "\n"); 
    }
    len += sprintf(out + len, "   "); 
    for (int x = 0; x < Tw_BoardWidth; x++) 
    {
        len += sprintf(out + len, "%c ", 'a' + x); 
    }
    len += sprintf(out + len, "\n"); 

    len += sprintf(out + len, "Turn: %s\n", Tw_Color_Str(board->CurTurn)); 
    len += sprintf(out + len, "Ply: %d\n", board->Ply); 

    for (Tw_Color col = Tw_Color_First; col < (Tw_Color) board->NumPlayers; col++) 
    {
        len += sprintf(out + len, "%6s ", Tw_Color_Str(col)); 

        len += sprintf(out + len, "Corners: [ "); 
        Tw_TileSet_FOR_EACH(board->Players[col].OpenCorners.Keys, tile, 
        {
            len += sprintf(out + len, "%s ", Tw_Tile_Str(tile)); 
        });
        len += sprintf(out + len, "]"); 


        len += sprintf(out + len, "\n"); 
    }
}

/**
 * Print the board state. 
 * 
 * @param board Board
 */
static inline void Tw_Board_Print(const Tw_Board* board) 
{
    char buf[Tw_BoardStrSize]; 
    Tw_Board_ToStr(board, buf); 
    printf("%s", buf); 
}

/**
 * Initialize the board. It does not have to be deinitialized. 
 * 
 * @param board Board
 * @param numPlayers Number of players in the game
 */
static inline void Tw_InitBoard(Tw_Board* board, int numPlayers) 
{
    Tw_Init(); 
    board->NumPlayers = numPlayers; 
    board->CurTurn = Tw_Color_First; 
    board->Finished = false; 
    board->Ply = 0; 

    for (Tw_Color col = Tw_Color_First; col < Tw_NumColors; col++) 
    {
        Tw_InitPlayer(&board->Players[col], col, col < (Tw_Color) numPlayers); 

        if (col < (Tw_Color) numPlayers) 
        {
            Tw_Player_AddCorner(&board->Players[col], Tw_Tile_A01, board, col); 
            Tw_Player_AddCorner(&board->Players[col], Tw_Tile_A20, board, col); 
            Tw_Player_AddCorner(&board->Players[col], Tw_Tile_T01, board, col); 
            Tw_Player_AddCorner(&board->Players[col], Tw_Tile_T20, board, col); 
            Tw_Player_PushState(&board->Players[col]); 
        }
        else 
        {
            board->Players[col].CanPlay = false; 
            Tw_RotPcConSet_Clear(&board->Players[col].RotPcCons); 
        }
    }
    Tw_InitTileSet(&board->All); 
}

/**
 * @param board Board
 * @param col Player
 * @return Number of pieces remaining for the player
 */
static inline int Tw_Board_NumPlayerPcs(const Tw_Board* board, Tw_Color col) 
{
    int total = 0; 

    for (Tw_Pc pc = Tw_Pc_First; pc < Tw_NumPcs; pc++) 
    {
        total += Tw_RotPcConSet_HasAny(&board->Players[col].RotPcCons, &Tw_PcInfos[pc].RotPcCons); 
    }

    return total; 
}

/**
 * Appends list of remaining pieces for the player. 
 * 
 * @param board Board
 * @param col Player
 * @param out Output list 
 */
static inline void Tw_Board_PlayerPcs(const Tw_Board* board, Tw_Color col, Tw_PcList* out) 
{
    for (Tw_Pc pc = Tw_Pc_First; pc < Tw_NumPcs; pc++) 
    {
        if (Tw_RotPcConSet_HasAny(&board->Players[col].RotPcCons, &Tw_PcInfos[pc].RotPcCons)) 
        {
            Tw_PcList_Push(out, pc); 
        }
    }
}

/**
 * @param board Board
 * @param col Player
 * @return Number of playable open corners for a player. 
 */
static inline int Tw_Board_NumPlayerCorners(const Tw_Board* board, Tw_Color col) 
{
    return Tw_TileSet_Count(&board->Players[col].OpenCorners.Keys); 
}

/**
 * Appends all playable open corners for a player to a list. 
 * 
 * @param board Board
 * @param col Player
 * @param out Output list 
 */
static inline void Tw_Board_PlayerCorners(const Tw_Board* board, Tw_Color col, Tw_TileList* out) 
{
    Tw_TileSet_FOR_EACH(board->Players[col].OpenCorners.Keys, tile, 
    {
        Tw_TileList_Push(out, tile); 
    });
}
