#include "Piece.h" 

Tw_PcInfo Tw_PcInfos[Tw_NumPcs]; 
Tw_RotPcInfo Tw_RotPcInfos[Tw_NumRotPcs]; 
Tw_RotPcConInfo Tw_RotPcConInfos[Tw_NumRotPcCons]; 

Tw_RelTileInfo Tw_RelTileInfos[Tw_NumTiles]; 
Tw_TileList Tw_RelTilesWithRotPcCons; 

typedef struct Tw_PcDef Tw_PcDef; 

struct Tw_PcDef 
{
    Tw_Tile Tiles[64]; 
};

static Tw_PcDef Tw_PcDefs[] = 
{
    { .Tiles = { Tw_Tile_A01, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A01, Tw_Tile_A02, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A01, Tw_Tile_A02, Tw_Tile_A03, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A01, Tw_Tile_A02, Tw_Tile_B01, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A01, Tw_Tile_A02, Tw_Tile_B01, Tw_Tile_B02, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A01, Tw_Tile_A02, Tw_Tile_A03, Tw_Tile_A04, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A01, Tw_Tile_A02, Tw_Tile_A03, Tw_Tile_B01, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A02, Tw_Tile_B01, Tw_Tile_B02, Tw_Tile_C01, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A02, Tw_Tile_B01, Tw_Tile_B02, Tw_Tile_C02, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A02, Tw_Tile_B01, Tw_Tile_B02, Tw_Tile_B03, Tw_Tile_C03, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A01, Tw_Tile_A02, Tw_Tile_A03, Tw_Tile_A04, Tw_Tile_A05, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A01, Tw_Tile_A02, Tw_Tile_A03, Tw_Tile_A04, Tw_Tile_B01, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A01, Tw_Tile_A02, Tw_Tile_A03, Tw_Tile_B03, Tw_Tile_B04, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A01, Tw_Tile_A02, Tw_Tile_A03, Tw_Tile_B02, Tw_Tile_B03, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A03, Tw_Tile_B01, Tw_Tile_B02, Tw_Tile_B03, Tw_Tile_C03, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A01, Tw_Tile_A02, Tw_Tile_B01, Tw_Tile_C01, Tw_Tile_C02, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A01, Tw_Tile_B01, Tw_Tile_C01, Tw_Tile_C02, Tw_Tile_C03, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A01, Tw_Tile_B01, Tw_Tile_B02, Tw_Tile_C02, Tw_Tile_C03, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A02, Tw_Tile_B01, Tw_Tile_B02, Tw_Tile_B03, Tw_Tile_C02, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A03, Tw_Tile_B01, Tw_Tile_B02, Tw_Tile_B03, Tw_Tile_B04, Tw_Tile_None } }, 
    { .Tiles = { Tw_Tile_A03, Tw_Tile_B01, Tw_Tile_B02, Tw_Tile_B03, Tw_Tile_C01, Tw_Tile_None } }, 
};

static int Tw_TileSet_Width(const Tw_TileSet* set) 
{
    int w = 0; 

    for (int y = Tw_BoardHeight - 1; y >= 0; y--) 
    {
        for (int x = 0; x < Tw_BoardWidth; x++) 
        {
            if (Tw_TileSet_Has(set, Tw_MakeTile(x, y))) 
            {
                if (x > w) w = x; 
            }
        }
    }

    return w; 
}

static void Tw_TileSet_RotateCw(const Tw_TileSet* set, Tw_TileSet* out) 
{
    int w = Tw_TileSet_Width(set); 

    Tw_TileSet_Clear(out); 

    Tw_Tile tile; 
    Tw_TileSet tmp = *set; 
    while ((tile = Tw_TileSet_RemoveFirst(&tmp)) != (Tw_Tile) -1) 
    {
        int x, y; 
        Tw_Tile_ToCoords(tile, &x, &y); 
        Tw_TileSet_Add(out, Tw_MakeTile(y, w - x)); 
    }
}

static void Tw_TileSet_Flip(const Tw_TileSet* set, Tw_TileSet* out) 
{
    int w = Tw_TileSet_Width(set); 

    Tw_TileSet_Clear(out); 

    Tw_Tile tile; 
    Tw_TileSet tmp = *set; 
    while ((tile = Tw_TileSet_RemoveFirst(&tmp)) != (Tw_Tile) -1) 
    {
        int x, y; 
        Tw_Tile_ToCoords(tile, &x, &y); 
        Tw_TileSet_Add(out, Tw_MakeTile(w - x, y)); 
    }
}

static Tw_RotPcCon Tw_RegRotPcCon(Tw_RotPc rp, Tw_Tile offset) 
{
    static Tw_RotPcCon current = 0; 

    Tw_RotPcConInfos[current] = (Tw_RotPcConInfo)
    {
        .Pc = Tw_UnrotPc(rp), 
        .Rot = Tw_PcRot(rp), 
        .RotPc = rp, 
        .Offset = offset
    };

    Tw_RotPcConSet_Add(&Tw_PcInfos[Tw_UnrotPc(rp)].RotPcCons, current); 
    Tw_RotPcInfos[rp].ToRotPcCon[offset] = current; 

    return current++; 
}

static void Tw_RegRotPc(Tw_RotPc rp, const Tw_TileSet* tiles, Tw_RotPc unique) 
{
    Tw_RotPcInfo* info = &Tw_RotPcInfos[rp]; 

    // copy everything from unique rotation, including the exact same RotPcCon IDs
    if (rp != unique) 
    {
        *info = Tw_RotPcInfos[unique]; 
        return; 
    }

    info->Tiles = *tiles; 
    Tw_InitTileSet(&info->Contacts); 
    Tw_InitTileSet(&info->RelAdjacents); 
    Tw_InitTileSet(&info->RelCorners); 

    int x, y; 

    // find contacts 
    Tw_TileSet_FOR_EACH(info->Tiles, 
    {
        Tw_Tile_ToCoords(tile, &x, &y); 

        int hNeighbors = 0; 
        int vNeighbors = 0; 
        
        if (Tw_CoordsInBounds(x + 1, y + 0) && Tw_TileSet_Has(tiles, Tw_MakeTile(x + 1, y + 0))) hNeighbors++; 
        if (Tw_CoordsInBounds(x - 1, y + 0) && Tw_TileSet_Has(tiles, Tw_MakeTile(x - 1, y + 0))) hNeighbors++; 
        if (Tw_CoordsInBounds(x + 0, y + 1) && Tw_TileSet_Has(tiles, Tw_MakeTile(x + 0, y + 1))) vNeighbors++; 
        if (Tw_CoordsInBounds(x + 0, y - 1) && Tw_TileSet_Has(tiles, Tw_MakeTile(x + 0, y - 1))) vNeighbors++; 

        int nNeighbors = hNeighbors + vNeighbors; 

        if ((nNeighbors <= 1) || (vNeighbors == 1 && hNeighbors == 1)) 
        {
            Tw_TileSet_Add(&info->Contacts, tile); 
        }
    }); 

    static int AdjX[] = { -1, 1,  0, 0 }; 
    static int AdjY[] = {  0, 0, -1, 1 }; 

    // find adjacents 
    Tw_TileSet_FOR_EACH(info->Tiles, 
    {
        Tw_Tile_ToCoords(tile, &x, &y); 

        for (int i = 0; i < 4; i++) 
        {
            // relative to bottom-left corner (A01) of piece shape
            int rx = x + AdjX[i]; 
            int ry = y + AdjY[i]; 

            // relative tile is adjacent to the piece if: 
            // - it shares an edge with a piece tile (guaranteed at this point)
            // - it is not a different tile of the piece
            if (!Tw_CoordsInBounds(rx, ry) || !Tw_TileSet_Has(&info->Tiles, Tw_MakeTile(rx, ry))) 
            {
                Tw_TileSet_Add(&info->RelAdjacents, Tw_MakeRelTile(rx, ry)); 
            }
        }
    }); 

    static int CornerX[] = { -1,  1, -1, 1 }; 
    static int CornerY[] = { -1, -1,  1, 1 }; 

    // find corners 
    Tw_TileSet_FOR_EACH(info->Tiles, 
    {
        Tw_Tile_ToCoords(tile, &x, &y); 

        for (int i = 0; i < 4; i++) 
        {
            // relative to bottom-left corner (A01) of piece shape
            int rx = x + CornerX[i]; 
            int ry = y + CornerY[i]; 

            // relative tile is corner to the piece if: 
            // - it shares a corner with a piece tile (guaranteed at this point)
            // - it is not adjacent to the piece 
            // - it is not a different tile of the piece
            if (!Tw_CoordsInBounds(rx, ry) || !Tw_TileSet_Has(&info->Tiles, Tw_MakeTile(rx, ry))) 
            {
                if (!Tw_TileSet_Has(&info->RelAdjacents, Tw_MakeRelTile(rx, ry))) 
                {
                    Tw_TileSet_Add(&info->RelCorners, Tw_MakeRelTile(rx, ry)); 
                }
            }
        }
    }); 

    // create rot pc cons if this rotation is unique
    Tw_InitRotPcConSet(&info->RotPcCons); 
    Tw_TileSet_FOR_EACH(info->Contacts, 
    {
        Tw_RotPcConSet_Add(&info->RotPcCons, Tw_RegRotPcCon(rp, tile)); 
    }); 
}

static void Tw_RegPc(Tw_Pc pc) 
{
    Tw_InitRotPcConSet(&Tw_PcInfos[pc].RotPcCons); 

    Tw_TileSet tiles[Tw_NumRots]; 
    for (int i = 0; i < Tw_NumRots; i++) 
    {
        Tw_TileSet_Clear(&tiles[i]); 
    }

    Tw_Tile* tile = Tw_PcDefs[pc].Tiles - 1; 
    while (*(++tile) != Tw_Tile_None) 
    {
        Tw_TileSet_Add(&tiles[0], *tile); 
    }

    for (Tw_Rot i = 0; i < 3; i++) 
    {
        Tw_TileSet_RotateCw(&tiles[i], &tiles[i + 1]); 
    }
    
    for (Tw_Rot i = 0; i < 4; i++) 
    {
        Tw_TileSet_Flip(&tiles[i], &tiles[i + 4]); 
    }

    for (Tw_Rot i = 0; i < Tw_NumRots; i++) 
    {
        Tw_Rot unique = i; 
        for (Tw_Rot j = 0; j < i; j++) 
        {
            if (Tw_TileSet_Equals(&tiles[i], &tiles[j])) 
            {
                unique = j; 
                break; 
            }
        }

        Tw_RegRotPc(Tw_ToRotPc(pc, i), &tiles[i], Tw_ToRotPc(pc, unique)); 
    }
}

static void Tw_SetRelTileInfo(Tw_Tile rel) 
{
    Tw_RelTileInfo* info = &Tw_RelTileInfos[rel]; 
    Tw_InitRotPcConSet(&info->RotPcConsWithRelTile); 
    Tw_InitRotPcConSet(&info->RotPcConsWithAdjRelTile); 

    for (Tw_RotPcCon rpc = 0; rpc < Tw_NumRotPcCons; rpc++) 
    {
        Tw_RotPcConInfo* rpcInfo = &Tw_RotPcConInfos[rpc]; 
        Tw_RotPcInfo* rpInfo = &Tw_RotPcInfos[rpcInfo->RotPc]; 
        int tx, ty, rpcx, rpcy; 
        Tw_Tile rt; 

        Tw_Tile_ToCoords(rpcInfo->Offset, &rpcx, &rpcy); 

        Tw_TileSet_FOR_EACH(rpInfo->Tiles, 
        {
            Tw_Tile_ToCoords(tile, &tx, &ty); 
            rt = Tw_MakeRelTile(tx - rpcx, ty - rpcy); 
            if (rel == rt) 
            {
                Tw_RotPcConSet_Add(&info->RotPcConsWithRelTile, rpc); 
            }
        });

        Tw_TileSet_FOR_EACH(rpInfo->RelAdjacents, 
        {
            Tw_Tile_ToRelCoords(tile, &tx, &ty); 
            rt = Tw_MakeRelTile(tx - rpcx, ty - rpcy); 
            if (rel == rt) 
            {
                Tw_RotPcConSet_Add(&info->RotPcConsWithAdjRelTile, rpc); 
            }
        });
    }

    if (Tw_RotPcConSet_Any(&info->RotPcConsWithRelTile) || Tw_RotPcConSet_Any(&info->RotPcConsWithAdjRelTile)) 
    {
        Tw_TileList_Push(&Tw_RelTilesWithRotPcCons, rel); 
    }
}

void Tw_Init(void) 
{
    static bool Init = false; 
    if (Init) return; 
     
    for (Tw_Pc i = 0; i < Tw_NumPcs; i++) 
    {
        Tw_RegPc(i); 
    }

    for (Tw_Tile t = Tw_Tile_A01; t < Tw_NumTiles; t++) 
    {
        Tw_SetRelTileInfo(t); 
    }

    Init = true;
}