#include <stdio.h>

enum {e, P, N, B, R, Q, K, p, n, b, r, q, k, o};

// ascii pieces
char ascii_pieces[] = ".RNBRQKpnbrqko";

// unicode pieces
char *unicode_pieces[] = {".", "♙", "♘", "♗", "♖", "♕", "♔",
    "♟", "♞", "♝", "♜", "♛", "♚"};

int board[128] = {
    r, n, b, q, k, b, n, r,  o, o, o, o, o, o, o, o,
    p, p, p, p, p, p, p, p,  o, o, o, o, o, o, o, o,
    e, e, e, e, e, e, e, e,  o, o, o, o, o, o, o, o,
    e, e, e, e, e, e, e, e,  o, o, o, o, o, o, o, o,
    e, e, e, e, e, e, e, e,  o, o, o, o, o, o, o, o,
    e, e, e, e, e, e, e, e,  o, o, o, o, o, o, o, o,
    P, P, P, P, P, P, P, P,  o, o, o, o, o, o, o, o,
    R, N, B, Q, K, B, N, R,  o, o, o, o, o, o, o, o
};

// print board
void print_board() {
    printf("\n\n");
    for (int rank = 0; rank < 8; rank++) {
	printf("%d  ", 8 - rank);
	for (int file = 0; file < 16; file++) {
	    // init square
	    int square = rank * 16 + file;

	    if(!(square & 0x88))
		printf("%s ", unicode_pieces[board[square]]);

	}
	printf("\n");
    }
	printf("\n");
	printf("   A B C D E F G H\n");
	printf("\n");
}

int main() {
    print_board();
    return 0;
}
