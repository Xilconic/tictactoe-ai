#include "stdafx.h"
#include "TicTacToeGameCppUnitTestFramework.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TicTacToeGameTests
{
	TEST_CLASS(TicTacToeGameTests)
	{
	public:

		TEST_METHOD(AssertGameEnvironmentConstructor)
		{
			GamePlayer * xPlayer = 0;
			GamePlayer * oPlayer = 0;

			GameEnvironment environment = GameEnvironment(xPlayer, oPlayer);

			Assert::Fail(L"TODO: define initial state for game environment.");
		}

	};
}
