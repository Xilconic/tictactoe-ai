#include "stdafx.h"
#include "TicTacToeGameEnvironment.h"

GameEnvironment::GameEnvironment(GamePlayer* x, GamePlayer* o)
{
	// TODO: Probably need to clean up API of constructor.
}

GamePlayer* GameEnvironment::getCurrentPlayer() const
{
	// TODO: get current player based on board state's current player
	return 0;
}

void GameEnvironment::playGame()
{
	game.reset();
	while (!game.getCurrentState().gameFinished)
	{
		GamePlayer* currentPlayer = getCurrentPlayer();

		BoardState currentState = game.getCurrentState();
		// TODO: this is probably passing by value? Should be passing by reference?
		Move intendedMove = currentPlayer->getMove(currentState);
		game.playPiece(currentState.curentPlayer, intendedMove.row, intendedMove.column);
	}
}