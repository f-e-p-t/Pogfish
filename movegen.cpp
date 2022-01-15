#include<iostream>
using namespace std;

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

int64_t chessBoard[8][8] = {0};
int64_t chessBoard_CC[8][8] = {0};

int64_t moveList[4][219] = {0};
int64_t eml[4][219] = {0};
int64_t bestMove[4] = {0};

int64_t playMove_CC(int64_t castlingRightsRemoved){
    // castling
    if(chessBoard_CC[y][x] == white_rook && y == 7 && x == 0){
        if(castlingRightsRemoved == 1){ QSCastlingRights_white = false;}
    } else if(chessBoard_CC[y][x] == white_rook && y == 7 && x == 7){
        if(castlingRightsRemoved == 1){ KSCastlingRights_white = false;}
    } else if(chessBoard_CC[y][x] == black_rook && y == 0 && x == 0){
        if(castlingRightsRemoved == 1){ QSCastlingRights_black = false;}
    } else if(chessBoard_CC[y][x] == white_rook && y == 0 && x == 7){
        if(castlingRightsRemoved == 1){ KSCastlingRights_black = false;}
    }
    if(chessBoard_CC[y][x] == white_king && y == 7 && x == 4 && y_to == 7 && x_to == 6 && KSCastlingRights_white){ chessBoard_CC[7][7] = empty_square; chessBoard_CC[7][5] = white_rook;
    } else if(chessBoard_CC[y][x] == white_king && y == 7 && x == 4 && y_to == 7 && x_to == 2 && QSCastlingRights_white){ chessBoard_CC[7][0] = empty_square; chessBoard_CC[7][3] = white_rook;
    } else if(chessBoard_CC[y][x] == black_king && y == 0 && x == 4 && y_to == 0 && x_to == 6 && KSCastlingRights_black){ chessBoard_CC[0][7] = empty_square; chessBoard_CC[0][5] = black_rook;
    } else if(chessBoard_CC[y][x] == black_king && y == 0 && x == 4 && y_to == 0 && x_to == 2 && QSCastlingRights_black){ chessBoard_CC[0][0] = empty_square; chessBoard_CC[0][3] = black_rook;
    }
    if(chessBoard_CC[y][x] == white_king){ if(castlingRightsRemoved == 1){ KSCastlingRights_white = false; QSCastlingRights_white = false;}}
    if(chessBoard_CC[y][x] == black_king){ if(castlingRightsRemoved == 1){ KSCastlingRights_black = false; QSCastlingRights_black = false;}}
    // promotion
    if(chessBoard_CC[y][x] == white_pawn && y_to == 0){ chessBoard_CC[y][x] = empty_square; chessBoard_CC[y_to][x_to] = white_queen; return 0;
    } else if(chessBoard_CC[y][x] == black_pawn && y_to == 7){ chessBoard_CC[y][x] = empty_square; chessBoard_CC[y_to][x_to] = black_queen; return 0;
    }
    chessBoard_CC[y_to][x_to] = chessBoard_CC[y][x];
    chessBoard_CC[y][x] = empty_square;
    return 0;
}
int64_t playMove(int64_t castlingRightsRemoved){
    // castling
    if(chessBoard[move_y][move_x] == white_rook && move_y == 7 && move_x == 0){
        if(castlingRightsRemoved == 1){ QSCastlingRights_white = false;}
    } else if(chessBoard[move_y][move_x] == white_rook && move_y == 7 && move_x == 7){
        if(castlingRightsRemoved == 1){ KSCastlingRights_white = false;}
    } else if(chessBoard[move_y][move_x] == black_rook && move_y == 0 && move_x == 0){
        if(castlingRightsRemoved == 1){ QSCastlingRights_black = false;}
    } else if(chessBoard[move_y][move_x] == white_rook && move_y == 0 && move_x == 7){
        if(castlingRightsRemoved == 1){ KSCastlingRights_black = false;}
    }
    if(chessBoard[move_y][move_x] == white_king && move_y == 7 && move_x == 4 && moveTo_y == 7 && moveTo_x == 6 && KSCastlingRights_white){ chessBoard[7][7] = empty_square; chessBoard[7][5] = white_rook;
    } else if(chessBoard[move_y][move_x] == white_king && move_y == 7 && move_x == 4 && moveTo_y == 7 && moveTo_x == 2 && QSCastlingRights_white){ chessBoard[7][0] = empty_square; chessBoard[7][3] = white_rook;
    } else if(chessBoard[move_y][move_x] == black_king && move_y == 0 && move_x == 4 && moveTo_y == 0 && moveTo_x == 6 && KSCastlingRights_black){ chessBoard[0][7] = empty_square; chessBoard[0][5] = black_rook;
    } else if(chessBoard[move_y][move_x] == black_king && move_y == 0 && move_x == 4 && moveTo_y == 0 && moveTo_x == 2 && QSCastlingRights_black){ chessBoard[0][0] = empty_square; chessBoard[0][3] = black_rook;
    }
    if(chessBoard[move_y][move_x] == white_king){ if(castlingRightsRemoved == 1){ KSCastlingRights_white = false; QSCastlingRights_white = false;}}
    if(chessBoard[move_y][move_x] == black_king){ if(castlingRightsRemoved == 1){ KSCastlingRights_black = false; QSCastlingRights_black = false;}}
    // promotion
    if(chessBoard[move_y][move_x] == white_pawn && moveTo_y == 0){ chessBoard[move_y][move_x] = empty_square; chessBoard[moveTo_y][moveTo_x] = white_queen; memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard)); return 0;
    } else if(chessBoard[move_y][move_x] == black_pawn && moveTo_y == 7){ chessBoard[move_y][move_x] = empty_square; chessBoard[moveTo_y][moveTo_x] = black_queen; memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard)); return 0;
    }
    chessBoard[moveTo_y][moveTo_x] = chessBoard[move_y][move_x];
    chessBoard[move_y][move_x] = empty_square;
    memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
    return 0;
}
bool check(int64_t side){
    if(side == 1){ int64_t kp_y = 0; int64_t kp_x = 0;
        for(int64_t i = 0; i <= 7; i++){ for(int64_t j = 0; j <= 7; j++){
            if(chessBoard_CC[i][j] == white_king){ kp_y = i; kp_x = j; break;}}
        }
        for(int64_t i = 1; i < 8; i++){ // down & right
            if(kp_y + i > 7 || kp_x + i > 7){ break;
            } else if(chessBoard_CC[kp_y + i][kp_x + i] == black_bishop || chessBoard_CC[kp_y + i][kp_x + i] == black_queen){ return true;
            } else if(chessBoard_CC[kp_y + i][kp_x + i] >= 1 && chessBoard_CC[kp_y + i][kp_x + i] != black_bishop && chessBoard_CC[kp_y + i][kp_x + i] != black_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // down & left
            if(kp_y + i > 7 || kp_x - i < 0){ break;
            } else if(chessBoard_CC[kp_y + i][kp_x - i] == black_bishop || chessBoard_CC[kp_y + i][kp_x - i] == black_queen){ return true;
            } else if(chessBoard_CC[kp_y + i][kp_x - i] >= 1 && chessBoard_CC[kp_y + i][kp_x - i] != black_bishop && chessBoard_CC[kp_y + i][kp_x - i] != black_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up & left
            if(kp_y - i < 0 || kp_x - i < 0){ break;
            } else if(chessBoard_CC[kp_y - i][kp_x - i] == black_bishop || chessBoard_CC[kp_y - i][kp_x - i] == black_queen){ return true;
            } else if(chessBoard_CC[kp_y - i][kp_x - i] >= 1 && chessBoard_CC[kp_y - i][kp_x - i] != black_bishop && chessBoard_CC[kp_y - i][kp_x - i] != black_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up & right
            if(kp_y - i < 0 || kp_x + i > 7){ break;
            } else if(chessBoard_CC[kp_y - i][kp_x + i] == black_bishop || chessBoard_CC[kp_y - i][kp_x + i] == black_queen){ return true;
            } else if(chessBoard_CC[kp_y - i][kp_x + i] >= 1 && chessBoard_CC[kp_y - i][kp_x + i] != black_bishop && chessBoard_CC[kp_y - i][kp_x + i] != black_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // down
            if(kp_y + i > 7){ break;
            } else if(chessBoard_CC[kp_y + i][kp_x] == black_rook || chessBoard_CC[kp_y + i][kp_x] == black_queen){ return true;
            } else if(chessBoard_CC[kp_y + i][kp_x] >= 1 && chessBoard_CC[kp_y + i][kp_x] != black_rook && chessBoard_CC[kp_y + i][kp_x] != black_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // left
            if(kp_x - i < 0){ break;
            } else if(chessBoard_CC[kp_y][kp_x - i] == black_rook || chessBoard_CC[kp_y][kp_x - i] == black_queen){ return true;
            } else if(chessBoard_CC[kp_y][kp_x - i] >= 1 && chessBoard_CC[kp_y][kp_x - i] != black_rook && chessBoard_CC[kp_y][kp_x - i] != black_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up
            if(kp_y - i < 0){ break;
            } else if(chessBoard_CC[kp_y - i][kp_x] == black_rook || chessBoard_CC[kp_y - i][kp_x] == black_queen){ return true;
            } else if(chessBoard_CC[kp_y - i][kp_x] >= 1 && chessBoard_CC[kp_y - i][kp_x] != black_rook && chessBoard_CC[kp_y - i][kp_x] != black_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // right
            if(kp_x + i > 7){ break;
            } else if(chessBoard_CC[kp_y][kp_x + i] == black_rook || chessBoard_CC[kp_y][kp_x + i] == black_queen){ return true;
            } else if(chessBoard_CC[kp_y][kp_x + i] >= 1 && chessBoard_CC[kp_y][kp_x + i] != black_rook && chessBoard_CC[kp_y][kp_x + i] != black_queen){ break;
            }
        }
        if(chessBoard_CC[kp_y + 1][kp_x + 2] == black_knight && kp_y + 1 <= 7 && kp_x + 2 <= 7){ return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x - 2] == black_knight && kp_y + 1 <= 7 && kp_x - 2 >= 0){ return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x + 2] == black_knight && kp_y - 1 >= 0 && kp_x + 2 <= 7){ return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x - 2] == black_knight && kp_y - 1 >= 0 && kp_x - 2 >= 0){ return true;
        } else if(chessBoard_CC[kp_y + 2][kp_x + 1] == black_knight && kp_y + 2 <= 7 && kp_x + 1 <= 7){ return true;
        } else if(chessBoard_CC[kp_y + 2][kp_x - 1] == black_knight && kp_y + 2 <= 7 && kp_x - 1 >= 0){ return true;
        } else if(chessBoard_CC[kp_y - 2][kp_x + 1] == black_knight && kp_y - 2 >= 0 && kp_x + 1 <= 7){ return true;
        } else if(chessBoard_CC[kp_y - 2][kp_x - 1] == black_knight && kp_y - 2 >= 0 && kp_x - 1 >= 0){ return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x + 1] == black_pawn && kp_y - 1 >= 0 && kp_x + 1 <= 7){ return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x - 1] == black_pawn && kp_y - 1 >= 0 && kp_x - 1 >= 0){ return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x + 1] == black_king && kp_y + 1 <= 7 && kp_x + 1 <= 7){ return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x - 1] == black_king && kp_y + 1 <= 7 && kp_x - 1 >= 0){ return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x + 1] == black_king && kp_y - 1 >= 0 && kp_x + 1 <= 7){ return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x - 1] == black_king && kp_y - 1 >= 0 && kp_x - 1 >= 0){ return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x] == black_king && kp_y + 1 <= 7){ return true;
        } else if(chessBoard_CC[kp_y][kp_x - 1] == black_king && kp_x - 1 >= 0){ return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x] == black_king && kp_y - 1 >= 0){ return true;
        } else if(chessBoard_CC[kp_y][kp_x + 1] == black_king && kp_x + 1 <= 7){ return true;
        }
        return false;
    }
    else{ int64_t kp_y = 0; int64_t kp_x = 0;
        for(int64_t i = 0; i <= 7; i++){ for(int64_t j = 0; j <= 7; j++){
            if(chessBoard_CC[i][j] == black_king){ kp_y = i; kp_x = j; break;}}
        }
        for(int64_t i = 1; i < 8; i++){ // down & right
            if(kp_y + i > 7 || kp_x + i > 7){ break;    
            } else if(chessBoard_CC[kp_y + i][kp_x + i] == white_bishop || chessBoard_CC[kp_y + i][kp_x + i] == white_queen){ return true;
            } else if(chessBoard_CC[kp_y + i][kp_x + i] >= 1 && chessBoard_CC[kp_y + i][kp_x + i] != white_bishop && chessBoard_CC[kp_y + i][kp_x + i] != white_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // down & left
            if(kp_y + i > 7 || kp_x - i < 0){ break;
            } else if(chessBoard_CC[kp_y + i][kp_x - i] == white_bishop || chessBoard_CC[kp_y + i][kp_x - i] == white_queen){ return true;
            } else if(chessBoard_CC[kp_y + i][kp_x - i] >= 1 && chessBoard_CC[kp_y + i][kp_x - i] != white_bishop && chessBoard_CC[kp_y + i][kp_x - i] != white_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up & left
            if(kp_y - i < 0 || kp_x - i < 0){ break;   
            } else if(chessBoard_CC[kp_y - i][kp_x - i] == white_bishop || chessBoard_CC[kp_y - i][kp_x - i] == white_queen){ return true;
            } else if(chessBoard_CC[kp_y - i][kp_x - i] >= 1 && chessBoard_CC[kp_y - i][kp_x - i] != white_bishop && chessBoard_CC[kp_y - i][kp_x - i] != white_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up & right
            if(kp_y - i < 0 || kp_x + i > 7){ break;   
            } else if(chessBoard_CC[kp_y - i][kp_x + i] == white_bishop || chessBoard_CC[kp_y - i][kp_x + i] == white_queen){ return true;
            } else if(chessBoard_CC[kp_y - i][kp_x + i] >= 1 && chessBoard_CC[kp_y - i][kp_x + i] != white_bishop && chessBoard_CC[kp_y - i][kp_x + i] != white_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // down
            if(kp_y + i > 7){ break;
            } else if(chessBoard_CC[kp_y + i][kp_x] == white_rook || chessBoard_CC[kp_y + i][kp_x] == white_queen){ return true;
            } else if(chessBoard_CC[kp_y + i][kp_x] >= 1 && chessBoard_CC[kp_y + i][kp_x] != white_rook && chessBoard_CC[kp_y + i][kp_x] != white_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // left
            if(kp_x - i < 0){ break;
            } else if(chessBoard_CC[kp_y][kp_x - i] == white_rook || chessBoard_CC[kp_y][kp_x - i] == white_queen){ return true;
            } else if(chessBoard_CC[kp_y][kp_x - i] >= 1 && chessBoard_CC[kp_y][kp_x - i] != white_rook && chessBoard_CC[kp_y][kp_x - i] != white_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up
            if(kp_y - i < 0){ break;
            } else if(chessBoard_CC[kp_y - i][kp_x] == white_rook || chessBoard_CC[kp_y - i][kp_x] == white_queen){ return true;
            } else if(chessBoard_CC[kp_y - i][kp_x] >= 1 && chessBoard_CC[kp_y - i][kp_x] != white_rook && chessBoard_CC[kp_y - i][kp_x] != white_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // right
            if(kp_x + i > 7){ break;
            } else if(chessBoard_CC[kp_y][kp_x + i] == white_rook || chessBoard_CC[kp_y][kp_x + i] == white_queen){ return true;
            } else if(chessBoard_CC[kp_y][kp_x + i] >= 1 && chessBoard_CC[kp_y][kp_x + i] != white_rook && chessBoard_CC[kp_y][kp_x + i] != white_queen){ break;
            }
        }
        if(chessBoard_CC[kp_y + 1][kp_x + 2] == white_knight && kp_y + 1 <= 7 && kp_x + 2 <= 7){ return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x - 2] == white_knight && kp_y + 1 <= 7 && kp_x - 2 >= 0){ return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x + 2] == white_knight && kp_y - 1 >= 0 && kp_x + 2 <= 7){ return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x - 2] == white_knight && kp_y - 1 >= 0 && kp_x - 2 >= 0){ return true;
        } else if(chessBoard_CC[kp_y + 2][kp_x + 1] == white_knight && kp_y + 2 <= 7 && kp_x + 1 <= 7){ return true;
        } else if(chessBoard_CC[kp_y + 2][kp_x - 1] == white_knight && kp_y + 2 <= 7 && kp_x - 1 >= 0){ return true;
        } else if(chessBoard_CC[kp_y - 2][kp_x + 1] == white_knight && kp_y - 2 >= 0 && kp_x + 1 <= 7){ return true;
        } else if(chessBoard_CC[kp_y - 2][kp_x - 1] == white_knight && kp_y - 2 >= 0 && kp_x - 1 >= 0){ return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x + 1] == white_pawn && kp_y + 1 >= 0 && kp_x + 1 <= 7){ return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x - 1] == white_pawn && kp_y + 1 <= 7 && kp_x - 1 >= 0){ return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x + 1] == white_king && kp_y + 1 <= 7 && kp_x + 1 <= 7){ return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x - 1] == white_king && kp_y + 1 <= 7 && kp_x - 1 >= 0){ return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x + 1] == white_king && kp_y - 1 >= 0 && kp_x + 1 <= 7){ return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x - 1] == white_king && kp_y - 1 >= 0 && kp_x - 1 >= 0){ return true;
        } else if(chessBoard_CC[kp_y + 1][kp_x] == white_king && kp_y + 1 <= 7){ return true;
        } else if(chessBoard_CC[kp_y][kp_x - 1] == white_king && kp_x - 1 >= 0){ return true;
        } else if(chessBoard_CC[kp_y - 1][kp_x] == white_king && kp_y - 1 >= 0){ return true;
        } else if(chessBoard_CC[kp_y][kp_x + 1] == white_king && kp_x + 1 <= 7){ return true;
        }
        return false;
    }
}
void insertMove_white(int64_t se){
    if(se == 1){
        playMove_CC(0);
        if(check(1)){ memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
        } else{ moveList[0][n] = y; moveList[1][n] = x; moveList[2][n] = y_to; moveList[3][n] = x_to; n++; memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));}
    } else{
        playMove_CC(0);
        if(check(1)){ memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
        } else{ eml[0][o] = y; eml[1][o] = x; eml[2][o] = y_to; eml[3][o] = x_to; o++; memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));}
    }
}
void insertMove_black(int64_t se){
    if(se == 1){
        playMove_CC(0);
        if(check(0)){ memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
        } else{ moveList[0][n] = y; moveList[1][n] = x; moveList[2][n] = y_to; moveList[3][n] = x_to; n++; memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));}
    } else{
        playMove_CC(0);
        if(check(0)){ memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
        } else{ eml[0][o] = y; eml[1][o] = x; eml[2][o] = y_to; eml[3][o] = x_to; o++; memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));}
    }
}  

class Move_gen{
    public:     
        void w_pawn(int64_t se){
            if(chessBoard[y - 1][x] == 0){ y_to = y - 1; x_to = x; insertMove_white(se);}
            if(chessBoard[y - 1][x + 1] >= 11){    if(x + 1 <= 7){ y_to = y - 1; x_to = x + 1; insertMove_white(se);}}
            if(chessBoard[y - 1][x - 1] >= 11){    if(x - 1 >= 0){ y_to = y - 1; x_to = x - 1; insertMove_white(se);}}
            if(y == 6){    if(chessBoard[y - 1][x] == 0 && chessBoard[y - 2][x] == 0){ y_to = y - 2; x_to = x; insertMove_white(se);}} 
        }
        void b_pawn(int64_t se){
            if(chessBoard[y + 1][x] == 0){ y_to = y + 1; x_to = x; insertMove_black(se);}
            if(chessBoard[y + 1][x + 1] <= 6 && chessBoard[y + 1][x + 1] > 0){    if(x + 1 <= 7){ y_to = y + 1; x_to = x + 1; insertMove_black(se);}}
            if(chessBoard[y + 1][x - 1] <= 6 && chessBoard[y + 1][x - 1] > 0){    if(x - 1 >= 0){ y_to = y + 1; x_to = x - 1; insertMove_black(se);}}
            if(y == 1){    if(chessBoard[y + 1][x] == 0 && chessBoard[y + 2][x] == 0){ y_to = y + 2; x_to = x; insertMove_black(se);}} 
        }
        void w_knight(int64_t se){
            if(chessBoard[y + 1][x + 2] >= 11 || chessBoard[y + 1][x + 2] == 0){
                if(y + 1 <= 7 && x + 2 <= 7){ y_to = y + 1; x_to = x + 2; insertMove_white(se);}
            }
            if(chessBoard[y - 1][x + 2] >= 11 || chessBoard[y - 1][x + 2] == 0){
                if(y - 1 >= 0 && x + 2 <= 7){ y_to = y - 1; x_to = x + 2; insertMove_white(se);} 
            }
            if(chessBoard[y + 1][x - 2] >= 11 || chessBoard[y + 1][x - 2] == 0){
                if(y + 1 <= 7 && x - 2 >= 0){ y_to = y + 1; x_to = x - 2; insertMove_white(se);}
            }
            if(chessBoard[y - 1][x - 2] >= 11 || chessBoard[y - 1][x - 2] == 0){
                if(y - 1 >= 0 && x - 2 >= 0){ y_to = y - 1; x_to = x - 2; insertMove_white(se);} 
            }
            if(chessBoard[y + 2][x + 1] >= 11 || chessBoard[y + 2][x + 1] == 0){
                if(y + 2 <= 7 && x + 1 <= 7){ y_to = y + 2; x_to = x + 1; insertMove_white(se);}
            }
            if(chessBoard[y - 2][x + 1] >= 11 || chessBoard[y - 2][x + 1] == 0){
                if(y - 2 >= 0 && x + 1 <= 7){ y_to = y - 2; x_to = x + 1; insertMove_white(se);}
            }
            if(chessBoard[y + 2][x - 1] >= 11 || chessBoard[y + 2][x - 1] == 0){
                if(y + 2 <= 7 && x - 1 >= 0){ y_to = y + 2; x_to = x - 1; insertMove_white(se);}
            }
            if(chessBoard[y - 2][x - 1] >= 11 || chessBoard[y - 2][x - 1] == 0){
                if(y - 2 >= 0 && x - 1 >= 0){ y_to = y - 2; x_to = x - 1; insertMove_white(se);}
            }
        }
        void b_knight(int64_t se){
            if(chessBoard[y + 1][x + 2] <= 6 || chessBoard[y + 1][x + 2] == 0){
                if(y + 1 <= 7 && x + 2 <= 7){ y_to = y + 1; x_to = x + 2; insertMove_black(se);}
            }
            if(chessBoard[y - 1][x + 2] <= 6 || chessBoard[y - 1][x + 2] == 0){
                if(y - 1 >= 0 && x + 2 <= 7){ y_to = y - 1; x_to = x + 2; insertMove_black(se);} 
            }
            if(chessBoard[y + 1][x - 2] <= 6 || chessBoard[y + 1][x - 2] == 0){
                if(y + 1 <= 7 && x - 2 >= 0){ y_to = y + 1; x_to = x - 2; insertMove_black(se);}
            }
            if(chessBoard[y - 1][x - 2] <= 6 || chessBoard[y - 1][x - 2] == 0){
                if(y - 1 >= 0 && x - 2 >= 0){ y_to = y - 1; x_to = x - 2; insertMove_black(se);} 
            }
            if(chessBoard[y + 2][x + 1] <= 6 || chessBoard[y + 2][x + 1] == 0){
                if(y + 2 <= 7 && x + 1 <= 7){ y_to = y + 2; x_to = x + 1; insertMove_black(se);}
            }
            if(chessBoard[y - 2][x + 1] <= 6 || chessBoard[y - 2][x + 1] == 0){
                if(y - 2 >= 0 && x + 1 <= 7){ y_to = y - 2; x_to = x + 1; insertMove_black(se);}
            }
            if(chessBoard[y + 2][x - 1] <= 6 || chessBoard[y + 2][x - 1] == 0){
                if(y + 2 <= 7 && x - 1 >= 0){ y_to = y + 2; x_to = x - 1; insertMove_black(se);}
            }
            if(chessBoard[y - 2][x - 1] <= 6 || chessBoard[y - 2][x - 1] == 0){
                if(y - 2 >= 0 && x - 1 >= 0){ y_to = y - 2; x_to = x - 1; insertMove_black(se);}
            }
        }
        void w_bishop(int64_t se){
            for(int64_t i = 1; i < 8; i++){ // down & right
                if(y + i > 7 || x + i > 7){ break;}
                if(chessBoard[y + i][x + i] == empty_square){ y_to = y + i; x_to = x + i; insertMove_white(se);
                } else if(chessBoard[y + i][x + i] <= 6 && chessBoard[y + i][x + i] != empty_square){ break;
                } else if(chessBoard[y + i][x + i] >= 11){ y_to = y + i; x_to = x + i; insertMove_white(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // down & left
                if(y + i > 7 || x - i < 0){ break;}
                if(chessBoard[y + i][x - i] == empty_square){ y_to = y + i; x_to = x - i; insertMove_white(se);
                } else if(chessBoard[y + i][x - i] <= 6 && chessBoard[y + i][x - i] != empty_square){ break;
                } else if(chessBoard[y + i][x - i] >= 11){ y_to = y + i; x_to = x - i; insertMove_white(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & left
                if(y - i < 0 || x - i < 0){ break;}
                if(chessBoard[y - i][x - i] == empty_square){ y_to = y - i; x_to = x - i; insertMove_white(se);
                } else if(chessBoard[y - i][x - i] <= 6 && chessBoard[y - i][x - i] != empty_square){ break;
                } else if(chessBoard[y - i][x - i] >= 11){ y_to = y - i; x_to = x - i; insertMove_white(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & right
                if(y - i < 0 || x + i > 7){ break;}
                if(chessBoard[y - i][x + i] == empty_square){ y_to = y - i; x_to = x + i; insertMove_white(se);
                } else if(chessBoard[y - i][x + i] <= 6 && chessBoard[y - i][x + i] != empty_square){ break;
                } else if(chessBoard[y - i][x + i] >= 11){ y_to = y - i; x_to = x + i; insertMove_white(se); break;}
            }
        }
        void b_bishop(int64_t se){
            for(int64_t i = 1; i < 8; i++){ // down & right
                if(y + i > 7 || x + i > 7){ break;}
                if(chessBoard[y + i][x + i] == empty_square){ y_to = y + i; x_to = x + i; insertMove_black(se);
                } else if(chessBoard[y + i][x + i] >= 11){ break;
                } else if(chessBoard[y + i][x + i] <= 6 && chessBoard[y + i][x + i] != 0){ y_to = y + i; x_to = x + i; insertMove_black(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // down & left
                if(y + i > 7 || x - i < 0){ break;}
                if(chessBoard[y + i][x - i] == empty_square){ y_to = y + i; x_to = x - i; insertMove_black(se);
                } else if(chessBoard[y + i][x - i] >= 11){break;
                } else if(chessBoard[y + i][x - i] <= 6 && chessBoard[y + i][x - i] != 0){ y_to = y + i; x_to = x - i; insertMove_black(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & left
                if(y - i < 0 || x - i < 0){ break;}
                if(chessBoard[y - i][x - i] == empty_square){ y_to = y - i; x_to = x - i; insertMove_black(se);
                } else if(chessBoard[y - i][x - i] >= 11){ break;
                } else if(chessBoard[y - i][x - i] <= 6 && chessBoard[y - i][x - i] != empty_square){ y_to = y - i; x_to = x - i; insertMove_black(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & right
                if(y - i < 0 || x + i > 7){ break;}
                if(chessBoard[y - i][x + i] == empty_square){ y_to = y - i; x_to = x + i; insertMove_black(se);
                } else if(chessBoard[y - i][x + i] >= 11){ break;
                } else if(chessBoard[y - i][x + i] <= 6 && chessBoard[y - i][x + i] != empty_square){ y_to = y - i; x_to = x + i; insertMove_black(se); break;}
            }
        }
        void w_rook(int64_t se){
            for(int64_t i = 1; i < 8; i++){ // down
                if(y + i > 7){ break;
                } else if(chessBoard[y + i][x] == empty_square){ y_to = y + i; x_to = x; insertMove_white(se);
                } else if(chessBoard[y + i][x] <= 6 && chessBoard[y + i][x] != empty_square){ break;
                } else if(chessBoard[y + i][x] >= 11){ y_to = y + i; x_to = x; insertMove_white(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // left
                if(x - i < 0){ break;
                } else if(chessBoard[y][x - i] == empty_square){ y_to = y; x_to = x - i; insertMove_white(se);
                } else if(chessBoard[y][x - i] <= 6 && chessBoard[y][x - i] != empty_square){ break;
                } else if(chessBoard[y][x - i] >= 11){ y_to = y; x_to = x - i; insertMove_white(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up
                if(y - i < 0){ break;
                } else if(chessBoard[y - i][x] == empty_square){ y_to = y - i; x_to = x; insertMove_white(se);
                } else if(chessBoard[y - i][x] <= 6 && chessBoard[y - i][x] != empty_square){ break;
                } else if(chessBoard[y - i][x] >= 11){ y_to = y - i; x_to = x; insertMove_white(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // right
                if(x + i > 7){ break;
                } else if(chessBoard[y][x + i] == empty_square){ y_to = y; x_to = x + i; insertMove_white(se);
                } else if(chessBoard[y][x + i] <= 6 && chessBoard[y][x + i] != empty_square){ break;
                } else if(chessBoard[y][x + i] >= 11){ y_to = y; x_to = x + i; insertMove_white(se); break;}
            }
        }
        void b_rook(int64_t se){
            for(int64_t i = 1; i < 8; i++){ // down
                if(y + i > 7){ break;
                } else if(chessBoard[y + i][x] == empty_square){ y_to = y + i; x_to = x; insertMove_black(se);
                } else if(chessBoard[y + i][x] >= 11){ break;
                } else if(chessBoard[y + i][x] <= 6 && chessBoard[y + i][x] != empty_square){ y_to = y + i; x_to = x; insertMove_black(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // left
                if(x - i < 0){ break;
                } else if(chessBoard[y][x - i] == empty_square){ y_to = y; x_to = x - i; insertMove_black(se);
                } else if(chessBoard[y][x - i] >= 11){ break;
                } else if(chessBoard[y][x - i] <= 6 && chessBoard[y][x - i] != empty_square){ y_to = y; x_to = x - i; insertMove_black(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up
                if(y - i < 0){ break;
                } else if(chessBoard[y - i][x] == empty_square){ y_to = y - i; x_to = x; insertMove_black(se);
                } else if(chessBoard[y - i][x] >= 11){ break;
                } else if(chessBoard[y - i][x] <= 6 && chessBoard[y - i][x] != empty_square){ y_to = y - i; x_to = x; insertMove_black(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // right
                if(x + i > 7){ break;
                } else if(chessBoard[y][x + i] == empty_square){ y_to = y; x_to = x + i; insertMove_black(se);
                } else if(chessBoard[y][x + i] >= 11){ break;
                } else if(chessBoard[y][x + i] <= 6 && chessBoard[y][x + i] != empty_square){ y_to = y; x_to = x + i; insertMove_black(se); break;}
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
            if(chessBoard[y + 1][x] == empty_square || chessBoard[y + 1][x] >= 11){    if(y + 1 <= 7){ y_to = y + 1; x_to = x; insertMove_white(se);}}
            if(chessBoard[y - 1][x] == empty_square || chessBoard[y - 1][x] >= 11){    if(y - 1 >= 0){ y_to = y - 1; x_to = x; insertMove_white(se);}}
            if(chessBoard[y][x + 1] == empty_square || chessBoard[y][x + 1] >= 11){    if(x + 1 <= 7){ y_to = y; x_to = x + 1; insertMove_white(se);}}
            if(chessBoard[y][x - 1] == empty_square || chessBoard[y][x - 1] >= 11){    if(x - 1 >= 0){ y_to = y; x_to = x - 1; insertMove_white(se);}}
            if(chessBoard[y + 1][x + 1] == empty_square || chessBoard[y + 1][x + 1] >= 11){    if(y + 1 <= 7 && x + 1 <= 7){ y_to = y + 1; x_to = x + 1; insertMove_white(se);}}
            if(chessBoard[y + 1][x - 1] == empty_square || chessBoard[y + 1][x - 1] >= 11){    if(y + 1 <= 7 && x - 1 >= 0){ y_to = y + 1; x_to = x - 1; insertMove_white(se);}}
            if(chessBoard[y - 1][x + 1] == empty_square || chessBoard[y - 1][x + 1] >= 11){    if(y - 1 >= 0 && x + 1 <= 7){ y_to = y - 1; x_to = x + 1; insertMove_white(se);}}
            if(chessBoard[y - 1][x - 1] == empty_square || chessBoard[y - 1][x - 1] >= 11){    if(y - 1 >= 0 && x - 1 >= 0){ y_to = y - 1; x_to = x - 1; insertMove_white(se);}}
            if(y == 7 && x == 4 && KSCastlingRights_white && chessBoard[7][5] == empty_square && chessBoard[7][6] == empty_square){ y_to = y; x_to = x + 2; insertMove_white(se);}
            if(y == 7 && x == 4 && QSCastlingRights_white && chessBoard[7][3] == 0 && chessBoard[7][2] == 0 && chessBoard[7][1] == 0){ y_to = y; x_to = x - 2; insertMove_white(se);}
        }
        void b_king(int64_t se){
            if(chessBoard[y + 1][x] <= 6){    if(y + 1 <= 7){ y_to = y + 1; x_to = x; insertMove_black(se);}}
            if(chessBoard[y - 1][x] <= 6){    if(y - 1 >= 0){ y_to = y - 1; x_to = x; insertMove_black(se);}}
            if(chessBoard[y][x + 1] <= 6){    if(x + 1 <= 7){ y_to = y; x_to = x + 1; insertMove_black(se);}}
            if(chessBoard[y][x - 1] <= 6){    if(x - 1 >= 0){ y_to = y; x_to = x - 1; insertMove_black(se);}}
            if(chessBoard[y + 1][x + 1] <= 6){    if(y + 1 <= 7 && x + 1 <= 7){ y_to = y + 1; x_to = x + 1; insertMove_black(se);}}
            if(chessBoard[y + 1][x - 1] <= 6){    if(y + 1 <= 7 && x - 1 >= 0){ y_to = y + 1; x_to = x - 1; insertMove_black(se);}}
            if(chessBoard[y - 1][x + 1] <= 6){    if(y - 1 >= 0 && x + 1 <= 7){ y_to = y - 1; x_to = x + 1; insertMove_black(se);}}
            if(chessBoard[y - 1][x - 1] <= 6){    if(y - 1 >= 0 && x - 1 >= 0){ y_to = y - 1; x_to = x - 1; insertMove_black(se);}}
            if(y == 0 && x == 4 && KSCastlingRights_black && chessBoard[0][5] == empty_square && chessBoard[0][6] == empty_square){ y_to = y; x_to = x + 2; insertMove_black(se);
            }
            if(y == 0 && x == 4 && QSCastlingRights_black && chessBoard[0][3] == 0 && chessBoard[0][2] == 0 && chessBoard[0][1] == 0){ y_to = y; x_to = x - 2; insertMove_black(se);}
        }
};
Move_gen moveGen;