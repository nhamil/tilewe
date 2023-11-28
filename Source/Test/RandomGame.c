#include <stdlib.h> 
#include <time.h> 

#include "Tilewe/Tilewe.h"

int main(void) 
{
    srand(time(NULL)); 

    Tw_Board board; 
    Tw_MoveList moves; 

    Tw_InitBoard(&board, 4); 
    while (!board.Finished) 
    {
        Tw_InitMoveList(&moves); 
        Tw_Board_GenMoves(&board, &moves); 
        Tw_Board_Push(&board, moves.Elements[rand() % moves.Count]); 
        Tw_Move_Print(moves.Elements[rand() % moves.Count]); 
        printf("\n"); 
        Tw_Board_Print(&board); 
        printf("\n"); 
    }
    return 0; 
}
