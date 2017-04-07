#ifndef __TICTACTOE_ENVIRONMENT_H_INCLUDED__
#define __TICTACTOE_ENVIRONMENT_H_INCLUDED__

#include "TicTacToeExportApi.h"
#include "TicTacToeGamePlayer.h"

class TICTACTOEGAME_API GameEnvironment
{
private:
	GamePlayer * playerX;
	GamePlayer * playerO;
	TicTacToeGame game;

	GamePlayer* getCurrentPlayer(const BoardState &) const;
	void processTurn(void);

public:
	GameEnvironment(GamePlayer &, GamePlayer &);

	/*
	 Plays a game of tic-tac-toe between two players.
	*/
	void playGame(void);
};

#endif // !__TICTACTOE_ENVIRONMENT_H_INCLUDED__
