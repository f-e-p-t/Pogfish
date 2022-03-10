#include<iostream>
using namespace std;

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

int64_t nodes = 0;
class Board{
    public:
        int64_t chessBoard[8][8] = {0};
        int64_t CC[8][8] = {0};
        bool side;
        bool KSCastlingRights_white = true;
        bool QSCastlingRights_white = true;
        bool KSCastlingRights_black = true;
        bool QSCastlingRights_black = true;
        bool opening;
        bool middlegame;
        bool endgame;
        void playMove(bool castlingRightsRemoved, int64_t _move[]){
            side = !side;
            int64_t from_y = _move[0];
            int64_t from_x = _move[1];
            int64_t to_y = _move[2];
            int64_t to_x = _move[3];
            // castling
            if(chessBoard[from_y][from_x] == white_rook && from_y == 7 && from_x == 0){
                if(castlingRightsRemoved){ QSCastlingRights_white = false;}
            } else if(chessBoard[from_y][from_x] == white_rook && from_y == 7 && from_x == 7){
                if(castlingRightsRemoved){ KSCastlingRights_white = false;}
            } else if(chessBoard[from_y][from_x] == black_rook && from_y == 0 && from_x == 0){
                if(castlingRightsRemoved){ QSCastlingRights_black = false;}
            } else if(chessBoard[from_y][from_x] == black_rook && from_y == 0 && from_x == 7){
                if(castlingRightsRemoved){ KSCastlingRights_black = false;}
            }
            if(chessBoard[from_y][from_x] == white_king && from_y == 7 && from_x == 4 && to_y == 7 && to_x == 6 && chessBoard[7][7] == white_rook && KSCastlingRights_white){ chessBoard[7][7] = empty_square; chessBoard[7][5] = white_rook;
            } else if(chessBoard[from_y][from_x] == white_king && from_y == 7 && from_x == 4 && to_y == 7 && to_x == 2 && chessBoard[7][0] == white_rook && QSCastlingRights_white){ chessBoard[7][0] = empty_square; chessBoard[7][3] = white_rook;
            } else if(chessBoard[from_y][from_x] == black_king && from_y == 0 && from_x == 4 && to_y == 0 && to_x == 6 && chessBoard[0][7] == black_rook && KSCastlingRights_black){ chessBoard[0][7] = empty_square; chessBoard[0][5] = black_rook;
            } else if(chessBoard[from_y][from_x] == black_king && from_y == 0 && from_x == 4 && to_y == 0 && to_x == 2 && chessBoard[0][0] == black_rook && QSCastlingRights_black){ chessBoard[0][0] = empty_square; chessBoard[0][3] = black_rook;
            }
            if(chessBoard[from_y][from_x] == white_king){ if(castlingRightsRemoved){ KSCastlingRights_white = false; QSCastlingRights_white = false;}}
            if(chessBoard[from_y][from_x] == black_king){ if(castlingRightsRemoved){ KSCastlingRights_black = false; QSCastlingRights_black = false;}}
            // promotion
            if(chessBoard[from_y][from_x] == white_pawn && to_y == 0){ chessBoard[from_y][from_x] = empty_square; chessBoard[to_y][to_x] = white_queen; memcpy(CC, chessBoard, sizeof(chessBoard)); return ;
            } else if(chessBoard[from_y][from_x] == black_pawn && to_y == 7){ chessBoard[from_y][from_x] = empty_square; chessBoard[to_y][to_x] = black_queen; memcpy(CC, chessBoard, sizeof(chessBoard)); return ;
            }
            chessBoard[to_y][to_x] = chessBoard[from_y][from_x];
            chessBoard[from_y][from_x] = empty_square;
            memcpy(CC, chessBoard, sizeof(chessBoard));
        }
        void playMove_CC(bool castlingRightsRemoved, int64_t y, int64_t x, int64_t y_to, int64_t x_to){
            // castling
            if(CC[y][x] == white_king || CC[y][x] == black_king)
            {
            if(CC[y][x] == white_rook && y == 7 && x == 0){
                if(castlingRightsRemoved){ QSCastlingRights_white = false;}
            } else if(CC[y][x] == white_rook && y == 7 && x == 7){
                if(castlingRightsRemoved){ KSCastlingRights_white = false;}
            } else if(CC[y][x] == black_rook && y == 0 && x == 0){
                if(castlingRightsRemoved){ QSCastlingRights_black = false;}
            } else if(CC[y][x] == white_rook && y == 0 && x == 7){
                if(castlingRightsRemoved){ KSCastlingRights_black = false;}
            }
            if(CC[y][x] == white_king && y == 7 && x == 4 && y_to == 7 && x_to == 6 && KSCastlingRights_white){ CC[7][7] = empty_square; CC[7][5] = white_rook;
            } else if(CC[y][x] == white_king && y == 7 && x == 4 && y_to == 7 && x_to == 2 && QSCastlingRights_white){ CC[7][0] = empty_square; CC[7][3] = white_rook;
            } else if(CC[y][x] == black_king && y == 0 && x == 4 && y_to == 0 && x_to == 6 && KSCastlingRights_black){ CC[0][7] = empty_square; CC[0][5] = black_rook;
            } else if(CC[y][x] == black_king && y == 0 && x == 4 && y_to == 0 && x_to == 2 && QSCastlingRights_black){ CC[0][0] = empty_square; CC[0][3] = black_rook;
            }
            if(CC[y][x] == white_king){ if(castlingRightsRemoved){ KSCastlingRights_white = false; QSCastlingRights_white = false;}}
            if(CC[y][x] == black_king){ if(castlingRightsRemoved){ KSCastlingRights_black = false; QSCastlingRights_black = false;}}
            }
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
        void printBoard(){
            cout << "-----------------------------------------" << endl;
            for(int64_t i = 0; i < 8; i++){
                cout << "|";
                for(int64_t j = 0; j < 8; j++){
                    if(chessBoard[i][j] == white_pawn){ cout << "  P |";
                    } else if(chessBoard[i][j] == white_knight){ cout << "  N |";
                    } else if(chessBoard[i][j] == white_bishop){ cout << "  B |";
                    } else if(chessBoard[i][j] == white_rook){ cout << "  R |";
                    } else if(chessBoard[i][j] == white_queen){ cout << "  Q |";
                    } else if(chessBoard[i][j] == white_king){ cout << "  K |";
                    } else if(chessBoard[i][j] == black_pawn){ cout << "  p |";
                    } else if(chessBoard[i][j] == black_knight){ cout << "  n |";
                    } else if(chessBoard[i][j] == black_bishop){ cout << "  b |";
                    } else if(chessBoard[i][j] == black_rook){ cout << "  r |";
                    } else if(chessBoard[i][j] == black_queen){ cout << "  q |";
                    } else if(chessBoard[i][j] == black_king){ cout << "  k |";
                    } else{ cout << "  - |";
                    }
                }
                cout << endl; cout << "-----------------------------------------" << endl;
            } cout << endl;
        }
};
Board board;

struct List{
    public:
        int64_t list[219][5] = {0};
        int64_t count = 0;
};
bool check(bool side){
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
void insertMove_white(int64_t list[219][5], int64_t y, int64_t x, int64_t y_to, int64_t x_to){
    board.playMove_CC(0, y, x, y_to, x_to);
    if(check(1)){ memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));
    } else{ list[list[218][0]][0] = y; list[list[218][0]][1] = x; list[list[218][0]][2] = y_to; list[list[218][0]][3] = x_to; list[218][0]++; memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));}
    nodes++;
}
void insertMove_black(int64_t list[219][5], int64_t y, int64_t x, int64_t y_to, int64_t x_to){
    board.playMove_CC(0, y, x, y_to, x_to);
    if(check(0)){ memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));
    } else{ list[list[218][0]][0] = y; list[list[218][0]][1] = x; list[list[218][0]][2] = y_to; list[list[218][0]][3] = x_to; list[218][0]++; memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));}
    nodes++;
}

class Move_gen{
    public:     
        void w_pawn(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            if(board.chessBoard[y - 1][x] == 0){ y_to = y - 1; x_to = x; insertMove_white(list, y, x, y_to, x_to);}
            if(board.chessBoard[y - 1][x + 1] >= 11){    if(x + 1 <= 7){ y_to = y - 1; x_to = x + 1; insertMove_white(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y - 1][x - 1] >= 11){    if(x - 1 >= 0){ y_to = y - 1; x_to = x - 1; insertMove_white(list, y, x, y_to, x_to);}}
            if(y == 6){    if(board.chessBoard[y - 1][x] == 0 && board.chessBoard[y - 2][x] == 0){ y_to = y - 2; x_to = x; insertMove_white(list, y, x, y_to, x_to);}} 
        }
        void b_pawn(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            if(board.chessBoard[y + 1][x] == 0){ y_to = y + 1; x_to = x; insertMove_black(list, y, x, y_to, x_to);}
            if(board.chessBoard[y + 1][x + 1] <= 6 && board.chessBoard[y + 1][x + 1] > 0){    if(x + 1 <= 7){ y_to = y + 1; x_to = x + 1; insertMove_black(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y + 1][x - 1] <= 6 && board.chessBoard[y + 1][x - 1] > 0){    if(x - 1 >= 0){ y_to = y + 1; x_to = x - 1; insertMove_black(list, y, x, y_to, x_to);}}
            if(y == 1){    if(board.chessBoard[y + 1][x] == 0 && board.chessBoard[y + 2][x] == 0){ y_to = y + 2; x_to = x; insertMove_black(list, y, x, y_to, x_to);}} 
        }
        void w_knight(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            if(board.chessBoard[y + 1][x + 2] >= 11 || board.chessBoard[y + 1][x + 2] == 0){
                if(y + 1 <= 7 && x + 2 <= 7){ y_to = y + 1; x_to = x + 2; insertMove_white(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y - 1][x + 2] >= 11 || board.chessBoard[y - 1][x + 2] == 0){
                if(y - 1 >= 0 && x + 2 <= 7){ y_to = y - 1; x_to = x + 2; insertMove_white(list, y, x, y_to, x_to);} 
            }
            if(board.chessBoard[y + 1][x - 2] >= 11 || board.chessBoard[y + 1][x - 2] == 0){
                if(y + 1 <= 7 && x - 2 >= 0){ y_to = y + 1; x_to = x - 2; insertMove_white(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y - 1][x - 2] >= 11 || board.chessBoard[y - 1][x - 2] == 0){
                if(y - 1 >= 0 && x - 2 >= 0){ y_to = y - 1; x_to = x - 2; insertMove_white(list, y, x, y_to, x_to);} 
            }
            if(board.chessBoard[y + 2][x + 1] >= 11 || board.chessBoard[y + 2][x + 1] == 0){
                if(y + 2 <= 7 && x + 1 <= 7){ y_to = y + 2; x_to = x + 1; insertMove_white(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y - 2][x + 1] >= 11 || board.chessBoard[y - 2][x + 1] == 0){
                if(y - 2 >= 0 && x + 1 <= 7){ y_to = y - 2; x_to = x + 1; insertMove_white(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y + 2][x - 1] >= 11 || board.chessBoard[y + 2][x - 1] == 0){
                if(y + 2 <= 7 && x - 1 >= 0){ y_to = y + 2; x_to = x - 1; insertMove_white(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y - 2][x - 1] >= 11 || board.chessBoard[y - 2][x - 1] == 0){
                if(y - 2 >= 0 && x - 1 >= 0){ y_to = y - 2; x_to = x - 1; insertMove_white(list, y, x, y_to, x_to);}
            }
        }
        void b_knight(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            if(board.chessBoard[y + 1][x + 2] <= 6 || board.chessBoard[y + 1][x + 2] == 0){
                if(y + 1 <= 7 && x + 2 <= 7){ y_to = y + 1; x_to = x + 2; insertMove_black(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y - 1][x + 2] <= 6 || board.chessBoard[y - 1][x + 2] == 0){
                if(y - 1 >= 0 && x + 2 <= 7){ y_to = y - 1; x_to = x + 2; insertMove_black(list, y, x, y_to, x_to);} 
            }
            if(board.chessBoard[y + 1][x - 2] <= 6 || board.chessBoard[y + 1][x - 2] == 0){
                if(y + 1 <= 7 && x - 2 >= 0){ y_to = y + 1; x_to = x - 2; insertMove_black(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y - 1][x - 2] <= 6 || board.chessBoard[y - 1][x - 2] == 0){
                if(y - 1 >= 0 && x - 2 >= 0){ y_to = y - 1; x_to = x - 2; insertMove_black(list, y, x, y_to, x_to);} 
            }
            if(board.chessBoard[y + 2][x + 1] <= 6 || board.chessBoard[y + 2][x + 1] == 0){
                if(y + 2 <= 7 && x + 1 <= 7){ y_to = y + 2; x_to = x + 1; insertMove_black(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y - 2][x + 1] <= 6 || board.chessBoard[y - 2][x + 1] == 0){
                if(y - 2 >= 0 && x + 1 <= 7){ y_to = y - 2; x_to = x + 1; insertMove_black(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y + 2][x - 1] <= 6 || board.chessBoard[y + 2][x - 1] == 0){
                if(y + 2 <= 7 && x - 1 >= 0){ y_to = y + 2; x_to = x - 1; insertMove_black(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y - 2][x - 1] <= 6 || board.chessBoard[y - 2][x - 1] == 0){
                if(y - 2 >= 0 && x - 1 >= 0){ y_to = y - 2; x_to = x - 1; insertMove_black(list, y, x, y_to, x_to);}
            }
        }
        void w_bishop(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            for(int64_t i = 1; i < 8; i++){ // down & right
                if(y + i > 7 || x + i > 7){ break;}
                if(board.chessBoard[y + i][x + i] == empty_square){ y_to = y + i; x_to = x + i; insertMove_white(list, y, x, y_to, x_to);
                } else if(board.chessBoard[y + i][x + i] <= 6 && board.chessBoard[y + i][x + i] != empty_square){ break;
                } else if(board.chessBoard[y + i][x + i] >= 11){ y_to = y + i; x_to = x + i; insertMove_white(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // down & left
                if(y + i > 7 || x - i < 0){ break;}
                if(board.chessBoard[y + i][x - i] == empty_square){ y_to = y + i; x_to = x - i; insertMove_white(list, y, x, y_to, x_to);
                } else if(board.chessBoard[y + i][x - i] <= 6 && board.chessBoard[y + i][x - i] != empty_square){ break;
                } else if(board.chessBoard[y + i][x - i] >= 11){ y_to = y + i; x_to = x - i; insertMove_white(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & left
                if(y - i < 0 || x - i < 0){ break;}
                if(board.chessBoard[y - i][x - i] == empty_square){ y_to = y - i; x_to = x - i; insertMove_white(list, y, x, y_to, x_to);
                } else if(board.chessBoard[y - i][x - i] <= 6 && board.chessBoard[y - i][x - i] != empty_square){ break;
                } else if(board.chessBoard[y - i][x - i] >= 11){ y_to = y - i; x_to = x - i; insertMove_white(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & right
                if(y - i < 0 || x + i > 7){ break;}
                if(board.chessBoard[y - i][x + i] == empty_square){ y_to = y - i; x_to = x + i; insertMove_white(list, y, x, y_to, x_to);
                } else if(board.chessBoard[y - i][x + i] <= 6 && board.chessBoard[y - i][x + i] != empty_square){ break;
                } else if(board.chessBoard[y - i][x + i] >= 11){ y_to = y - i; x_to = x + i; insertMove_white(list, y, x, y_to, x_to); break;}
            }
        }
        void b_bishop(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            for(int64_t i = 1; i < 8; i++){ // down & right
                if(y + i > 7 || x + i > 7){ break;}
                if(board.chessBoard[y + i][x + i] == empty_square){ y_to = y + i; x_to = x + i; insertMove_black(list, y, x, y_to, x_to);
                } else if(board.chessBoard[y + i][x + i] >= 11){ break;
                } else if(board.chessBoard[y + i][x + i] <= 6 && board.chessBoard[y + i][x + i] != 0){ y_to = y + i; x_to = x + i; insertMove_black(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // down & left
                if(y + i > 7 || x - i < 0){ break;}
                if(board.chessBoard[y + i][x - i] == empty_square){ y_to = y + i; x_to = x - i; insertMove_black(list, y, x, y_to, x_to);
                } else if(board.chessBoard[y + i][x - i] >= 11){break;
                } else if(board.chessBoard[y + i][x - i] <= 6 && board.chessBoard[y + i][x - i] != 0){ y_to = y + i; x_to = x - i; insertMove_black(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & left
                if(y - i < 0 || x - i < 0){ break;}
                if(board.chessBoard[y - i][x - i] == empty_square){ y_to = y - i; x_to = x - i; insertMove_black(list, y, x, y_to, x_to);
                } else if(board.chessBoard[y - i][x - i] >= 11){ break;
                } else if(board.chessBoard[y - i][x - i] <= 6 && board.chessBoard[y - i][x - i] != empty_square){ y_to = y - i; x_to = x - i; insertMove_black(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & right
                if(y - i < 0 || x + i > 7){ break;}
                if(board.chessBoard[y - i][x + i] == empty_square){ y_to = y - i; x_to = x + i; insertMove_black(list, y, x, y_to, x_to);
                } else if(board.chessBoard[y - i][x + i] >= 11){ break;
                } else if(board.chessBoard[y - i][x + i] <= 6 && board.chessBoard[y - i][x + i] != empty_square){ y_to = y - i; x_to = x + i; insertMove_black(list, y, x, y_to, x_to); break;}
            }
        }
        void w_rook(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            for(int64_t i = 1; i < 8; i++){ // down
                if(y + i > 7){ break;
                } else if(board.chessBoard[y + i][x] == empty_square){ y_to = y + i; x_to = x; insertMove_white(list, y, x, y_to, x_to);
                } else if(board.chessBoard[y + i][x] <= 6 && board.chessBoard[y + i][x] != empty_square){ break;
                } else if(board.chessBoard[y + i][x] >= 11){ y_to = y + i; x_to = x; insertMove_white(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // left
                if(x - i < 0){ break;
                } else if(board.chessBoard[y][x - i] == empty_square){ y_to = y; x_to = x - i; insertMove_white(list, y, x, y_to, x_to);
                } else if(board.chessBoard[y][x - i] <= 6 && board.chessBoard[y][x - i] != empty_square){ break;
                } else if(board.chessBoard[y][x - i] >= 11){ y_to = y; x_to = x - i; insertMove_white(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up
                if(y - i < 0){ break;
                } else if(board.chessBoard[y - i][x] == empty_square){ y_to = y - i; x_to = x; insertMove_white(list, y, x, y_to, x_to);
                } else if(board.chessBoard[y - i][x] <= 6 && board.chessBoard[y - i][x] != empty_square){ break;
                } else if(board.chessBoard[y - i][x] >= 11){ y_to = y - i; x_to = x; insertMove_white(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // right
                if(x + i > 7){ break;
                } else if(board.chessBoard[y][x + i] == empty_square){ y_to = y; x_to = x + i; insertMove_white(list, y, x, y_to, x_to);
                } else if(board.chessBoard[y][x + i] <= 6 && board.chessBoard[y][x + i] != empty_square){ break;
                } else if(board.chessBoard[y][x + i] >= 11){ y_to = y; x_to = x + i; insertMove_white(list, y, x, y_to, x_to); break;}
            }
        }
        void b_rook(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            for(int64_t i = 1; i < 8; i++){ // down
                if(y + i > 7){ break;
                } else if(board.chessBoard[y + i][x] == empty_square){ y_to = y + i; x_to = x; insertMove_black(list, y, x, y_to, x_to);
                } else if(board.chessBoard[y + i][x] >= 11){ break;
                } else if(board.chessBoard[y + i][x] <= 6 && board.chessBoard[y + i][x] != empty_square){ y_to = y + i; x_to = x; insertMove_black(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // left
                if(x - i < 0){ break;
                } else if(board.chessBoard[y][x - i] == empty_square){ y_to = y; x_to = x - i; insertMove_black(list, y, x, y_to, x_to);
                } else if(board.chessBoard[y][x - i] >= 11){ break;
                } else if(board.chessBoard[y][x - i] <= 6 && board.chessBoard[y][x - i] != empty_square){ y_to = y; x_to = x - i; insertMove_black(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up
                if(y - i < 0){ break;
                } else if(board.chessBoard[y - i][x] == empty_square){ y_to = y - i; x_to = x; insertMove_black(list, y, x, y_to, x_to);
                } else if(board.chessBoard[y - i][x] >= 11){ break;
                } else if(board.chessBoard[y - i][x] <= 6 && board.chessBoard[y - i][x] != empty_square){ y_to = y - i; x_to = x; insertMove_black(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // right
                if(x + i > 7){ break;
                } else if(board.chessBoard[y][x + i] == empty_square){ y_to = y; x_to = x + i; insertMove_black(list, y, x, y_to, x_to);
                } else if(board.chessBoard[y][x + i] >= 11){ break;
                } else if(board.chessBoard[y][x + i] <= 6 && board.chessBoard[y][x + i] != empty_square){ y_to = y; x_to = x + i; insertMove_black(list, y, x, y_to, x_to); break;}
            }
        }
        void w_queen(int64_t list[219][5], int64_t y, int64_t x){
            w_bishop(list, y, x);
            w_rook(list, y, x);
        }
        void b_queen(int64_t list[219][5], int64_t y, int64_t x){
            b_bishop(list, y, x);
            b_rook(list, y, x);
        }
        void w_king(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            if(board.chessBoard[y + 1][x] == empty_square || board.chessBoard[y + 1][x] >= 11){    if(y + 1 <= 7){ y_to = y + 1; x_to = x; insertMove_white(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y - 1][x] == empty_square || board.chessBoard[y - 1][x] >= 11){    if(y - 1 >= 0){ y_to = y - 1; x_to = x; insertMove_white(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y][x + 1] == empty_square || board.chessBoard[y][x + 1] >= 11){    if(x + 1 <= 7){ y_to = y; x_to = x + 1; insertMove_white(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y][x - 1] == empty_square || board.chessBoard[y][x - 1] >= 11){    if(x - 1 >= 0){ y_to = y; x_to = x - 1; insertMove_white(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y + 1][x + 1] == empty_square || board.chessBoard[y + 1][x + 1] >= 11){    if(y + 1 <= 7 && x + 1 <= 7){ y_to = y + 1; x_to = x + 1; insertMove_white(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y + 1][x - 1] == empty_square || board.chessBoard[y + 1][x - 1] >= 11){    if(y + 1 <= 7 && x - 1 >= 0){ y_to = y + 1; x_to = x - 1; insertMove_white(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y - 1][x + 1] == empty_square || board.chessBoard[y - 1][x + 1] >= 11){    if(y - 1 >= 0 && x + 1 <= 7){ y_to = y - 1; x_to = x + 1; insertMove_white(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y - 1][x - 1] == empty_square || board.chessBoard[y - 1][x - 1] >= 11){    if(y - 1 >= 0 && x - 1 >= 0){ y_to = y - 1; x_to = x - 1; insertMove_white(list, y, x, y_to, x_to);}}
            if(y == 7 && x == 4 && board.KSCastlingRights_white && board.chessBoard[7][5] == empty_square && board.chessBoard[7][6] == empty_square){ y_to = y; x_to = x + 2; insertMove_white(list, y, x, y_to, x_to);}
            if(y == 7 && x == 4 && board.QSCastlingRights_white && board.chessBoard[7][3] == 0 && board.chessBoard[7][2] == 0 && board.chessBoard[7][1] == 0){ y_to = y; x_to = x - 2; insertMove_white(list, y, x, y_to, x_to);}
        }
        void b_king(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            if(board.chessBoard[y + 1][x] <= 6){    if(y + 1 <= 7){ y_to = y + 1; x_to = x; insertMove_black(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y - 1][x] <= 6){    if(y - 1 >= 0){ y_to = y - 1; x_to = x; insertMove_black(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y][x + 1] <= 6){    if(x + 1 <= 7){ y_to = y; x_to = x + 1; insertMove_black(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y][x - 1] <= 6){    if(x - 1 >= 0){ y_to = y; x_to = x - 1; insertMove_black(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y + 1][x + 1] <= 6){    if(y + 1 <= 7 && x + 1 <= 7){ y_to = y + 1; x_to = x + 1; insertMove_black(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y + 1][x - 1] <= 6){    if(y + 1 <= 7 && x - 1 >= 0){ y_to = y + 1; x_to = x - 1; insertMove_black(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y - 1][x + 1] <= 6){    if(y - 1 >= 0 && x + 1 <= 7){ y_to = y - 1; x_to = x + 1; insertMove_black(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y - 1][x - 1] <= 6){    if(y - 1 >= 0 && x - 1 >= 0){ y_to = y - 1; x_to = x - 1; insertMove_black(list, y, x, y_to, x_to);}}
            if(y == 0 && x == 4 && board.KSCastlingRights_black && board.chessBoard[0][5] == empty_square && board.chessBoard[0][6] == empty_square){ y_to = y; x_to = x + 2; insertMove_black(list, y, x, y_to, x_to);}
            if(y == 0 && x == 4 && board.QSCastlingRights_black && board.chessBoard[0][3] == 0 && board.chessBoard[0][2] == 0 && board.chessBoard[0][1] == 0){ y_to = y; x_to = x - 2; insertMove_black(list, y, x, y_to, x_to);}
        }
};
Move_gen moveGen;

List generateMoves(int64_t side){
    List moves;
    if(side == 1){
        for(int64_t i = 0; i < 8; i++){ for(int64_t j = 0; j < 8; j++){
            switch(board.chessBoard[i][j]){
                case 1: moveGen.w_pawn(moves.list, i, j); break;
                case 2: moveGen.w_knight(moves.list, i, j); break;
                case 3: moveGen.w_bishop(moves.list, i, j); break;
                case 4: moveGen.w_rook(moves.list, i, j); break;
                case 5: moveGen.w_queen(moves.list, i, j); break;
                case 6: moveGen.w_king(moves.list, i, j); break;
                default: break;
            }}}
    }
    else{
        for(int64_t i = 0; i < 8; i++){ for(int64_t j = 0; j < 8; j++){
            switch(board.chessBoard[i][j]){
                case 11: moveGen.b_pawn(moves.list, i, j); break;
                case 12: moveGen.b_knight(moves.list, i, j); break;
                case 13: moveGen.b_bishop(moves.list, i, j); break;
                case 14: moveGen.b_rook(moves.list, i, j); break;
                case 15: moveGen.b_queen(moves.list, i, j); break;
                case 16: moveGen.b_king(moves.list, i, j); break;
                default: break;
            }}}
    }
    moves.count = moves.list[218][0];
    return moves;
}
