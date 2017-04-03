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
					PlayerIndicator expectedValue = PlayerIndicator::None;
					Assert::AreEqual(expectedValue, state.boardCells.at(i).at(j));
				}
			}

			Assert::AreEqual(PlayerIndicator::None, state.curentPlayer);
			Assert::AreEqual(PlayerIndicator::None, state.winner);
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
					PlayerIndicator expectedValue = PlayerIndicator::None;
					Assert::AreEqual(expectedValue, currentState.boardCells.at(i).at(j));
				}
			}
			Assert::AreEqual(PlayerIndicator::X, currentState.curentPlayer);
			Assert::AreEqual(PlayerIndicator::None, currentState.winner);
		}

		TEST_METHOD(AssertGetCurrentStateReturnsDeepCopy)
		{
			TicTacToeGame game;

			BoardState currentState = game.getCurrentState();

			Assert::AreEqual(PlayerIndicator::X, currentState.curentPlayer);

			currentState.curentPlayer = PlayerIndicator::O;

			BoardState currentState2 = game.getCurrentState();
			Assert::AreEqual(PlayerIndicator::X, currentState2.curentPlayer);
		}

		TEST_METHOD(AssertPlayPieceReturnsFalseWhenPlayingForNone)
		{
			TicTacToeGame game;

			bool isValid = game.playPiece(PlayerIndicator::None, RowIndicator::Middle, ColumnIndicator::Middle);

			Assert::IsFalse(isValid);
		}

		TEST_METHOD(AssertPlayPieceReturnsFalseWhenPlayingForOWhenCurrentPlayerX)
		{
			TicTacToeGame game;

			Assert::AreEqual(PlayerIndicator::X, game.getCurrentState().curentPlayer);

			bool isValid = game.playPiece(PlayerIndicator::O, RowIndicator::Middle, ColumnIndicator::Middle);

			Assert::IsFalse(isValid);
		}

		TEST_METHOD(AssertPlayPieceThrowsExceptionWhenPlayingForXWhenCurrentPlayerO)
		{
			TicTacToeGame game;
			game.playPiece(PlayerIndicator::X, RowIndicator::Middle, ColumnIndicator::Middle);

			Assert::AreEqual(PlayerIndicator::O, game.getCurrentState().curentPlayer);

			bool isValid = game.playPiece(PlayerIndicator::X, RowIndicator::Middle, ColumnIndicator::Middle);

			Assert::IsFalse(isValid);
		}

		TEST_METHOD(AssertPlayPieceReturnsTrueWhenPlayingForCurrentXPlayerToEmptyCell)
		{
			for (char i = 0; i < 3; i++)
			{
				RowIndicator row = RowIndicator(i);
				for (char j = 0; j < 3; j++)
				{
					ColumnIndicator column = ColumnIndicator(j);

					TicTacToeGame game;

					bool isValid = game.playPiece(PlayerIndicator::X, row, column);

					Assert::IsTrue(isValid);

					BoardState state = game.getCurrentState();
					Assert::AreEqual(PlayerIndicator::O, state.curentPlayer);
					Assert::AreEqual(PlayerIndicator::X, state.boardCells[i][j]);
				}
			}
		}

		TEST_METHOD(AssertPlayPieceReturnsFalseWhenPlayingForCurrentOPlayerToAlreadyPlayedCell)
		{
			for (char i = 0; i < 3; i++)
			{
				RowIndicator row = RowIndicator(i);
				for (char j = 0; j < 3; j++)
				{
					ColumnIndicator column = ColumnIndicator(j);

					TicTacToeGame game;

					bool isValid = game.playPiece(PlayerIndicator::X, row, column);

					Assert::IsTrue(isValid);

					isValid = game.playPiece(PlayerIndicator::O, row, column);

					Assert::IsFalse(isValid);

					BoardState state = game.getCurrentState();
					Assert::AreEqual(PlayerIndicator::O, state.curentPlayer);
					Assert::AreEqual(PlayerIndicator::X, state.boardCells[i][j]);
				}
			}
		}
	};
}