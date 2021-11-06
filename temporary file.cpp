int y;
int x;
int y_to;
int x_to;
int y;
int x;
int y_to;
int x_to;
int playMove_CC(){
    // castling
    if(chessBoard_CC[y][x] == white_rook && y == 7 && x == 0){
        QSCastlingRights_white = false;
    } else if(chessBoard_CC[y][x] == white_rook && y == 7 && x == 7){
        KSCastlingRights_white = false;
    } else if(chessBoard_CC[y][x] == black_rook && y == 0 && x == 0){
        QSCastlingRights_black = false;
    } else if(chessBoard_CC[y][x] == white_rook && y == 0 && x == 7){
        KSCastlingRights_black = false;
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
        KSCastlingRights_white = false;
        QSCastlingRights_white = false;
    }
    if(chessBoard_CC[y][x] == black_king){
        KSCastlingRights_black = false;
        QSCastlingRights_black = false;
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








class Move_gen{
    public:
        void w_pawn(int se){
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
        void b_pawn(int se){
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
        void w_knight(int se){
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
                    playMove_CC();
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
        void b_knight(int se){
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
        void w_bishop(int se){
            for(int i = 1; i < 8; i++){ // down & right
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
            for(int i = 1; i < 8; i++){ // down & left
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
            for(int i = 1; i < 8; i++){ // up & left
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
            for(int i = 1; i < 8; i++){ // up & right
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
        void b_bishop(int se){
            for(int i = 1; i < 8; i++){ // down & right
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
            for(int i = 1; i < 8; i++){ // down & left
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
            for(int i = 1; i < 8; i++){ // up & left
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
            for(int i = 1; i < 8; i++){ // up & right
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
        void w_rook(int se){
            for(int i = 1; i < 8; i++){ // down
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
            for(int i = 1; i < 8; i++){ // left
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
            for(int i = 1; i < 8; i++){ // up
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
            for(int i = 1; i < 8; i++){ // right
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
        void b_rook(int se){
            for(int i = 1; i < 8; i++){ // down
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
            for(int i = 1; i < 8; i++){ // left
                if(x - i < 0){
                    break;
                } else if(chessBoard[y][x - i] == empty_square){
                    y_to = y;
                    x_to = x - i;
                    insertMove_black(se);
                } else if(chessBoard[y][x - i] >= 11){
                    break;
                } else if(chessBoard[y + i][x] <= 6 && chessBoard[y + i][x] != empty_square){
                    y_to = y;
                    x_to = x - i;
                    insertMove_black(se);
                    break;
                }
            }
            for(int i = 1; i < 8; i++){ // up
                if(y - i < 0){
                    break;
                } else if(chessBoard[y - i][x] == empty_square){
                    y_to = y - i;
                    x_to = x;
                    insertMove_black(se);
                } else if(chessBoard[y - i][x] >= 11){
                    break;
                } else if(chessBoard[y + i][x] <= 6 && chessBoard[y + i][x] != empty_square){
                    y_to = y - i;
                    x_to = x;
                    insertMove_black(se);
                    break;
                }
            }
            for(int i = 1; i < 8; i++){ // right
                if(x + i > 7){
                    break;
                } else if(chessBoard[y][x + i] == empty_square){
                    y_to = y;
                    x_to = x + i;
                    insertMove_black(se);
                } else if(chessBoard[y][x + i] >= 11){
                    break;
                } else if(chessBoard[y + i][x] <= 6 && chessBoard[y + i][x] != empty_square){
                    y_to = y;
                    x_to = x + i;
                    insertMove_black(se);
                    break;
                }
            }
        }
        void w_queen(int se){
            w_bishop(se);
            w_rook(se);
        }
        void b_queen(int se){
            b_bishop(se);
            b_rook(se);
        }
        void w_king(int se){
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
        void b_king(int se){
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