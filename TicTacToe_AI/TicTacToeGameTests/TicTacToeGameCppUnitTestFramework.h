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
				case None:
					return L"None";
				case X:
					return L"X";
				case O:
					return L"O";
				default:
					return L"";
				}
			}
		}
	}
}