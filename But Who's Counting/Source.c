#include "stdio.h"
#include "Definitions.h"


#define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/pppp1ppp/RNBQKBNR b KQkq e3 0 1"
#define FEN2 "8/2K5/R1P5/4Bk2/1P3P2/5b2/8/2r5 b - - 0 60"
#define FEN3 "r7/p2bb1k1/1pp1p2R/6n1/1PpP2P1/P2p1P2/8/2K5 w - - 3 31"

int main() {
	AllInit();

	S_BOARD board[1];
	
	ParseFen(START_FEN, board);
	PrintBoard(board);

	ParseFen(FEN1, board);
	PrintBoard(board);

	ParseFen(FEN2, board);
	PrintBoard(board);

	ParseFen(FEN3, board);
	PrintBoard(board);

	getchar();

	return 0;
}