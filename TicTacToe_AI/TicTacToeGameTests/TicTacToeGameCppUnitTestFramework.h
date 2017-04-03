#pragma once
#include "CppUnitTest.h"
#include "..\TicTacToeGame\TicTacToeGame.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> static std::wstring ToString<PlayerIndicator>(const PlayerIndicator& indicator)
			{
				switch (indicator)
				{
				case PlayerIndicator::None:
					return L"None";
				case PlayerIndicator::X:
					return L"X";
				case PlayerIndicator::O:
					return L"O";
				default:
					return L"";
				}
			}
		}
	}
}