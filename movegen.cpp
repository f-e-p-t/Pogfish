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
class Board{
    public:
        int64_t chessBoard[8][8] = {0};
        int64_t CC[8][8] = {0};
        bool side;
        void playMove(int64_t castlingRightsRemoved, int64_t _move[]){
            side = !side;
            int64_t from_y = _move[0];
            int64_t from_x = _move[1];
            int64_t to_y = _move[2];
            int64_t to_x = _move[3];
            // castling
            if(chessBoard[from_y][from_x] == white_rook && from_y == 7 && from_x == 0){
                if(castlingRightsRemoved == 1){ QSCastlingRights_white = false;}
            } else if(chessBoard[from_y][from_x] == white_rook && from_y == 7 && from_x == 7){
                if(castlingRightsRemoved == 1){ KSCastlingRights_white = false;}
            } else if(chessBoard[from_y][from_x] == black_rook && from_y == 0 && from_x == 0){
                if(castlingRightsRemoved == 1){ QSCastlingRights_black = false;}
            } else if(chessBoard[from_y][from_x] == white_rook && from_y == 0 && from_x == 7){
                if(castlingRightsRemoved == 1){ KSCastlingRights_black = false;}
            }
            if(chessBoard[from_y][from_x] == white_king && from_y == 7 && from_x == 4 && to_y == 7 && to_x == 6 && KSCastlingRights_white){ chessBoard[7][7] = empty_square; chessBoard[7][5] = white_rook;
            } else if(chessBoard[from_y][from_x] == white_king && from_y == 7 && from_x == 4 && to_y == 7 && to_x == 2 && QSCastlingRights_white){ chessBoard[7][0] = empty_square; chessBoard[7][3] = white_rook;
            } else if(chessBoard[from_y][from_x] == black_king && from_y == 0 && from_x == 4 && to_y == 0 && to_x == 6 && KSCastlingRights_black){ chessBoard[0][7] = empty_square; chessBoard[0][5] = black_rook;
            } else if(chessBoard[from_y][from_x] == black_king && from_y == 0 && from_x == 4 && to_y == 0 && to_x == 2 && QSCastlingRights_black){ chessBoard[0][0] = empty_square; chessBoard[0][3] = black_rook;
            }
            if(chessBoard[from_y][from_x] == white_king){ if(castlingRightsRemoved == 1){ KSCastlingRights_white = false; QSCastlingRights_white = false;}}
            if(chessBoard[from_y][from_x] == black_king){ if(castlingRightsRemoved == 1){ KSCastlingRights_black = false; QSCastlingRights_black = false;}}
            // promotion
            if(chessBoard[from_y][from_x] == white_pawn && to_y == 0){ chessBoard[from_y][from_x] = empty_square; chessBoard[to_y][to_x] = white_queen; memcpy(CC, chessBoard, sizeof(chessBoard)); return ;
            } else if(chessBoard[from_y][from_x] == black_pawn && to_y == 7){ chessBoard[from_y][from_x] = empty_square; chessBoard[to_y][to_x] = black_queen; memcpy(CC, chessBoard, sizeof(chessBoard)); return ;
            }
            chessBoard[to_y][to_x] = chessBoard[from_y][from_x];
            chessBoard[from_y][from_x] = empty_square;
            memcpy(CC, chessBoard, sizeof(chessBoard));
        }
        void playMove_CC(int64_t castlingRightsRemoved){
            // castling
            if(CC[y][x] == white_rook && y == 7 && x == 0){
                if(castlingRightsRemoved == 1){ QSCastlingRights_white = false;}
            } else if(CC[y][x] == white_rook && y == 7 && x == 7){
                if(castlingRightsRemoved == 1){ KSCastlingRights_white = false;}
            } else if(CC[y][x] == black_rook && y == 0 && x == 0){
                if(castlingRightsRemoved == 1){ QSCastlingRights_black = false;}
            } else if(CC[y][x] == white_rook && y == 0 && x == 7){
                if(castlingRightsRemoved == 1){ KSCastlingRights_black = false;}
            }
            if(CC[y][x] == white_king && y == 7 && x == 4 && y_to == 7 && x_to == 6 && KSCastlingRights_white){ CC[7][7] = empty_square; CC[7][5] = white_rook;
            } else if(CC[y][x] == white_king && y == 7 && x == 4 && y_to == 7 && x_to == 2 && QSCastlingRights_white){ CC[7][0] = empty_square; CC[7][3] = white_rook;
            } else if(CC[y][x] == black_king && y == 0 && x == 4 && y_to == 0 && x_to == 6 && KSCastlingRights_black){ CC[0][7] = empty_square; CC[0][5] = black_rook;
            } else if(CC[y][x] == black_king && y == 0 && x == 4 && y_to == 0 && x_to == 2 && QSCastlingRights_black){ CC[0][0] = empty_square; CC[0][3] = black_rook;
            }
            if(CC[y][x] == white_king){ if(castlingRightsRemoved == 1){ KSCastlingRights_white = false; QSCastlingRights_white = false;}}
            if(CC[y][x] == black_king){ if(castlingRightsRemoved == 1){ KSCastlingRights_black = false; QSCastlingRights_black = false;}}
            // promotion
            if(CC[y][x] == white_pawn && y_to == 0){ CC[y][x] = empty_square; CC[y_to][x_to] = white_queen; return;
            } else if(CC[y][x] == black_pawn && y_to == 7){ CC[y][x] = empty_square; CC[y_to][x_to] = black_queen; return;
            }
            CC[y_to][x_to] = CC[y][x];
            CC[y][x] = empty_square;
        }
        void unplayMove(int64_t prevBoard[8][8]){
            side = !side;
            memcpy(chessBoard, prevBoard, sizeof(chessBoard));
            memcpy(CC, chessBoard, sizeof(chessBoard));
        }
};
Board board;

int64_t moveList[219][5] = {0};
int64_t eml[219][5] = {0};
int64_t boardStates[50][8][8] = {0};

bool check(int64_t side){
    if(side == 1){ int64_t kp_y = 0; int64_t kp_x = 0;
        for(int64_t i = 0; i <= 7; i++){ for(int64_t j = 0; j <= 7; j++){
            if(board.CC[i][j] == white_king){ kp_y = i; kp_x = j; break;}}
        }
        for(int64_t i = 1; i < 8; i++){ // down & right
            if(kp_y + i > 7 || kp_x + i > 7){ break;
            } else if(board.CC[kp_y + i][kp_x + i] == black_bishop || board.CC[kp_y + i][kp_x + i] == black_queen){ return true;
            } else if(board.CC[kp_y + i][kp_x + i] >= 1 && board.CC[kp_y + i][kp_x + i] != black_bishop && board.CC[kp_y + i][kp_x + i] != black_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // down & left
            if(kp_y + i > 7 || kp_x - i < 0){ break;
            } else if(board.CC[kp_y + i][kp_x - i] == black_bishop || board.CC[kp_y + i][kp_x - i] == black_queen){ return true;
            } else if(board.CC[kp_y + i][kp_x - i] >= 1 && board.CC[kp_y + i][kp_x - i] != black_bishop && board.CC[kp_y + i][kp_x - i] != black_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up & left
            if(kp_y - i < 0 || kp_x - i < 0){ break;
            } else if(board.CC[kp_y - i][kp_x - i] == black_bishop || board.CC[kp_y - i][kp_x - i] == black_queen){ return true;
            } else if(board.CC[kp_y - i][kp_x - i] >= 1 && board.CC[kp_y - i][kp_x - i] != black_bishop && board.CC[kp_y - i][kp_x - i] != black_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up & right
            if(kp_y - i < 0 || kp_x + i > 7){ break;
            } else if(board.CC[kp_y - i][kp_x + i] == black_bishop || board.CC[kp_y - i][kp_x + i] == black_queen){ return true;
            } else if(board.CC[kp_y - i][kp_x + i] >= 1 && board.CC[kp_y - i][kp_x + i] != black_bishop && board.CC[kp_y - i][kp_x + i] != black_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // down
            if(kp_y + i > 7){ break;
            } else if(board.CC[kp_y + i][kp_x] == black_rook || board.CC[kp_y + i][kp_x] == black_queen){ return true;
            } else if(board.CC[kp_y + i][kp_x] >= 1 && board.CC[kp_y + i][kp_x] != black_rook && board.CC[kp_y + i][kp_x] != black_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // left
            if(kp_x - i < 0){ break;
            } else if(board.CC[kp_y][kp_x - i] == black_rook || board.CC[kp_y][kp_x - i] == black_queen){ return true;
            } else if(board.CC[kp_y][kp_x - i] >= 1 && board.CC[kp_y][kp_x - i] != black_rook && board.CC[kp_y][kp_x - i] != black_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up
            if(kp_y - i < 0){ break;
            } else if(board.CC[kp_y - i][kp_x] == black_rook || board.CC[kp_y - i][kp_x] == black_queen){ return true;
            } else if(board.CC[kp_y - i][kp_x] >= 1 && board.CC[kp_y - i][kp_x] != black_rook && board.CC[kp_y - i][kp_x] != black_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // right
            if(kp_x + i > 7){ break;
            } else if(board.CC[kp_y][kp_x + i] == black_rook || board.CC[kp_y][kp_x + i] == black_queen){ return true;
            } else if(board.CC[kp_y][kp_x + i] >= 1 && board.CC[kp_y][kp_x + i] != black_rook && board.CC[kp_y][kp_x + i] != black_queen){ break;
            }
        }
        if(board.CC[kp_y + 1][kp_x + 2] == black_knight && kp_y + 1 <= 7 && kp_x + 2 <= 7){ return true;
        } else if(board.CC[kp_y + 1][kp_x - 2] == black_knight && kp_y + 1 <= 7 && kp_x - 2 >= 0){ return true;
        } else if(board.CC[kp_y - 1][kp_x + 2] == black_knight && kp_y - 1 >= 0 && kp_x + 2 <= 7){ return true;
        } else if(board.CC[kp_y - 1][kp_x - 2] == black_knight && kp_y - 1 >= 0 && kp_x - 2 >= 0){ return true;
        } else if(board.CC[kp_y + 2][kp_x + 1] == black_knight && kp_y + 2 <= 7 && kp_x + 1 <= 7){ return true;
        } else if(board.CC[kp_y + 2][kp_x - 1] == black_knight && kp_y + 2 <= 7 && kp_x - 1 >= 0){ return true;
        } else if(board.CC[kp_y - 2][kp_x + 1] == black_knight && kp_y - 2 >= 0 && kp_x + 1 <= 7){ return true;
        } else if(board.CC[kp_y - 2][kp_x - 1] == black_knight && kp_y - 2 >= 0 && kp_x - 1 >= 0){ return true;
        } else if(board.CC[kp_y - 1][kp_x + 1] == black_pawn && kp_y - 1 >= 0 && kp_x + 1 <= 7){ return true;
        } else if(board.CC[kp_y - 1][kp_x - 1] == black_pawn && kp_y - 1 >= 0 && kp_x - 1 >= 0){ return true;
        } else if(board.CC[kp_y + 1][kp_x + 1] == black_king && kp_y + 1 <= 7 && kp_x + 1 <= 7){ return true;
        } else if(board.CC[kp_y + 1][kp_x - 1] == black_king && kp_y + 1 <= 7 && kp_x - 1 >= 0){ return true;
        } else if(board.CC[kp_y - 1][kp_x + 1] == black_king && kp_y - 1 >= 0 && kp_x + 1 <= 7){ return true;
        } else if(board.CC[kp_y - 1][kp_x - 1] == black_king && kp_y - 1 >= 0 && kp_x - 1 >= 0){ return true;
        } else if(board.CC[kp_y + 1][kp_x] == black_king && kp_y + 1 <= 7){ return true;
        } else if(board.CC[kp_y][kp_x - 1] == black_king && kp_x - 1 >= 0){ return true;
        } else if(board.CC[kp_y - 1][kp_x] == black_king && kp_y - 1 >= 0){ return true;
        } else if(board.CC[kp_y][kp_x + 1] == black_king && kp_x + 1 <= 7){ return true;
        }
        return false;
    }
    else{ int64_t kp_y = 0; int64_t kp_x = 0;
        for(int64_t i = 0; i <= 7; i++){ for(int64_t j = 0; j <= 7; j++){
            if(board.CC[i][j] == black_king){ kp_y = i; kp_x = j; break;}}
        }
        for(int64_t i = 1; i < 8; i++){ // down & right
            if(kp_y + i > 7 || kp_x + i > 7){ break;    
            } else if(board.CC[kp_y + i][kp_x + i] == white_bishop || board.CC[kp_y + i][kp_x + i] == white_queen){ return true;
            } else if(board.CC[kp_y + i][kp_x + i] >= 1 && board.CC[kp_y + i][kp_x + i] != white_bishop && board.CC[kp_y + i][kp_x + i] != white_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // down & left
            if(kp_y + i > 7 || kp_x - i < 0){ break;
            } else if(board.CC[kp_y + i][kp_x - i] == white_bishop || board.CC[kp_y + i][kp_x - i] == white_queen){ return true;
            } else if(board.CC[kp_y + i][kp_x - i] >= 1 && board.CC[kp_y + i][kp_x - i] != white_bishop && board.CC[kp_y + i][kp_x - i] != white_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up & left
            if(kp_y - i < 0 || kp_x - i < 0){ break;   
            } else if(board.CC[kp_y - i][kp_x - i] == white_bishop || board.CC[kp_y - i][kp_x - i] == white_queen){ return true;
            } else if(board.CC[kp_y - i][kp_x - i] >= 1 && board.CC[kp_y - i][kp_x - i] != white_bishop && board.CC[kp_y - i][kp_x - i] != white_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up & right
            if(kp_y - i < 0 || kp_x + i > 7){ break;   
            } else if(board.CC[kp_y - i][kp_x + i] == white_bishop || board.CC[kp_y - i][kp_x + i] == white_queen){ return true;
            } else if(board.CC[kp_y - i][kp_x + i] >= 1 && board.CC[kp_y - i][kp_x + i] != white_bishop && board.CC[kp_y - i][kp_x + i] != white_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // down
            if(kp_y + i > 7){ break;
            } else if(board.CC[kp_y + i][kp_x] == white_rook || board.CC[kp_y + i][kp_x] == white_queen){ return true;
            } else if(board.CC[kp_y + i][kp_x] >= 1 && board.CC[kp_y + i][kp_x] != white_rook && board.CC[kp_y + i][kp_x] != white_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // left
            if(kp_x - i < 0){ break;
            } else if(board.CC[kp_y][kp_x - i] == white_rook || board.CC[kp_y][kp_x - i] == white_queen){ return true;
            } else if(board.CC[kp_y][kp_x - i] >= 1 && board.CC[kp_y][kp_x - i] != white_rook && board.CC[kp_y][kp_x - i] != white_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // up
            if(kp_y - i < 0){ break;
            } else if(board.CC[kp_y - i][kp_x] == white_rook || board.CC[kp_y - i][kp_x] == white_queen){ return true;
            } else if(board.CC[kp_y - i][kp_x] >= 1 && board.CC[kp_y - i][kp_x] != white_rook && board.CC[kp_y - i][kp_x] != white_queen){ break;
            }
        }
        for(int64_t i = 1; i < 8; i++){ // right
            if(kp_x + i > 7){ break;
            } else if(board.CC[kp_y][kp_x + i] == white_rook || board.CC[kp_y][kp_x + i] == white_queen){ return true;
            } else if(board.CC[kp_y][kp_x + i] >= 1 && board.CC[kp_y][kp_x + i] != white_rook && board.CC[kp_y][kp_x + i] != white_queen){ break;
            }
        }
        if(board.CC[kp_y + 1][kp_x + 2] == white_knight && kp_y + 1 <= 7 && kp_x + 2 <= 7){ return true;
        } else if(board.CC[kp_y + 1][kp_x - 2] == white_knight && kp_y + 1 <= 7 && kp_x - 2 >= 0){ return true;
        } else if(board.CC[kp_y - 1][kp_x + 2] == white_knight && kp_y - 1 >= 0 && kp_x + 2 <= 7){ return true;
        } else if(board.CC[kp_y - 1][kp_x - 2] == white_knight && kp_y - 1 >= 0 && kp_x - 2 >= 0){ return true;
        } else if(board.CC[kp_y + 2][kp_x + 1] == white_knight && kp_y + 2 <= 7 && kp_x + 1 <= 7){ return true;
        } else if(board.CC[kp_y + 2][kp_x - 1] == white_knight && kp_y + 2 <= 7 && kp_x - 1 >= 0){ return true;
        } else if(board.CC[kp_y - 2][kp_x + 1] == white_knight && kp_y - 2 >= 0 && kp_x + 1 <= 7){ return true;
        } else if(board.CC[kp_y - 2][kp_x - 1] == white_knight && kp_y - 2 >= 0 && kp_x - 1 >= 0){ return true;
        } else if(board.CC[kp_y + 1][kp_x + 1] == white_pawn && kp_y + 1 >= 0 && kp_x + 1 <= 7){ return true;
        } else if(board.CC[kp_y + 1][kp_x - 1] == white_pawn && kp_y + 1 <= 7 && kp_x - 1 >= 0){ return true;
        } else if(board.CC[kp_y + 1][kp_x + 1] == white_king && kp_y + 1 <= 7 && kp_x + 1 <= 7){ return true;
        } else if(board.CC[kp_y + 1][kp_x - 1] == white_king && kp_y + 1 <= 7 && kp_x - 1 >= 0){ return true;
        } else if(board.CC[kp_y - 1][kp_x + 1] == white_king && kp_y - 1 >= 0 && kp_x + 1 <= 7){ return true;
        } else if(board.CC[kp_y - 1][kp_x - 1] == white_king && kp_y - 1 >= 0 && kp_x - 1 >= 0){ return true;
        } else if(board.CC[kp_y + 1][kp_x] == white_king && kp_y + 1 <= 7){ return true;
        } else if(board.CC[kp_y][kp_x - 1] == white_king && kp_x - 1 >= 0){ return true;
        } else if(board.CC[kp_y - 1][kp_x] == white_king && kp_y - 1 >= 0){ return true;
        } else if(board.CC[kp_y][kp_x + 1] == white_king && kp_x + 1 <= 7){ return true;
        }
        return false;
    }
}
void insertMove_white(int64_t se){
    if(se == 1){
        board.playMove_CC(0);
        if(check(1)){ memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));
        } else{ moveList[n][0] = y; moveList[n][1] = x; moveList[n][2] = y_to; moveList[n][3] = x_to; n++; memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));}
    } else{
        board.playMove_CC(0);
        if(check(1)){ memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));
        } else{ eml[o][0] = y; eml[o][1] = x; eml[o][2] = y_to; eml[o][3] = x_to; o++; memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));}
    }
}
void insertMove_black(int64_t se){
    if(se == 1){
        board.playMove_CC(0);
        if(check(0)){ memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));
        } else{ moveList[n][0] = y; moveList[n][1] = x; moveList[n][2] = y_to; moveList[n][3] = x_to; n++; memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));}
    } else{
        board.playMove_CC(0);
        if(check(0)){ memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));
        } else{ eml[o][0] = y; eml[o][1] = x; eml[o][2] = y_to; eml[o][3] = x_to; o++; memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));}
    }
}  

class Move_gen{
    public:     
        void w_pawn(int64_t se){
            if(board.chessBoard[y - 1][x] == 0){ y_to = y - 1; x_to = x; insertMove_white(se);}
            if(board.chessBoard[y - 1][x + 1] >= 11){    if(x + 1 <= 7){ y_to = y - 1; x_to = x + 1; insertMove_white(se);}}
            if(board.chessBoard[y - 1][x - 1] >= 11){    if(x - 1 >= 0){ y_to = y - 1; x_to = x - 1; insertMove_white(se);}}
            if(y == 6){    if(board.chessBoard[y - 1][x] == 0 && board.chessBoard[y - 2][x] == 0){ y_to = y - 2; x_to = x; insertMove_white(se);}} 
        }
        void b_pawn(int64_t se){
            if(board.chessBoard[y + 1][x] == 0){ y_to = y + 1; x_to = x; insertMove_black(se);}
            if(board.chessBoard[y + 1][x + 1] <= 6 && board.chessBoard[y + 1][x + 1] > 0){    if(x + 1 <= 7){ y_to = y + 1; x_to = x + 1; insertMove_black(se);}}
            if(board.chessBoard[y + 1][x - 1] <= 6 && board.chessBoard[y + 1][x - 1] > 0){    if(x - 1 >= 0){ y_to = y + 1; x_to = x - 1; insertMove_black(se);}}
            if(y == 1){    if(board.chessBoard[y + 1][x] == 0 && board.chessBoard[y + 2][x] == 0){ y_to = y + 2; x_to = x; insertMove_black(se);}} 
        }
        void w_knight(int64_t se){
            if(board.chessBoard[y + 1][x + 2] >= 11 || board.chessBoard[y + 1][x + 2] == 0){
                if(y + 1 <= 7 && x + 2 <= 7){ y_to = y + 1; x_to = x + 2; insertMove_white(se);}
            }
            if(board.chessBoard[y - 1][x + 2] >= 11 || board.chessBoard[y - 1][x + 2] == 0){
                if(y - 1 >= 0 && x + 2 <= 7){ y_to = y - 1; x_to = x + 2; insertMove_white(se);} 
            }
            if(board.chessBoard[y + 1][x - 2] >= 11 || board.chessBoard[y + 1][x - 2] == 0){
                if(y + 1 <= 7 && x - 2 >= 0){ y_to = y + 1; x_to = x - 2; insertMove_white(se);}
            }
            if(board.chessBoard[y - 1][x - 2] >= 11 || board.chessBoard[y - 1][x - 2] == 0){
                if(y - 1 >= 0 && x - 2 >= 0){ y_to = y - 1; x_to = x - 2; insertMove_white(se);} 
            }
            if(board.chessBoard[y + 2][x + 1] >= 11 || board.chessBoard[y + 2][x + 1] == 0){
                if(y + 2 <= 7 && x + 1 <= 7){ y_to = y + 2; x_to = x + 1; insertMove_white(se);}
            }
            if(board.chessBoard[y - 2][x + 1] >= 11 || board.chessBoard[y - 2][x + 1] == 0){
                if(y - 2 >= 0 && x + 1 <= 7){ y_to = y - 2; x_to = x + 1; insertMove_white(se);}
            }
            if(board.chessBoard[y + 2][x - 1] >= 11 || board.chessBoard[y + 2][x - 1] == 0){
                if(y + 2 <= 7 && x - 1 >= 0){ y_to = y + 2; x_to = x - 1; insertMove_white(se);}
            }
            if(board.chessBoard[y - 2][x - 1] >= 11 || board.chessBoard[y - 2][x - 1] == 0){
                if(y - 2 >= 0 && x - 1 >= 0){ y_to = y - 2; x_to = x - 1; insertMove_white(se);}
            }
        }
        void b_knight(int64_t se){
            if(board.chessBoard[y + 1][x + 2] <= 6 || board.chessBoard[y + 1][x + 2] == 0){
                if(y + 1 <= 7 && x + 2 <= 7){ y_to = y + 1; x_to = x + 2; insertMove_black(se);}
            }
            if(board.chessBoard[y - 1][x + 2] <= 6 || board.chessBoard[y - 1][x + 2] == 0){
                if(y - 1 >= 0 && x + 2 <= 7){ y_to = y - 1; x_to = x + 2; insertMove_black(se);} 
            }
            if(board.chessBoard[y + 1][x - 2] <= 6 || board.chessBoard[y + 1][x - 2] == 0){
                if(y + 1 <= 7 && x - 2 >= 0){ y_to = y + 1; x_to = x - 2; insertMove_black(se);}
            }
            if(board.chessBoard[y - 1][x - 2] <= 6 || board.chessBoard[y - 1][x - 2] == 0){
                if(y - 1 >= 0 && x - 2 >= 0){ y_to = y - 1; x_to = x - 2; insertMove_black(se);} 
            }
            if(board.chessBoard[y + 2][x + 1] <= 6 || board.chessBoard[y + 2][x + 1] == 0){
                if(y + 2 <= 7 && x + 1 <= 7){ y_to = y + 2; x_to = x + 1; insertMove_black(se);}
            }
            if(board.chessBoard[y - 2][x + 1] <= 6 || board.chessBoard[y - 2][x + 1] == 0){
                if(y - 2 >= 0 && x + 1 <= 7){ y_to = y - 2; x_to = x + 1; insertMove_black(se);}
            }
            if(board.chessBoard[y + 2][x - 1] <= 6 || board.chessBoard[y + 2][x - 1] == 0){
                if(y + 2 <= 7 && x - 1 >= 0){ y_to = y + 2; x_to = x - 1; insertMove_black(se);}
            }
            if(board.chessBoard[y - 2][x - 1] <= 6 || board.chessBoard[y - 2][x - 1] == 0){
                if(y - 2 >= 0 && x - 1 >= 0){ y_to = y - 2; x_to = x - 1; insertMove_black(se);}
            }
        }
        void w_bishop(int64_t se){
            for(int64_t i = 1; i < 8; i++){ // down & right
                if(y + i > 7 || x + i > 7){ break;}
                if(board.chessBoard[y + i][x + i] == empty_square){ y_to = y + i; x_to = x + i; insertMove_white(se);
                } else if(board.chessBoard[y + i][x + i] <= 6 && board.chessBoard[y + i][x + i] != empty_square){ break;
                } else if(board.chessBoard[y + i][x + i] >= 11){ y_to = y + i; x_to = x + i; insertMove_white(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // down & left
                if(y + i > 7 || x - i < 0){ break;}
                if(board.chessBoard[y + i][x - i] == empty_square){ y_to = y + i; x_to = x - i; insertMove_white(se);
                } else if(board.chessBoard[y + i][x - i] <= 6 && board.chessBoard[y + i][x - i] != empty_square){ break;
                } else if(board.chessBoard[y + i][x - i] >= 11){ y_to = y + i; x_to = x - i; insertMove_white(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & left
                if(y - i < 0 || x - i < 0){ break;}
                if(board.chessBoard[y - i][x - i] == empty_square){ y_to = y - i; x_to = x - i; insertMove_white(se);
                } else if(board.chessBoard[y - i][x - i] <= 6 && board.chessBoard[y - i][x - i] != empty_square){ break;
                } else if(board.chessBoard[y - i][x - i] >= 11){ y_to = y - i; x_to = x - i; insertMove_white(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & right
                if(y - i < 0 || x + i > 7){ break;}
                if(board.chessBoard[y - i][x + i] == empty_square){ y_to = y - i; x_to = x + i; insertMove_white(se);
                } else if(board.chessBoard[y - i][x + i] <= 6 && board.chessBoard[y - i][x + i] != empty_square){ break;
                } else if(board.chessBoard[y - i][x + i] >= 11){ y_to = y - i; x_to = x + i; insertMove_white(se); break;}
            }
        }
        void b_bishop(int64_t se){
            for(int64_t i = 1; i < 8; i++){ // down & right
                if(y + i > 7 || x + i > 7){ break;}
                if(board.chessBoard[y + i][x + i] == empty_square){ y_to = y + i; x_to = x + i; insertMove_black(se);
                } else if(board.chessBoard[y + i][x + i] >= 11){ break;
                } else if(board.chessBoard[y + i][x + i] <= 6 && board.chessBoard[y + i][x + i] != 0){ y_to = y + i; x_to = x + i; insertMove_black(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // down & left
                if(y + i > 7 || x - i < 0){ break;}
                if(board.chessBoard[y + i][x - i] == empty_square){ y_to = y + i; x_to = x - i; insertMove_black(se);
                } else if(board.chessBoard[y + i][x - i] >= 11){break;
                } else if(board.chessBoard[y + i][x - i] <= 6 && board.chessBoard[y + i][x - i] != 0){ y_to = y + i; x_to = x - i; insertMove_black(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & left
                if(y - i < 0 || x - i < 0){ break;}
                if(board.chessBoard[y - i][x - i] == empty_square){ y_to = y - i; x_to = x - i; insertMove_black(se);
                } else if(board.chessBoard[y - i][x - i] >= 11){ break;
                } else if(board.chessBoard[y - i][x - i] <= 6 && board.chessBoard[y - i][x - i] != empty_square){ y_to = y - i; x_to = x - i; insertMove_black(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & right
                if(y - i < 0 || x + i > 7){ break;}
                if(board.chessBoard[y - i][x + i] == empty_square){ y_to = y - i; x_to = x + i; insertMove_black(se);
                } else if(board.chessBoard[y - i][x + i] >= 11){ break;
                } else if(board.chessBoard[y - i][x + i] <= 6 && board.chessBoard[y - i][x + i] != empty_square){ y_to = y - i; x_to = x + i; insertMove_black(se); break;}
            }
        }
        void w_rook(int64_t se){
            for(int64_t i = 1; i < 8; i++){ // down
                if(y + i > 7){ break;
                } else if(board.chessBoard[y + i][x] == empty_square){ y_to = y + i; x_to = x; insertMove_white(se);
                } else if(board.chessBoard[y + i][x] <= 6 && board.chessBoard[y + i][x] != empty_square){ break;
                } else if(board.chessBoard[y + i][x] >= 11){ y_to = y + i; x_to = x; insertMove_white(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // left
                if(x - i < 0){ break;
                } else if(board.chessBoard[y][x - i] == empty_square){ y_to = y; x_to = x - i; insertMove_white(se);
                } else if(board.chessBoard[y][x - i] <= 6 && board.chessBoard[y][x - i] != empty_square){ break;
                } else if(board.chessBoard[y][x - i] >= 11){ y_to = y; x_to = x - i; insertMove_white(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up
                if(y - i < 0){ break;
                } else if(board.chessBoard[y - i][x] == empty_square){ y_to = y - i; x_to = x; insertMove_white(se);
                } else if(board.chessBoard[y - i][x] <= 6 && board.chessBoard[y - i][x] != empty_square){ break;
                } else if(board.chessBoard[y - i][x] >= 11){ y_to = y - i; x_to = x; insertMove_white(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // right
                if(x + i > 7){ break;
                } else if(board.chessBoard[y][x + i] == empty_square){ y_to = y; x_to = x + i; insertMove_white(se);
                } else if(board.chessBoard[y][x + i] <= 6 && board.chessBoard[y][x + i] != empty_square){ break;
                } else if(board.chessBoard[y][x + i] >= 11){ y_to = y; x_to = x + i; insertMove_white(se); break;}
            }
        }
        void b_rook(int64_t se){
            for(int64_t i = 1; i < 8; i++){ // down
                if(y + i > 7){ break;
                } else if(board.chessBoard[y + i][x] == empty_square){ y_to = y + i; x_to = x; insertMove_black(se);
                } else if(board.chessBoard[y + i][x] >= 11){ break;
                } else if(board.chessBoard[y + i][x] <= 6 && board.chessBoard[y + i][x] != empty_square){ y_to = y + i; x_to = x; insertMove_black(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // left
                if(x - i < 0){ break;
                } else if(board.chessBoard[y][x - i] == empty_square){ y_to = y; x_to = x - i; insertMove_black(se);
                } else if(board.chessBoard[y][x - i] >= 11){ break;
                } else if(board.chessBoard[y][x - i] <= 6 && board.chessBoard[y][x - i] != empty_square){ y_to = y; x_to = x - i; insertMove_black(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up
                if(y - i < 0){ break;
                } else if(board.chessBoard[y - i][x] == empty_square){ y_to = y - i; x_to = x; insertMove_black(se);
                } else if(board.chessBoard[y - i][x] >= 11){ break;
                } else if(board.chessBoard[y - i][x] <= 6 && board.chessBoard[y - i][x] != empty_square){ y_to = y - i; x_to = x; insertMove_black(se); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // right
                if(x + i > 7){ break;
                } else if(board.chessBoard[y][x + i] == empty_square){ y_to = y; x_to = x + i; insertMove_black(se);
                } else if(board.chessBoard[y][x + i] >= 11){ break;
                } else if(board.chessBoard[y][x + i] <= 6 && board.chessBoard[y][x + i] != empty_square){ y_to = y; x_to = x + i; insertMove_black(se); break;}
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
            if(board.chessBoard[y + 1][x] == empty_square || board.chessBoard[y + 1][x] >= 11){    if(y + 1 <= 7){ y_to = y + 1; x_to = x; insertMove_white(se);}}
            if(board.chessBoard[y - 1][x] == empty_square || board.chessBoard[y - 1][x] >= 11){    if(y - 1 >= 0){ y_to = y - 1; x_to = x; insertMove_white(se);}}
            if(board.chessBoard[y][x + 1] == empty_square || board.chessBoard[y][x + 1] >= 11){    if(x + 1 <= 7){ y_to = y; x_to = x + 1; insertMove_white(se);}}
            if(board.chessBoard[y][x - 1] == empty_square || board.chessBoard[y][x - 1] >= 11){    if(x - 1 >= 0){ y_to = y; x_to = x - 1; insertMove_white(se);}}
            if(board.chessBoard[y + 1][x + 1] == empty_square || board.chessBoard[y + 1][x + 1] >= 11){    if(y + 1 <= 7 && x + 1 <= 7){ y_to = y + 1; x_to = x + 1; insertMove_white(se);}}
            if(board.chessBoard[y + 1][x - 1] == empty_square || board.chessBoard[y + 1][x - 1] >= 11){    if(y + 1 <= 7 && x - 1 >= 0){ y_to = y + 1; x_to = x - 1; insertMove_white(se);}}
            if(board.chessBoard[y - 1][x + 1] == empty_square || board.chessBoard[y - 1][x + 1] >= 11){    if(y - 1 >= 0 && x + 1 <= 7){ y_to = y - 1; x_to = x + 1; insertMove_white(se);}}
            if(board.chessBoard[y - 1][x - 1] == empty_square || board.chessBoard[y - 1][x - 1] >= 11){    if(y - 1 >= 0 && x - 1 >= 0){ y_to = y - 1; x_to = x - 1; insertMove_white(se);}}
            if(y == 7 && x == 4 && KSCastlingRights_white && board.chessBoard[7][5] == empty_square && board.chessBoard[7][6] == empty_square){ y_to = y; x_to = x + 2; insertMove_white(se);}
            if(y == 7 && x == 4 && QSCastlingRights_white && board.chessBoard[7][3] == 0 && board.chessBoard[7][2] == 0 && board.chessBoard[7][1] == 0){ y_to = y; x_to = x - 2; insertMove_white(se);}
        }
        void b_king(int64_t se){
            if(board.chessBoard[y + 1][x] <= 6){    if(y + 1 <= 7){ y_to = y + 1; x_to = x; insertMove_black(se);}}
            if(board.chessBoard[y - 1][x] <= 6){    if(y - 1 >= 0){ y_to = y - 1; x_to = x; insertMove_black(se);}}
            if(board.chessBoard[y][x + 1] <= 6){    if(x + 1 <= 7){ y_to = y; x_to = x + 1; insertMove_black(se);}}
            if(board.chessBoard[y][x - 1] <= 6){    if(x - 1 >= 0){ y_to = y; x_to = x - 1; insertMove_black(se);}}
            if(board.chessBoard[y + 1][x + 1] <= 6){    if(y + 1 <= 7 && x + 1 <= 7){ y_to = y + 1; x_to = x + 1; insertMove_black(se);}}
            if(board.chessBoard[y + 1][x - 1] <= 6){    if(y + 1 <= 7 && x - 1 >= 0){ y_to = y + 1; x_to = x - 1; insertMove_black(se);}}
            if(board.chessBoard[y - 1][x + 1] <= 6){    if(y - 1 >= 0 && x + 1 <= 7){ y_to = y - 1; x_to = x + 1; insertMove_black(se);}}
            if(board.chessBoard[y - 1][x - 1] <= 6){    if(y - 1 >= 0 && x - 1 >= 0){ y_to = y - 1; x_to = x - 1; insertMove_black(se);}}
            if(y == 0 && x == 4 && KSCastlingRights_black && board.chessBoard[0][5] == empty_square && board.chessBoard[0][6] == empty_square){ y_to = y; x_to = x + 2; insertMove_black(se);
            }
            if(y == 0 && x == 4 && QSCastlingRights_black && board.chessBoard[0][3] == 0 && board.chessBoard[0][2] == 0 && board.chessBoard[0][1] == 0){ y_to = y; x_to = x - 2; insertMove_black(se);}
        }
};
Move_gen moveGen;

void generateMoves(int64_t side, int64_t se){
    if(se == 1){ n = 0; memset(moveList, 0, sizeof(moveList));
    } else{ o = 0; memset(eml, 0, sizeof(eml));}
    if(side == 1){
        for(int64_t i = 0; i < 8; i++){ y = i; for(int64_t j = 0; j < 8; j++){ x = j;
            if(board.chessBoard[y][x] == white_pawn){ moveGen.w_pawn(se);
            } else if(board.chessBoard[y][x] == white_knight){ moveGen.w_knight(se);
            } else if(board.chessBoard[y][x] == white_bishop){ moveGen.w_bishop(se);
            } else if(board.chessBoard[y][x] == white_rook){ moveGen.w_rook(se);
            } else if(board.chessBoard[y][x] == white_queen){ moveGen.w_queen(se);
            } else if(board.chessBoard[y][x] == white_king){ moveGen.w_king(se);
            }}
        }
    }
    else{
        for(int64_t i = 0; i < 8; i++){ y = i; for(int64_t j = 0; j < 8; j++){ x = j;
            if(board.chessBoard[y][x] == black_pawn){ moveGen.b_pawn(se);
            } else if(board.chessBoard[y][x] == black_knight){ moveGen.b_knight(se);
            } else if(board.chessBoard[y][x] == black_bishop){ moveGen.b_bishop(se);
            } else if(board.chessBoard[y][x] == black_rook){ moveGen.b_rook(se);
            } else if(board.chessBoard[y][x] == black_queen){ moveGen.b_queen(se);
            } else if(board.chessBoard[y][x] == black_king){ moveGen.b_king(se);
            }}
        }
    }
}