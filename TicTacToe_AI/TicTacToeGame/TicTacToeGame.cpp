// TicTacToeGame.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "TicTacToeGame.h"

TicTacToeGame::TicTacToeGame()
{
	state.curentPlayer = PlayerIndicator::X;
    return;
}

void TicTacToeGame::toggleNextPlayer()
{
	switch (state.curentPlayer)
	{
	case PlayerIndicator::X:
		state.curentPlayer = PlayerIndicator::O;
		break;
	case PlayerIndicator::O:
		state.curentPlayer = PlayerIndicator::X;
		break;
	}
}

BoardState TicTacToeGame::getCurrentState()
{
	return state;
}

bool TicTacToeGame::playPiece(PlayerIndicator player, RowIndicator row, ColumnIndicator column)
{
	if (player != state.curentPlayer)
	{
		return false;
	}
	char rowIndex = char(row);
	char columnIndex = char(column);
	if (state.boardCells[rowIndex][columnIndex] != PlayerIndicator::None)
	{
		return false;
	}
	state.boardCells[rowIndex][columnIndex] = player;

	toggleNextPlayer();
	return true;
}