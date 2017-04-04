#ifndef __TICTACTOEGAME_CPPUNITTESTFRAMEWORK_H_INCLUDED__
#define __TICTACTOEGAME_CPPUNITTESTFRAMEWORK_H_INCLUDED__

#include "CppUnitTest.h"
#include "..\TicTacToeGame\TicTacToeGame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> static std::wstring ToString<Player>(const Player& indicator)
			{
				switch (indicator)
				{
				case Player::None:
					return L"None";
				case Player::X:
					return L"X";
				case Player::O:
					return L"O";
				default:
					return L"";
				}
			}
		}
	}
}

#endif // !__TICTACTOEGAME_CPPUNITTESTFRAMEWORK_H_INCLUDED__
