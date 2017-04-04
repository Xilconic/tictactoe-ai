#ifndef __TICTACTOE_COMMON_H_INCLUDED__
#define __TICTACTOE_COMMON_H_INCLUDED__

#include "TicTacToeExportApi.h"

/*
Denotes the player, if any.
*/
enum class TICTACTOEGAME_API Player
{
	/*
	Denoted the absense of a player.
	*/
	None,
	/*
	Denotes the 'X' player.
	*/
	X,
	/*
	Denotes the 'O' player.
	*/
	O
};

/*
Denotes the row to play a piece to.
*/
enum class TICTACTOEGAME_API Row
{
	Top = 0,
	Middle = 1,
	Bottom = 2
};

/*
Denotes the column to play a piece to.
*/
enum class TICTACTOEGAME_API Column
{
	Left = 0,
	Middle = 1,
	Right = 2
};

#endif // !__TICTACTOE_COMMON_H_INCLUDED__
