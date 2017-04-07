#include "stdafx.h"
#include "TicTacToeGameCppUnitTestFramework.h"
#include <queue>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TicTacToeGameTests
{
	/*
	 Implementation of GamePlayer that replays moves from a given queue.
	*/
	class PreprogrammedPlayer: public GamePlayer
	{
	private:
		std::queue<Move>& replayQueue;

	public:
		PreprogrammedPlayer(std::queue<Move> & queue) : replayQueue(queue) {};
		Move getMove(const BoardState & gamestate)
		{
			Move moveToPlay = replayQueue.front();
			replayQueue.pop();
			return moveToPlay;
		}
	};

	TEST_CLASS(TicTacToeGameTests)
	{
	public:

		TEST_METHOD(AcceptanceTestThatGameEnvironmentCanPlayGameOfTicTacToe)
		{
			std::queue<Move> xMoves;
			xMoves.push(Move(Row::Top, Column::Right));
			xMoves.push(Move(Row::Middle, Column::Right));
			xMoves.push(Move(Row::Bottom, Column::Right));

			std::queue<Move> yMoves;
			yMoves.push(Move(Row::Top, Column::Left));
			yMoves.push(Move(Row::Middle, Column::Left));
			yMoves.push(Move(Row::Bottom, Column::Right));

			GamePlayer * xPlayer = &PreprogrammedPlayer(xMoves);
			GamePlayer * oPlayer = &PreprogrammedPlayer(yMoves);

			GameEnvironment environment = GameEnvironment(*xPlayer, *oPlayer);
			environment.playGame();
		}

	};
}
