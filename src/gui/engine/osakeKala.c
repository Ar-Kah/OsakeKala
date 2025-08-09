#include <stdio.h>
#include <ctype.h>

// FEN debug positions
char start_position[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
char tricky_position[] = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";

enum {e, P, N, B, R, Q, K, p, n, b, r, q, k, o};

enum side { white, black};

// square encoding
enum square {
    a8 = 0, b8, c8, d8, e8, f8, g8, h8,
    a7 = 16, b7, c7, d7, e7, f7, g7, h7,
    a6 = 32, b6, c6, d6, e6, f6, g6, h6,
    a5 = 48, b5, c5, d5, e5, f5, g5, h5,
    a4 = 64, b4, c4, d4, e4, f4, g4, h4,
    a3 = 80, b3, c3, d3, e3, f3, g3, h3,
    a2 = 96, b2, c2, d2, e2, f2, g2, h2,
    a1 = 112, b1, c1, d1, e1, f1, g1, h1, no_sq
};

// castling rights (15 dec => 1111 => both side can castle to both sides)
int castle = 15;

enum castling {
    KC = 1, QC = 2, kc = 4, qc = 8
};

// ascii pieces
char ascii_pieces[] = ".RNBRQKpnbrqko";

// unicode pieces
char *unicode_pieces[] = {".", "♟", "♞", "♝", "♜", "♛", "♚", "♙", "♘", "♗", "♖", "♕", "♔" };

// board initialization with in- and out-squares
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

// side to move
int side = white;

// castling rights

// en passant square
int enpassant = no_sq;

// convert board square indexes to coordinates
char *square_to_coords[] = {
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", "i8", "j8", "k8", "l8", "m8", "n8", "o8", "p8",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", "i7", "j7", "k7", "l7", "m7", "n7", "o7", "p7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", "i6", "j6", "k6", "l6", "m6", "n6", "o6", "p6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "i5", "j5", "k5", "l5", "m5", "n5", "o5", "p5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "i4", "j4", "k4", "l4", "m4", "n4", "o4", "p4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "i3", "j3", "k3", "l3", "m3", "n3", "o3", "p3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "i2", "j2", "k2", "l2", "m2", "n2", "o2", "p2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "i1", "j1", "k1", "l1", "m1", "n1", "o1", "p1",
};

// encode ascii pieces
int char_pieces[] = {
    ['P'] = P,
    ['N'] = N,
    ['B'] = B,
    ['R'] = R,
    ['Q'] = Q,
    ['K'] = K,
    ['p'] = p,
    ['n'] = n,
    ['b'] = b,
    ['r'] = r,
    ['q'] = q,
    ['k'] = k,
};

// reset board function
void reset_board() {
    // loop over board ranks
    for (int rank = 0; rank < 8; rank++) {

        // loop over board files
        for (int file = 0; file < 16; file++) {

            // init square
            int square = rank * 16 + file;

            // if square is on board
            if(!(square & 0x88))
                // reset curretn board to empty
                board[square] = e;
       	}
    }
    // reset stats
    side = -1;
    castle = 0;
    enpassant = no_sq;
};

// parse FEN
void parse_fen(char *fen) {
    // reset board
    reset_board();

    // loop over board ranks
    for (int rank = 0; rank < 8; rank++) {

        // loop over board files
        for (int file = 0; file < 16; file++) {

            // init square
            int square = rank * 16 + file;

            // if square is on board
            if(!(square & 0x88))
                {
	       
                    if (isalpha(*fen)) {
                        // set the piece on board
                        board[square] = char_pieces[*fen];

                        // increment FEN pointer
                        fen++;
                    }
                    // match empty squares
                    if (isdigit(*fen)) {
                        // calculate ofset
                        int offset = *fen - '0';

                        //decrement file on empty square
                        if (!(board[square]))
                            file--;

                        // skip empty square
                        file += offset;
		    
                        // increment FEN pointer
                        fen++;
                    }

                    // match end of rank
                    if (*fen == '/')
                        fen++;
                }
       	}
    }
    //increment FEN
    fen++;

    // parse side to move
    side = *fen == 'w' ? white : black;

    // go to castling rights parsing
    fen += 2;

    // parse castling rights
    while (*fen != ' ')
        {

            switch(*fen) {
            case 'K':
                castle |= KC;
                break;
            case 'Q':
                castle |= QC;
                break;
            case 'k':
                castle |= kc;
                break;
            case 'q':
                castle |= qc;
                break;
            case '-':
                break;
            }

            // increment fen
            fen++;
        }
    // goto to enpassant square
    fen++;

    // parse enpassant square
    if (*fen != '-'){
        int file = fen[0] - 'a';
        int rank = 8 - (fen[1] - '0');

        // set up enpassant square
        enpassant = rank * 16 + file;
    }
    else {
        enpassant = no_sq;
    }
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

	printf("---------------\n");
	printf("Side: %s\n", (side == white) ? "white" : "black");
    printf("Castling: %c%c%c%c\n", (castle & KC) ? 'K' : '-',
	       (castle & QC) ? 'Q' : '-',
	       (castle & kc) ? 'k' : '-',
	       (castle & qc) ? 'q' : '-');

	printf("Enpassant: %s\n\n", square_to_coords[enpassant]);
}

int main() {

    parse_fen("8/8/8/3N4/8/8/8/8 w KQkq e3 0 1");
    print_board();
    return 0;
}
