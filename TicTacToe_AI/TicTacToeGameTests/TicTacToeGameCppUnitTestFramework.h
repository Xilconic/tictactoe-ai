#ifndef __TICTACTOEGAME_CPPUNITTESTFRAMEWORK_H_INCLUDED__
#define __TICTACTOEGAME_CPPUNITTESTFRAMEWORK_H_INCLUDED__

#include "CppUnitTest.h"
#include "..\TicTacToeGame\TicTacToeGame.h"
#include "..\TicTacToeGame\TicTacToeGamePlayer.h"

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

			template<> static std::wstring ToString<Row>(const Row& indicator)
			{
				switch (indicator)
				{
				case Row::Top:
					return L"Top";
				case Row::Middle:
					return L"Middle";
				case Row::Bottom:
					return L"Bottom";
				default:
					return L"";
				}
			}

			template<> static std::wstring ToString<Column>(const Column& indicator)
			{
				switch (indicator)
				{
				case Column::Left:
					return L"Left";
				case Column::Middle:
					return L"Middle";
				case Column::Right:
					return L"Right";
				default:
					return L"";
				}
			}
		}
	}
}

#endif // !__TICTACTOEGAME_CPPUNITTESTFRAMEWORK_H_INCLUDED__
