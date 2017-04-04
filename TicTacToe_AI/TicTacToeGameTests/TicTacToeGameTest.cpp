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
					Player expectedValue = Player::None;
					Assert::AreEqual(expectedValue, state.boardCells.at(i).at(j));
				}
			}

			Assert::AreEqual(Player::None, state.curentPlayer);
			Assert::AreEqual(Player::None, state.winner);
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
					Player expectedValue = Player::None;
					Assert::AreEqual(expectedValue, currentState.boardCells.at(i).at(j));
				}
			}
			Assert::AreEqual(Player::X, currentState.curentPlayer);
			Assert::AreEqual(Player::None, currentState.winner);
			Assert::IsFalse(currentState.gameFinished);
		}

		TEST_METHOD(AssertGetCurrentStateReturnsDeepCopy)
		{
			TicTacToeGame game;

			BoardState currentState = game.getCurrentState();

			Assert::AreEqual(Player::X, currentState.curentPlayer);

			currentState.curentPlayer = Player::O;

			BoardState currentState2 = game.getCurrentState();
			Assert::AreEqual(Player::X, currentState2.curentPlayer);
		}

		TEST_METHOD(AssertPlayPieceReturnsFalseWhenPlayingForNone)
		{
			TicTacToeGame game;

			bool isValid = game.playPiece(Player::None, Row::Middle, Column::Middle);

			Assert::IsFalse(isValid);
		}

		TEST_METHOD(AssertPlayPieceReturnsFalseWhenPlayingForOWhenCurrentPlayerX)
		{
			TicTacToeGame game;

			Assert::AreEqual(Player::X, game.getCurrentState().curentPlayer);

			bool isValid = game.playPiece(Player::O, Row::Middle, Column::Middle);

			Assert::IsFalse(isValid);
		}

		TEST_METHOD(AssertPlayPieceThrowsExceptionWhenPlayingForXWhenCurrentPlayerO)
		{
			TicTacToeGame game;
			game.playPiece(Player::X, Row::Middle, Column::Middle);

			Assert::AreEqual(Player::O, game.getCurrentState().curentPlayer);

			bool isValid = game.playPiece(Player::X, Row::Middle, Column::Middle);

			Assert::IsFalse(isValid);
		}

		TEST_METHOD(AssertPlayPieceReturnsTrueWhenPlayingForCurrentXPlayerToEmptyCell)
		{
			TicTacToeGame game;

			for (char i = 0; i < 3; i++)
			{
				Row row = Row(i);
				for (char j = 0; j < 3; j++)
				{
					Column column = Column(j);

					bool isValid = game.playPiece(Player::X, row, column);

					Assert::IsTrue(isValid);

					BoardState state = game.getCurrentState();
					Assert::AreEqual(Player::O, state.curentPlayer);
					Assert::AreEqual(Player::X, state.boardCells[i][j]);
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
				Row row = Row(i);
				for (char j = 0; j < 3; j++)
				{
					Column column = Column(j);

					bool isValid = game.playPiece(Player::X, row, column);

					Assert::IsTrue(isValid);

					isValid = game.playPiece(Player::O, row, column);

					Assert::IsFalse(isValid);

					BoardState state = game.getCurrentState();
					Assert::AreEqual(Player::O, state.curentPlayer);
					Assert::AreEqual(Player::X, state.boardCells[i][j]);

					game.reset();
				}
			}
		}

		TEST_METHOD(AssertPlayPieceUpdatesWinnerXOnWinningRow)
		{
			TicTacToeGame game;

			for (char i = 0; i < 3; i++)
			{
				Row rowX = Row(i);
				Row rowO = i == 0 ? Row::Middle : Row::Top;

				game.playPiece(Player::X, rowX, Column::Left);
				game.playPiece(Player::O, rowO, Column::Left);

				game.playPiece(Player::X, rowX, Column::Middle);
				game.playPiece(Player::O, rowO, Column::Middle);

				game.playPiece(Player::X, rowX, Column::Right);

				BoardState state = game.getCurrentState();
				Assert::AreEqual(Player::X, state.winner);
				Assert::IsTrue(state.gameFinished);

				game.reset();
			}
		}

		TEST_METHOD(AssertPlayPieceUpdatesWinnerOOnWinningRow)
		{
			TicTacToeGame game;

			for (char i = 0; i < 3; i++)
			{
				Row rowX = i == 0 ? Row::Middle : Row::Top;
				Row rowO = Row(i);

				game.playPiece(Player::X, rowX, Column::Left);
				game.playPiece(Player::O, rowO, Column::Left);

				game.playPiece(Player::X, rowX, Column::Middle);
				game.playPiece(Player::O, rowO, Column::Middle);

				rowX = i == 2 ? Row::Middle : Row::Bottom;
				game.playPiece(Player::X, rowX, Column::Left);
				game.playPiece(Player::O, rowO, Column::Right);

				BoardState state = game.getCurrentState();
				Assert::AreEqual(Player::O, state.winner);
				Assert::IsTrue(state.gameFinished);

				game.reset();
			}
		}

		TEST_METHOD(AssertPlayPieceUpdatesWinnerXOnWinningColumn)
		{
			TicTacToeGame game;

			for (char i = 0; i < 3; i++)
			{
				Column colX = Column(i);
				Column colO = i == 0 ? Column::Middle : Column::Left;

				game.playPiece(Player::X, Row::Top, colX);
				game.playPiece(Player::O, Row::Top, colO);

				game.playPiece(Player::X, Row::Middle, colX);
				game.playPiece(Player::O, Row::Middle, colO);

				game.playPiece(Player::X, Row::Bottom, colX);

				BoardState state = game.getCurrentState();
				Assert::AreEqual(Player::X, state.winner);
				Assert::IsTrue(state.gameFinished);

				game.reset();
			}
		}

		TEST_METHOD(AssertPlayPieceUpdatesWinnerOOnWinningColumn)
		{
			TicTacToeGame game;

			for (char i = 0; i < 3; i++)
			{
				Column colX = i == 0 ? Column::Middle : Column::Left;
				Column colO = Column(i);

				game.playPiece(Player::X, Row::Top, colX);
				game.playPiece(Player::O, Row::Top, colO);

				game.playPiece(Player::X, Row::Middle, colX);
				game.playPiece(Player::O, Row::Middle, colO);

				colX = i == 2 ? Column::Middle : Column::Right;
				game.playPiece(Player::X, Row::Bottom, colX);
				game.playPiece(Player::O, Row::Bottom, colO);

				BoardState state = game.getCurrentState();
				Assert::AreEqual(Player::O, state.winner);
				Assert::IsTrue(state.gameFinished);

				game.reset();
			}
		}

		TEST_METHOD(AssertPlayPieceUpdatesWinnerXOnWinningDiagonal)
		{
			TicTacToeGame game;

			game.playPiece(Player::X, Row::Top, Column::Left);
			game.playPiece(Player::O, Row::Middle, Column::Left);

			game.playPiece(Player::X, Row::Middle, Column::Middle);
			game.playPiece(Player::O, Row::Top, Column::Middle);

			game.playPiece(Player::X, Row::Bottom, Column::Right);

			BoardState state = game.getCurrentState();
			Assert::AreEqual(Player::X, state.winner);
			Assert::IsTrue(state.gameFinished);

			game.reset();

			game.playPiece(Player::X, Row::Bottom, Column::Left);
			game.playPiece(Player::O, Row::Middle, Column::Left);

			game.playPiece(Player::X, Row::Middle, Column::Middle);
			game.playPiece(Player::O, Row::Middle, Column::Right);

			game.playPiece(Player::X, Row::Top, Column::Right);

			state = game.getCurrentState();
			Assert::AreEqual(Player::X, state.winner);
			Assert::IsTrue(state.gameFinished);
		}

		TEST_METHOD(AssertPlayPieceUpdatesWinnerOOnWinningDiagonal)
		{
			TicTacToeGame game;

			game.playPiece(Player::X, Row::Middle, Column::Left);
			game.playPiece(Player::O, Row::Top, Column::Left);

			game.playPiece(Player::X, Row::Bottom, Column::Middle);
			game.playPiece(Player::O, Row::Middle, Column::Middle);

			game.playPiece(Player::X, Row::Middle, Column::Right);
			game.playPiece(Player::O, Row::Bottom, Column::Right);

			BoardState state = game.getCurrentState();
			Assert::AreEqual(Player::O, state.winner);
			Assert::IsTrue(state.gameFinished);

			game.reset();

			game.playPiece(Player::X, Row::Middle, Column::Left);
			game.playPiece(Player::O, Row::Middle, Column::Middle);

			game.playPiece(Player::X, Row::Bottom, Column::Middle);
			game.playPiece(Player::O, Row::Bottom, Column::Left);

			game.playPiece(Player::X, Row::Middle, Column::Right);
			game.playPiece(Player::O, Row::Top, Column::Right);

			state = game.getCurrentState();
			Assert::AreEqual(Player::O, state.winner);
			Assert::IsTrue(state.gameFinished);
		}

		TEST_METHOD(AssertPlayPieceUpdatesGameFinishedWhenNoMovesLeft)
		{
			TicTacToeGame game;
			game.playPiece(Player::X, Row::Top, Column::Left);
			game.playPiece(Player::O, Row::Top, Column::Middle);

			game.playPiece(Player::X, Row::Middle, Column::Middle);
			game.playPiece(Player::O, Row::Top, Column::Right);

			game.playPiece(Player::X, Row::Middle, Column::Right);
			game.playPiece(Player::O, Row::Middle, Column::Left);

			game.playPiece(Player::X, Row::Bottom, Column::Left);
			game.playPiece(Player::O, Row::Bottom, Column::Right);

			game.playPiece(Player::X, Row::Bottom, Column::Middle);

			BoardState state = game.getCurrentState();
			Assert::AreEqual(Player::None, state.winner);
			Assert::IsTrue(state.gameFinished);
		}
	};
}