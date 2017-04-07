#include "stdafx.h"
#include "TicTacToeGameEnvironment.h"

GameEnvironment::GameEnvironment(GamePlayer & x, GamePlayer & o)
{
	playerX = &x;
	playerO = &o;
}

GamePlayer* GameEnvironment::getCurrentPlayer(const BoardState & currentState) const
{
	switch (currentState.curentPlayer)
	{
		case Player::X:
				return playerX;
		case Player::O:
			return playerO;
	}
}

void GameEnvironment::processTurn()
{
	BoardState currentState = game.getCurrentState();

	GamePlayer* currentPlayer = getCurrentPlayer(currentState);
	Move intendedMove = currentPlayer->getMove(currentState);
	game.playPiece(currentState.curentPlayer, intendedMove.row, intendedMove.column);
}

void GameEnvironment::playGame()
{
	game.reset();
	while (!game.getCurrentState().gameFinished)
	{
		processTurn();
	}
}
