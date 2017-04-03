#include "stdafx.h"
#include "TicTacToeGameCppUnitTestFramework.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TicTacToeGameTests
{		
	TEST_CLASS(TicTacToeGameTests)
	{
	public:
		
		TEST_METHOD(AssertDefaultConstructedBoardState)
		{
			BoardState state;

			Assert::AreEqual(3, (int)state.boardCells.size());
			for (size_t i = 0; i < state.boardCells.size(); i++)
			{
				Assert::AreEqual(3, (int)state.boardCells.at(i).size());
				for (size_t j = 0; j < state.boardCells.at(i).size(); j++)
				{
					PlayerIndicator expectedValue = None;
					Assert::AreEqual(expectedValue, state.boardCells.at(i).at(j));
				}
			}

			Assert::AreEqual(None, state.curentPlayer);
			Assert::AreEqual(None, state.winner);
		}

		TEST_METHOD(AssertDefaultConstructorTicTacToeGame)
		{
			TicTacToeGame game;

			BoardState currentState = game.getCurrentState();

			Assert::AreEqual(3, (int)currentState.boardCells.size());
			for (size_t i = 0; i < currentState.boardCells.size(); i++)
			{
				Assert::AreEqual(3, (int)currentState.boardCells.at(i).size());
				for (size_t j = 0; j < currentState.boardCells.at(i).size(); j++)
				{
					PlayerIndicator expectedValue = None;
					Assert::AreEqual(expectedValue, currentState.boardCells.at(i).at(j));
				}
			}
			Assert::AreEqual(X, currentState.curentPlayer);
			Assert::AreEqual(None, currentState.winner);
		}

		TEST_METHOD(AssertGetCurrentStateReturnsDeepCopy)
		{
			TicTacToeGame game;

			BoardState currentState = game.getCurrentState();

			Assert::AreEqual(X, currentState.curentPlayer);

			currentState.curentPlayer = O;

			BoardState currentState2 = game.getCurrentState();
			Assert::AreEqual(X, currentState2.curentPlayer);
		}
	};
}