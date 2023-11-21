#include "Test/Test.h" 
#include "Tilewe/Tilewe.h"

TEST_CASE(FinishedWithin84Ply, 
{
    Tw_Board board[1]; 
    Tw_MoveList moves[1]; 

    Tw_InitBoard(board, 4); 
    while (!board->Finished)
    {
        Tw_InitMoveList(moves); 
        Tw_Board_GenMoves(board, moves); 

        // if board is not finished, there are moves to play
        TEST_EXPECT_GT(moves->Count, 0); 

        Tw_Board_Push(board, moves->Elements[0]); 
        TEST_EXPECT_LTE(board->Ply, 84); 
    }

    // all four players can play at least this many turns, and probably more
    TEST_EXPECT_GT(board->Ply, 3 * 4); 
})

TEST_CASE(NumPlayerPcs, 
{
    Tw_Board board[1]; 

    Tw_InitBoard(board, 3); 

    TEST_EXPECT_EQ(Tw_Board_NumPlayerPcs(board, Tw_Color_Blue), 21); 
    TEST_EXPECT_EQ(Tw_Board_NumPlayerPcs(board, Tw_Color_Yellow), 21); 
    TEST_EXPECT_EQ(Tw_Board_NumPlayerPcs(board, Tw_Color_Red), 21); 
    TEST_EXPECT_EQ(Tw_Board_NumPlayerPcs(board, Tw_Color_Green), 0); 

    Tw_Board_Push(board, Tw_MakeMove(Tw_Pc_Z5, Tw_Rot_E, Tw_Tile_A01, Tw_Tile_A01)); 

    TEST_EXPECT_EQ(Tw_Board_NumPlayerPcs(board, Tw_Color_Blue), 20); 
    TEST_EXPECT_EQ(Tw_Board_NumPlayerPcs(board, Tw_Color_Yellow), 21); 
    TEST_EXPECT_EQ(Tw_Board_NumPlayerPcs(board, Tw_Color_Red), 21); 
    TEST_EXPECT_EQ(Tw_Board_NumPlayerPcs(board, Tw_Color_Green), 0); 

    Tw_Board_Push(board, Tw_MakeMove(Tw_Pc_Z5, Tw_Rot_N, Tw_Tile_A20, Tw_Tile_A03)); 

    TEST_EXPECT_EQ(Tw_Board_NumPlayerPcs(board, Tw_Color_Blue), 20); 
    TEST_EXPECT_EQ(Tw_Board_NumPlayerPcs(board, Tw_Color_Yellow), 20); 
    TEST_EXPECT_EQ(Tw_Board_NumPlayerPcs(board, Tw_Color_Red), 21); 
    TEST_EXPECT_EQ(Tw_Board_NumPlayerPcs(board, Tw_Color_Green), 0); 
})

TEST_CASE(PushPopIsSameState, 
{
    Tw_Board board[1]; 
    Tw_MoveList moves[1]; 

    Tw_InitBoard(board, 4); 
    Tw_InitMoveList(moves); 
    Tw_Board_GenMoves(board, moves); 

    for (int i = 0; i < moves->Count; i++) 
    {
        int numPcs[Tw_NumColors]; 
        for (Tw_Color col = Tw_Color_First; col < Tw_NumColors; col++) 
        {
            numPcs[col] = Tw_Board_NumPlayerPcs(board, col); 
        }

        Tw_Board_Push(board, moves->Elements[i]); 
        Tw_Board_Pop(board); 

        for (Tw_Color col = Tw_Color_First; col < Tw_NumColors; col++) 
        {
            TEST_EXPECT_EQ(Tw_Board_NumPlayerPcs(board, col), numPcs[col]); 
        }
    }
})

TEST_CASE(InitialMoveCount, 
{
    Tw_Board board[1]; 
    Tw_MoveList moves[1]; 

    Tw_InitBoard(board, 4); 
    Tw_InitMoveList(moves); 
    Tw_Board_GenMoves(board, moves); 

    TEST_EXPECT_EQ(moves->Count, 232); 
})

TEST_MAIN(TestBoard, 
{
    Tw_Init(); 
    TEST_RUN(FinishedWithin84Ply); 
    TEST_RUN(NumPlayerPcs); 
    TEST_RUN(PushPopIsSameState); 
    TEST_RUN(InitialMoveCount); 
})
