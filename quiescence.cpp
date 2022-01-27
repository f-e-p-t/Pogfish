#include<iostream>
using namespace std;

List capturesOnly(int64_t side){
    List moves;
    if(side == 1){
        for(int64_t i = 0; i < 8; i++){ y = i; for(int64_t j = 0; j < 8; j++){ x = j;
            if(board.chessBoard[y][x] == white_pawn){ moveGen.w_pawn(moves.list);
            } else if(board.chessBoard[y][x] == white_knight){ moveGen.w_knight(moves.list);
            } else if(board.chessBoard[y][x] == white_bishop){ moveGen.w_bishop(moves.list);
            } else if(board.chessBoard[y][x] == white_rook){ moveGen.w_rook(moves.list);
            } else if(board.chessBoard[y][x] == white_queen){ moveGen.w_queen(moves.list);
            } else if(board.chessBoard[y][x] == white_king){ moveGen.w_king(moves.list);
            }}
        }
    }
    else{
        for(int64_t i = 0; i < 8; i++){ y = i; for(int64_t j = 0; j < 8; j++){ x = j;
            if(board.chessBoard[y][x] == black_pawn){ moveGen.b_pawn(moves.list);
            } else if(board.chessBoard[y][x] == black_knight){ moveGen.b_knight(moves.list);
            } else if(board.chessBoard[y][x] == black_bishop){ moveGen.b_bishop(moves.list);
            } else if(board.chessBoard[y][x] == black_rook){ moveGen.b_rook(moves.list);
            } else if(board.chessBoard[y][x] == black_queen){ moveGen.b_queen(moves.list);
            } else if(board.chessBoard[y][x] == black_king){ moveGen.b_king(moves.list);
            }}
        }
    }
    moves.count = moves.list[218][0];
    return moves;
}

int64_t quiescence(int64_t alpha, int64_t beta){
    return alpha;
}