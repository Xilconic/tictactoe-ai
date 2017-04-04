#include "stdafx.h"
#include "TicTacToeGameCppUnitTestFramework.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TicTacToeGamePlayerTests
{
	TEST_CLASS(TicTacToeGamePlayerTests)
	{
	public:

		TEST_METHOD(AssertConstructorForMoveStructure)
		{
			Row row = Row::Top;
			Column column = Column::Right;

			Move move = Move(row, column);

			Assert::AreEqual(row, move.row);
			Assert::AreEqual(column, move.column);
		}
	};
}
