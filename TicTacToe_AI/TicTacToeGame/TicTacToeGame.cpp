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
	case Player::X:
		state.curentPlayer = Player::O;
		break;
	case Player::O:
		state.curentPlayer = Player::X;
		break;
	}
}

BoardState TicTacToeGame::getCurrentState()
{
	return state;
}

bool TicTacToeGame::isThreeInRow(Player player, Row row)
{
	char rowIndex = char(row);
	return state.boardCells[rowIndex][0] == player &&
		state.boardCells[rowIndex][1] == player &&
		state.boardCells[rowIndex][2] == player;
}

bool TicTacToeGame::isThreeInColumn(Player player, Column column)
{
	char columnIndex = char(column);
	return state.boardCells[0][columnIndex] == player &&
		state.boardCells[1][columnIndex] == player &&
		state.boardCells[2][columnIndex] == player;
}

bool TicTacToeGame::isThreeInDiagonal(Player player)
{
	return (state.boardCells[0][0] == player &&
			state.boardCells[1][1] == player &&
			state.boardCells[2][2] == player) ||
		   (state.boardCells[2][0] == player &&
			state.boardCells[1][1] == player &&
			state.boardCells[0][2] == player);
}

Player TicTacToeGame::determineWinner()
{
	Player players[2] = { Player::X, Player::O };
	for (size_t i = 0; i < state.boardCells.size(); i++)
	{
		for each (Player player in players)
		{
			if (isThreeInRow(player, Row(i)))
			{
				return player;
			}
		}
	}

	for (size_t i = 0; i < state.boardCells[0].size(); i++)
	{
		for each (Player player in players)
		{
			if (isThreeInColumn(player, Column(i)))
			{
				return player;
			}
		}
	}

	for each (Player player in players)
	{
		if (isThreeInDiagonal(player))
		{
			return player;
		}
	}

	return Player::None;
}

bool TicTacToeGame::playPiece(Player player, Row row, Column column)
{
	if (player != state.curentPlayer)
	{
		return false;
	}
	char rowIndex = char(row);
	char columnIndex = char(column);
	if (state.boardCells[rowIndex][columnIndex] != Player::None)
	{
		return false;
	}
	state.boardCells[rowIndex][columnIndex] = player;

	nrOfPiecesPlayed++;

	state.winner = determineWinner();
	if (state.winner != Player::None || nrOfPiecesPlayed == 9)
	{
		state.gameFinished = true;
	}

	toggleNextPlayer();
	return true;
}

void TicTacToeGame::reset()
{
	state = BoardState();
	state.curentPlayer = Player::X;
	nrOfPiecesPlayed = 0;
}