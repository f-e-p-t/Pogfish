#include<iostream>
#include<cmath>
#include<string>
using namespace std;

int tempo = 1;
int move_move = 1;
bool isLegalMove;
bool KSCastlingRights_white = true;
bool QSCastlingRights_white = true;
bool KSCastlingRights_black = true;
bool QSCastlingRights_black = true;

int wkp_y;
int wkp_x;
int bkp_y;
int bkp_x;

int move_y;
int move_x;
int moveTo_y;
int moveTo_x;

const int empty_square = 0;
const int white_pawn = 1;
const int white_knight = 2;
const int white_bishop = 3;
const int white_rook = 4;
const int white_queen = 5;
const int white_king = 6;
const int black_pawn = 11;
const int black_knight = 12;
const int black_bishop = 13;
const int black_rook = 14;
const int black_queen = 15;
const int black_king = 16;

int n;
int depth;
int TEST;

double value(int piece){
    double pieceValue;
    switch(piece){
        case 1:
            pieceValue = 1;
            break;
        case 2:
            pieceValue = 3;
            break;
        case 3:
            pieceValue = 3;
            break;
        case 4:
            pieceValue = 5;
            break;
        case 5:
            pieceValue = 9;
            break;
        case 6:
            pieceValue = 0;
            break;
        case 11:
            pieceValue = 1;
            break;
        case 12:
            pieceValue = 3;
            break;
        case 13:
            pieceValue = 3;
            break;
        case 14:
            pieceValue = 5;
            break;
        case 15:
            pieceValue = 9;
            break;
        case 16:
            pieceValue = 0;
        default:
            pieceValue = 0;
    }
    return pieceValue;
}

string FEN = "rnbqkbnrppppppppooooooooooooooooooooooooooooooooPPPPPPPPRNBQKBNR";

int chessBoard[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

int chessBoard_CC[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

int boardStates[50][8][8];
int depthProgress[50];
int moveList[4][218];
int clearMoveList[4][218];

// ----------------------------------------------------------------------- Rules of chess -----------------------------------------------------------------------

void playMove_CC(){
    if(chessBoard_CC[move_y][move_x] == white_king && move_y == 7 && move_x == 4 && moveTo_y == 7 && moveTo_x == 6){
        chessBoard_CC[7][7] = empty_square;
        chessBoard_CC[7][5] = white_rook;
    } else if(chessBoard_CC[move_y][move_x] == white_king && move_y == 7 && move_x == 4 && moveTo_y == 7 && moveTo_x == 2){
        chessBoard_CC[7][0] = empty_square;
        chessBoard_CC[7][3] = white_rook;
    } else if(chessBoard_CC[move_y][move_x] == black_king && move_y == 0 && move_x == 4 && moveTo_y == 0 && moveTo_x == 6){
        chessBoard_CC[0][7] = empty_square;
        chessBoard_CC[0][5] = black_rook;
    } else if(chessBoard_CC[move_y][move_x] == black_king && move_y == 0 && move_x == 4 && moveTo_y == 0 && moveTo_x == 2){
        chessBoard_CC[0][0] = empty_square;
        chessBoard_CC[0][3] = black_rook;
    } else{
    }
    chessBoard_CC[moveTo_y][moveTo_x] = chessBoard_CC[move_y][move_x];
    chessBoard_CC[move_y][move_x] = empty_square;
}

void getKingPos_white(){
    for(int y = 0; y <= 7; y++){
        for(int x = 0; x <= 7; x++){
            if(chessBoard_CC[y][x] == white_king){
                wkp_y = y;
                wkp_x = x;
                break;
            }
        }
    }
}
void getKingPos_black(){
    for(int y = 0; y <= 7; y++){
        for(int x = 0; x <= 7; x++){
            if(chessBoard_CC[y][x] == black_king){
                bkp_y = y;
                bkp_x = x;
                break;
            }
        }
    }
}
bool check_white(){
    getKingPos_white();
    for(int cs = 1; cs < 8; cs++){ // down & right
        if(wkp_y + cs > 7 || wkp_x + cs > 7){
            break;
        } else if(chessBoard_CC[wkp_y + cs][wkp_x + cs] == black_bishop || chessBoard_CC[wkp_y + cs][wkp_x + cs] == black_queen){
            return true;
        } else if(chessBoard_CC[wkp_y + cs][wkp_x + cs] >= 1 && chessBoard_CC[wkp_y + cs][wkp_x + cs] != black_bishop && chessBoard_CC[wkp_y + cs][wkp_x + cs] != black_queen){
            break;
        } else{
        }
    }
    for(int cs = 1; cs < 8; cs++){ // down & left
        if(wkp_y + cs > 7 || wkp_x - cs < 0){
            break;
        } else if(chessBoard_CC[wkp_y + cs][wkp_x - cs] == black_bishop || chessBoard_CC[wkp_y + cs][wkp_x - cs] == black_queen){
            return true;
        } else if(chessBoard_CC[wkp_y + cs][wkp_x - cs] >= 1 && chessBoard_CC[wkp_y + cs][wkp_x - cs] != black_bishop && chessBoard_CC[wkp_y + cs][wkp_x - cs] != black_queen){
            break;
        } else{
        }
    }
    for(int cs = 1; cs < 8; cs++){ // up & left
        if(wkp_y - cs < 0 || wkp_x - cs < 0){
            break;
        } else if(chessBoard_CC[wkp_y - cs][wkp_x - cs] == black_bishop || chessBoard_CC[wkp_y - cs][wkp_x - cs] == black_queen){
            return true;
        } else if(chessBoard_CC[wkp_y - cs][wkp_x - cs] >= 1 && chessBoard_CC[wkp_y - cs][wkp_x - cs] != black_bishop && chessBoard_CC[wkp_y - cs][wkp_x - cs] != black_queen){
            break;
        } else{
        }
    }
    for(int cs = 1; cs < 8; cs++){ // up & right
        if(wkp_y - cs < 0 || wkp_x + cs > 7){
            break;
        } else if(chessBoard_CC[wkp_y - cs][wkp_x + cs] == black_bishop || chessBoard_CC[wkp_y - cs][wkp_x + cs] == black_queen){
            return true;
        } else if(chessBoard_CC[wkp_y - cs][wkp_x + cs] >= 1 && chessBoard_CC[wkp_y - cs][wkp_x + cs] != black_bishop && chessBoard_CC[wkp_y - cs][wkp_x + cs] != black_queen){
            break;
        } else{
        }
    }
    for(int cs = 1; cs < 8; cs++){ // down
        if(wkp_y + cs > 7){
            break;
        } else if(chessBoard_CC[wkp_y + cs][wkp_x] == black_rook || chessBoard_CC[wkp_y + cs][wkp_x] == black_queen){
            return true;
        } else if(chessBoard_CC[wkp_y + cs][wkp_x] >= 1 && chessBoard_CC[wkp_y + cs][wkp_x] != black_rook && chessBoard_CC[wkp_y + cs][wkp_x] != black_queen){
            break;
        } else{
        }
    }
    for(int cs = 1; cs < 8; cs++){ // left
        if(wkp_x - cs < 0){
            break;
        } else if(chessBoard_CC[wkp_y][wkp_x - cs] == black_rook || chessBoard_CC[wkp_y][wkp_x - cs] == black_queen){
            return true;
        } else if(chessBoard_CC[wkp_y][wkp_x - cs] >= 1 && chessBoard_CC[wkp_y][wkp_x - cs] != black_rook && chessBoard_CC[wkp_y][wkp_x - cs] != black_queen){
            break;
        } else{
        }
    }
    for(int cs = 1; cs < 8; cs++){ // up
        if(wkp_y - cs < 0){
            break;
        } else if(chessBoard_CC[wkp_y - cs][wkp_x] == black_rook || chessBoard_CC[wkp_y - cs][wkp_x] == black_queen){
            return true;
        } else if(chessBoard_CC[wkp_y - cs][wkp_x] >= 1 && chessBoard_CC[wkp_y - cs][wkp_x] != black_rook && chessBoard_CC[wkp_y - cs][wkp_x] != black_queen){
            break;
        } else{
        }
    }
    for(int cs = 1; cs < 8; cs++){ // right
        if(wkp_x + cs > 7){
            break;
        } else if(chessBoard_CC[wkp_y][wkp_x + cs] == black_rook || chessBoard_CC[wkp_y][wkp_x + cs] == black_queen){
            return true;
        } else if(chessBoard_CC[wkp_y][wkp_x + cs] >= 1 && chessBoard_CC[wkp_y][wkp_x + cs] != black_rook && chessBoard_CC[wkp_y][wkp_x + cs] != black_queen){
            break;
        } else{
        }
    }
    if(chessBoard_CC[wkp_y + 1][wkp_x + 2] == black_knight && wkp_y + 1 <= 7 && wkp_x + 2 <= 7){ // knight checks ~
        return true;
    } else if(chessBoard_CC[wkp_y + 1][wkp_x - 2] == black_knight && wkp_y + 1 <= 7 && wkp_x - 2 >= 0){
        return true;
    } else if(chessBoard_CC[wkp_y - 1][wkp_x + 2] == black_knight && wkp_y - 1 >= 0 && wkp_x + 2 <= 7){
        return true;
    } else if(chessBoard_CC[wkp_y - 1][wkp_x - 2] == black_knight && wkp_y - 1 >= 0 && wkp_x - 2 >= 0){
        return true;
    } else if(chessBoard_CC[wkp_y + 2][wkp_x + 1] == black_knight && wkp_y + 2 <= 7 && wkp_x + 1 <= 7){
        return true;
    } else if(chessBoard_CC[wkp_y + 2][wkp_x - 1] == black_knight && wkp_y + 2 <= 7 && wkp_x - 1 >= 0){
        return true;
    } else if(chessBoard_CC[wkp_y - 2][wkp_x + 1] == black_knight && wkp_y - 2 >= 0 && wkp_x + 1 <= 7){
        return true;
    } else if(chessBoard_CC[wkp_y - 2][wkp_x - 1] == black_knight && wkp_y - 2 >= 0 && wkp_x - 1 >= 0){
        return true;
    } else if(chessBoard_CC[wkp_y - 1][wkp_x + 1] == black_pawn && wkp_y - 1 >= 0 && wkp_x + 1 <= 7){ // pawn checks ~
        return true;
    } else if(chessBoard_CC[wkp_y - 1][wkp_x - 1] == black_pawn && wkp_y - 1 >= 0 && wkp_x - 1 >= 0){
        return true;
    } else if(chessBoard_CC[wkp_y + 1][wkp_x + 1] == black_king && wkp_y + 1 <= 7 && wkp_x + 1 <= 7){ // king 'checks' ~
        return true;
    } else if(chessBoard_CC[wkp_y + 1][wkp_x - 1] == black_king && wkp_y + 1 <= 7 && wkp_x - 1 >= 0){
        return true;
    } else if(chessBoard_CC[wkp_y - 1][wkp_x + 1] == black_king && wkp_y - 1 >= 0 && wkp_x + 1 <= 7){
        return true;
    } else if(chessBoard_CC[wkp_y - 1][wkp_x - 1] == black_king && wkp_y - 1 >= 0 && wkp_x - 1 >= 0){
        return true;
    } else if(chessBoard_CC[wkp_y + 1][wkp_x] == black_king && wkp_y + 1 <= 7){
        return true;
    } else if(chessBoard_CC[wkp_y][wkp_x - 1] == black_king && wkp_x - 1 >= 0){
        return true;
    } else if(chessBoard_CC[wkp_y - 1][wkp_x] == black_king && wkp_y - 1 >= 0){
        return true;
    } else if(chessBoard_CC[wkp_y][wkp_x + 1] == black_king && wkp_x + 1 <= 7){
        return true;
    } else{
    }
    return false;
}
bool check_black(){
    getKingPos_black();
    for(int cs = 1; cs < 8; cs++){ // down & right
        if(bkp_y + cs > 7 || bkp_x + cs > 7){
            break;    
        } else if(chessBoard_CC[bkp_y + cs][bkp_x + cs] == white_bishop || chessBoard_CC[bkp_y + cs][bkp_x + cs] == white_queen){
            return true;
        } else if(chessBoard_CC[bkp_y + cs][bkp_x + cs] >= 1 && chessBoard_CC[bkp_y + cs][bkp_x + cs] != white_bishop && chessBoard_CC[bkp_y + cs][bkp_x + cs] != white_queen){
            break;
        } else{
        }
    }
    for(int cs = 1; cs < 8; cs++){ // down & left
        if(bkp_y + cs > 7 || bkp_x - cs < 0){
            break;
        } else if(chessBoard_CC[bkp_y + cs][bkp_x - cs] == white_bishop || chessBoard_CC[bkp_y + cs][bkp_x - cs] == white_queen){
            return true;
        } else if(chessBoard_CC[bkp_y + cs][bkp_x - cs] >= 1 && chessBoard_CC[bkp_y + cs][bkp_x - cs] != white_bishop && chessBoard_CC[bkp_y + cs][bkp_x - cs] != white_queen){
            break;
        } else{
        }
    }
    for(int cs = 1; cs < 8; cs++){ // up & left
        if(bkp_y - cs < 0 || bkp_x - cs < 0){
            break;   
        } else if(chessBoard_CC[bkp_y - cs][bkp_x - cs] == white_bishop || chessBoard_CC[bkp_y - cs][bkp_x - cs] == white_queen){
            return true;
        } else if(chessBoard_CC[bkp_y - cs][bkp_x - cs] >= 1 && chessBoard_CC[bkp_y - cs][bkp_x - cs] != white_bishop && chessBoard_CC[bkp_y - cs][bkp_x - cs] != white_queen){
            break;
        } else{
        }
    }
    for(int cs = 1; cs < 8; cs++){ // up & right
        if(bkp_y - cs < 0 || bkp_x + cs > 7){
            break;   
        } else if(chessBoard_CC[bkp_y - cs][bkp_x + cs] == white_bishop || chessBoard_CC[bkp_y - cs][bkp_x + cs] == white_queen){
            return true;
        } else if(chessBoard_CC[bkp_y - cs][bkp_x + cs] >= 1 && chessBoard_CC[bkp_y - cs][bkp_x + cs] != white_bishop && chessBoard_CC[bkp_y - cs][bkp_x + cs] != white_queen){
            break;
        } else{
        }
    }
    for(int cs = 1; cs < 8; cs++){ // down
        if(bkp_x + cs > 7){
            break;
        } else if(chessBoard_CC[bkp_y + cs][bkp_x] == white_rook || chessBoard_CC[bkp_y + cs][bkp_x] == white_queen){
            return true;
        } else if(chessBoard_CC[bkp_y + cs][bkp_x] >= 1 && chessBoard_CC[bkp_y + cs][bkp_x] != white_rook && chessBoard_CC[bkp_y + cs][bkp_x] != white_queen){
            break;
        } else{
        }
    }
    for(int cs = 1; cs < 8; cs++){ // left
        if(bkp_x - cs < 0){
            break;
        } else if(chessBoard_CC[bkp_y][bkp_x - cs] == white_rook || chessBoard_CC[bkp_y][bkp_x - cs] == white_queen){
            return true;
        } else if(chessBoard_CC[bkp_y][bkp_x - cs] >= 1 && chessBoard_CC[bkp_y][bkp_x - cs] != white_rook && chessBoard_CC[bkp_y][bkp_x - cs] != white_queen){
            break;
        } else{
        }
    }
    for(int cs = 1; cs < 8; cs++){ // up
        if(bkp_y - cs < 0){
            break;
        } else if(chessBoard_CC[bkp_y - cs][bkp_x] == white_rook || chessBoard_CC[bkp_y - cs][bkp_x] == white_queen){
            return true;
        } else if(chessBoard_CC[bkp_y - cs][bkp_x] >= 1 && chessBoard_CC[bkp_y - cs][bkp_x] != white_rook && chessBoard_CC[bkp_y - cs][bkp_x] != white_queen){
            break;
        } else{
        }
    }
    for(int cs = 1; cs < 8; cs++){ // right
        if(bkp_x + cs > 7){
            break;
        } else if(chessBoard_CC[bkp_y][bkp_x + cs] == white_rook || chessBoard_CC[bkp_y][bkp_x + cs] == white_queen){
            return true;
        } else if(chessBoard_CC[bkp_y][bkp_x + cs] >= 1 && chessBoard_CC[bkp_y][bkp_x + cs] != white_rook && chessBoard_CC[bkp_y][bkp_x + cs] != white_queen){
            break;
        } else{
        }
    }
    if(chessBoard_CC[bkp_y + 1][bkp_x + 2] == white_knight && bkp_y + 1 <= 7 && bkp_x + 2 <= 7){ // knight checks ~
        return true;
    } else if(chessBoard_CC[bkp_y + 1][bkp_x - 2] == white_knight && bkp_y + 1 <= 7 && bkp_x - 2 >= 0){
        return true;
    } else if(chessBoard_CC[bkp_y - 1][bkp_x + 2] == white_knight && bkp_y - 1 >= 0 && bkp_x + 2 <= 7){
        return true;
    } else if(chessBoard_CC[bkp_y - 1][bkp_x - 2] == white_knight && bkp_y - 1 >= 0 && bkp_x - 2 >= 0){
        return true;
    } else if(chessBoard_CC[bkp_y + 2][bkp_x + 1] == white_knight && bkp_y + 2 <= 7 && bkp_x + 1 <= 7){
        return true;
    } else if(chessBoard_CC[bkp_y + 2][bkp_x - 1] == white_knight && bkp_y + 2 <= 7 && bkp_x - 1 >= 0){
        return true;
    } else if(chessBoard_CC[bkp_y - 2][bkp_x + 1] == white_knight && bkp_y - 2 >= 0 && bkp_x + 1 <= 7){
        return true;
    } else if(chessBoard_CC[bkp_y - 2][bkp_x - 1] == white_knight && bkp_y - 2 >= 0 && bkp_x - 1 >= 0){
        return true;
    } else if(chessBoard_CC[bkp_y + 1][bkp_x + 1] == white_pawn && bkp_y - 1 >= 0 && bkp_x + 1 <= 7){ // pawn checks ~
        return true;
    } else if(chessBoard_CC[bkp_y + 1][bkp_x - 1] == white_pawn && bkp_y - 1 >= 0 && bkp_x - 1 >= 0){
        return true;
    } else if(chessBoard_CC[bkp_y + 1][bkp_x + 1] == white_king && bkp_y + 1 <= 7 && bkp_x + 1 <= 7){ // king 'checks' ~
        return true;
    } else if(chessBoard_CC[bkp_y + 1][bkp_x - 1] == white_king && bkp_y + 1 <= 7 && bkp_x - 1 >= 0){
        return true;
    } else if(chessBoard_CC[bkp_y - 1][bkp_x + 1] == white_king && bkp_y - 1 >= 0 && bkp_x + 1 <= 7){
        return true;
    } else if(chessBoard_CC[bkp_y - 1][bkp_x - 1] == white_king && bkp_y - 1 >= 0 && bkp_x - 1 >= 0){
        return true;
    } else if(chessBoard_CC[bkp_y + 1][bkp_x] == white_king && bkp_y + 1 <= 7){
        return true;
    } else if(chessBoard_CC[bkp_y][bkp_x - 1] == white_king && bkp_x - 1 >= 0){
        return true;
    } else if(chessBoard_CC[bkp_y - 1][bkp_x] == white_king && bkp_y - 1 >= 0){
        return true;
    } else if(chessBoard_CC[bkp_y][bkp_x + 1] == white_king && bkp_x + 1 <= 7){
        return true;
    } else{
    }
    return false;
}
void insertMove_white(){
    playMove_CC();
    if(check_white()){
        memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
    } else{
        moveList[0][n] = move_y;
        moveList[1][n] = move_x;
        moveList[2][n] = moveTo_y;
        moveList[3][n] = moveTo_x;
        n++;
        memcpy(chessBoard_CC,  chessBoard, sizeof(chessBoard));
    }
}
void insertMove_black(){
    playMove_CC();
    if(check_black()){
        memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
    } else{
        moveList[0][n] = move_y;
        moveList[1][n] = move_x;
        moveList[2][n] = moveTo_y;
        moveList[3][n] = moveTo_x;
        n++;
        memcpy(chessBoard_CC,  chessBoard, sizeof(chessBoard));
    }
}

// (castling through check & en passant)
class Move_gen{
    public:
        void w_pawn(){
            if(chessBoard[move_y - 1][move_x] == 0){
                moveTo_y = move_y - 1;
                moveTo_x = move_x;
                insertMove_white();
            }
            if(chessBoard[move_y - 1][move_x + 1] >= 11){
                if(move_x + 1 <= 7){
                    moveTo_y = move_y - 1;
                    moveTo_x = move_x + 1;
                    insertMove_white();
                }
            }
            if(chessBoard[move_y - 1][move_x - 1] >= 11){
                if(move_x - 1 >= 0){
                    moveTo_y = move_y - 1;
                    moveTo_x = move_x - 1;
                    insertMove_white();
                }
            }
            if(move_y == 6){
                if(chessBoard[move_y - 1][move_x] == 0 && chessBoard[move_y - 2][move_x] == 0){
                    moveTo_y = move_y - 2;
                    moveTo_x = move_x;
                    insertMove_white();   
                }
            } 
        }
        void b_pawn(){
            if(chessBoard[move_y + 1][move_x] == 0){
                moveTo_y = move_y + 1;
                moveTo_x = move_x;
                insertMove_black();
            }
            if(chessBoard[move_y + 1][move_x + 1] <= 6 && chessBoard[move_y + 1][move_x + 1] > 0){
                if(move_x + 1 <= 7){
                    moveTo_y = move_y + 1;
                    moveTo_x = move_x + 1;
                    insertMove_black();
                }
            }
            if(chessBoard[move_y + 1][move_x - 1] <= 6 && chessBoard[move_y + 1][move_x - 1] > 0){
                if(move_x - 1 >= 0){
                    moveTo_y = move_y + 1;
                    moveTo_x = move_x - 1;
                    insertMove_black();
                }
            }
            if(move_y == 1){
                if(chessBoard[move_y + 1][move_x] == 0 && chessBoard[move_y + 2][move_x] == 0){
                    moveTo_y = move_y + 2;
                    moveTo_x = move_x;
                    insertMove_black();   
                }
            } 
        }
        void w_knight(){
            if(chessBoard[move_y + 1][move_x + 2] >= 11 || chessBoard[move_y + 1][move_x + 2] == 0){
                if(move_y + 1 <= 7 && move_x + 2 <= 7){
                    moveTo_y = move_y + 1;
                    moveTo_x = move_x + 2;
                    insertMove_white();
                }
            }
            if(chessBoard[move_y - 1][move_x + 2] >= 11 || chessBoard[move_y - 1][move_x + 2] == 0){
                if(move_y - 1 >= 0 && move_x + 2 <= 7){
                    moveTo_y = move_y - 1;
                    moveTo_x = move_x + 2;
                    insertMove_white();
                } 
            }
            if(chessBoard[move_y + 1][move_x - 2] >= 11 || chessBoard[move_y + 1][move_x - 2] == 0){
                if(move_y + 1 <= 7 && move_x - 2 >= 0){
                    moveTo_y = move_y + 1;
                    moveTo_x = move_x - 2;
                    insertMove_white();
                }
            }
            if(chessBoard[move_y - 1][move_x - 2] >= 11 || chessBoard[move_y - 1][move_x - 2] == 0){
                if(move_y - 1 >= 0 && move_x - 2 >= 0){
                    moveTo_y = move_y - 1;
                    moveTo_x = move_x - 2;
                    insertMove_white();
                } 
            }
            if(chessBoard[move_y + 2][move_x + 1] >= 11 || chessBoard[move_y + 2][move_x + 1] == 0){
                if(move_y + 2 <= 7 && move_x + 1 <= 7){
                    moveTo_y = move_y + 2;
                    moveTo_x = move_x + 1;
                    insertMove_white();
                }
            }
            if(chessBoard[move_y - 2][move_x + 1] >= 11 || chessBoard[move_y - 2][move_x + 1] == 0){
                if(move_y - 2 >= 0 && move_x + 1 <= 7){
                    moveTo_y = move_y - 2;
                    moveTo_x = move_x + 1;
                    insertMove_white();
                }
            }
            if(chessBoard[move_y + 2][move_x - 1] >= 11 || chessBoard[move_y + 2][move_x - 1] == 0){
                if(move_y + 2 <= 7 && move_x - 1 >= 0){
                    moveTo_y = move_y + 2;
                    moveTo_x = move_x - 1;
                    playMove_CC();
                    insertMove_white();
                }
            }
            if(chessBoard[move_y - 2][move_x - 1] >= 11 || chessBoard[move_y - 2][move_x - 1] == 0){
                if(move_y - 2 >= 0 && move_x - 1 >= 0){
                    moveTo_y = move_y - 2;
                    moveTo_x = move_x - 1;
                    insertMove_white();
                }
            }
        }
        void b_knight(){
            if(chessBoard[move_y + 1][move_x + 2] <= 6 || chessBoard[move_y + 1][move_x + 2] == 0){
                if(move_y + 1 <= 7 && move_x + 2 <= 7){
                    moveTo_y = move_y + 1;
                    moveTo_x = move_x + 2;
                    insertMove_black();
                }
            }
            if(chessBoard[move_y - 1][move_x + 2] <= 6 || chessBoard[move_y - 1][move_x + 2] == 0){
                if(move_y - 1 >= 0 && move_x + 2 <= 7){
                    moveTo_y = move_y - 1;
                    moveTo_x = move_x + 2;
                    insertMove_black();
                } 
            }
            if(chessBoard[move_y + 1][move_x - 2] <= 6 || chessBoard[move_y + 1][move_x - 2] == 0){
                if(move_y + 1 <= 7 && move_x - 2 >= 0){
                    moveTo_y = move_y + 1;
                    moveTo_x = move_x - 2;
                    insertMove_black();
                }
            }
            if(chessBoard[move_y - 1][move_x - 2] <= 6 || chessBoard[move_y - 1][move_x - 2] == 0){
                if(move_y - 1 >= 0 && move_x - 2 >= 0){
                    moveTo_y = move_y - 1;
                    moveTo_x = move_x - 2;
                    insertMove_black();
                } 
            }
            if(chessBoard[move_y + 2][move_x + 1] <= 6 || chessBoard[move_y + 2][move_x + 1] == 0){
                if(move_y + 2 <= 7 && move_x + 1 <= 7){
                    moveTo_y = move_y + 2;
                    moveTo_x = move_x + 1;
                    insertMove_black();
                }
            }
            if(chessBoard[move_y - 2][move_x + 1] <= 6 || chessBoard[move_y - 2][move_x + 1] == 0){
                if(move_y - 2 >= 0 && move_x + 1 <= 7){
                    moveTo_y = move_y - 2;
                    moveTo_x = move_x + 1;
                    insertMove_black();
                }
            }
            if(chessBoard[move_y + 2][move_x - 1] <= 6 || chessBoard[move_y + 2][move_x - 1] == 0){
                if(move_y + 2 <= 7 && move_x - 1 >= 0){
                    moveTo_y = move_y + 2;
                    moveTo_x = move_x - 1;
                    insertMove_black();
                }
            }
            if(chessBoard[move_y - 2][move_x - 1] <= 6 || chessBoard[move_y - 2][move_x - 1] == 0){
                if(move_y - 2 >= 0 && move_x - 1 >= 0){
                    moveTo_y = move_y - 2;
                    moveTo_x = move_x - 1;
                    insertMove_black();
                }
            }
        }
        void w_bishop(){
            for(int diag = 1; diag < 8; diag++){ // down & right
                if(move_y + diag > 7 || move_x + diag > 7){
                    break;
                }
                if(chessBoard[move_y + diag][move_x + diag] == empty_square){
                    moveTo_y = move_y + diag;
                    moveTo_x = move_x + diag;
                    insertMove_white();
                } else if(chessBoard[move_y + diag][move_x + diag] <= 6 && chessBoard[move_y + diag][move_x + diag] != empty_square){
                    break;
                } else if(chessBoard[move_y + diag][move_x + diag] >= 11){
                    moveTo_y = move_y + diag;
                    moveTo_x = move_x + diag;
                    insertMove_white();
                    break;
                }
            }
            for(int diag = 1; diag < 8; diag++){ // down & left
                if(move_y + diag > 7 || move_x - diag < 0){
                    break;
                }
                if(chessBoard[move_y + diag][move_x - diag] == empty_square){
                    moveTo_y = move_y + diag;
                    moveTo_x = move_x - diag;
                    insertMove_white();
                } else if(chessBoard[move_y + diag][move_x - diag] <= 6 && chessBoard[move_y + diag][move_x - diag] != empty_square){
                    break;
                } else if(chessBoard[move_y + diag][move_x - diag] >= 11){
                    moveTo_y = move_y + diag;
                    moveTo_x = move_x - diag;
                    insertMove_white();
                    break;
                }
            }
            for(int diag = 1; diag < 8; diag++){ // up & left
                if(move_y - diag < 0 || move_x - diag < 0){
                    break;
                }
                if(chessBoard[move_y - diag][move_x - diag] == empty_square){
                    moveTo_y = move_y - diag;
                    moveTo_x = move_x - diag;
                    insertMove_white();
                } else if(chessBoard[move_y - diag][move_x - diag] <= 6 && chessBoard[move_y - diag][move_x - diag] != empty_square){
                    break;
                } else if(chessBoard[move_y - diag][move_x - diag] >= 11){
                    moveTo_y = move_y - diag;
                    moveTo_x = move_x - diag;
                    insertMove_white();
                    break;
                }
            }
            for(int diag = 1; diag < 8; diag++){ // up & right
                if(move_y - diag < 0 || move_x + diag > 7){
                    break;
                }
                if(chessBoard[move_y - diag][move_x + diag] == empty_square){
                    moveTo_y = move_y - diag;
                    moveTo_x = move_x + diag;
                    insertMove_white();
                } else if(chessBoard[move_y - diag][move_x + diag] <= 6 && chessBoard[move_y - diag][move_x + diag] != empty_square){
                    break;
                } else if(chessBoard[move_y - diag][move_x + diag] >= 11){
                    moveTo_y = move_y - diag;
                    moveTo_x = move_x + diag;
                    insertMove_white();
                    break;
                }
            }
        }
        void b_bishop(){
            for(int diag = 1; diag < 8; diag++){ // down & right
                if(move_y + diag > 7 || move_x + diag > 7){
                    break;
                }
                if(chessBoard[move_y + diag][move_x + diag] == empty_square){
                    moveTo_y = move_y + diag;
                    moveTo_x = move_x + diag;
                    insertMove_black();
                } else if(chessBoard[move_y + diag][move_x + diag] >= 11){
                    break;
                } else if(chessBoard[move_y + diag][move_x + diag] <= 6 && chessBoard[move_y + diag][move_x + diag] != 0){
                    moveTo_y = move_y + diag;
                    moveTo_x = move_x + diag;
                    insertMove_black();
                    break;
                }
            }
            for(int diag = 1; diag < 8; diag++){ // down & left
                if(move_y + diag > 7 || move_x - diag < 0){
                    break;
                }
                if(chessBoard[move_y + diag][move_x - diag] == empty_square){
                    moveTo_y = move_y + diag;
                    moveTo_x = move_x - diag;
                    insertMove_black();
                } else if(chessBoard[move_y + diag][move_x - diag] >= 11){
                    break;
                } else if(chessBoard[move_y + diag][move_x - diag] <= 6 && chessBoard[move_y + diag][move_x - diag] != 0){
                    moveTo_y = move_y + diag;
                    moveTo_x = move_x - diag;
                    insertMove_black();
                    break;
                }
            }
            for(int diag = 1; diag < 8; diag++){ // up & left
                if(move_y - diag < 0 || move_x - diag < 0){
                    break;
                }
                if(chessBoard[move_y - diag][move_x - diag] == empty_square){
                    moveTo_y = move_y - diag;
                    moveTo_x = move_x - diag;
                    insertMove_black();
                } else if(chessBoard[move_y - diag][move_x - diag] >= 11){
                    break;
                } else if(chessBoard[move_y - diag][move_x - diag] <= 6 && chessBoard[move_y - diag][move_x - diag] != empty_square){
                    moveTo_y = move_y - diag;
                    moveTo_x = move_x - diag;
                    insertMove_black();
                    break;
                }
            }
            for(int diag = 1; diag < 8; diag++){ // up & right
                if(move_y - diag < 0 || move_x + diag > 7){
                    break;
                }
                if(chessBoard[move_y - diag][move_x + diag] == empty_square){
                    moveTo_y = move_y - diag;
                    moveTo_x = move_x + diag;
                    insertMove_black();
                } else if(chessBoard[move_y - diag][move_x + diag] >= 11){
                    break;
                } else if(chessBoard[move_y - diag][move_x + diag] <= 6 && chessBoard[move_y - diag][move_x + diag] != empty_square){
                    moveTo_y = move_y - diag;
                    moveTo_x = move_x + diag;
                    insertMove_black();
                    break;
                }
            }
        }
        void w_rook_moves(){
            for(int raf = 1; raf < 8; raf++){ // down
                if(move_y + raf > 7){
                    break;
                } else if(chessBoard[move_y + raf][move_x] == empty_square){
                    moveTo_y = move_y + raf;
                    moveTo_x = move_x;
                    insertMove_white();
                } else if(chessBoard[move_y + raf][move_x] <= 6 && chessBoard[move_y + raf][move_x] != empty_square){
                    break;
                } else if(chessBoard[move_y + raf][move_x] >= 11){
                    moveTo_y = move_y + raf;
                    moveTo_x = move_x;
                    insertMove_white();
                    break;
                }
            }
            for(int raf = 1; raf < 8; raf++){ // left
                if(move_x - raf < 0){
                    break;
                } else if(chessBoard[move_y][move_x - raf] == empty_square){
                    moveTo_y = move_y;
                    moveTo_x = move_x - raf;
                    insertMove_white();
                } else if(chessBoard[move_y][move_x - raf] <= 6 && chessBoard[move_y][move_x - raf] != empty_square){
                    break;
                } else if(chessBoard[move_y][move_x - raf] >= 11){
                    moveTo_y = move_y;
                    moveTo_x = move_x - raf;
                    insertMove_white();
                    break;
                }
            }
            for(int raf = 1; raf < 8; raf++){ // up
                if(move_y - raf < 0){
                    break;
                } else if(chessBoard[move_y - raf][move_x] == empty_square){
                    moveTo_y = move_y - raf;
                    moveTo_x = move_x;
                    insertMove_white();
                } else if(chessBoard[move_y - raf][move_x] <= 6 && chessBoard[move_y - raf][move_x] != empty_square){
                    break;
                } else if(chessBoard[move_y - raf][move_x] >= 11){
                    moveTo_y = move_y - raf;
                    moveTo_x = move_x;
                    insertMove_white();
                    break;
                }
            }
            for(int raf = 1; raf < 8; raf++){ // right
                if(move_x + raf > 7){
                    break;
                } else if(chessBoard[move_y][move_x + raf] == empty_square){
                    moveTo_y = move_y;
                    moveTo_x = move_x + raf;
                    insertMove_white();
                } else if(chessBoard[move_y][move_x + raf] <= 6 && chessBoard[move_y][move_x + raf] != empty_square){
                    break;
                } else if(chessBoard[move_y][move_x + raf] >= 11){
                    moveTo_y = move_y;
                    moveTo_x = move_x + raf;
                    insertMove_white();
                    break;
                }
            }
        }
        void b_rook_moves(){
            for(int raf = 1; raf < 8; raf++){ // down
                if(move_y + raf > 7){
                    break;
                } else if(chessBoard[move_y + raf][move_x] == empty_square){
                    moveTo_y = move_y + raf;
                    moveTo_x = move_x;
                    insertMove_black();
                } else if(chessBoard[move_y + raf][move_x] >= 11){
                    break;
                } else if(chessBoard[move_y + raf][move_x] <= 6 && chessBoard[move_y + raf][move_x] != empty_square){
                    moveTo_y = move_y + raf;
                    moveTo_x = move_x;
                    insertMove_black();
                    break;
                }
            }
            for(int raf = 1; raf < 8; raf++){ // left
                if(move_x - raf < 0){
                    break;
                } else if(chessBoard[move_y][move_x - raf] == empty_square){
                    moveTo_y = move_y;
                    moveTo_x = move_x - raf;
                    insertMove_black();
                } else if(chessBoard[move_y][move_x - raf] >= 11){
                    break;
                } else if(chessBoard[move_y + raf][move_x] <= 6 && chessBoard[move_y + raf][move_x] != empty_square){
                    moveTo_y = move_y;
                    moveTo_x = move_x - raf;
                    insertMove_black();
                    break;
                }
            }
            for(int raf = 1; raf < 8; raf++){ // up
                if(move_y - raf < 0){
                    break;
                } else if(chessBoard[move_y - raf][move_x] == empty_square){
                    moveTo_y = move_y - raf;
                    moveTo_x = move_x;
                    insertMove_black();
                } else if(chessBoard[move_y - raf][move_x] >= 11){
                    break;
                } else if(chessBoard[move_y + raf][move_x] <= 6 && chessBoard[move_y + raf][move_x] != empty_square){
                    moveTo_y = move_y - raf;
                    moveTo_x = move_x;
                    insertMove_black();
                    break;
                }
            }
            for(int raf = 1; raf < 8; raf++){ // right
                if(move_x + raf > 7){
                    break;
                } else if(chessBoard[move_y][move_x + raf] == empty_square){
                    moveTo_y = move_y;
                    moveTo_x = move_x + raf;
                    insertMove_black();
                } else if(chessBoard[move_y][move_x + raf] >= 11){
                    break;
                } else if(chessBoard[move_y + raf][move_x] <= 6 && chessBoard[move_y + raf][move_x] != empty_square){
                    moveTo_y = move_y;
                    moveTo_x = move_x + raf;
                    insertMove_black();
                    break;
                }
            }
        }
        void w_queen_moves(){
            w_bishop();
            w_rook_moves();
        }
        void b_queen_moves(){
            b_bishop();
            b_rook_moves();
        }
        void w_king_moves(){
            if(chessBoard[move_y + 1][move_x] == empty_square || chessBoard[move_y + 1][move_x] >= 11){
                if(move_y + 1 <= 7){
                    moveTo_y = move_y + 1;
                    moveTo_x = move_x;
                    insertMove_white();
                }
            }
            if(chessBoard[move_y - 1][move_x] == empty_square || chessBoard[move_y - 1][move_x] >= 11){
                if(move_y - 1 >= 0){
                    moveTo_y = move_y - 1;
                    moveTo_x = move_x;
                    insertMove_white();
                }
            }
            if(chessBoard[move_y][move_x + 1] == empty_square || chessBoard[move_y][move_x + 1] >= 11){
                if(move_x + 1 <= 7){
                    moveTo_y = move_y;
                    moveTo_x = move_x + 1;
                    insertMove_white();
                }
            }
            if(chessBoard[move_y][move_x - 1] == empty_square || chessBoard[move_y][move_x - 1] >= 11){
                if(move_x - 1 >= 0){
                    moveTo_y = move_y;
                    moveTo_x = move_x - 1;
                    insertMove_white();
                }
            }
            if(chessBoard[move_y + 1][move_x + 1] == empty_square || chessBoard[move_y + 1][move_x + 1] >= 11){
                if(move_y + 1 <= 7 && move_x + 1 <= 7){
                    moveTo_y = move_y + 1;
                    moveTo_x = move_x + 1;
                    insertMove_white();
                }
            }
            if(chessBoard[move_y + 1][move_x - 1] == empty_square || chessBoard[move_y + 1][move_x - 1] >= 11){
                if(move_y + 1 <= 7 && move_x - 1 >= 0){
                    moveTo_y = move_y + 1;
                    moveTo_x = move_x - 1;
                    insertMove_white();
                }
            }
            if(chessBoard[move_y - 1][move_x + 1] == empty_square || chessBoard[move_y - 1][move_x + 1] >= 11){
                if(move_y - 1 >= 0 && move_x + 1 <= 7){
                    moveTo_y = move_y - 1;
                    moveTo_x = move_x + 1;
                    insertMove_white();
                }
            }
            if(chessBoard[move_y - 1][move_x - 1] == empty_square || chessBoard[move_y - 1][move_x - 1] >= 11){
                if(move_y - 1 >= 0 && move_x - 1 >= 0){
                    moveTo_y = move_y - 1;
                    moveTo_x = move_x - 1;
                    insertMove_white();
                }
            }
            if(move_y == 7 && move_x == 4 && KSCastlingRights_white && chessBoard[7][5] == empty_square && chessBoard[7][6] == empty_square){ // castling KS
                moveTo_y = move_y;
                moveTo_x = move_x + 2;
                insertMove_white();
            }
            if(move_y == 7 && move_x == 4 && QSCastlingRights_white && chessBoard[7][3] == 0 && chessBoard[7][2] == 0 && chessBoard[7][1] == 0){ // castling QS
                moveTo_y = move_y;
                moveTo_x = move_x - 2;
                insertMove_white();
            }
        }
        void b_king_moves(){
            if(chessBoard[move_y + 1][move_x] <= 6){
                if(move_y + 1 <= 7){
                    moveTo_y = move_y + 1;
                    moveTo_x = move_x;
                    insertMove_black();
                }
            }
            if(chessBoard[move_y - 1][move_x] <= 6){
                if(move_y - 1 >= 0){
                    moveTo_y = move_y - 1;
                    moveTo_x = move_x;
                    insertMove_black();
                }
            }
            if(chessBoard[move_y][move_x + 1] <= 6){
                if(move_x + 1 <= 7){
                    moveTo_y = move_y;
                    moveTo_x = move_x + 1;
                    insertMove_black();
                }
            }
            if(chessBoard[move_y][move_x - 1] <= 6){
                if(move_x - 1 >= 0){
                    moveTo_y = move_y;
                    moveTo_x = move_x - 1;
                    insertMove_black();
                }
            }
            if(chessBoard[move_y + 1][move_x + 1] <= 6){
                if(move_y + 1 <= 7 && move_x + 1 <= 7){
                    moveTo_y = move_y + 1;
                    moveTo_x = move_x + 1;
                    insertMove_black();
                }
            }
            if(chessBoard[move_y + 1][move_x - 1] <= 6){
                if(move_y + 1 <= 7 && move_x - 1 >= 0){
                    moveTo_y = move_y + 1;
                    moveTo_x = move_x - 1;
                    insertMove_black();
                }
            }
            if(chessBoard[move_y - 1][move_x + 1] <= 6){
                if(move_y - 1 >= 0 && move_x + 1 <= 7){
                    moveTo_y = move_y - 1;
                    moveTo_x = move_x + 1;
                    insertMove_black();
                }
            }
            if(chessBoard[move_y - 1][move_x - 1] <= 6){
                if(move_y - 1 >= 0 && move_x - 1 >= 0){
                    moveTo_y = move_y - 1;
                    moveTo_x = move_x - 1;
                    insertMove_black();
                }
            }
            if(move_y == 0 && move_x == 4 && KSCastlingRights_black && chessBoard[0][5] == empty_square && chessBoard[0][6] == empty_square){ // castling KS
                moveTo_y = move_y;
                moveTo_x = move_x + 2;
                insertMove_black();
            }
            if(move_y == 0 && move_x == 4 && QSCastlingRights_black && chessBoard[0][3] == 0 && chessBoard[0][2] == 0 && chessBoard[0][1] == 0){ // castling QS
                moveTo_y = move_y;
                moveTo_x = move_x - 2;
                insertMove_black();
            }
        }
};
Move_gen Movegen;

void initializeBoard(){
    int FENpos = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(FEN[FENpos] == 'p'){
                chessBoard[i][j] = black_pawn;
            } else if(FEN[FENpos] == 'n'){
                chessBoard[i][j] = black_knight;
            } else if(FEN[FENpos] == 'b'){
                chessBoard[i][j] = black_bishop;
            } else if(FEN[FENpos] == 'r'){
                chessBoard[i][j] = black_rook;
            } else if(FEN[FENpos] == 'q'){
                chessBoard[i][j] = black_queen;
            } else if(FEN[FENpos] == 'k'){
                chessBoard[i][j] = black_king;
            } else if(FEN[FENpos] == 'P'){
                chessBoard[i][j] = white_pawn;
            } else if(FEN[FENpos] == 'N'){
                chessBoard[i][j] = white_knight;
            } else if(FEN[FENpos] == 'B'){
                chessBoard[i][j] = white_bishop;
            } else if(FEN[FENpos] == 'R'){
                chessBoard[i][j] = white_rook;
            } else if(FEN[FENpos] == 'Q'){
                chessBoard[i][j] = white_queen;
            } else if(FEN[FENpos] == 'K'){
                chessBoard[i][j] = white_king;
            } else{
                chessBoard[i][j] = empty_square;
            }
            FENpos += 1;
        }
    }
}
void printBoard(){
    for(int y_pos = 0; y_pos < 8; y_pos++){
        for(int x_pos = 0; x_pos < 8; x_pos++){
            if(chessBoard[y_pos][x_pos] == white_pawn){
                cout << "P  ";
            } else if(chessBoard[y_pos][x_pos] == white_knight){
                cout << "N  ";
            } else if(chessBoard[y_pos][x_pos] == white_bishop){
                cout << "B  ";
            } else if(chessBoard[y_pos][x_pos] == white_rook){
                cout << "R  ";
            } else if(chessBoard[y_pos][x_pos] == white_queen){
                cout << "Q  ";
            } else if(chessBoard[y_pos][x_pos] == white_king){
                cout << "K  ";
            } else if(chessBoard[y_pos][x_pos] == black_pawn){
                cout << "p  ";
            } else if(chessBoard[y_pos][x_pos] == black_knight){
                cout << "n  ";
            } else if(chessBoard[y_pos][x_pos] == black_bishop){
                cout << "b  ";
            } else if(chessBoard[y_pos][x_pos] == black_rook){
                cout << "r  ";
            } else if(chessBoard[y_pos][x_pos] == black_queen){
                cout << "q  ";
            } else if(chessBoard[y_pos][x_pos] == black_king){
                cout << "k  ";
            } else{
                cout << "-  ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

// ----------------------------------------------------------------------- Search & Evaluation -----------------------------------------------------------------------

double material(){
    double material_eval = 0;
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            if(chessBoard[y][x] <= 6 && chessBoard[y][x] != 0){
                material_eval += value(chessBoard[y][x]);
            } else if(chessBoard[y][x] >= 11){
                material_eval -= value(chessBoard[y][x]);
            }
        }
    }
    return material_eval;
}

int playMove(){

    // castling
    if(chessBoard[move_y][move_x] == white_rook && move_y == 7 && move_x == 0){
        QSCastlingRights_white = false;
    } else if(chessBoard[move_y][move_x] == white_rook && move_y == 7 && move_x == 7){
        KSCastlingRights_white = false;
    } else if(chessBoard[move_y][move_x] == black_rook && move_y == 0 && move_x == 0){
        QSCastlingRights_black = false;
    } else if(chessBoard[move_y][move_x] == white_rook && move_y == 0 && move_x == 7){
        KSCastlingRights_black = false;
    }
    if(chessBoard[move_y][move_x] == white_king && move_y == 7 && move_x == 4 && moveTo_y == 7 && moveTo_x == 6 && KSCastlingRights_white){
        chessBoard[7][7] = empty_square;
        chessBoard[7][5] = white_rook;
    } else if(chessBoard[move_y][move_x] == white_king && move_y == 7 && move_x == 4 && moveTo_y == 7 && moveTo_x == 2 && QSCastlingRights_white){
        chessBoard[7][0] = empty_square;
        chessBoard[7][3] = white_rook;
    } else if(chessBoard[move_y][move_x] == black_king && move_y == 0 && move_x == 4 && moveTo_y == 0 && moveTo_x == 6 && KSCastlingRights_black){
        chessBoard[0][7] = empty_square;
        chessBoard[0][5] = black_rook;
    } else if(chessBoard[move_y][move_x] == black_king && move_y == 0 && move_x == 4 && moveTo_y == 0 && moveTo_x == 2 && QSCastlingRights_black){
        chessBoard[0][0] = empty_square;
        chessBoard[0][3] = black_rook;
    } else{
    }
    if(chessBoard[move_y][move_x] == white_king){
        KSCastlingRights_white = false;
        QSCastlingRights_white = false;
    }
    if(chessBoard[move_y][move_x] == black_king){
        KSCastlingRights_black = false;
        QSCastlingRights_black = false;
    }

    // promotion
    if(chessBoard[move_y][move_x] == white_pawn && moveTo_y == 0){
        chessBoard[move_y][move_x] = empty_square;
        chessBoard[moveTo_y][moveTo_x] = white_queen;
        memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
        return 0;
    } else if(chessBoard[move_y][move_x] == black_pawn && moveTo_y == 7){
        chessBoard[move_y][move_x] = empty_square;
        chessBoard[moveTo_y][moveTo_x] = black_queen;
        memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
        return 0;
    } else{
    }

    chessBoard[moveTo_y][moveTo_x] = chessBoard[move_y][move_x];
    chessBoard[move_y][move_x] = empty_square;

    // updates the carbon copy - chessBoard_CC
    memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));

    return 0;
}

void generateMoves_white(){
    n = 0;
    for(int im = 0; im < 8; im++){
        move_y = im;
        for(int jm = 0; jm < 8; jm++){
            move_x = jm;
            if(chessBoard[move_y][move_x] == white_pawn){
                Movegen.w_pawn();
            } else if(chessBoard[move_y][move_x] == white_knight){
                Movegen.w_knight();
            } else if(chessBoard[move_y][move_x] == white_bishop){
                Movegen.w_bishop();
            } else if(chessBoard[move_y][move_x] == white_rook){
                Movegen.w_rook_moves();
            } else if(chessBoard[move_y][move_x] == white_queen){
                Movegen.w_queen_moves();
            } else if(chessBoard[move_y][move_x] == white_king){
                Movegen.w_king_moves();
            } else{
            }
        }
    }
}
void generateMoves_black(){
    n = 0;
    for(int im = 0; im < 8; im++){
        move_y = im;
        for(int jm = 0; jm < 8; jm ++){
            move_x = jm;
            if(chessBoard[move_y][move_x] == black_pawn){
                Movegen.b_pawn();
            } else if(chessBoard[move_y][move_x] == black_knight){
                Movegen.b_knight();
            } else if(chessBoard[move_y][move_x] == black_bishop){
                Movegen.b_bishop();
            } else if(chessBoard[move_y][move_x] == black_rook){
                Movegen.b_rook_moves();
            } else if(chessBoard[move_y][move_x] == black_queen){
                Movegen.b_queen_moves();
            } else if(chessBoard[move_y][move_x] == black_king){
                Movegen.b_king_moves();
            } else{
            }
        }
    }
}

double staticEval_wtm(){
    double eval = 0;
    eval = material();
    return eval;
}
double staticEval_btm(){
    double eval = 0;
    eval = material();
    return eval;
}

// search (removes castling rights)
double search(int depth, int max_depth){
    memcpy(moveList, clearMoveList, sizeof(moveList));
    if(depth % 2 == 0){
        generateMoves_white();
    } else{
        generateMoves_black();
    }
    memcpy(boardStates[depth], chessBoard, sizeof(chessBoard));
    for(int ms = 0; ms < n; ms++){
        move_y = moveList[0][depthProgress[depth]];
        move_x = moveList[1][depthProgress[depth]];
        moveTo_y = moveList[2][depthProgress[depth]];
        moveTo_x = moveList[3][depthProgress[depth]];
        if(move_x == 0 && move_y == 0 && moveTo_x == 0 && moveTo_y == 0){
            break;
        }
        playMove();
        depthProgress[depth]++;
        if(depth > 1){
            depth--;
            search(depth, max_depth);
            return 0;
        }
        if(staticEval_wtm() == -9){
            cout << "Queen blundered! ";
        }
        memcpy(chessBoard, boardStates[depth], sizeof(chessBoard));
        TEST++;
    }
    if(depth < max_depth){
        depthProgress[depth] = 0;
        depth++;
        memcpy(chessBoard, boardStates[depth], sizeof(chessBoard));
        search(depth, max_depth);
    }
    return 0;
}

int getMove_white(){
    generateMoves_white();
    isLegalMove = false;
    cout << "White's move ---> ";
    cin >> move_y;
    cin >> move_x;
    cin >> moveTo_y;
    cin >> moveTo_x;
    for(int i = 0; i < n; i++){
        if(move_y == moveList[0][i] && move_x == moveList[1][i] && moveTo_y == moveList[2][i] && moveTo_x == moveList[3][i]){
            playMove();
            isLegalMove = true;
            return 0;
        }      
    }
    cout << "Illegal Move!" << endl;
    return 0;
}
int getMove_black(){
    generateMoves_black();
    isLegalMove = false;
    cout << "Black's move ---> ";
    cin >> move_y;
    cin >> move_x;
    cin >> moveTo_y;
    cin >> moveTo_x;
    for(int i = 0; i < n; i++){
        if(move_y == moveList[0][i] && move_x == moveList[1][i] && moveTo_y == moveList[2][i] && moveTo_x == moveList[3][i]){
            playMove();
            isLegalMove = true;
            return 0;
        }      
    }
    cout << "Illegal Move!" << endl;
    return 0;
}

int main(){

    initializeBoard();

    printBoard();
    
    search(4, 4);
    cout << "Positions scanned - " << TEST << endl;

    while(move_move <= 5949){
        cout << "Move - " << move_move << endl;

        do{
            getMove_white();
        } while(!isLegalMove);

        generateMoves_black();
        if(n == 0 && check_black() == true){
            printBoard();
            cout << staticEval_btm() << endl;
            cout << "Checkmate - white is victorious" << endl;
            break;
        } else if(n == 0 && check_black() == false){
            printBoard();
            cout << staticEval_btm() << endl;
            cout << "Stalemate - draw" << endl;
            break;
        } else{
        }

        printBoard();
        tempo++;
        cout << staticEval_btm() << endl;

        do{
            getMove_black();
        } while(!isLegalMove);

        generateMoves_white();
        if(n == 0 && check_white() == true){
            printBoard();
            cout << staticEval_wtm() << endl;
            cout << "Checkmate - black is victorious" << endl;
            break;
        } else if(n == 0 && check_white() == false){
            printBoard();
            cout << staticEval_wtm() << endl;
            cout << "Stalemate - draw" << endl;
            break;
        } else{
        }

        printBoard();
        tempo++;
        move_move++;
        cout << staticEval_wtm() << endl;
    }
    return 0;
}