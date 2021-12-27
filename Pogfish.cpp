#include<iostream>
#include<cmath>
#include<string.h>
#include<algorithm>
using namespace std;

int64_t tempo = 1;
int64_t move_move = 1;
bool isLegalMove;
bool opening;
bool middlegame;
bool endgame;
bool KSCastlingRights_white = true;
bool QSCastlingRights_white = true;
bool KSCastlingRights_black = true;
bool QSCastlingRights_black = true;
int64_t best_index;

int64_t move_y;
int64_t move_x;
int64_t moveTo_y;
int64_t moveTo_x;
int64_t y;
int64_t x;
int64_t y_to;
int64_t x_to;

const int64_t empty_square = 0;
const int64_t white_pawn = 1;
const int64_t white_knight = 2;
const int64_t white_bishop = 3;
const int64_t white_rook = 4;
const int64_t white_queen = 5;
const int64_t white_king = 6;
const int64_t black_pawn = 11;
const int64_t black_knight = 12;
const int64_t black_bishop = 13;
const int64_t black_rook = 14;
const int64_t black_queen = 15;
const int64_t black_king = 16;

int64_t n = 0;
int64_t o = 0;
int64_t TEST = 0;

int64_t value(int64_t piece){
    int64_t pieceValue;
    switch(piece){
        case 1:
            pieceValue = 100;
            break;
        case 2:
            pieceValue = 300;
            break;
        case 3:
            pieceValue = 300;
            break;
        case 4:
            pieceValue = 500;
            break;
        case 5:
            pieceValue = 900;
            break;
        case 6:
            pieceValue = 0;
            break;
        case 11:
            pieceValue = 100;
            break;
        case 12:
            pieceValue = 300;
            break;
        case 13:
            pieceValue = 300;
            break;
        case 14:
            pieceValue = 500;
            break;
        case 15:
            pieceValue = 900;
            break;
        case 16:
            pieceValue = 0;
        default:
            pieceValue = 0;
    }
    return pieceValue;
}
int64_t getMax(int64_t values[], int64_t numValues){
    int64_t best = values[0];
    best_index = 0;
    for(int64_t i = 0; i < numValues; i++){
        if(values[i] > best){
            best = values[i];
            best_index = i;
        }
    }
    return best;
}
int64_t getMin(int64_t values[], int64_t numValues){
    int64_t best = values[0];
    best_index = 0;
    for(int64_t i = 0; i < numValues; i++){
        if(values[i] < best){
            best = values[i];
            best_index = i;
        }
    }
    return best;
}
int64_t duoMax(int64_t a, int64_t b){
    int64_t max;
    max = (a + b + abs(a - b))/2;
    return max;
}

string FEN = "rnbqkbnrppppppppooooooooooooooooooooooooooooooooPPPPPPPPRNBQKBNR";
int64_t chessBoard[8][8] = {0};
int64_t chessBoard_CC[8][8] = {0};

int64_t boardStates[50][8][8] = {0};
int64_t moveList[4][219] = {0};
int64_t eml[4][219] = {0};
int64_t bestMove[4] = {0};

// ------------------------------------------------------------------------- Rules of chess --------------------------------------------------------------------------

int64_t playMove(int64_t castlingRightsRemoved){
    // castling
    if(chessBoard[move_y][move_x] == white_rook && move_y == 7 && move_x == 0){
        if(castlingRightsRemoved == 1){
            QSCastlingRights_white = false;
        }
    } else if(chessBoard[move_y][move_x] == white_rook && move_y == 7 && move_x == 7){
        if(castlingRightsRemoved == 1){
            KSCastlingRights_white = false;
        }
    } else if(chessBoard[move_y][move_x] == black_rook && move_y == 0 && move_x == 0){
        if(castlingRightsRemoved == 1){
            QSCastlingRights_black = false;
        }
    } else if(chessBoard[move_y][move_x] == white_rook && move_y == 0 && move_x == 7){
        if(castlingRightsRemoved == 1){
            KSCastlingRights_black = false;
        }
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
        if(castlingRightsRemoved == 1){
            KSCastlingRights_white = false;
            QSCastlingRights_white = false;
        }
    }
    if(chessBoard[move_y][move_x] == black_king){
        if(castlingRightsRemoved == 1){
            KSCastlingRights_black = false;
            QSCastlingRights_black = false;
        }
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

    memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
    return 0;
}
int64_t playMove_CC(int64_t castlingRightsRemoved){
    // castling
    if(chessBoard_CC[y][x] == white_rook && y == 7 && x == 0){
        if(castlingRightsRemoved == 1){
            QSCastlingRights_white = false;
        }
    } else if(chessBoard_CC[y][x] == white_rook && y == 7 && x == 7){
        if(castlingRightsRemoved == 1){
            KSCastlingRights_white = false;
        }
    } else if(chessBoard_CC[y][x] == black_rook && y == 0 && x == 0){
        if(castlingRightsRemoved == 1){
            QSCastlingRights_black = false;
        }
    } else if(chessBoard_CC[y][x] == white_rook && y == 0 && x == 7){
        if(castlingRightsRemoved == 1){
            KSCastlingRights_black = false;
        }
    }
    if(chessBoard_CC[y][x] == white_king && y == 7 && x == 4 && y_to == 7 && x_to == 6 && KSCastlingRights_white){
        chessBoard_CC[7][7] = empty_square;
        chessBoard_CC[7][5] = white_rook;
    } else if(chessBoard_CC[y][x] == white_king && y == 7 && x == 4 && y_to == 7 && x_to == 2 && QSCastlingRights_white){
        chessBoard_CC[7][0] = empty_square;
        chessBoard_CC[7][3] = white_rook;
    } else if(chessBoard_CC[y][x] == black_king && y == 0 && x == 4 && y_to == 0 && x_to == 6 && KSCastlingRights_black){
        chessBoard_CC[0][7] = empty_square;
        chessBoard_CC[0][5] = black_rook;
    } else if(chessBoard_CC[y][x] == black_king && y == 0 && x == 4 && y_to == 0 && x_to == 2 && QSCastlingRights_black){
        chessBoard_CC[0][0] = empty_square;
        chessBoard_CC[0][3] = black_rook;
    } else{
    }
    if(chessBoard_CC[y][x] == white_king){
        if(castlingRightsRemoved == 1){
            KSCastlingRights_white = false;
            QSCastlingRights_white = false;
        }
    }
    if(chessBoard_CC[y][x] == black_king){
        if(castlingRightsRemoved == 1){
            KSCastlingRights_black = false;
            QSCastlingRights_black = false;
        }
    }
    // promotion
    if(chessBoard_CC[y][x] == white_pawn && y_to == 0){
        chessBoard_CC[y][x] = empty_square;
        chessBoard_CC[y_to][x_to] = white_queen;
        return 0;
    } else if(chessBoard_CC[y][x] == black_pawn && y_to == 7){
        chessBoard_CC[y][x] = empty_square;
        chessBoard_CC[y_to][x_to] = black_queen;
        return 0;
    } else{
    }

    chessBoard_CC[y_to][x_to] = chessBoard_CC[y][x];
    chessBoard_CC[y][x] = empty_square;
    return 0;
}
bool check(int side){
    if(side == 1){
        int64_t kp_y = 0;
        int64_t kp_x = 0;
        for(int64_t i = 0; i <= 7; i++){
            for(int64_t j = 0; j <= 7; j++){
                if(chessBoard_CC[i][j] == white_king){
                    kp_y = i;
                    kp_x = j;
                    break;
                }
            }
        }
        for(int64_t i = 1; i < 8; i++){ // down & right
            if(kp_y + i > 7 || kp_x + i > 7){
                break;
            } else if(chessBoard_CC[kp_y + i][kp_x + i] == black_bishop || chessBoard_CC[kp_y + i][kp_x + i] == black_queen){
                return true;
            } else if(chessBoard_CC[kp_y + i][kp_x + i] >= 1 && chessBoard_CC[kp_y + i][kp_x + i] != black_bishop && chessBoard_CC[kp_y + i][kp_x + i] != black_queen){
                break;
            } else{
            }
        }
        for(int64_t i = 1; i < 8; i++){ // down & left
            if(kp_y + i > 7 || kp_x - i < 0){
                break;
            } else if(chessBoard_CC[kp_y + i][kp_x - i] == black_bishop || chessBoard_CC[kp_y + i][kp_x - i] == black_queen){
                return true;
            } else if(chessBoard_CC[kp_y + i][kp_x - i] >= 1 && chessBoard_CC[kp_y + i][kp_x - i] != black_bishop && chessBoard_CC[kp_y + i][kp_x - i] != black_queen){
                break;
            } else{
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up & left
            if(kp_y - i < 0 || kp_x - i < 0){
                break;
            } else if(chessBoard_CC[kp_y - i][kp_x - i] == black_bishop || chessBoard_CC[kp_y - i][kp_x - i] == black_queen){
                return true;
            } else if(chessBoard_CC[kp_y - i][kp_x - i] >= 1 && chessBoard_CC[kp_y - i][kp_x - i] != black_bishop && chessBoard_CC[kp_y - i][kp_x - i] != black_queen){
                break;
            } else{
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up & right
            if(kp_y - i < 0 || kp_x + i > 7){
                break;
            } else if(chessBoard_CC[kp_y - i][kp_x + i] == black_bishop || chessBoard_CC[kp_y - i][kp_x + i] == black_queen){
                return true;
            } else if(chessBoard_CC[kp_y - i][kp_x + i] >= 1 && chessBoard_CC[kp_y - i][kp_x + i] != black_bishop && chessBoard_CC[kp_y - i][kp_x + i] != black_queen){
                break;
            } else{
            }
        }
        for(int64_t i = 1; i < 8; i++){ // down
            if(kp_y + i > 7){
                break;
            } else if(chessBoard_CC[kp_y + i][kp_x] == black_rook || chessBoard_CC[kp_y + i][kp_x] == black_queen){
                return true;
            } else if(chessBoard_CC[kp_y + i][kp_x] >= 1 && chessBoard_CC[kp_y + i][kp_x] != black_rook && chessBoard_CC[kp_y + i][kp_x] != black_queen){
                break;
            } else{
            }
        }
        for(int64_t i = 1; i < 8; i++){ // left
            if(kp_x - i < 0){
                break;
            } else if(chessBoard_CC[kp_y][kp_x - i] == black_rook || chessBoard_CC[kp_y][kp_x - i] == black_queen){
                return true;
            } else if(chessBoard_CC[kp_y][kp_x - i] >= 1 && chessBoard_CC[kp_y][kp_x - i] != black_rook && chessBoard_CC[kp_y][kp_x - i] != black_queen){
                break;
            } else{
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up
            if(kp_y - i < 0){
                break;
            } else if(chessBoard_CC[kp_y - i][kp_x] == black_rook || chessBoard_CC[kp_y - i][kp_x] == black_queen){
                return true;
            } else if(chessBoard_CC[kp_y - i][kp_x] >= 1 && chessBoard_CC[kp_y - i][kp_x] != black_rook && chessBoard_CC[kp_y - i][kp_x] != black_queen){
                break;
            } else{
            }
        }
        for(int64_t i = 1; i < 8; i++){ // right
            if(kp_x + i > 7){
                break;
            } else if(chessBoard_CC[kp_y][kp_x + i] == black_rook || chessBoard_CC[kp_y][kp_x + i] == black_queen){
                return true;
            } else if(chessBoard_CC[kp_y][kp_x + i] >= 1 && chessBoard_CC[kp_y][kp_x + i] != black_rook && chessBoard_CC[kp_y][kp_x + i] != black_queen){
                break;
            } else{
            }
        }
        if(chessBoard_CC[kp_y + 1][kp_x + 2] == black_knight && kp_y + 1 <= 7 && kp_x + 2 <= 7){ // knight checks ~
            return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x - 2] == black_knight && kp_y + 1 <= 7 && kp_x - 2 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x + 2] == black_knight && kp_y - 1 >= 0 && kp_x + 2 <= 7){
            return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x - 2] == black_knight && kp_y - 1 >= 0 && kp_x - 2 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y + 2][kp_x + 1] == black_knight && kp_y + 2 <= 7 && kp_x + 1 <= 7){
            return true;
        } else if(chessBoard_CC[kp_y + 2][kp_x - 1] == black_knight && kp_y + 2 <= 7 && kp_x - 1 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y - 2][kp_x + 1] == black_knight && kp_y - 2 >= 0 && kp_x + 1 <= 7){
            return true;
        } else if(chessBoard_CC[kp_y - 2][kp_x - 1] == black_knight && kp_y - 2 >= 0 && kp_x - 1 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x + 1] == black_pawn && kp_y - 1 >= 0 && kp_x + 1 <= 7){ // pawn checks ~
            return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x - 1] == black_pawn && kp_y - 1 >= 0 && kp_x - 1 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x + 1] == black_king && kp_y + 1 <= 7 && kp_x + 1 <= 7){ // king 'checks' ~
            return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x - 1] == black_king && kp_y + 1 <= 7 && kp_x - 1 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x + 1] == black_king && kp_y - 1 >= 0 && kp_x + 1 <= 7){
            return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x - 1] == black_king && kp_y - 1 >= 0 && kp_x - 1 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x] == black_king && kp_y + 1 <= 7){
            return true;
        } else if(chessBoard_CC[kp_y][kp_x - 1] == black_king && kp_x - 1 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x] == black_king && kp_y - 1 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y][kp_x + 1] == black_king && kp_x + 1 <= 7){
            return true;
        } else{
        }
        return false;
    }
    else{
        int64_t kp_y = 0;
        int64_t kp_x = 0;
        for(int64_t i = 0; i <= 7; i++){
            for(int64_t j = 0; j <= 7; j++){
                if(chessBoard_CC[i][j] == black_king){
                    kp_y = i;
                    kp_x = j;
                    break;
                }
            }
        }
        for(int64_t i = 1; i < 8; i++){ // down & right
            if(kp_y + i > 7 || kp_x + i > 7){
                break;    
            } else if(chessBoard_CC[kp_y + i][kp_x + i] == white_bishop || chessBoard_CC[kp_y + i][kp_x + i] == white_queen){
                return true;
            } else if(chessBoard_CC[kp_y + i][kp_x + i] >= 1 && chessBoard_CC[kp_y + i][kp_x + i] != white_bishop && chessBoard_CC[kp_y + i][kp_x + i] != white_queen){
                break;
            } else{
            }
        }
        for(int64_t i = 1; i < 8; i++){ // down & left
            if(kp_y + i > 7 || kp_x - i < 0){
                break;
            } else if(chessBoard_CC[kp_y + i][kp_x - i] == white_bishop || chessBoard_CC[kp_y + i][kp_x - i] == white_queen){
                return true;
            } else if(chessBoard_CC[kp_y + i][kp_x - i] >= 1 && chessBoard_CC[kp_y + i][kp_x - i] != white_bishop && chessBoard_CC[kp_y + i][kp_x - i] != white_queen){
                break;
            } else{
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up & left
            if(kp_y - i < 0 || kp_x - i < 0){
                break;   
            } else if(chessBoard_CC[kp_y - i][kp_x - i] == white_bishop || chessBoard_CC[kp_y - i][kp_x - i] == white_queen){
                return true;
            } else if(chessBoard_CC[kp_y - i][kp_x - i] >= 1 && chessBoard_CC[kp_y - i][kp_x - i] != white_bishop && chessBoard_CC[kp_y - i][kp_x - i] != white_queen){
                break;
            } else{
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up & right
            if(kp_y - i < 0 || kp_x + i > 7){
                break;   
            } else if(chessBoard_CC[kp_y - i][kp_x + i] == white_bishop || chessBoard_CC[kp_y - i][kp_x + i] == white_queen){
                return true;
            } else if(chessBoard_CC[kp_y - i][kp_x + i] >= 1 && chessBoard_CC[kp_y - i][kp_x + i] != white_bishop && chessBoard_CC[kp_y - i][kp_x + i] != white_queen){
                break;
            } else{
            }
        }
        for(int64_t i = 1; i < 8; i++){ // down
            if(kp_y + i > 7){
                break;
            } else if(chessBoard_CC[kp_y + i][kp_x] == white_rook || chessBoard_CC[kp_y + i][kp_x] == white_queen){
                return true;
            } else if(chessBoard_CC[kp_y + i][kp_x] >= 1 && chessBoard_CC[kp_y + i][kp_x] != white_rook && chessBoard_CC[kp_y + i][kp_x] != white_queen){
                break;
            } else{
            }
        }
        for(int64_t i = 1; i < 8; i++){ // left
            if(kp_x - i < 0){
                break;
            } else if(chessBoard_CC[kp_y][kp_x - i] == white_rook || chessBoard_CC[kp_y][kp_x - i] == white_queen){
                return true;
            } else if(chessBoard_CC[kp_y][kp_x - i] >= 1 && chessBoard_CC[kp_y][kp_x - i] != white_rook && chessBoard_CC[kp_y][kp_x - i] != white_queen){
                break;
            } else{
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up
            if(kp_y - i < 0){
                break;
            } else if(chessBoard_CC[kp_y - i][kp_x] == white_rook || chessBoard_CC[kp_y - i][kp_x] == white_queen){
                return true;
            } else if(chessBoard_CC[kp_y - i][kp_x] >= 1 && chessBoard_CC[kp_y - i][kp_x] != white_rook && chessBoard_CC[kp_y - i][kp_x] != white_queen){
                break;
            } else{
            }
        }
        for(int64_t i = 1; i < 8; i++){ // right
            if(kp_x + i > 7){
                break;
            } else if(chessBoard_CC[kp_y][kp_x + i] == white_rook || chessBoard_CC[kp_y][kp_x + i] == white_queen){
                return true;
            } else if(chessBoard_CC[kp_y][kp_x + i] >= 1 && chessBoard_CC[kp_y][kp_x + i] != white_rook && chessBoard_CC[kp_y][kp_x + i] != white_queen){
                break;
            } else{
            }
        }
        if(chessBoard_CC[kp_y + 1][kp_x + 2] == white_knight && kp_y + 1 <= 7 && kp_x + 2 <= 7){ // knight checks ~
            return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x - 2] == white_knight && kp_y + 1 <= 7 && kp_x - 2 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x + 2] == white_knight && kp_y - 1 >= 0 && kp_x + 2 <= 7){
            return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x - 2] == white_knight && kp_y - 1 >= 0 && kp_x - 2 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y + 2][kp_x + 1] == white_knight && kp_y + 2 <= 7 && kp_x + 1 <= 7){
            return true;
        } else if(chessBoard_CC[kp_y + 2][kp_x - 1] == white_knight && kp_y + 2 <= 7 && kp_x - 1 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y - 2][kp_x + 1] == white_knight && kp_y - 2 >= 0 && kp_x + 1 <= 7){
            return true;
        } else if(chessBoard_CC[kp_y - 2][kp_x - 1] == white_knight && kp_y - 2 >= 0 && kp_x - 1 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x + 1] == white_pawn && kp_y + 1 >= 0 && kp_x + 1 <= 7){ // pawn checks ~
            return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x - 1] == white_pawn && kp_y + 1 <= 7 && kp_x - 1 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x + 1] == white_king && kp_y + 1 <= 7 && kp_x + 1 <= 7){ // king 'checks' ~
            return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x - 1] == white_king && kp_y + 1 <= 7 && kp_x - 1 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x + 1] == white_king && kp_y - 1 >= 0 && kp_x + 1 <= 7){
            return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x - 1] == white_king && kp_y - 1 >= 0 && kp_x - 1 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x] == white_king && kp_y + 1 <= 7){
            return true;
        } else if(chessBoard_CC[kp_y][kp_x - 1] == white_king && kp_x - 1 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x] == white_king && kp_y - 1 >= 0){
            return true;
        } else if(chessBoard_CC[kp_y][kp_x + 1] == white_king && kp_x + 1 <= 7){
            return true;
        } else{
        }
        return false;
    }
}
void insertMove_white(int64_t se){
    if(se == 1){
        playMove_CC(0);
        if(check(1)){
            memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
        } else{
            moveList[0][n] = y;
            moveList[1][n] = x;
            moveList[2][n] = y_to;
            moveList[3][n] = x_to;
            n++;
            memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
        }
    } else{
        playMove_CC(0);
        if(check(1)){
            memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
        } else{
            eml[0][o] = y;
            eml[1][o] = x;
            eml[2][o] = y_to;
            eml[3][o] = x_to;
            o++;
            memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
        }
    }
}
void insertMove_black(int64_t se){
    if(se == 1){
        playMove_CC(0);
        if(check(0)){
            memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
        } else{
            moveList[0][n] = y;
            moveList[1][n] = x;
            moveList[2][n] = y_to;
            moveList[3][n] = x_to;
            n++;
            memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
        }
    } else{
        playMove_CC(0);
        if(check(0)){
            memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
        } else{
            eml[0][o] = y;
            eml[1][o] = x;
            eml[2][o] = y_to;
            eml[3][o] = x_to;
            o++;
            memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
        }
    }
}  
int64_t pieceCount(){
    int64_t pieceCount = 0;
    for(int64_t i = 0; i < 8; i++){
        for(int64_t j = 0; j < 8; j++){
            if(chessBoard[i][j] != empty_square){
                pieceCount++;
            }
        }
    }
    return pieceCount;
}

// (castling through check & en passant)
class Move_gen{
    public:     
        void w_pawn(int64_t se){
            if(chessBoard[y - 1][x] == 0){
                y_to = y - 1;
                x_to = x;
                insertMove_white(se);
            }
            if(chessBoard[y - 1][x + 1] >= 11){
                if(x + 1 <= 7){
                    y_to = y - 1;
                    x_to = x + 1;
                    insertMove_white(se);
                }
            }
            if(chessBoard[y - 1][x - 1] >= 11){
                if(x - 1 >= 0){
                    y_to = y - 1;
                    x_to = x - 1;
                    insertMove_white(se);
                }
            }
            if(y == 6){
                if(chessBoard[y - 1][x] == 0 && chessBoard[y - 2][x] == 0){
                    y_to = y - 2;
                    x_to = x;
                    insertMove_white(se);   
                }
            } 
        }
        void b_pawn(int64_t se){
            if(chessBoard[y + 1][x] == 0){
                y_to = y + 1;
                x_to = x;
                insertMove_black(se);
            }
            if(chessBoard[y + 1][x + 1] <= 6 && chessBoard[y + 1][x + 1] > 0){
                if(x + 1 <= 7){
                    y_to = y + 1;
                    x_to = x + 1;
                    insertMove_black(se);
                }
            }
            if(chessBoard[y + 1][x - 1] <= 6 && chessBoard[y + 1][x - 1] > 0){
                if(x - 1 >= 0){
                    y_to = y + 1;
                    x_to = x - 1;
                    insertMove_black(se);
                }
            }
            if(y == 1){
                if(chessBoard[y + 1][x] == 0 && chessBoard[y + 2][x] == 0){
                    y_to = y + 2;
                    x_to = x;
                    insertMove_black(se); 
                }
            } 
        }
        void w_knight(int64_t se){
            if(chessBoard[y + 1][x + 2] >= 11 || chessBoard[y + 1][x + 2] == 0){
                if(y + 1 <= 7 && x + 2 <= 7){
                    y_to = y + 1;
                    x_to = x + 2;
                    insertMove_white(se);
                }
            }
            if(chessBoard[y - 1][x + 2] >= 11 || chessBoard[y - 1][x + 2] == 0){
                if(y - 1 >= 0 && x + 2 <= 7){
                    y_to = y - 1;
                    x_to = x + 2;
                    insertMove_white(se);
                } 
            }
            if(chessBoard[y + 1][x - 2] >= 11 || chessBoard[y + 1][x - 2] == 0){
                if(y + 1 <= 7 && x - 2 >= 0){
                    y_to = y + 1;
                    x_to = x - 2;
                    insertMove_white(se);
                }
            }
            if(chessBoard[y - 1][x - 2] >= 11 || chessBoard[y - 1][x - 2] == 0){
                if(y - 1 >= 0 && x - 2 >= 0){
                    y_to = y - 1;
                    x_to = x - 2;
                    insertMove_white(se);
                } 
            }
            if(chessBoard[y + 2][x + 1] >= 11 || chessBoard[y + 2][x + 1] == 0){
                if(y + 2 <= 7 && x + 1 <= 7){
                    y_to = y + 2;
                    x_to = x + 1;
                    insertMove_white(se);
                }
            }
            if(chessBoard[y - 2][x + 1] >= 11 || chessBoard[y - 2][x + 1] == 0){
                if(y - 2 >= 0 && x + 1 <= 7){
                    y_to = y - 2;
                    x_to = x + 1;
                    insertMove_white(se);
                }
            }
            if(chessBoard[y + 2][x - 1] >= 11 || chessBoard[y + 2][x - 1] == 0){
                if(y + 2 <= 7 && x - 1 >= 0){
                    y_to = y + 2;
                    x_to = x - 1;
                    insertMove_white(se);
                }
            }
            if(chessBoard[y - 2][x - 1] >= 11 || chessBoard[y - 2][x - 1] == 0){
                if(y - 2 >= 0 && x - 1 >= 0){
                    y_to = y - 2;
                    x_to = x - 1;
                    insertMove_white(se);
                }
            }
        }
        void b_knight(int64_t se){
            if(chessBoard[y + 1][x + 2] <= 6 || chessBoard[y + 1][x + 2] == 0){
                if(y + 1 <= 7 && x + 2 <= 7){
                    y_to = y + 1;
                    x_to = x + 2;
                    insertMove_black(se);
                }
            }
            if(chessBoard[y - 1][x + 2] <= 6 || chessBoard[y - 1][x + 2] == 0){
                if(y - 1 >= 0 && x + 2 <= 7){
                    y_to = y - 1;
                    x_to = x + 2;
                    insertMove_black(se);
                } 
            }
            if(chessBoard[y + 1][x - 2] <= 6 || chessBoard[y + 1][x - 2] == 0){
                if(y + 1 <= 7 && x - 2 >= 0){
                    y_to = y + 1;
                    x_to = x - 2;
                    insertMove_black(se);
                }
            }
            if(chessBoard[y - 1][x - 2] <= 6 || chessBoard[y - 1][x - 2] == 0){
                if(y - 1 >= 0 && x - 2 >= 0){
                    y_to = y - 1;
                    x_to = x - 2;
                    insertMove_black(se);
                } 
            }
            if(chessBoard[y + 2][x + 1] <= 6 || chessBoard[y + 2][x + 1] == 0){
                if(y + 2 <= 7 && x + 1 <= 7){
                    y_to = y + 2;
                    x_to = x + 1;
                    insertMove_black(se);
                }
            }
            if(chessBoard[y - 2][x + 1] <= 6 || chessBoard[y - 2][x + 1] == 0){
                if(y - 2 >= 0 && x + 1 <= 7){
                    y_to = y - 2;
                    x_to = x + 1;
                    insertMove_black(se);
                }
            }
            if(chessBoard[y + 2][x - 1] <= 6 || chessBoard[y + 2][x - 1] == 0){
                if(y + 2 <= 7 && x - 1 >= 0){
                    y_to = y + 2;
                    x_to = x - 1;
                    insertMove_black(se);
                }
            }
            if(chessBoard[y - 2][x - 1] <= 6 || chessBoard[y - 2][x - 1] == 0){
                if(y - 2 >= 0 && x - 1 >= 0){
                    y_to = y - 2;
                    x_to = x - 1;
                    insertMove_black(se);
                }
            }
        }
        void w_bishop(int64_t se){
            for(int64_t i = 1; i < 8; i++){ // down & right
                if(y + i > 7 || x + i > 7){
                    break;
                }
                if(chessBoard[y + i][x + i] == empty_square){
                    y_to = y + i;
                    x_to = x + i;
                    insertMove_white(se);
                } else if(chessBoard[y + i][x + i] <= 6 && chessBoard[y + i][x + i] != empty_square){
                    break;
                } else if(chessBoard[y + i][x + i] >= 11){
                    y_to = y + i;
                    x_to = x + i;
                    insertMove_white(se);
                    break;
                }
            }
            for(int64_t i = 1; i < 8; i++){ // down & left
                if(y + i > 7 || x - i < 0){
                    break;
                }
                if(chessBoard[y + i][x - i] == empty_square){
                    y_to = y + i;
                    x_to = x - i;
                    insertMove_white(se);
                } else if(chessBoard[y + i][x - i] <= 6 && chessBoard[y + i][x - i] != empty_square){
                    break;
                } else if(chessBoard[y + i][x - i] >= 11){
                    y_to = y + i;
                    x_to = x - i;
                    insertMove_white(se);
                    break;
                }
            }
            for(int64_t i = 1; i < 8; i++){ // up & left
                if(y - i < 0 || x - i < 0){
                    break;
                }
                if(chessBoard[y - i][x - i] == empty_square){
                    y_to = y - i;
                    x_to = x - i;
                    insertMove_white(se);
                } else if(chessBoard[y - i][x - i] <= 6 && chessBoard[y - i][x - i] != empty_square){
                    break;
                } else if(chessBoard[y - i][x - i] >= 11){
                    y_to = y - i;
                    x_to = x - i;
                    insertMove_white(se);
                    break;
                }
            }
            for(int64_t i = 1; i < 8; i++){ // up & right
                if(y - i < 0 || x + i > 7){
                    break;
                }
                if(chessBoard[y - i][x + i] == empty_square){
                    y_to = y - i;
                    x_to = x + i;
                    insertMove_white(se);
                } else if(chessBoard[y - i][x + i] <= 6 && chessBoard[y - i][x + i] != empty_square){
                    break;
                } else if(chessBoard[y - i][x + i] >= 11){
                    y_to = y - i;
                    x_to = x + i;
                    insertMove_white(se);
                    break;
                }
            }
        }
        void b_bishop(int64_t se){
            for(int64_t i = 1; i < 8; i++){ // down & right
                if(y + i > 7 || x + i > 7){
                    break;
                }
                if(chessBoard[y + i][x + i] == empty_square){
                    y_to = y + i;
                    x_to = x + i;
                    insertMove_black(se);
                } else if(chessBoard[y + i][x + i] >= 11){
                    break;
                } else if(chessBoard[y + i][x + i] <= 6 && chessBoard[y + i][x + i] != 0){
                    y_to = y + i;
                    x_to = x + i;
                    insertMove_black(se);
                    break;
                }
            }
            for(int64_t i = 1; i < 8; i++){ // down & left
                if(y + i > 7 || x - i < 0){
                    break;
                }
                if(chessBoard[y + i][x - i] == empty_square){
                    y_to = y + i;
                    x_to = x - i;
                    insertMove_black(se);
                } else if(chessBoard[y + i][x - i] >= 11){
                    break;
                } else if(chessBoard[y + i][x - i] <= 6 && chessBoard[y + i][x - i] != 0){
                    y_to = y + i;
                    x_to = x - i;
                    insertMove_black(se);
                    break;
                }
            }
            for(int64_t i = 1; i < 8; i++){ // up & left
                if(y - i < 0 || x - i < 0){
                    break;
                }
                if(chessBoard[y - i][x - i] == empty_square){
                    y_to = y - i;
                    x_to = x - i;
                    insertMove_black(se);
                } else if(chessBoard[y - i][x - i] >= 11){
                    break;
                } else if(chessBoard[y - i][x - i] <= 6 && chessBoard[y - i][x - i] != empty_square){
                    y_to = y - i;
                    x_to = x - i;
                    insertMove_black(se);
                    break;
                }
            }
            for(int64_t i = 1; i < 8; i++){ // up & right
                if(y - i < 0 || x + i > 7){
                    break;
                }
                if(chessBoard[y - i][x + i] == empty_square){
                    y_to = y - i;
                    x_to = x + i;
                    insertMove_black(se);
                } else if(chessBoard[y - i][x + i] >= 11){
                    break;
                } else if(chessBoard[y - i][x + i] <= 6 && chessBoard[y - i][x + i] != empty_square){
                    y_to = y - i;
                    x_to = x + i;
                    insertMove_black(se);
                    break;
                }
            }
        }
        void w_rook(int64_t se){
            for(int64_t i = 1; i < 8; i++){ // down
                if(y + i > 7){
                    break;
                } else if(chessBoard[y + i][x] == empty_square){
                    y_to = y + i;
                    x_to = x;
                    insertMove_white(se);
                } else if(chessBoard[y + i][x] <= 6 && chessBoard[y + i][x] != empty_square){
                    break;
                } else if(chessBoard[y + i][x] >= 11){
                    y_to = y + i;
                    x_to = x;
                    insertMove_white(se);
                    break;
                }
            }
            for(int64_t i = 1; i < 8; i++){ // left
                if(x - i < 0){
                    break;
                } else if(chessBoard[y][x - i] == empty_square){
                    y_to = y;
                    x_to = x - i;
                    insertMove_white(se);
                } else if(chessBoard[y][x - i] <= 6 && chessBoard[y][x - i] != empty_square){
                    break;
                } else if(chessBoard[y][x - i] >= 11){
                    y_to = y;
                    x_to = x - i;
                    insertMove_white(se);
                    break;
                }
            }
            for(int64_t i = 1; i < 8; i++){ // up
                if(y - i < 0){
                    break;
                } else if(chessBoard[y - i][x] == empty_square){
                    y_to = y - i;
                    x_to = x;
                    insertMove_white(se);
                } else if(chessBoard[y - i][x] <= 6 && chessBoard[y - i][x] != empty_square){
                    break;
                } else if(chessBoard[y - i][x] >= 11){
                    y_to = y - i;
                    x_to = x;
                    insertMove_white(se);
                    break;
                }
            }
            for(int64_t i = 1; i < 8; i++){ // right
                if(x + i > 7){
                    break;
                } else if(chessBoard[y][x + i] == empty_square){
                    y_to = y;
                    x_to = x + i;
                    insertMove_white(se);
                } else if(chessBoard[y][x + i] <= 6 && chessBoard[y][x + i] != empty_square){
                    break;
                } else if(chessBoard[y][x + i] >= 11){
                    y_to = y;
                    x_to = x + i;
                    insertMove_white(se);
                    break;
                }
            }
        }
        void b_rook(int64_t se){
            for(int64_t i = 1; i < 8; i++){ // down
                if(y + i > 7){
                    break;
                } else if(chessBoard[y + i][x] == empty_square){
                    y_to = y + i;
                    x_to = x;
                    insertMove_black(se);
                } else if(chessBoard[y + i][x] >= 11){
                    break;
                } else if(chessBoard[y + i][x] <= 6 && chessBoard[y + i][x] != empty_square){
                    y_to = y + i;
                    x_to = x;
                    insertMove_black(se);
                    break;
                }
            }
            for(int64_t i = 1; i < 8; i++){ // left
                if(x - i < 0){
                    break;
                } else if(chessBoard[y][x - i] == empty_square){
                    y_to = y;
                    x_to = x - i;
                    insertMove_black(se);
                } else if(chessBoard[y][x - i] >= 11){
                    break;
                } else if(chessBoard[y][x - i] <= 6 && chessBoard[y][x - i] != empty_square){
                    y_to = y;
                    x_to = x - i;
                    insertMove_black(se);
                    break;
                }
            }
            for(int64_t i = 1; i < 8; i++){ // up
                if(y - i < 0){
                    break;
                } else if(chessBoard[y - i][x] == empty_square){
                    y_to = y - i;
                    x_to = x;
                    insertMove_black(se);
                } else if(chessBoard[y - i][x] >= 11){
                    break;
                } else if(chessBoard[y - i][x] <= 6 && chessBoard[y - i][x] != empty_square){
                    y_to = y - i;
                    x_to = x;
                    insertMove_black(se);
                    break;
                }
            }
            for(int64_t i = 1; i < 8; i++){ // right
                if(x + i > 7){
                    break;
                } else if(chessBoard[y][x + i] == empty_square){
                    y_to = y;
                    x_to = x + i;
                    insertMove_black(se);
                } else if(chessBoard[y][x + i] >= 11){
                    break;
                } else if(chessBoard[y][x + i] <= 6 && chessBoard[y][x + i] != empty_square){
                    y_to = y;
                    x_to = x + i;
                    insertMove_black(se);
                    break;
                }
            }
        }
        void w_queen(int64_t se){
            w_bishop(se);
            w_rook(se);
        }
        void b_queen(int64_t se){
            b_bishop(se);
            b_rook(se);
        }
        void w_king(int64_t se){
            if(chessBoard[y + 1][x] == empty_square || chessBoard[y + 1][x] >= 11){
                if(y + 1 <= 7){
                    y_to = y + 1;
                    x_to = x;
                    insertMove_white(se);
                }
            }
            if(chessBoard[y - 1][x] == empty_square || chessBoard[y - 1][x] >= 11){
                if(y - 1 >= 0){
                    y_to = y - 1;
                    x_to = x;
                    insertMove_white(se);
                }
            }
            if(chessBoard[y][x + 1] == empty_square || chessBoard[y][x + 1] >= 11){
                if(x + 1 <= 7){
                    y_to = y;
                    x_to = x + 1;
                    insertMove_white(se);
                }
            }
            if(chessBoard[y][x - 1] == empty_square || chessBoard[y][x - 1] >= 11){
                if(x - 1 >= 0){
                    y_to = y;
                    x_to = x - 1;
                    insertMove_white(se);
                }
            }
            if(chessBoard[y + 1][x + 1] == empty_square || chessBoard[y + 1][x + 1] >= 11){
                if(y + 1 <= 7 && x + 1 <= 7){
                    y_to = y + 1;
                    x_to = x + 1;
                    insertMove_white(se);
                }
            }
            if(chessBoard[y + 1][x - 1] == empty_square || chessBoard[y + 1][x - 1] >= 11){
                if(y + 1 <= 7 && x - 1 >= 0){
                    y_to = y + 1;
                    x_to = x - 1;
                    insertMove_white(se);
                }
            }
            if(chessBoard[y - 1][x + 1] == empty_square || chessBoard[y - 1][x + 1] >= 11){
                if(y - 1 >= 0 && x + 1 <= 7){
                    y_to = y - 1;
                    x_to = x + 1;
                    insertMove_white(se);
                }
            }
            if(chessBoard[y - 1][x - 1] == empty_square || chessBoard[y - 1][x - 1] >= 11){
                if(y - 1 >= 0 && x - 1 >= 0){
                    y_to = y - 1;
                    x_to = x - 1;
                    insertMove_white(se);
                }
            }
            if(y == 7 && x == 4 && KSCastlingRights_white && chessBoard[7][5] == empty_square && chessBoard[7][6] == empty_square){ // castling KS
                y_to = y;
                x_to = x + 2;
                insertMove_white(se);
            }
            if(y == 7 && x == 4 && QSCastlingRights_white && chessBoard[7][3] == 0 && chessBoard[7][2] == 0 && chessBoard[7][1] == 0){ // castling QS
                y_to = y;
                x_to = x - 2;
                insertMove_white(se);
            }
        }
        void b_king(int64_t se){
            if(chessBoard[y + 1][x] <= 6){
                if(y + 1 <= 7){
                    y_to = y + 1;
                    x_to = x;
                    insertMove_black(se);
                }
            }
            if(chessBoard[y - 1][x] <= 6){
                if(y - 1 >= 0){
                    y_to = y - 1;
                    x_to = x;
                    insertMove_black(se);
                }
            }
            if(chessBoard[y][x + 1] <= 6){
                if(x + 1 <= 7){
                    y_to = y;
                    x_to = x + 1;
                    insertMove_black(se);
                }
            }
            if(chessBoard[y][x - 1] <= 6){
                if(x - 1 >= 0){
                    y_to = y;
                    x_to = x - 1;
                    insertMove_black(se);
                }
            }
            if(chessBoard[y + 1][x + 1] <= 6){
                if(y + 1 <= 7 && x + 1 <= 7){
                    y_to = y + 1;
                    x_to = x + 1;
                    insertMove_black(se);
                }
            }
            if(chessBoard[y + 1][x - 1] <= 6){
                if(y + 1 <= 7 && x - 1 >= 0){
                    y_to = y + 1;
                    x_to = x - 1;
                    insertMove_black(se);
                }
            }
            if(chessBoard[y - 1][x + 1] <= 6){
                if(y - 1 >= 0 && x + 1 <= 7){
                    y_to = y - 1;
                    x_to = x + 1;
                    insertMove_black(se);
                }
            }
            if(chessBoard[y - 1][x - 1] <= 6){
                if(y - 1 >= 0 && x - 1 >= 0){
                    y_to = y - 1;
                    x_to = x - 1;
                    insertMove_black(se);
                }
            }
            if(y == 0 && x == 4 && KSCastlingRights_black && chessBoard[0][5] == empty_square && chessBoard[0][6] == empty_square){ // castling KS
                y_to = y;
                x_to = x + 2;
                insertMove_black(se);
            }
            if(y == 0 && x == 4 && QSCastlingRights_black && chessBoard[0][3] == 0 && chessBoard[0][2] == 0 && chessBoard[0][1] == 0){ // castling QS
                y_to = y;
                x_to = x - 2;
                insertMove_black(se);
            }
        }
};
Move_gen moveGen;

void initializeBoard(){
    int64_t FENpos = 0;
    for(int64_t i = 0; i < 8; i++){
        for(int64_t j = 0; j < 8; j++){
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
    memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
}
void printBoard(){
    cout << "-----------------------------------------" << endl;
    for(int64_t y_pos = 0; y_pos < 8; y_pos++){
        cout << "|";
        for(int64_t x_pos = 0; x_pos < 8; x_pos++){
            if(chessBoard[y_pos][x_pos] == white_pawn){
                cout << "  P |";
            } else if(chessBoard[y_pos][x_pos] == white_knight){
                cout << "  N |";
            } else if(chessBoard[y_pos][x_pos] == white_bishop){
                cout << "  B |";
            } else if(chessBoard[y_pos][x_pos] == white_rook){
                cout << "  R |";
            } else if(chessBoard[y_pos][x_pos] == white_queen){
                cout << "  Q |";
            } else if(chessBoard[y_pos][x_pos] == white_king){
                cout << "  K |";
            } else if(chessBoard[y_pos][x_pos] == black_pawn){
                cout << "  p |";
            } else if(chessBoard[y_pos][x_pos] == black_knight){
                cout << "  n |";
            } else if(chessBoard[y_pos][x_pos] == black_bishop){
                cout << "  b |";
            } else if(chessBoard[y_pos][x_pos] == black_rook){
                cout << "  r |";
            } else if(chessBoard[y_pos][x_pos] == black_queen){
                cout << "  q |";
            } else if(chessBoard[y_pos][x_pos] == black_king){
                cout << "  k |";
            } else{
                cout << "  - |";
            }
        }
        cout << endl;
        cout << "-----------------------------------------" << endl;
    }
    cout << endl;
}

// ----------------------------------------------------------------------- Search & Evaluation -----------------------------------------------------------------------

class Evaluation{
    public:
        int64_t material(){
            int64_t material_eval = 0;
            for(int64_t i = 0; i < 8; i++){
                for(int64_t j = 0; j < 8; j++){
                    if(chessBoard[i][j] <= 6 && chessBoard[i][j] != 0){
                        material_eval += value(chessBoard[i][j]);
                    } else if(chessBoard[i][j] >= 11){
                        material_eval -= value(chessBoard[i][j]);
                    }
                }
            }
            return material_eval;
        }
        int64_t development(){
            int64_t development = 0;
            for(int64_t i = 0; i < 8; i++){
                if(chessBoard[7][i] == empty_square || chessBoard[7][i] == white_king || chessBoard[7][i] == white_rook){
                    development += 10;
                }
                if(chessBoard[0][i] == empty_square || chessBoard[0][i] == black_king || chessBoard[7][i] == black_rook){
                    development -= 10;
                }
            }
            for(int64_t i = 0; i < 2; i++){
                for(int64_t j = 0; j < 4; j++){
                    if(chessBoard[4 + i][2 + j] == white_pawn){
                        development += 5;
                    }
                }
            }
            for(int64_t i = 0; i < 2; i++){
                for(int64_t j = 0; j < 4; j++){
                    if(chessBoard[2 + i][2 + j] == black_pawn){
                        development -= 5;
                    }
                }
            }
            return development;
        } 
        int64_t endgameKingRestriction(){
            int64_t kingRestriction = 0;
            int64_t kp_y;
            int64_t kp_x;
            for(int64_t i = 0; i <= 7; i++){
                for(int64_t j = 0; j <= 7; j++){
                    if(chessBoard_CC[i][j] == white_king){
                        kp_y = i;
                        kp_x = j;
                        break;
                    }
                }
            }
            if(kp_y > 3){
                kingRestriction -= 5 * (-4 + kp_y);
            } else{
                kingRestriction -= 5 * (3 - kp_y);
            }
            if(kp_x > 3){
                kingRestriction -= 5 * (-4 + kp_x);
            } else{
                kingRestriction -= 5 * (3 - kp_x);
            }
            for(int64_t i = 0; i <= 7; i++){
                for(int64_t j = 0; j <= 7; j++){
                    if(chessBoard_CC[i][j] == black_king){
                        kp_y = i;
                        kp_x = j;
                        break;
                    }
                }
            }
            if(kp_y > 3){
                kingRestriction += 5 * (-4 + kp_y);
            } else{
                kingRestriction += 5 * (3 - kp_y);
            }
            if(kp_x > 3){
                kingRestriction += 5 * (-4 + kp_x);
            } else{
                kingRestriction += 5 * (3 - kp_x);
            }
            return kingRestriction;
        }
};
Evaluation evaluation;

void order(){
    int64_t orderIndex = 0;
    for(int64_t i = 0; i < n; i++){
        if(value(chessBoard[moveList[2][i]][moveList[3][i]]) > 100){
            swap(moveList[0][i], moveList[0][orderIndex]);
            swap(moveList[1][i], moveList[1][orderIndex]);
            swap(moveList[2][i], moveList[2][orderIndex]);
            swap(moveList[3][i], moveList[3][orderIndex]);
            orderIndex++;
        }
    }
}
void generateMoves(int64_t side, int64_t se){
    if(se == 1){
        n = 0;
        memset(moveList, 0, sizeof(moveList));
    } else{
        o = 0;
        memset(eml, 0, sizeof(eml));
    }
    if(side == 1){
        for(int64_t i = 0; i < 8; i++){
            y = i;
            for(int64_t j = 0; j < 8; j++){
                x = j;
                if(chessBoard[y][x] == white_pawn){
                    moveGen.w_pawn(se);
                } else if(chessBoard[y][x] == white_knight){
                    moveGen.w_knight(se);
                } else if(chessBoard[y][x] == white_bishop){
                    moveGen.w_bishop(se);
                } else if(chessBoard[y][x] == white_rook){
                    moveGen.w_rook(se);
                } else if(chessBoard[y][x] == white_queen){
                    moveGen.w_queen(se);
                } else if(chessBoard[y][x] == white_king){
                    moveGen.w_king(se);
                } else{
                }
            }
        }
    }
    else{
        for(int64_t i = 0; i < 8; i++){
            y = i;
            for(int64_t j = 0; j < 8; j++){
                x = j;
                if(chessBoard[y][x] == black_pawn){
                    moveGen.b_pawn(se);
                } else if(chessBoard[y][x] == black_knight){
                    moveGen.b_knight(se);
                } else if(chessBoard[y][x] == black_bishop){
                    moveGen.b_bishop(se);
                } else if(chessBoard[y][x] == black_rook){
                    moveGen.b_rook(se);
                } else if(chessBoard[y][x] == black_queen){
                    moveGen.b_queen(se);
                } else if(chessBoard[y][x] == black_king){
                    moveGen.b_king(se);
                } else{
                }
            }
        }
    }
}
void assign(int64_t index){
    move_y = moveList[0][index];
    move_x = moveList[1][index];
    moveTo_y = moveList[2][index];
    moveTo_x = moveList[3][index];  
}

// add checks to enemy moves eval
int64_t staticEval(int64_t side, int64_t dtm){
    if(side == 1){
        int64_t eval = 0;
        generateMoves(1, 2);
        if(o == 0){
            if(check(1)){
                return (-1000000 - dtm);
            } else{
                return 0;
            }
        }
        int64_t responses[219] = {0};
        for(int64_t i = 0; i < o; i++){
            if(value(chessBoard[eml[2][i]][eml[3][i]]) > value(chessBoard[eml[0][i]][eml[1][i]])){
                responses[i] = value(chessBoard[eml[2][i]][eml[3][i]]) - value(chessBoard[eml[0][i]][eml[1][i]]);
            }
        }
        eval += evaluation.material() + getMax(responses, o);
        if(opening){
            eval += evaluation.development();
        }
        if(endgame){
            eval += evaluation.endgameKingRestriction();
        }
        return eval;
    } else{
        int64_t eval = 0;
        generateMoves(0, 2);
        if(o == 0){
            if(check(0)){
                return (1000000 + dtm);
            } else{
                return 0;
            }
        }
        int64_t responses[219] = {0};
        for(int64_t i = 0; i < o; i++){
            if(value(chessBoard[eml[2][i]][eml[3][i]]) > value(chessBoard[eml[0][i]][eml[1][i]])){
                responses[i] = value(chessBoard[eml[2][i]][eml[3][i]]) - value(chessBoard[eml[0][i]][eml[1][i]]);
            }
        }
        eval += evaluation.material() - getMax(responses, o);
        if(opening){
            eval += evaluation.development();
        }
        if(endgame){
            eval += evaluation.endgameKingRestriction();
        }
        return eval;    
    }
}








// search
int search(int64_t depth, int64_t cap, int64_t alpha, int64_t beta){
    if(depth == 0){
        TEST++;
        return staticEval(1, 0);
    }
    generateMoves((depth + 1) % 2, 1);
    order();
    if(n == 0){
        if(check((depth + 1) % 2)){
            memcpy(chessBoard, boardStates[depth + 1], sizeof(chessBoard));
            generateMoves(depth % 2, 1);
            order();
            return -(1000000 + depth);
        }
        return 0;
    }
    memcpy(boardStates[depth], chessBoard, sizeof(chessBoard));
    // For move in moveList
    for(int64_t i = 0; i < 219; i++){
        assign(i);
        if(move_y == 0 && move_x == 0 && moveTo_y == 0 && moveTo_x == 0){
            if(depth != cap){
                memcpy(chessBoard, boardStates[depth + 1], sizeof(chessBoard));
                generateMoves(depth % 2, 1);
                order();
            }
            break;
        }
        playMove(0);
        int64_t eval = -search(depth - 1, cap, -beta, -alpha);
        memcpy(chessBoard, boardStates[depth], sizeof(chessBoard));
        if(depth == cap){
            if(eval > alpha){
                assign(i);
                bestMove[0] = move_y;
                bestMove[1] = move_x;
                bestMove[2] = moveTo_y;
                bestMove[3] = moveTo_x;
                //cout << " " << move_y << " " << move_x << " " << moveTo_y << " " << moveTo_x << endl;
            }
        }
        // Pruning
        if(eval >= beta){
            if(depth != cap){
                memcpy(chessBoard, boardStates[depth + 1], sizeof(chessBoard));
                generateMoves(depth % 2, 1);
                order();
            }
            return beta;
        }
        alpha = duoMax(eval, alpha);
    }
    return alpha;
}









int64_t getMove_white(){
    generateMoves(1, 1);
    isLegalMove = false;
    cout << "White's move ---> ";
    cin >> move_y;
    cin >> move_x;
    cin >> moveTo_y;
    cin >> moveTo_x;
    for(int64_t i = 0; i < n; i++){
        if(move_y == moveList[0][i] && move_x == moveList[1][i] && moveTo_y == moveList[2][i] && moveTo_x == moveList[3][i]){
            playMove(1);
            isLegalMove = true;
            return 0;
        }      
    }
    cout << "Illegal Move!" << endl;
    return 0;
}
int64_t getMove_black(){
    generateMoves(0, 1);
    isLegalMove = false;
    cout << "Black's move ---> ";
    cin >> move_y;
    cin >> move_x;
    cin >> moveTo_y;
    cin >> moveTo_x;
    for(int64_t i = 0; i < n; i++){
        if(move_y == moveList[0][i] && move_x == moveList[1][i] && moveTo_y == moveList[2][i] && moveTo_x == moveList[3][i]){
            playMove(1);
            isLegalMove = true;
            return 0;
        }      
    }
    cout << "Illegal Move!" << endl;
    return 0;
}

class Engine{
    public:
        void move(int64_t _depth){
            int64_t alpha = -1000000000;
            int64_t beta = 1000000000;
            int64_t sdepth = _depth;
            cout << "Evaluated at " << search(sdepth, sdepth, alpha, beta) << " with ";
            cout << TEST << " positions searched" << endl;
            //order();
            move_y = bestMove[0];
            move_x = bestMove[1];
            moveTo_y = bestMove[2];
            moveTo_x = bestMove[3];
            playMove(1);
            TEST = 0;
        }
};
Engine engine;

int main(){

    initializeBoard();
    printBoard();
    opening = true;
    middlegame = false;
    endgame = false;

    while(move_move <= 5949){
        if(move_move == 13){
            opening = false;
            middlegame = true;
        }
        if(pieceCount() < 12){
            middlegame = false;
            endgame = true;
        }
        cout << "Move - " << move_move << endl;
        engine.move(6);
        //do{
            //getMove_white();
        //} while(!isLegalMove);

        generateMoves(0, 1);
        if(n == 0 && check(0) == true){
            printBoard();
            cout << "Checkmate - white wins" << endl;
            break;
        } else if(n == 0 && check(0) == false){
            printBoard();
            cout << "Stalemate - draw" << endl;
            break;
        } else{
        }

        printBoard();
        tempo++;

        do{
            getMove_black();
        } while(!isLegalMove);

        generateMoves(1, 1);
        if(n == 0 && check(1) == true){
            printBoard();
            cout << "Checkmate - black wins" << endl;
            break;
        } else if(n == 0 && check(1) == false){
            printBoard();
            cout << "Stalemate - draw" << endl;
            break;
        } else{
        }

        printBoard();
        tempo++;
        move_move++;
    }
    return 0;
}