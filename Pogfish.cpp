#include<iostream>
#include<cmath>
#include<string.h>
#include<unordered_map>
#include<random>
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

int64_t value(int64_t piece){
    int64_t pieceValue = 0;
    switch(piece){
        case 1: pieceValue = 100; break;
        case 2: pieceValue = 300; break;
        case 3: pieceValue = 300; break;
        case 4: pieceValue = 500; break;
        case 5: pieceValue = 900; break;
        case 6: pieceValue = 0; break;
        case 11: pieceValue = 100; break;
        case 12: pieceValue = 300; break;
        case 13: pieceValue = 300; break;
        case 14: pieceValue = 500; break;
        case 15: pieceValue = 900; break;
        case 16: pieceValue = 0; break;
        default: pieceValue = 0;
    }
    return pieceValue;
}
int64_t pieceIndex(int64_t piece){
    int64_t pieceIndex = 0;
    switch(piece){
        case 1: pieceIndex = 0; break;
        case 2: pieceIndex = 1; break;
        case 3: pieceIndex = 2; break;
        case 4: pieceIndex = 3; break;
        case 5: pieceIndex = 4; break;
        case 6: pieceIndex = 5; break;
        case 11: pieceIndex = 6; break;
        case 12: pieceIndex = 7; break;
        case 13: pieceIndex = 8; break;
        case 14: pieceIndex = 9; break;
        case 15: pieceIndex = 10; break;
        case 16: pieceIndex = 11; break;
        default: pieceIndex = 0;
    }
    return pieceIndex;
}
int64_t getMax(int64_t values[], int64_t numValues){
    int64_t best = values[0];
    best_index = 0;
    for(int64_t i = 0; i < numValues; i++){
        if(values[i] > best){ best = values[i]; best_index = i;}
    }
    return best;
}
int64_t getMin(int64_t values[], int64_t numValues){
    int64_t best = values[0];
    best_index = 0;
    for(int64_t i = 0; i < numValues; i++){
        if(values[i] < best){ best = values[i]; best_index = i;}
    }
    return best;
}
int64_t duoMax(int64_t a, int64_t b){
    int64_t max;
    max = (a + b + abs(a - b))/2;
    return max;
}

string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
int64_t chessBoard[8][8] = {0};
int64_t chessBoard_CC[8][8] = {0};
int64_t openingPawnHeatmap_white[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 10, 10, 0, 0, 0},
    {0, 0, 5, 5, 5, 5, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};
int64_t openingPawnHeatmap_black[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, -5, -5, -5, -5, 0, 0},
    {0, 0, 0, -10, -10, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};
int64_t openingKnightHeatmap_white[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 5, 5, 0, 0, 0},
    {0, 0, 0, 5, 5, 0, 0, 0},
    {0, 0, 10, 0, 0, 10, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, -5, 0, 0, 0, 0, -5, 0}
};
int64_t openingKnightHeatmap_black[8][8] = {
    {0, 5, 0, 0, 0, 0, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, -10, 0, 0, -10, 0, 0},
    {0, 0, 0, -5, -5, 0, 0, 0},
    {0, 0, 0, -5, -5, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

int64_t zobrist_keys[12][8][8] = {0};
int64_t side_key = 0;
struct TranspositionData{
    int64_t evaluation;
    int64_t depthEvaluated;
};
std::unordered_map<int64_t, TranspositionData> TTable;
int64_t Hash(int64_t position[8][8], int side){
    int64_t hash = 0;
    for(int i = 0; i < 8; i++){ for(int j = 0; j < 8; j++){
        if(chessBoard[i][j] != empty_square){
            hash ^= zobrist_keys[i][j][pieceIndex(chessBoard[i][j])];
        }}
    }
    if(side == 1){ hash ^= side_key;}
    return hash;
}

int64_t boardStates[50][8][8] = {0};
int64_t moveList[4][219] = {0};
int64_t eml[4][219] = {0};
int64_t bestMove[4] = {0};

// ------------------------------------------------------------------------- Rules of chess --------------------------------------------------------------------------

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
int64_t pieceCount(){
    int64_t pieceCount = 0;
    for(int64_t i = 0; i < 8; i++){ for(int64_t j = 0; j < 8; j++){
        if(chessBoard[i][j] != empty_square){ pieceCount++;}}
    }
    return pieceCount;
}

// (castling through check & en passant)
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

void initializeBoard(){
    int64_t pos = 0;
    int64_t fenpos = 0;
    while(pos < 64){
        if(FEN[fenpos] == '1'){ pos++;
        } else if(FEN[fenpos] == '2'){ pos+=2;
        } else if(FEN[fenpos] == '3'){ pos+=3;
        } else if(FEN[fenpos] == '4'){ pos+=4;
        } else if(FEN[fenpos] == '5'){ pos+=5;
        } else if(FEN[fenpos] == '6'){ pos+=6;
        } else if(FEN[fenpos] == '7'){ pos+=7;
        } else if(FEN[fenpos] == '8'){ pos+=8;
        } else if(FEN[fenpos] == 'p'){ chessBoard[pos/8][pos % 8] = black_pawn; pos++;
        } else if(FEN[fenpos] == 'n'){ chessBoard[pos/8][pos % 8] = black_knight; pos++;
        } else if(FEN[fenpos] == 'b'){ chessBoard[pos/8][pos % 8] = black_bishop; pos++;
        } else if(FEN[fenpos] == 'r'){ chessBoard[pos/8][pos % 8] = black_rook; pos++;
        } else if(FEN[fenpos] == 'q'){ chessBoard[pos/8][pos % 8] = black_queen; pos++;
        } else if(FEN[fenpos] == 'k'){ chessBoard[pos/8][pos % 8] = black_king; pos++;
        } else if(FEN[fenpos] == 'P'){ chessBoard[pos/8][pos % 8] = white_pawn; pos++;
        } else if(FEN[fenpos] == 'N'){ chessBoard[pos/8][pos % 8] = white_knight; pos++;
        } else if(FEN[fenpos] == 'B'){ chessBoard[pos/8][pos % 8] = white_bishop; pos++;
        } else if(FEN[fenpos] == 'R'){ chessBoard[pos/8][pos % 8] = white_rook; pos++;
        } else if(FEN[fenpos] == 'Q'){ chessBoard[pos/8][pos % 8] = white_queen; pos++;
        } else if(FEN[fenpos] == 'K'){ chessBoard[pos/8][pos % 8] = white_king; pos++;
        }
        fenpos++;
    }
    memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
}
void printBoard(){
    cout << "-----------------------------------------" << endl;
    for(int64_t y_pos = 0; y_pos < 8; y_pos++){
        cout << "|";
        for(int64_t x_pos = 0; x_pos < 8; x_pos++){
            if(chessBoard[y_pos][x_pos] == white_pawn){ cout << "  P |";
            } else if(chessBoard[y_pos][x_pos] == white_knight){ cout << "  N |";
            } else if(chessBoard[y_pos][x_pos] == white_bishop){ cout << "  B |";
            } else if(chessBoard[y_pos][x_pos] == white_rook){ cout << "  R |";
            } else if(chessBoard[y_pos][x_pos] == white_queen){ cout << "  Q |";
            } else if(chessBoard[y_pos][x_pos] == white_king){ cout << "  K |";
            } else if(chessBoard[y_pos][x_pos] == black_pawn){ cout << "  p |";
            } else if(chessBoard[y_pos][x_pos] == black_knight){ cout << "  n |";
            } else if(chessBoard[y_pos][x_pos] == black_bishop){ cout << "  b |";
            } else if(chessBoard[y_pos][x_pos] == black_rook){ cout << "  r |";
            } else if(chessBoard[y_pos][x_pos] == black_queen){ cout << "  q |";
            } else if(chessBoard[y_pos][x_pos] == black_king){ cout << "  k |";
            } else{ cout << "  - |";
            }
        }
        cout << endl; cout << "-----------------------------------------" << endl;
    } cout << endl;
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
            int64_t development;
            for(int i = 0; i < 8; i++){ for(int j = 0; j < 8; j++){
                if(chessBoard[i][j] == white_pawn){ development += openingPawnHeatmap_white[i][j];
                } else if(chessBoard[i][j] == black_pawn){ development += openingPawnHeatmap_white[i][j];
                } else if(chessBoard[i][j] == white_knight){ development += openingKnightHeatmap_white[i][j];
                } else if(chessBoard[i][j] == black_knight){ development += openingKnightHeatmap_black[i][j];}
            }}
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
    int64_t pieceValue = 0;
    for(int i = 0; i < n; i++){ pieceValue = value(chessBoard[moveList[2][i]][moveList[3][i]]); if(pieceValue >= 100){
        for(int j = 0; j < i; j++){ if(pieceValue > value(chessBoard[moveList[2][j]][moveList[3][j]])){
        swap(moveList[0][j], moveList[0][i]), swap(moveList[1][j], moveList[1][i]);
        swap(moveList[2][j], moveList[2][i]), swap(moveList[3][j], moveList[3][i]);
        }}
    }}
}
void generateMoves(int64_t side, int64_t se){
    if(se == 1){ n = 0; memset(moveList, 0, sizeof(moveList));
    } else{ o = 0; memset(eml, 0, sizeof(eml));}
    if(side == 1){
        for(int64_t i = 0; i < 8; i++){ y = i; for(int64_t j = 0; j < 8; j++){ x = j;
            if(chessBoard[y][x] == white_pawn){ moveGen.w_pawn(se);
            } else if(chessBoard[y][x] == white_knight){ moveGen.w_knight(se);
            } else if(chessBoard[y][x] == white_bishop){ moveGen.w_bishop(se);
            } else if(chessBoard[y][x] == white_rook){ moveGen.w_rook(se);
            } else if(chessBoard[y][x] == white_queen){ moveGen.w_queen(se);
            } else if(chessBoard[y][x] == white_king){ moveGen.w_king(se);
            }}
        }
    }
    else{
        for(int64_t i = 0; i < 8; i++){ y = i; for(int64_t j = 0; j < 8; j++){ x = j;
            if(chessBoard[y][x] == black_pawn){ moveGen.b_pawn(se);
            } else if(chessBoard[y][x] == black_knight){ moveGen.b_knight(se);
            } else if(chessBoard[y][x] == black_bishop){ moveGen.b_bishop(se);
            } else if(chessBoard[y][x] == black_rook){ moveGen.b_rook(se);
            } else if(chessBoard[y][x] == black_queen){ moveGen.b_queen(se);
            } else if(chessBoard[y][x] == black_king){ moveGen.b_king(se);
            }}
        }
    }
}
void assign(int64_t index){ move_y = moveList[0][index]; move_x = moveList[1][index]; moveTo_y = moveList[2][index]; moveTo_x = moveList[3][index]; }

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


int search(int64_t depth, int64_t cap, int64_t alpha, int64_t beta){
    if(depth == 0){
        int64_t eval = staticEval(1, 0);
        TEST++;
        return eval;
    }
    generateMoves((depth + 1) % 2, 1);
    order();
    if(n == 0){
        if(check((depth + 1) % 2)){ 
            return -(1000000 + depth);
        }
        return 0;
    }
    memcpy(boardStates[depth], chessBoard, sizeof(chessBoard));
    int64_t eval;
    bool alphaIncreased; 
    // For move in moveList
    for(int i = 0; i < 219; i++){
        assign(i);
        if(move_y == 0 && move_x == 0 && moveTo_y == 0 && moveTo_x == 0){ break;}
        playMove(0);
        int64_t boardHash = Hash(chessBoard, (depth + 1) % 2);
        if(i > 4 && !alphaIncreased && depth > 2){
            eval = -search(depth - 3, cap, -beta, -alpha);
        }else if(TTable[boardHash].depthEvaluated > 0 && TTable[boardHash].depthEvaluated >= depth){
            eval = TTable[boardHash].evaluation;
        } else{
            eval = -search(depth - 1, cap, -beta, -alpha);
        }
        memcpy(chessBoard, boardStates[depth], sizeof(chessBoard));
        memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
        TTable[boardHash].evaluation = eval;
        TTable[boardHash].depthEvaluated = depth;
        generateMoves((depth + 1) % 2, 1);
        order();
        if(depth == cap){
            if(eval > alpha){
                alphaIncreased = true;
                bestMove[0] = moveList[0][i], bestMove[1] = moveList[1][i], bestMove[2] = moveList[2][i], bestMove[3] = moveList[3][i];
            }
        }
        if(eval >= beta){ return beta;}
        alpha = duoMax(eval, alpha);
    }
    return alpha;
}


int64_t getMove_white(){
    generateMoves(1, 1);
    isLegalMove = false;
    cout << "White's move ---> "; cin >> move_y; cin >> move_x; cin >> moveTo_y; cin >> moveTo_x;
    for(int64_t i = 0; i < n; i++){
        if(move_y == moveList[0][i] && move_x == moveList[1][i] && moveTo_y == moveList[2][i] && moveTo_x == moveList[3][i]){ playMove(1); isLegalMove = true; return 0;}      
    }
    cout << "Illegal Move!" << endl;
    return 0;
}
int64_t getMove_black(){
    generateMoves(0, 1);
    isLegalMove = false;
    cout << "Black's move ---> "; cin >> move_y; cin >> move_x; cin >> moveTo_y; cin >> moveTo_x;
    for(int64_t i = 0; i < n; i++){
        if(move_y == moveList[0][i] && move_x == moveList[1][i] && moveTo_y == moveList[2][i] && moveTo_x == moveList[3][i]){ playMove(1); isLegalMove = true; return 0;}      
    }
    cout << "Illegal Move!" << endl;
    return 0;
}
class Engine{
    public:
        void move_white(int64_t _depth){
            int64_t alpha = -1000000000;
            int64_t beta = 1000000000;
            int64_t sdepth = _depth;
            cout << "Evaluated at " << search(sdepth, sdepth, alpha, beta) << " with ";
            cout << TEST << " positions searched. Played - " << bestMove[0] << " " << bestMove[1] << " " << bestMove[2] << " " << bestMove[3] << " " << endl;
            move_y = bestMove[0];
            move_x = bestMove[1];
            moveTo_y = bestMove[2];
            moveTo_x = bestMove[3];
            playMove(1);
            TEST = 0;
            memset(bestMove, 0, sizeof(bestMove));
            TTable.clear();

        }
};
Engine engine;

int main(void){

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<long long int> distrib(0, 9223372036854775807);
    for (int i = 0; i < 12; i++){
        for(int j = 0; j < 8; j++){
            for(int k = 0; k < 8; k++){
                zobrist_keys[i][j][k] = distrib(gen);
            }
        }
    }
    side_key = distrib(gen);

    initializeBoard();
    printBoard();
    opening = 1;
    middlegame = 1;
    endgame = 0;

    while(move_move <= 5949){
        if(move_move == 15){ opening = false; middlegame = true;}
        if(pieceCount() < 15){ middlegame = false; endgame = true;}
        cout << "Move - " << move_move << endl;
        engine.move_white(8);
        //do{
        //    getMove_white();
        //} while(!isLegalMove);

        generateMoves(0, 1);
        if(n == 0 && check(0) == true){ printBoard(); cout << "Checkmate - white wins" << endl; break;
        } else if(n == 0 && check(0) == false){ printBoard(); cout << "Stalemate - draw" << endl; break;
        }

        printBoard();

        do{
            getMove_black();
        } while(!isLegalMove);
        //engine.move_white(7);
        TTable.clear();

        generateMoves(1, 1);
        if(n == 0 && check(1) == true){ printBoard(); cout << "Checkmate - black wins" << endl; break;
        } else if(n == 0 && check(1) == false){ printBoard(); cout << "Stalemate - draw" << endl; break;
        }

        printBoard();
        move_move++;
    }
}