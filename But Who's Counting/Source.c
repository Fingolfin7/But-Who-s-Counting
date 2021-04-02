#include "stdio.h"
#include "Definitions.h"

int main() {
	AllInit();
	U64 playBitBoard = 0ULL;

	printf("Set square 61: \n");
	SETBIT(playBitBoard, 61);
	PrintBitBoard(playBitBoard);

	printf("Set square 24: \n");
	SETBIT(playBitBoard, 24);
	PrintBitBoard(playBitBoard);

	printf("Clear square 61: \n");
	CLRBIT(playBitBoard, 61);
	PrintBitBoard(playBitBoard);

	return 0;
}