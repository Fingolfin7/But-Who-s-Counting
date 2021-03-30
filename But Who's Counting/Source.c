#include "stdio.h"
#include "Definitions.h"

int main() {
	AllInit();
	U64 playBitBoard = 0ULL;

	playBitBoard |= (1ULL << SQ64(D2));
	playBitBoard |= (1ULL << SQ64(D3));
	playBitBoard |= (1ULL << SQ64(D4));

	printf("\n");

	PrintBitBoard(playBitBoard);

	int count = CNT(playBitBoard);

	printf("Count: %d\n", count);

	int index = POP(&playBitBoard);
	printf("Index: %d\n", index);

	PrintBitBoard(playBitBoard);

	count = CNT(playBitBoard);

	printf("Count: %d\n", count);
	return 0;
}