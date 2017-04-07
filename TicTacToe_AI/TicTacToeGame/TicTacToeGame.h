#ifndef __TICTACTOE_GAME_H_INCLUDED__
#define __TICTACTOE_GAME_H_INCLUDED__

#include <array>
#include "TicTacToeExportApi.h"
#include "TicTacToeCommon.h"

/*
Class holding the state of a game of TicTacToe.
*/
struct TICTACTOEGAME_API BoardState
{
	/*
	The state of the 3x3 game board, indicating where players have played their pieces.
	*/
	std::array<std::array<Player, 3>, 3> boardCells =
	{
		{
			{ { Player::None, Player::None, Player::None } },
			{ { Player::None, Player::None, Player::None } },
			{ { Player::None, Player::None, Player::None } }
		}
	};

	/*
	Indicates the player whose turn it it.
	*/
	Player curentPlayer = Player::None;

	/*
	Indicates the winner of the game.
	*/
	Player winner = Player::None;

	/*
	Indicates if the game is finished.
	*/
	bool gameFinished = false;
};

/*
The tic-tac-toe game engine.
*/
class TICTACTOEGAME_API TicTacToeGame {
private:
	BoardState state;
	char nrOfPiecesPlayed;

	void toggleNextPlayer(void);
	Player determineWinner(void) const;
	bool isThreeInRow(Player, Row) const;
	bool isThreeInColumn(Player, Column) const;
	bool isThreeInDiagonal(Player) const;

public:
	/*
	Initializes a game of tic-tac-toe.
	*/
	TicTacToeGame(void);

	/*
	Gets the curent board state.
	*/
	BoardState getCurrentState(void) const;

	/*
	Marks the move of a player playing a piece to the board. Returns false for an invalid move.
	*/
	bool playPiece(Player, Row, Column);

	/*
	Resets the board to the starting situation.
	*/
	void reset(void);
};

#endif // !__TICTACTOE_GAME_H_INCLUDED__
