// TicTacToeGame.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "TicTacToeGame.h"

TicTacToeGame::TicTacToeGame()
{
	reset();
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

bool TicTacToeGame::isThreeInRow(PlayerIndicator player, RowIndicator row)
{
	char rowIndex = char(row);
	return state.boardCells[rowIndex][0] == player &&
		state.boardCells[rowIndex][1] == player &&
		state.boardCells[rowIndex][2] == player;
}

bool TicTacToeGame::isThreeInColumn(PlayerIndicator player, ColumnIndicator column)
{
	char columnIndex = char(column);
	return state.boardCells[0][columnIndex] == player &&
		state.boardCells[1][columnIndex] == player &&
		state.boardCells[2][columnIndex] == player;
}

bool TicTacToeGame::isThreeInDiagonal(PlayerIndicator player)
{
	return (state.boardCells[0][0] == player &&
			state.boardCells[1][1] == player &&
			state.boardCells[2][2] == player) ||
		   (state.boardCells[2][0] == player &&
			state.boardCells[1][1] == player &&
			state.boardCells[0][2] == player);
}

PlayerIndicator TicTacToeGame::determineWinner()
{
	PlayerIndicator players[2] = { PlayerIndicator::X, PlayerIndicator::O };
	for (char i = 0; i < state.boardCells.size(); i++)
	{
		for each (PlayerIndicator player in players)
		{
			if (isThreeInRow(player, RowIndicator(i)))
			{
				return player;
			}
		}
	}

	for (char i = 0; i < state.boardCells[0].size(); i++)
	{
		for each (PlayerIndicator player in players)
		{
			if (isThreeInColumn(player, ColumnIndicator(i)))
			{
				return player;
			}
		}
	}

	for each (PlayerIndicator player in players)
	{
		if (isThreeInDiagonal(player))
		{
			return player;
		}
	}

	return PlayerIndicator::None;
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

	nrOfPiecesPlayed++;

	state.winner = determineWinner();
	if (state.winner != PlayerIndicator::None || nrOfPiecesPlayed == 9)
	{
		state.gameFinished = true;
	}

	toggleNextPlayer();
	return true;
}

void TicTacToeGame::reset()
{
	state = BoardState();
	state.curentPlayer = PlayerIndicator::X;
	nrOfPiecesPlayed = 0;
}