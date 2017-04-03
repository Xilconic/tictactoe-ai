// TicTacToeGame.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "TicTacToeGame.h"

TicTacToeGame::TicTacToeGame()
{
	state.curentPlayer = X;
    return;
}

BoardState TicTacToeGame::getCurrentState()
{
	return state;
}
