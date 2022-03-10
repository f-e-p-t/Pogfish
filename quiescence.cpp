#include<iostream>
using namespace std;

void insertCapture_white(int64_t list[219][5], int64_t y, int64_t x, int64_t y_to, int64_t x_to){
    board.playMove_CC(0, y, x, y_to, x_to);
    if(check(1)){ memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));
    } else{ list[list[218][0]][0] = y; list[list[218][0]][1] = x; list[list[218][0]][2] = y_to; list[list[218][0]][3] = x_to; list[218][0]++; memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));}
    nodes++;
}
void insertCapture_black(int64_t list[219][5], int64_t y, int64_t x, int64_t y_to, int64_t x_to){
    board.playMove_CC(0, y, x, y_to, x_to);
    if(check(0)){ memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));
    } else{ list[list[218][0]][0] = y; list[list[218][0]][1] = x; list[list[218][0]][2] = y_to; list[list[218][0]][3] = x_to; list[218][0]++; memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));}
    nodes++;
}

class Capture_gen{
    public:
        void w_pawn(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            if(board.chessBoard[y - 1][x + 1] >= 11){    if(x + 1 <= 7){ y_to = y - 1; x_to = x + 1; insertCapture_white(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y - 1][x - 1] >= 11){    if(x - 1 >= 0){ y_to = y - 1; x_to = x - 1; insertCapture_white(list, y, x, y_to, x_to);}}
        }
        void b_pawn(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            if(board.chessBoard[y + 1][x + 1] <= 6 && board.chessBoard[y + 1][x + 1] > 0){    if(x + 1 <= 7){ y_to = y + 1; x_to = x + 1; insertCapture_black(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y + 1][x - 1] <= 6 && board.chessBoard[y + 1][x - 1] > 0){    if(x - 1 >= 0){ y_to = y + 1; x_to = x - 1; insertCapture_black(list, y, x, y_to, x_to);}}
        }
        void w_knight(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            if(board.chessBoard[y + 1][x + 2] >= 11){
                if(y + 1 <= 7 && x + 2 <= 7){ y_to = y + 1; x_to = x + 2; insertCapture_white(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y - 1][x + 2] >= 11){
                if(y - 1 >= 0 && x + 2 <= 7){ y_to = y - 1; x_to = x + 2; insertCapture_white(list, y, x, y_to, x_to);} 
            }
            if(board.chessBoard[y + 1][x - 2] >= 11){
                if(y + 1 <= 7 && x - 2 >= 0){ y_to = y + 1; x_to = x - 2; insertCapture_white(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y - 1][x - 2] >= 11){
                if(y - 1 >= 0 && x - 2 >= 0){ y_to = y - 1; x_to = x - 2; insertCapture_white(list, y, x, y_to, x_to);} 
            }
            if(board.chessBoard[y + 2][x + 1] >= 11){
                if(y + 2 <= 7 && x + 1 <= 7){ y_to = y + 2; x_to = x + 1; insertCapture_white(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y - 2][x + 1] >= 11){
                if(y - 2 >= 0 && x + 1 <= 7){ y_to = y - 2; x_to = x + 1; insertCapture_white(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y + 2][x - 1] >= 11){
                if(y + 2 <= 7 && x - 1 >= 0){ y_to = y + 2; x_to = x - 1; insertCapture_white(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y - 2][x - 1] >= 11){
                if(y - 2 >= 0 && x - 1 >= 0){ y_to = y - 2; x_to = x - 1; insertCapture_white(list, y, x, y_to, x_to);}
            }
        }
        void b_knight(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            if(board.chessBoard[y + 1][x + 2] <= 6){
                if(y + 1 <= 7 && x + 2 <= 7){ y_to = y + 1; x_to = x + 2; insertCapture_black(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y - 1][x + 2] <= 6){
                if(y - 1 >= 0 && x + 2 <= 7){ y_to = y - 1; x_to = x + 2; insertCapture_black(list, y, x, y_to, x_to);} 
            }
            if(board.chessBoard[y + 1][x - 2] <= 6){
                if(y + 1 <= 7 && x - 2 >= 0){ y_to = y + 1; x_to = x - 2; insertCapture_black(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y - 1][x - 2] <= 6){
                if(y - 1 >= 0 && x - 2 >= 0){ y_to = y - 1; x_to = x - 2; insertCapture_black(list, y, x, y_to, x_to);} 
            }
            if(board.chessBoard[y + 2][x + 1] <= 6){
                if(y + 2 <= 7 && x + 1 <= 7){ y_to = y + 2; x_to = x + 1; insertCapture_black(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y - 2][x + 1] <= 6){
                if(y - 2 >= 0 && x + 1 <= 7){ y_to = y - 2; x_to = x + 1; insertCapture_black(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y + 2][x - 1] <= 6){
                if(y + 2 <= 7 && x - 1 >= 0){ y_to = y + 2; x_to = x - 1; insertCapture_black(list, y, x, y_to, x_to);}
            }
            if(board.chessBoard[y - 2][x - 1] <= 6){
                if(y - 2 >= 0 && x - 1 >= 0){ y_to = y - 2; x_to = x - 1; insertCapture_black(list, y, x, y_to, x_to);}
            }
        }
        void w_bishop(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            for(int64_t i = 1; i < 8; i++){ // down & right
                if(y + i > 7 || x + i > 7){ break;}
                if(board.chessBoard[y + i][x + i] <= 6 && board.chessBoard[y + i][x + i] != empty_square){ break;
                } else if(board.chessBoard[y + i][x + i] >= 11){ y_to = y + i; x_to = x + i; insertCapture_white(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // down & left
                if(y + i > 7 || x - i < 0){ break;}
                if(board.chessBoard[y + i][x - i] <= 6 && board.chessBoard[y + i][x - i] != empty_square){ break;
                } else if(board.chessBoard[y + i][x - i] >= 11){ y_to = y + i; x_to = x - i; insertCapture_white(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & left
                if(y - i < 0 || x - i < 0){ break;}
                if(board.chessBoard[y - i][x - i] <= 6 && board.chessBoard[y - i][x - i] != empty_square){ break;
                } else if(board.chessBoard[y - i][x - i] >= 11){ y_to = y - i; x_to = x - i; insertCapture_white(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & right
                if(y - i < 0 || x + i > 7){ break;}
                if(board.chessBoard[y - i][x + i] <= 6 && board.chessBoard[y - i][x + i] != empty_square){ break;
                } else if(board.chessBoard[y - i][x + i] >= 11){ y_to = y - i; x_to = x + i; insertCapture_white(list, y, x, y_to, x_to); break;}
            }
        }
        void b_bishop(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            for(int64_t i = 1; i < 8; i++){ // down & right
                if(y + i > 7 || x + i > 7){ break;}
                if(board.chessBoard[y + i][x + i] >= 11){ break;
                } else if(board.chessBoard[y + i][x + i] <= 6 && board.chessBoard[y + i][x + i] != 0){ y_to = y + i; x_to = x + i; insertCapture_black(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // down & left
                if(y + i > 7 || x - i < 0){ break;}
                if(board.chessBoard[y + i][x - i] >= 11){break;
                } else if(board.chessBoard[y + i][x - i] <= 6 && board.chessBoard[y + i][x - i] != 0){ y_to = y + i; x_to = x - i; insertCapture_black(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & left
                if(y - i < 0 || x - i < 0){ break;}
                if(board.chessBoard[y - i][x - i] >= 11){ break;
                } else if(board.chessBoard[y - i][x - i] <= 6 && board.chessBoard[y - i][x - i] != empty_square){ y_to = y - i; x_to = x - i; insertCapture_black(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & right
                if(y - i < 0 || x + i > 7){ break;}
                if(board.chessBoard[y - i][x + i] >= 11){ break;
                } else if(board.chessBoard[y - i][x + i] <= 6 && board.chessBoard[y - i][x + i] != empty_square){ y_to = y - i; x_to = x + i; insertCapture_black(list, y, x, y_to, x_to); break;}
            }
        }
        void w_rook(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            for(int64_t i = 1; i < 8; i++){ // down
                if(y + i > 7){ break;}
                if(board.chessBoard[y + i][x] <= 6 && board.chessBoard[y + i][x] != empty_square){ break;
                } else if(board.chessBoard[y + i][x] >= 11){ y_to = y + i; x_to = x; insertCapture_white(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // left
                if(x - i < 0){ break;}
                if(board.chessBoard[y][x - i] <= 6 && board.chessBoard[y][x - i] != empty_square){ break;
                } else if(board.chessBoard[y][x - i] >= 11){ y_to = y; x_to = x - i; insertCapture_white(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up
                if(y - i < 0){ break;}
                if(board.chessBoard[y - i][x] <= 6 && board.chessBoard[y - i][x] != empty_square){ break;
                } else if(board.chessBoard[y - i][x] >= 11){ y_to = y - i; x_to = x; insertCapture_white(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // right
                if(x + i > 7){ break;}
                if(board.chessBoard[y][x + i] <= 6 && board.chessBoard[y][x + i] != empty_square){ break;
                } else if(board.chessBoard[y][x + i] >= 11){ y_to = y; x_to = x + i; insertCapture_white(list, y, x, y_to, x_to); break;}
            }
        }
        void b_rook(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            for(int64_t i = 1; i < 8; i++){ // down
                if(y + i > 7){ break;}
                if(board.chessBoard[y + i][x] >= 11){ break;
                } else if(board.chessBoard[y + i][x] <= 6 && board.chessBoard[y + i][x] != empty_square){ y_to = y + i; x_to = x; insertCapture_black(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // left
                if(x - i < 0){ break;}
                if(board.chessBoard[y][x - i] >= 11){ break;
                } else if(board.chessBoard[y][x - i] <= 6 && board.chessBoard[y][x - i] != empty_square){ y_to = y; x_to = x - i; insertCapture_black(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up
                if(y - i < 0){ break;}
                if(board.chessBoard[y - i][x] >= 11){ break;
                } else if(board.chessBoard[y - i][x] <= 6 && board.chessBoard[y - i][x] != empty_square){ y_to = y - i; x_to = x; insertCapture_black(list, y, x, y_to, x_to); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // right
                if(x + i > 7){ break;}
                if(board.chessBoard[y][x + i] >= 11){ break;
                } else if(board.chessBoard[y][x + i] <= 6 && board.chessBoard[y][x + i] != empty_square){ y_to = y; x_to = x + i; insertCapture_black(list, y, x, y_to, x_to); break;}
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
            if(board.chessBoard[y + 1][x] >= 11){    if(y + 1 <= 7){ y_to = y + 1; x_to = x; insertCapture_white(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y - 1][x] >= 11){    if(y - 1 >= 0){ y_to = y - 1; x_to = x; insertCapture_white(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y][x + 1] >= 11){    if(x + 1 <= 7){ y_to = y; x_to = x + 1; insertCapture_white(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y][x - 1] >= 11){    if(x - 1 >= 0){ y_to = y; x_to = x - 1; insertCapture_white(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y + 1][x + 1] >= 11){    if(y + 1 <= 7 && x + 1 <= 7){ y_to = y + 1; x_to = x + 1; insertCapture_white(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y + 1][x - 1] >= 11){    if(y + 1 <= 7 && x - 1 >= 0){ y_to = y + 1; x_to = x - 1; insertCapture_white(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y - 1][x + 1] >= 11){    if(y - 1 >= 0 && x + 1 <= 7){ y_to = y - 1; x_to = x + 1; insertCapture_white(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y - 1][x - 1] >= 11){    if(y - 1 >= 0 && x - 1 >= 0){ y_to = y - 1; x_to = x - 1; insertCapture_white(list, y, x, y_to, x_to);}}
        }
        void b_king(int64_t list[219][5], int64_t y, int64_t x){
            int64_t y_to = 0;
            int64_t x_to = 0;
            if(board.chessBoard[y + 1][x] <= 6 && board.chessBoard[y + 1][x] != 0){    if(y + 1 <= 7){ y_to = y + 1; x_to = x; insertCapture_black(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y - 1][x] <= 6 && board.chessBoard[y - 1][x] != 0){    if(y - 1 >= 0){ y_to = y - 1; x_to = x; insertCapture_black(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y][x + 1] <= 6 && board.chessBoard[y][x + 1] != 0){    if(x + 1 <= 7){ y_to = y; x_to = x + 1; insertCapture_black(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y][x - 1] <= 6 && board.chessBoard[y][x - 1] != 0){    if(x - 1 >= 0){ y_to = y; x_to = x - 1; insertCapture_black(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y + 1][x + 1] <= 6 && board.chessBoard[y + 1][x + 1] != 0){    if(y + 1 <= 7 && x + 1 <= 7){ y_to = y + 1; x_to = x + 1; insertCapture_black(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y + 1][x - 1] <= 6 && board.chessBoard[y + 1][x - 1] != 0){    if(y + 1 <= 7 && x - 1 >= 0){ y_to = y + 1; x_to = x - 1; insertCapture_black(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y - 1][x + 1] <= 6 && board.chessBoard[y - 1][x + 1] != 0){    if(y - 1 >= 0 && x + 1 <= 7){ y_to = y - 1; x_to = x + 1; insertCapture_black(list, y, x, y_to, x_to);}}
            if(board.chessBoard[y - 1][x - 1] <= 6 && board.chessBoard[y - 1][x - 1] != 0){    if(y - 1 >= 0 && x - 1 >= 0){ y_to = y - 1; x_to = x - 1; insertCapture_black(list, y, x, y_to, x_to);}}
        }
};
Capture_gen captureGen;

List generateCaptures(int64_t side){
    List moves;
    if(side == 1){
        for(int64_t i = 0; i < 8; i++){ for(int64_t j = 0; j < 8; j++){
            switch(board.chessBoard[i][j]){
                case 1: captureGen.w_pawn(moves.list, i, j); break;
                case 2: captureGen.w_knight(moves.list, i, j); break;
                case 3: captureGen.w_bishop(moves.list, i, j); break;
                case 4: captureGen.w_rook(moves.list, i, j); break;
                case 5: captureGen.w_queen(moves.list, i, j); break;
                case 6: captureGen.w_king(moves.list, i, j); break;
                default: break;
            }}}
    }
    else{
        for(int64_t i = 0; i < 8; i++){ for(int64_t j = 0; j < 8; j++){
            switch(board.chessBoard[i][j]){
                case 11: captureGen.b_pawn(moves.list, i, j); break;
                case 12: captureGen.b_knight(moves.list, i, j); break;
                case 13: captureGen.b_bishop(moves.list, i, j); break;
                case 14: captureGen.b_rook(moves.list, i, j); break;
                case 15: captureGen.b_queen(moves.list, i, j); break;
                case 16: captureGen.b_king(moves.list, i, j); break;
                default: break;
            }}}
    }
    moves.count = moves.list[218][0];
    return moves;
}