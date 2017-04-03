#include <array>

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TICTACTOEGAME_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TICTACTOEGAME_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TICTACTOEGAME_EXPORTS
#define TICTACTOEGAME_API __declspec(dllexport)
#else
#define TICTACTOEGAME_API __declspec(dllimport)
#endif

/*
 Denotes the player, if any.
*/
enum TICTACTOEGAME_API PlayerIndicator 
{
	/*
	 Denoted the absense of a player.
	*/
	None,
	/*
	 Denotes the 'X' player.
	*/
	X,
	/*
	 Denotes the 'O' player.
	*/
	O 
};

/*
 Class holding the state of a game of TicTacToe.
*/
struct TICTACTOEGAME_API BoardState 
{
	/*
	 The state of the 3x3 game board, indicating where players have played their pieces.
	*/
	std::array<std::array<PlayerIndicator, 3>, 3> boardCells = 
	{
		{
			{{ None, None, None }},
			{{ None, None, None }},
			{{ None, None, None }}
		}
	};

	/*
	 Indicates the player whose turn it it.
	*/
	PlayerIndicator curentPlayer = None;

	/*
	 Indicates the winner of the game.
	*/
	PlayerIndicator winner = None;
};

/*
 The tic-tac-toe game engine.
*/
class TICTACTOEGAME_API TicTacToeGame {
private:
	BoardState state;
public:
	/*
	 Initializes a game of tic-tac-toe.
	*/
	TicTacToeGame(void);

	/*
	 Gets the curent board state.
	*/
	BoardState getCurrentState(void);
};
