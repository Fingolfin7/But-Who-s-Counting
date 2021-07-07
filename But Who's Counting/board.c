//board.c
#include "stdio.h"
#include "Definitions.h"


int ParseFen(char* fen, S_BOARD *pos) {

	ASSERT(fen != NULL);
	ASSERT(pos != NULL);

	int rank = RANK_8;
	int file = FILE_A;
	int piece = 0;
	int count = 0;
	int i = 0;
	int sq64 = 0;
	int sq120 = 0;

	ResetBoard(pos);

	while ((rank >= RANK_1) && *fen) {
		count = 1;
		switch (*fen){
			case 'p': piece = bP; break;
			case 'r': piece = bR; break;
			case 'n': piece = bN; break;
			case 'b': piece = bB; break;
			case 'q': piece = bQ; break;
			case 'k': piece = bK; break;

			case 'P': piece = wP; break;
			case 'R': piece = wR; break;
			case 'N': piece = wN; break;
			case 'B': piece = wB; break;
			case 'Q': piece = wQ; break;
			case 'K': piece = wK; break;
		
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
				piece = Empty;
				count = *fen - '0'; //apparently you can subtract ascii digits like regular ints because the ascii values of 1-9 are actually 1-9

				break;

			case '/':
			case ' ':
				rank--;
				file = FILE_A;
				fen++; //increment pointer to the next character in the string
				continue;

			default:
				printf("FEN Error!\n");
				return -1;
		}

		for (i = 0; i < count; i++) {
			sq64 = rank * 8 + file;
			sq120 = SQ120(sq64);
			if (piece != Empty) {
				pos->pieces[sq120] = piece;
			}
			file++;
		}
		fen++;
	}

	ASSERT(*fen == 'w' || *fen == 'b');

	pos->side = (*fen == 'w') ? WHITE : BLACK;
	fen += 2;

	for (i = 0; i < 4; i++) {
		if (*fen == ' '){
			break;
		}
		switch (*fen){
			case 'K': pos->castlePerm |= WKCA;
			case 'Q': pos->castlePerm |= WQCA;
			case 'k': pos->castlePerm |= BKCA;
			case 'q': pos->castlePerm |= BQCA;
				 
			default: break;
		}
		fen++;
	}
	fen++;

	ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);

	if (*fen != '-') {
		file = fen[0] - 'a';
		rank = fen[1] - '1';

		ASSERT(file >= FILE_A && file <= FILE_H);
		ASSERT(rank >= RANK_1 && rank <= RANK_8);

		pos->enPas = FR2SQ(file, rank);
	}

	pos->posKey = GeneratePosKey(pos);

	return 0;
}

void ResetBoard(S_BOARD* pos) {
	int index = 0;

	for (index = 0; index < BRD_SQ_NUM; index++) {
		pos->pieces[index] = OFFBOARD;
	}

	for (index = 0; index < 64; index++) {
		pos->pieces[SQ120(index)] = Empty;
	}

	for (index = 0; index < 3; index++) {
		pos->bigPce[index] = 0;
		pos->majPce[index] = 0;
		pos->minPce[index] = 0;
		pos->pawns[index] = 0ULL;
	}

	for (index = 0; index < 13; index++) {
		pos->pceNum[index] = 0;
	}

	pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQR;

	pos->side = BOTH;
	pos->enPas = NO_SQR;
	pos->fiftyMove = 0;

	pos->ply = 0;
	pos->hisPly = 0;

	pos->castlePerm = 0;

	pos->posKey = 0ULL;
}

void PrintBoard(const S_BOARD* pos) {
	int sq, file, rank, piece;

	printf("\n Game Board \n");

	for (rank = RANK_8; rank >= RANK_1; rank--) {
		printf("%d   ", rank + 1);
		for (file = FILE_A; file <= FILE_H; file++) {
			sq = FR2SQ(file, rank);
			piece = pos->pieces[sq];
			printf("%3c", PieceChar[piece]);
		}
		printf("\n");
	}

	printf("\n   ");

	for (file = FILE_A; file <= FILE_H; file++) {
		printf("%3c", 'a' + file);
	}
	printf("\n");

	printf("side: %c\n", SideChar[pos->side]);
	printf("enPas: %d\n", pos->enPas);
	printf("castle: %c%c%c%c \n",
			pos->castlePerm & WKCA ? 'K' : '-',
			pos->castlePerm & WQCA ? 'Q' : '-',
			pos->castlePerm & BKCA ? 'k' : '-',
			pos->castlePerm & BQCA ? 'q' : '-'
		);
	printf("Pos key: %llX\n", pos->posKey);


}