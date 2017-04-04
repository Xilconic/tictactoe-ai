#ifndef __TICTACTOE_GAMEPLAYER_H_INCLUDED__
#define __TICTACTOE_GAMEPLAYER_H_INCLUDED__

#include "TicTacToeExportApi.h"
#include "TicTacToeCommon.h"
#include "TicTacToeGame.h"

/*
 Denotes a move a player intends to make.
*/
struct TICTACTOEGAME_API Move
{
	/*
	 The row to play a piece to.
	*/
	Row row;
	/*
	 The column to play a piece to.
	*/
	Column column;

	/*
	 Define an intended move to play a piece to the given row and column.
	*/
	Move(Row, Column);
};

/*
 Abstract class defining a player capable of playing tic-tac-toe.
*/
class TICTACTOEGAME_API GamePlayer
{
public:
	/*
	 Determines the move the players intends to take for the given game state.
	*/
	virtual Move getMove(BoardState gamestate) = 0;
};

#endif // !__TICTACTOE_GAMEPLAYER_H_INCLUDED__
