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
			Assert::IsFalse(state.gameFinished);
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
			Assert::IsFalse(currentState.gameFinished);
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
			TicTacToeGame game;

			for (char i = 0; i < 3; i++)
			{
				RowIndicator row = RowIndicator(i);
				for (char j = 0; j < 3; j++)
				{
					ColumnIndicator column = ColumnIndicator(j);

					bool isValid = game.playPiece(PlayerIndicator::X, row, column);

					Assert::IsTrue(isValid);

					BoardState state = game.getCurrentState();
					Assert::AreEqual(PlayerIndicator::O, state.curentPlayer);
					Assert::AreEqual(PlayerIndicator::X, state.boardCells[i][j]);
					Assert::IsFalse(state.gameFinished);

					game.reset();
				}
			}
		}

		TEST_METHOD(AssertPlayPieceReturnsFalseWhenPlayingForCurrentOPlayerToAlreadyPlayedCell)
		{
			TicTacToeGame game;

			for (char i = 0; i < 3; i++)
			{
				RowIndicator row = RowIndicator(i);
				for (char j = 0; j < 3; j++)
				{
					ColumnIndicator column = ColumnIndicator(j);

					bool isValid = game.playPiece(PlayerIndicator::X, row, column);

					Assert::IsTrue(isValid);

					isValid = game.playPiece(PlayerIndicator::O, row, column);

					Assert::IsFalse(isValid);

					BoardState state = game.getCurrentState();
					Assert::AreEqual(PlayerIndicator::O, state.curentPlayer);
					Assert::AreEqual(PlayerIndicator::X, state.boardCells[i][j]);

					game.reset();
				}
			}
		}

		TEST_METHOD(AssertPlayPieceUpdatesWinnerXOnWinningRow)
		{
			TicTacToeGame game;

			for (char i = 0; i < 3; i++)
			{
				RowIndicator rowX = RowIndicator(i);
				RowIndicator rowO = i == 0 ? RowIndicator::Middle : RowIndicator::Top;

				game.playPiece(PlayerIndicator::X, rowX, ColumnIndicator::Left);
				game.playPiece(PlayerIndicator::O, rowO, ColumnIndicator::Left);

				game.playPiece(PlayerIndicator::X, rowX, ColumnIndicator::Middle);
				game.playPiece(PlayerIndicator::O, rowO, ColumnIndicator::Middle);

				game.playPiece(PlayerIndicator::X, rowX, ColumnIndicator::Right);

				BoardState state = game.getCurrentState();
				Assert::AreEqual(PlayerIndicator::X, state.winner);
				Assert::IsTrue(state.gameFinished);

				game.reset();
			}
		}

		TEST_METHOD(AssertPlayPieceUpdatesWinnerOOnWinningRow)
		{
			TicTacToeGame game;

			for (char i = 0; i < 3; i++)
			{
				RowIndicator rowX = i == 0 ? RowIndicator::Middle : RowIndicator::Top;
				RowIndicator rowO = RowIndicator(i);

				game.playPiece(PlayerIndicator::X, rowX, ColumnIndicator::Left);
				game.playPiece(PlayerIndicator::O, rowO, ColumnIndicator::Left);

				game.playPiece(PlayerIndicator::X, rowX, ColumnIndicator::Middle);
				game.playPiece(PlayerIndicator::O, rowO, ColumnIndicator::Middle);

				rowX = i == 2 ? RowIndicator::Middle : RowIndicator::Bottom;
				game.playPiece(PlayerIndicator::X, rowX, ColumnIndicator::Left);
				game.playPiece(PlayerIndicator::O, rowO, ColumnIndicator::Right);

				BoardState state = game.getCurrentState();
				Assert::AreEqual(PlayerIndicator::O, state.winner);
				Assert::IsTrue(state.gameFinished);

				game.reset();
			}
		}

		TEST_METHOD(AssertPlayPieceUpdatesWinnerXOnWinningColumn)
		{
			TicTacToeGame game;

			for (char i = 0; i < 3; i++)
			{
				ColumnIndicator colX = ColumnIndicator(i);
				ColumnIndicator colO = i == 0 ? ColumnIndicator::Middle : ColumnIndicator::Left;

				game.playPiece(PlayerIndicator::X, RowIndicator::Top, colX);
				game.playPiece(PlayerIndicator::O, RowIndicator::Top, colO);

				game.playPiece(PlayerIndicator::X, RowIndicator::Middle, colX);
				game.playPiece(PlayerIndicator::O, RowIndicator::Middle, colO);

				game.playPiece(PlayerIndicator::X, RowIndicator::Bottom, colX);

				BoardState state = game.getCurrentState();
				Assert::AreEqual(PlayerIndicator::X, state.winner);
				Assert::IsTrue(state.gameFinished);

				game.reset();
			}
		}

		TEST_METHOD(AssertPlayPieceUpdatesWinnerOOnWinningColumn)
		{
			TicTacToeGame game;

			for (char i = 0; i < 3; i++)
			{
				ColumnIndicator colX = i == 0 ? ColumnIndicator::Middle : ColumnIndicator::Left;
				ColumnIndicator colO = ColumnIndicator(i);

				game.playPiece(PlayerIndicator::X, RowIndicator::Top, colX);
				game.playPiece(PlayerIndicator::O, RowIndicator::Top, colO);

				game.playPiece(PlayerIndicator::X, RowIndicator::Middle, colX);
				game.playPiece(PlayerIndicator::O, RowIndicator::Middle, colO);

				colX = i == 2 ? ColumnIndicator::Middle : ColumnIndicator::Right;
				game.playPiece(PlayerIndicator::X, RowIndicator::Bottom, colX);
				game.playPiece(PlayerIndicator::O, RowIndicator::Bottom, colO);

				BoardState state = game.getCurrentState();
				Assert::AreEqual(PlayerIndicator::O, state.winner);
				Assert::IsTrue(state.gameFinished);

				game.reset();
			}
		}

		TEST_METHOD(AssertPlayPieceUpdatesWinnerXOnWinningDiagonal)
		{
			TicTacToeGame game;

			game.playPiece(PlayerIndicator::X, RowIndicator::Top, ColumnIndicator::Left);
			game.playPiece(PlayerIndicator::O, RowIndicator::Middle, ColumnIndicator::Left);

			game.playPiece(PlayerIndicator::X, RowIndicator::Middle, ColumnIndicator::Middle);
			game.playPiece(PlayerIndicator::O, RowIndicator::Top, ColumnIndicator::Middle);

			game.playPiece(PlayerIndicator::X, RowIndicator::Bottom, ColumnIndicator::Right);

			BoardState state = game.getCurrentState();
			Assert::AreEqual(PlayerIndicator::X, state.winner);
			Assert::IsTrue(state.gameFinished);

			game.reset();

			game.playPiece(PlayerIndicator::X, RowIndicator::Bottom, ColumnIndicator::Left);
			game.playPiece(PlayerIndicator::O, RowIndicator::Middle, ColumnIndicator::Left);

			game.playPiece(PlayerIndicator::X, RowIndicator::Middle, ColumnIndicator::Middle);
			game.playPiece(PlayerIndicator::O, RowIndicator::Middle, ColumnIndicator::Right);

			game.playPiece(PlayerIndicator::X, RowIndicator::Top, ColumnIndicator::Right);

			state = game.getCurrentState();
			Assert::AreEqual(PlayerIndicator::X, state.winner);
			Assert::IsTrue(state.gameFinished);
		}

		TEST_METHOD(AssertPlayPieceUpdatesWinnerOOnWinningDiagonal)
		{
			TicTacToeGame game;

			game.playPiece(PlayerIndicator::X, RowIndicator::Middle, ColumnIndicator::Left);
			game.playPiece(PlayerIndicator::O, RowIndicator::Top, ColumnIndicator::Left);

			game.playPiece(PlayerIndicator::X, RowIndicator::Bottom, ColumnIndicator::Middle);
			game.playPiece(PlayerIndicator::O, RowIndicator::Middle, ColumnIndicator::Middle);

			game.playPiece(PlayerIndicator::X, RowIndicator::Middle, ColumnIndicator::Right);
			game.playPiece(PlayerIndicator::O, RowIndicator::Bottom, ColumnIndicator::Right);

			BoardState state = game.getCurrentState();
			Assert::AreEqual(PlayerIndicator::O, state.winner);
			Assert::IsTrue(state.gameFinished);

			game.reset();

			game.playPiece(PlayerIndicator::X, RowIndicator::Middle, ColumnIndicator::Left);
			game.playPiece(PlayerIndicator::O, RowIndicator::Middle, ColumnIndicator::Middle);

			game.playPiece(PlayerIndicator::X, RowIndicator::Bottom, ColumnIndicator::Middle);
			game.playPiece(PlayerIndicator::O, RowIndicator::Bottom, ColumnIndicator::Left);

			game.playPiece(PlayerIndicator::X, RowIndicator::Middle, ColumnIndicator::Right);
			game.playPiece(PlayerIndicator::O, RowIndicator::Top, ColumnIndicator::Right);

			state = game.getCurrentState();
			Assert::AreEqual(PlayerIndicator::O, state.winner);
			Assert::IsTrue(state.gameFinished);
		}

		TEST_METHOD(AssertPlayPieceUpdatesGameFinishedWhenNoMovesLeft)
		{
			TicTacToeGame game;
			game.playPiece(PlayerIndicator::X, RowIndicator::Top, ColumnIndicator::Left);
			game.playPiece(PlayerIndicator::O, RowIndicator::Top, ColumnIndicator::Middle);

			game.playPiece(PlayerIndicator::X, RowIndicator::Middle, ColumnIndicator::Middle);
			game.playPiece(PlayerIndicator::O, RowIndicator::Top, ColumnIndicator::Right);

			game.playPiece(PlayerIndicator::X, RowIndicator::Middle, ColumnIndicator::Right);
			game.playPiece(PlayerIndicator::O, RowIndicator::Middle, ColumnIndicator::Left);

			game.playPiece(PlayerIndicator::X, RowIndicator::Bottom, ColumnIndicator::Left);
			game.playPiece(PlayerIndicator::O, RowIndicator::Bottom, ColumnIndicator::Right);

			game.playPiece(PlayerIndicator::X, RowIndicator::Bottom, ColumnIndicator::Middle);

			BoardState state = game.getCurrentState();
			Assert::AreEqual(PlayerIndicator::None, state.winner);
			Assert::IsTrue(state.gameFinished);
		}
	};
}