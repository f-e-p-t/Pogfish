#include<iostream>
using namespace std;

void insertCapture_white(int64_t list[219][5]){
    board.playMove_CC(0);
    if(check(1)){ memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));
    } else{ list[list[218][0]][0] = y; list[list[218][0]][1] = x; list[list[218][0]][2] = y_to; list[list[218][0]][3] = x_to; list[218][0]++; memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));}
}
void insertCapture_black(int64_t list[219][5]){
    board.playMove_CC(0);
    if(check(0)){ memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));
    } else{ list[list[218][0]][0] = y; list[list[218][0]][1] = x; list[list[218][0]][2] = y_to; list[list[218][0]][3] = x_to; list[218][0]++; memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));}
}

class Capture_gen{
    public:
        void w_pawn(int64_t list[219][5]){
            if(board.chessBoard[y - 1][x + 1] >= 11){    if(x + 1 <= 7){ y_to = y - 1; x_to = x + 1; insertCapture_white(list);}}
            if(board.chessBoard[y - 1][x - 1] >= 11){    if(x - 1 >= 0){ y_to = y - 1; x_to = x - 1; insertCapture_white(list);}}
        }
        void b_pawn(int64_t list[219][5]){
            if(board.chessBoard[y + 1][x + 1] <= 6 && board.chessBoard[y + 1][x + 1] > 0){    if(x + 1 <= 7){ y_to = y + 1; x_to = x + 1; insertCapture_black(list);}}
            if(board.chessBoard[y + 1][x - 1] <= 6 && board.chessBoard[y + 1][x - 1] > 0){    if(x - 1 >= 0){ y_to = y + 1; x_to = x - 1; insertCapture_black(list);}}
        }
        void w_knight(int64_t list[219][5]){
            if(board.chessBoard[y + 1][x + 2] >= 11){
                if(y + 1 <= 7 && x + 2 <= 7){ y_to = y + 1; x_to = x + 2; insertCapture_white(list);}
            }
            if(board.chessBoard[y - 1][x + 2] >= 11){
                if(y - 1 >= 0 && x + 2 <= 7){ y_to = y - 1; x_to = x + 2; insertCapture_white(list);} 
            }
            if(board.chessBoard[y + 1][x - 2] >= 11){
                if(y + 1 <= 7 && x - 2 >= 0){ y_to = y + 1; x_to = x - 2; insertCapture_white(list);}
            }
            if(board.chessBoard[y - 1][x - 2] >= 11){
                if(y - 1 >= 0 && x - 2 >= 0){ y_to = y - 1; x_to = x - 2; insertCapture_white(list);} 
            }
            if(board.chessBoard[y + 2][x + 1] >= 11){
                if(y + 2 <= 7 && x + 1 <= 7){ y_to = y + 2; x_to = x + 1; insertCapture_white(list);}
            }
            if(board.chessBoard[y - 2][x + 1] >= 11){
                if(y - 2 >= 0 && x + 1 <= 7){ y_to = y - 2; x_to = x + 1; insertCapture_white(list);}
            }
            if(board.chessBoard[y + 2][x - 1] >= 11){
                if(y + 2 <= 7 && x - 1 >= 0){ y_to = y + 2; x_to = x - 1; insertCapture_white(list);}
            }
            if(board.chessBoard[y - 2][x - 1] >= 11){
                if(y - 2 >= 0 && x - 1 >= 0){ y_to = y - 2; x_to = x - 1; insertCapture_white(list);}
            }
        }
        void b_knight(int64_t list[219][5]){
            if(board.chessBoard[y + 1][x + 2] <= 6){
                if(y + 1 <= 7 && x + 2 <= 7){ y_to = y + 1; x_to = x + 2; insertCapture_black(list);}
            }
            if(board.chessBoard[y - 1][x + 2] <= 6){
                if(y - 1 >= 0 && x + 2 <= 7){ y_to = y - 1; x_to = x + 2; insertCapture_black(list);} 
            }
            if(board.chessBoard[y + 1][x - 2] <= 6){
                if(y + 1 <= 7 && x - 2 >= 0){ y_to = y + 1; x_to = x - 2; insertCapture_black(list);}
            }
            if(board.chessBoard[y - 1][x - 2] <= 6){
                if(y - 1 >= 0 && x - 2 >= 0){ y_to = y - 1; x_to = x - 2; insertCapture_black(list);} 
            }
            if(board.chessBoard[y + 2][x + 1] <= 6){
                if(y + 2 <= 7 && x + 1 <= 7){ y_to = y + 2; x_to = x + 1; insertCapture_black(list);}
            }
            if(board.chessBoard[y - 2][x + 1] <= 6){
                if(y - 2 >= 0 && x + 1 <= 7){ y_to = y - 2; x_to = x + 1; insertCapture_black(list);}
            }
            if(board.chessBoard[y + 2][x - 1] <= 6){
                if(y + 2 <= 7 && x - 1 >= 0){ y_to = y + 2; x_to = x - 1; insertCapture_black(list);}
            }
            if(board.chessBoard[y - 2][x - 1] <= 6){
                if(y - 2 >= 0 && x - 1 >= 0){ y_to = y - 2; x_to = x - 1; insertCapture_black(list);}
            }
        }
        void w_bishop(int64_t list[219][5]){
            for(int64_t i = 1; i < 8; i++){ // down & right
                if(y + i > 7 || x + i > 7){ break;}
                if(board.chessBoard[y + i][x + i] <= 6 && board.chessBoard[y + i][x + i] != empty_square){ break;
                } else if(board.chessBoard[y + i][x + i] >= 11){ y_to = y + i; x_to = x + i; insertCapture_white(list); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // down & left
                if(y + i > 7 || x - i < 0){ break;}
                if(board.chessBoard[y + i][x - i] <= 6 && board.chessBoard[y + i][x - i] != empty_square){ break;
                } else if(board.chessBoard[y + i][x - i] >= 11){ y_to = y + i; x_to = x - i; insertCapture_white(list); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & left
                if(y - i < 0 || x - i < 0){ break;}
                if(board.chessBoard[y - i][x - i] <= 6 && board.chessBoard[y - i][x - i] != empty_square){ break;
                } else if(board.chessBoard[y - i][x - i] >= 11){ y_to = y - i; x_to = x - i; insertCapture_white(list); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & right
                if(y - i < 0 || x + i > 7){ break;}
                if(board.chessBoard[y - i][x + i] <= 6 && board.chessBoard[y - i][x + i] != empty_square){ break;
                } else if(board.chessBoard[y - i][x + i] >= 11){ y_to = y - i; x_to = x + i; insertCapture_white(list); break;}
            }
        }
        void b_bishop(int64_t list[219][5]){
            for(int64_t i = 1; i < 8; i++){ // down & right
                if(y + i > 7 || x + i > 7){ break;}
                if(board.chessBoard[y + i][x + i] >= 11){ break;
                } else if(board.chessBoard[y + i][x + i] <= 6 && board.chessBoard[y + i][x + i] != 0){ y_to = y + i; x_to = x + i; insertCapture_black(list); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // down & left
                if(y + i > 7 || x - i < 0){ break;}
                if(board.chessBoard[y + i][x - i] >= 11){break;
                } else if(board.chessBoard[y + i][x - i] <= 6 && board.chessBoard[y + i][x - i] != 0){ y_to = y + i; x_to = x - i; insertCapture_black(list); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & left
                if(y - i < 0 || x - i < 0){ break;}
                if(board.chessBoard[y - i][x - i] >= 11){ break;
                } else if(board.chessBoard[y - i][x - i] <= 6 && board.chessBoard[y - i][x - i] != empty_square){ y_to = y - i; x_to = x - i; insertCapture_black(list); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up & right
                if(y - i < 0 || x + i > 7){ break;}
                if(board.chessBoard[y - i][x + i] >= 11){ break;
                } else if(board.chessBoard[y - i][x + i] <= 6 && board.chessBoard[y - i][x + i] != empty_square){ y_to = y - i; x_to = x + i; insertCapture_black(list); break;}
            }
        }
        void w_rook(int64_t list[219][5]){
            for(int64_t i = 1; i < 8; i++){ // down
                if(y + i > 7){ break;}
                if(board.chessBoard[y + i][x] <= 6 && board.chessBoard[y + i][x] != empty_square){ break;
                } else if(board.chessBoard[y + i][x] >= 11){ y_to = y + i; x_to = x; insertCapture_white(list); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // left
                if(x - i < 0){ break;}
                if(board.chessBoard[y][x - i] <= 6 && board.chessBoard[y][x - i] != empty_square){ break;
                } else if(board.chessBoard[y][x - i] >= 11){ y_to = y; x_to = x - i; insertCapture_white(list); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up
                if(y - i < 0){ break;}
                if(board.chessBoard[y - i][x] <= 6 && board.chessBoard[y - i][x] != empty_square){ break;
                } else if(board.chessBoard[y - i][x] >= 11){ y_to = y - i; x_to = x; insertCapture_white(list); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // right
                if(x + i > 7){ break;}
                if(board.chessBoard[y][x + i] <= 6 && board.chessBoard[y][x + i] != empty_square){ break;
                } else if(board.chessBoard[y][x + i] >= 11){ y_to = y; x_to = x + i; insertCapture_white(list); break;}
            }
        }
        void b_rook(int64_t list[219][5]){
            for(int64_t i = 1; i < 8; i++){ // down
                if(y + i > 7){ break;}
                if(board.chessBoard[y + i][x] >= 11){ break;
                } else if(board.chessBoard[y + i][x] <= 6 && board.chessBoard[y + i][x] != empty_square){ y_to = y + i; x_to = x; insertCapture_black(list); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // left
                if(x - i < 0){ break;}
                if(board.chessBoard[y][x - i] >= 11){ break;
                } else if(board.chessBoard[y][x - i] <= 6 && board.chessBoard[y][x - i] != empty_square){ y_to = y; x_to = x - i; insertCapture_black(list); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // up
                if(y - i < 0){ break;}
                if(board.chessBoard[y - i][x] >= 11){ break;
                } else if(board.chessBoard[y - i][x] <= 6 && board.chessBoard[y - i][x] != empty_square){ y_to = y - i; x_to = x; insertCapture_black(list); break;}
            }
            for(int64_t i = 1; i < 8; i++){ // right
                if(x + i > 7){ break;}
                if(board.chessBoard[y][x + i] >= 11){ break;
                } else if(board.chessBoard[y][x + i] <= 6 && board.chessBoard[y][x + i] != empty_square){ y_to = y; x_to = x + i; insertCapture_black(list); break;}
            }
        }
        void w_queen(int64_t list[219][5]){
            w_bishop(list);
            w_rook(list);
        }
        void b_queen(int64_t list[219][5]){
            b_bishop(list);
            b_rook(list);
        }
        void w_king(int64_t list[219][5]){
            if(board.chessBoard[y + 1][x] >= 11){    if(y + 1 <= 7){ y_to = y + 1; x_to = x; insertCapture_white(list);}}
            if(board.chessBoard[y - 1][x] >= 11){    if(y - 1 >= 0){ y_to = y - 1; x_to = x; insertCapture_white(list);}}
            if(board.chessBoard[y][x + 1] >= 11){    if(x + 1 <= 7){ y_to = y; x_to = x + 1; insertCapture_white(list);}}
            if(board.chessBoard[y][x - 1] >= 11){    if(x - 1 >= 0){ y_to = y; x_to = x - 1; insertCapture_white(list);}}
            if(board.chessBoard[y + 1][x + 1] >= 11){    if(y + 1 <= 7 && x + 1 <= 7){ y_to = y + 1; x_to = x + 1; insertCapture_white(list);}}
            if(board.chessBoard[y + 1][x - 1] >= 11){    if(y + 1 <= 7 && x - 1 >= 0){ y_to = y + 1; x_to = x - 1; insertCapture_white(list);}}
            if(board.chessBoard[y - 1][x + 1] >= 11){    if(y - 1 >= 0 && x + 1 <= 7){ y_to = y - 1; x_to = x + 1; insertCapture_white(list);}}
            if(board.chessBoard[y - 1][x - 1] >= 11){    if(y - 1 >= 0 && x - 1 >= 0){ y_to = y - 1; x_to = x - 1; insertCapture_white(list);}}
        }
        void b_king(int64_t list[219][5]){
            if(board.chessBoard[y + 1][x] <= 6 && board.chessBoard[y + 1][x] != 0){    if(y + 1 <= 7){ y_to = y + 1; x_to = x; insertCapture_black(list);}}
            if(board.chessBoard[y - 1][x] <= 6 && board.chessBoard[y - 1][x] != 0){    if(y - 1 >= 0){ y_to = y - 1; x_to = x; insertCapture_black(list);}}
            if(board.chessBoard[y][x + 1] <= 6 && board.chessBoard[y][x + 1] != 0){    if(x + 1 <= 7){ y_to = y; x_to = x + 1; insertCapture_black(list);}}
            if(board.chessBoard[y][x - 1] <= 6 && board.chessBoard[y][x - 1] != 0){    if(x - 1 >= 0){ y_to = y; x_to = x - 1; insertCapture_black(list);}}
            if(board.chessBoard[y + 1][x + 1] <= 6 && board.chessBoard[y + 1][x + 1] != 0){    if(y + 1 <= 7 && x + 1 <= 7){ y_to = y + 1; x_to = x + 1; insertCapture_black(list);}}
            if(board.chessBoard[y + 1][x - 1] <= 6 && board.chessBoard[y + 1][x - 1] != 0){    if(y + 1 <= 7 && x - 1 >= 0){ y_to = y + 1; x_to = x - 1; insertCapture_black(list);}}
            if(board.chessBoard[y - 1][x + 1] <= 6 && board.chessBoard[y - 1][x + 1] != 0){    if(y - 1 >= 0 && x + 1 <= 7){ y_to = y - 1; x_to = x + 1; insertCapture_black(list);}}
            if(board.chessBoard[y - 1][x - 1] <= 6 && board.chessBoard[y - 1][x - 1] != 0){    if(y - 1 >= 0 && x - 1 >= 0){ y_to = y - 1; x_to = x - 1; insertCapture_black(list);}}
        }
};
Capture_gen captureGen;

List generateCaptures(int64_t side){
    List moves;
    if(side == 1){
        for(int64_t i = 0; i < 8; i++){ y = i; for(int64_t j = 0; j < 8; j++){ x = j;
            if(board.chessBoard[y][x] == white_pawn){ captureGen.w_pawn(moves.list);
            } else if(board.chessBoard[y][x] == white_knight){ captureGen.w_knight(moves.list);
            } else if(board.chessBoard[y][x] == white_bishop){ captureGen.w_bishop(moves.list);
            } else if(board.chessBoard[y][x] == white_rook){ captureGen.w_rook(moves.list);
            } else if(board.chessBoard[y][x] == white_queen){ captureGen.w_queen(moves.list);
            } else if(board.chessBoard[y][x] == white_king){ captureGen.w_king(moves.list);
            }}
        }
    }
    else{
        for(int64_t i = 0; i < 8; i++){ y = i; for(int64_t j = 0; j < 8; j++){ x = j;
            if(board.chessBoard[y][x] == black_pawn){ captureGen.b_pawn(moves.list);
            } else if(board.chessBoard[y][x] == black_knight){ captureGen.b_knight(moves.list);
            } else if(board.chessBoard[y][x] == black_bishop){ captureGen.b_bishop(moves.list);
            } else if(board.chessBoard[y][x] == black_rook){ captureGen.b_rook(moves.list);
            } else if(board.chessBoard[y][x] == black_queen){ captureGen.b_queen(moves.list);
            } else if(board.chessBoard[y][x] == black_king){ captureGen.b_king(moves.list);
            }}
        }
    }
    moves.count = moves.list[218][0];
    return moves;
}