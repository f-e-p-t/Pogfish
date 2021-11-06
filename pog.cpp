#include<iostream>
#include<cmath>
#include<string.h>
#include<algorithm>
using namespace std;

int tempo = 1;
int move_move = 1;
bool isLegalMove;
bool KSCastlingRights_white = true;
bool QSCastlingRights_white = true;
bool KSCastlingRights_black = true;
bool QSCastlingRights_black = true;
int best_index;
int infinity = 1000000000;
int negativeInfinity = -1000000000;

int move_y;
int move_x;
int moveTo_y;
int moveTo_x;
int y;
int x;
int y_to;
int x_to;

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
int o;
int se;
int depth;
int TEST;

int value(int piece){
    int pieceValue;
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
int getMax(int values[]){
    int best = values[0];
    best_index = 0;
    for(int i = 0; i < o; i++){
        if(values[i] > best){
            best = values[i];
            best_index = i;
        }
    }
    return best;
}
int getMin(int values[]){
    int best = values[0];
    best_index = 0;
    for(int i = 0; i < o; i++){
        if(values[i] < best){
            best = values[i];
            best_index = i;
        }
    }
    return best;
}

string FEN = "ooooookopppoopppooooooooooooooooooooooooooooooooPPPooPPPoooRooKo";

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
int eml[4][218];
int candidateScores[20000];
int avg_taker[50];
int alpha_beta[50][2][218];

// ------------------------------------------------------------------------- Rules of chess --------------------------------------------------------------------------

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

bool check_white(){
    int wkp_y = 0;
    int wkp_x = 0;
    for(int i = 0; i <= 7; i++){
        for(int j = 0; j <= 7; j++){
            if(chessBoard_CC[i][j] == white_king){
                wkp_y = i;
                wkp_x = j;
                break;
            }
        }
    }
    for(int i = 1; i < 8; i++){ // down & right
        if(wkp_y + i > 7 || wkp_x + i > 7){
            break;
        } else if(chessBoard_CC[wkp_y + i][wkp_x + i] == black_bishop || chessBoard_CC[wkp_y + i][wkp_x + i] == black_queen){
            return true;
        } else if(chessBoard_CC[wkp_y + i][wkp_x + i] >= 1 && chessBoard_CC[wkp_y + i][wkp_x + i] != black_bishop && chessBoard_CC[wkp_y + i][wkp_x + i] != black_queen){
            break;
        } else{
        }
    }
    for(int i = 1; i < 8; i++){ // down & left
        if(wkp_y + i > 7 || wkp_x - i < 0){
            break;
        } else if(chessBoard_CC[wkp_y + i][wkp_x - i] == black_bishop || chessBoard_CC[wkp_y + i][wkp_x - i] == black_queen){
            return true;
        } else if(chessBoard_CC[wkp_y + i][wkp_x - i] >= 1 && chessBoard_CC[wkp_y + i][wkp_x - i] != black_bishop && chessBoard_CC[wkp_y + i][wkp_x - i] != black_queen){
            break;
        } else{
        }
    }
    for(int i = 1; i < 8; i++){ // up & left
        if(wkp_y - i < 0 || wkp_x - i < 0){
            break;
        } else if(chessBoard_CC[wkp_y - i][wkp_x - i] == black_bishop || chessBoard_CC[wkp_y - i][wkp_x - i] == black_queen){
            return true;
        } else if(chessBoard_CC[wkp_y - i][wkp_x - i] >= 1 && chessBoard_CC[wkp_y - i][wkp_x - i] != black_bishop && chessBoard_CC[wkp_y - i][wkp_x - i] != black_queen){
            break;
        } else{
        }
    }
    for(int i = 1; i < 8; i++){ // up & right
        if(wkp_y - i < 0 || wkp_x + i > 7){
            break;
        } else if(chessBoard_CC[wkp_y - i][wkp_x + i] == black_bishop || chessBoard_CC[wkp_y - i][wkp_x + i] == black_queen){
            return true;
        } else if(chessBoard_CC[wkp_y - i][wkp_x + i] >= 1 && chessBoard_CC[wkp_y - i][wkp_x + i] != black_bishop && chessBoard_CC[wkp_y - i][wkp_x + i] != black_queen){
            break;
        } else{
        }
    }
    for(int i = 1; i < 8; i++){ // down
        if(wkp_y + i > 7){
            break;
        } else if(chessBoard_CC[wkp_y + i][wkp_x] == black_rook || chessBoard_CC[wkp_y + i][wkp_x] == black_queen){
            return true;
        } else if(chessBoard_CC[wkp_y + i][wkp_x] >= 1 && chessBoard_CC[wkp_y + i][wkp_x] != black_rook && chessBoard_CC[wkp_y + i][wkp_x] != black_queen){
            break;
        } else{
        }
    }
    for(int i = 1; i < 8; i++){ // left
        if(wkp_x - i < 0){
            break;
        } else if(chessBoard_CC[wkp_y][wkp_x - i] == black_rook || chessBoard_CC[wkp_y][wkp_x - i] == black_queen){
            return true;
        } else if(chessBoard_CC[wkp_y][wkp_x - i] >= 1 && chessBoard_CC[wkp_y][wkp_x - i] != black_rook && chessBoard_CC[wkp_y][wkp_x - i] != black_queen){
            break;
        } else{
        }
    }
    for(int i = 1; i < 8; i++){ // up
        if(wkp_y - i < 0){
            break;
        } else if(chessBoard_CC[wkp_y - i][wkp_x] == black_rook || chessBoard_CC[wkp_y - i][wkp_x] == black_queen){
            return true;
        } else if(chessBoard_CC[wkp_y - i][wkp_x] >= 1 && chessBoard_CC[wkp_y - i][wkp_x] != black_rook && chessBoard_CC[wkp_y - i][wkp_x] != black_queen){
            break;
        } else{
        }
    }
    for(int i = 1; i < 8; i++){ // right
        if(wkp_x + i > 7){
            break;
        } else if(chessBoard_CC[wkp_y][wkp_x + i] == black_rook || chessBoard_CC[wkp_y][wkp_x + i] == black_queen){
            return true;
        } else if(chessBoard_CC[wkp_y][wkp_x + i] >= 1 && chessBoard_CC[wkp_y][wkp_x + i] != black_rook && chessBoard_CC[wkp_y][wkp_x + i] != black_queen){
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
    int bkp_y = 0;
    int bkp_x = 0;
    for(int i = 0; i <= 7; i++){
        for(int j = 0; j <= 7; j++){
            if(chessBoard_CC[i][j] == black_king){
                bkp_y = i;
                bkp_x = j;
                break;
            }
        }
    }
    for(int i = 1; i < 8; i++){ // down & right
        if(bkp_y + i > 7 || bkp_x + i > 7){
            break;    
        } else if(chessBoard_CC[bkp_y + i][bkp_x + i] == white_bishop || chessBoard_CC[bkp_y + i][bkp_x + i] == white_queen){
            return true;
        } else if(chessBoard_CC[bkp_y + i][bkp_x + i] >= 1 && chessBoard_CC[bkp_y + i][bkp_x + i] != white_bishop && chessBoard_CC[bkp_y + i][bkp_x + i] != white_queen){
            break;
        } else{
        }
    }
    for(int i = 1; i < 8; i++){ // down & left
        if(bkp_y + i > 7 || bkp_x - i < 0){
            break;
        } else if(chessBoard_CC[bkp_y + i][bkp_x - i] == white_bishop || chessBoard_CC[bkp_y + i][bkp_x - i] == white_queen){
            return true;
        } else if(chessBoard_CC[bkp_y + i][bkp_x - i] >= 1 && chessBoard_CC[bkp_y + i][bkp_x - i] != white_bishop && chessBoard_CC[bkp_y + i][bkp_x - i] != white_queen){
            break;
        } else{
        }
    }
    for(int i = 1; i < 8; i++){ // up & left
        if(bkp_y - i < 0 || bkp_x - i < 0){
            break;   
        } else if(chessBoard_CC[bkp_y - i][bkp_x - i] == white_bishop || chessBoard_CC[bkp_y - i][bkp_x - i] == white_queen){
            return true;
        } else if(chessBoard_CC[bkp_y - i][bkp_x - i] >= 1 && chessBoard_CC[bkp_y - i][bkp_x - i] != white_bishop && chessBoard_CC[bkp_y - i][bkp_x - i] != white_queen){
            break;
        } else{
        }
    }
    for(int i = 1; i < 8; i++){ // up & right
        if(bkp_y - i < 0 || bkp_x + i > 7){
            break;   
        } else if(chessBoard_CC[bkp_y - i][bkp_x + i] == white_bishop || chessBoard_CC[bkp_y - i][bkp_x + i] == white_queen){
            return true;
        } else if(chessBoard_CC[bkp_y - i][bkp_x + i] >= 1 && chessBoard_CC[bkp_y - i][bkp_x + i] != white_bishop && chessBoard_CC[bkp_y - i][bkp_x + i] != white_queen){
            break;
        } else{
        }
    }
    for(int i = 1; i < 8; i++){ // down
        if(bkp_x + i > 7){
            break;
        } else if(chessBoard_CC[bkp_y + i][bkp_x] == white_rook || chessBoard_CC[bkp_y + i][bkp_x] == white_queen){
            return true;
        } else if(chessBoard_CC[bkp_y + i][bkp_x] >= 1 && chessBoard_CC[bkp_y + i][bkp_x] != white_rook && chessBoard_CC[bkp_y + i][bkp_x] != white_queen){
            break;
        } else{
        }
    }
    for(int i = 1; i < 8; i++){ // left
        if(bkp_x - i < 0){
            break;
        } else if(chessBoard_CC[bkp_y][bkp_x - i] == white_rook || chessBoard_CC[bkp_y][bkp_x - i] == white_queen){
            return true;
        } else if(chessBoard_CC[bkp_y][bkp_x - i] >= 1 && chessBoard_CC[bkp_y][bkp_x - i] != white_rook && chessBoard_CC[bkp_y][bkp_x - i] != white_queen){
            break;
        } else{
        }
    }
    for(int i = 1; i < 8; i++){ // up
        if(bkp_y - i < 0){
            break;
        } else if(chessBoard_CC[bkp_y - i][bkp_x] == white_rook || chessBoard_CC[bkp_y - i][bkp_x] == white_queen){
            return true;
        } else if(chessBoard_CC[bkp_y - i][bkp_x] >= 1 && chessBoard_CC[bkp_y - i][bkp_x] != white_rook && chessBoard_CC[bkp_y - i][bkp_x] != white_queen){
            break;
        } else{
        }
    }
    for(int i = 1; i < 8; i++){ // right
        if(bkp_x + i > 7){
            break;
        } else if(chessBoard_CC[bkp_y][bkp_x + i] == white_rook || chessBoard_CC[bkp_y][bkp_x + i] == white_queen){
            return true;
        } else if(chessBoard_CC[bkp_y][bkp_x + i] >= 1 && chessBoard_CC[bkp_y][bkp_x + i] != white_rook && chessBoard_CC[bkp_y][bkp_x + i] != white_queen){
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
    } else if(chessBoard_CC[bkp_y + 1][bkp_x + 1] == white_pawn && bkp_y + 1 >= 0 && bkp_x + 1 <= 7){ // pawn checks ~
        return true;
    } else if(chessBoard_CC[bkp_y + 1][bkp_x - 1] == white_pawn && bkp_y + 1 <= 7 && bkp_x - 1 >= 0){
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
void insertMove_white(int se){
    if(se == 1){
        playMove_CC();
        if(check_white()){
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
        playMove_CC();
        if(check_white()){
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
void insertMove_black(int se){
    if(se == 1){
        playMove_CC();
        if(check_black()){
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
        playMove_CC();
        if(check_black()){
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

// (castling through check & en passant)
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
    memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
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

int material(){
    int material_eval = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(chessBoard[i][j] <= 6 && chessBoard[i][j] != 0){
                material_eval += value(chessBoard[i][j]);
            } else if(chessBoard[i][j] >= 11){
                material_eval -= value(chessBoard[i][j]);
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

    memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
    return 0;
}

void generateMoves_white(int se){
    if(se == 1){
        n = 0;
        memset(moveList, 0, sizeof(moveList));
    } else{
        o = 0;
        memset(eml, 0, sizeof(eml));
    }
    for(int i = 0; i < 8; i++){
        y = i;
        for(int j = 0; j < 8; j++){
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
void generateMoves_black(int se){
    if(se == 1){
        n = 0;
        memset(moveList, 0, sizeof(moveList));
    } else{
        o = 0;
        memset(eml, 0, sizeof(eml));
    }
    for(int i = 0; i < 8; i++){
        y = i;
        for(int j = 0; j < 8; j++){
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

// add checks to enemy moves eval
int staticEval_wtm(){
    int eval = 0;
    generateMoves_white(2);
    if(o == 0){
        if(check_white()){
            return negativeInfinity;
        } else{
            return 0;
        }
    }
    int responses[o] = {0};
    for(int i = 0; i < o; i++){
        if(value(chessBoard[eml[2][i]][eml[3][i]]) >= value(chessBoard[eml[0][i]][eml[1][i]])){
            responses[i] = value(chessBoard[eml[2][i]][eml[3][i]]) - value(chessBoard[eml[0][i]][eml[1][i]]);
        }
    }
    eval = material() + o + getMax(responses);
    return eval;
}
int staticEval_btm(){
    int eval = 0;
    generateMoves_black(2);
    if(o == 0){
        if(check_black()){
            return infinity;
        } else{
            return 0;
        }
    }
    int responses[o] = {0};
    for(int i = 0; i < o; i++){
        if(value(chessBoard[eml[2][i]][eml[3][i]]) > value(chessBoard[eml[0][i]][eml[1][i]])){
            responses[i] = value(chessBoard[eml[2][i]][eml[3][i]]) - value(chessBoard[eml[0][i]][eml[1][i]]);
        }
    }
    eval = material() - getMax(responses);
    return eval;
}

// white wants max & black wants min
int moveorder_exclusion_strength = 4;
void move_filter_max(){
    int moveHolder[4][moveorder_exclusion_strength];
    int boardState[8][8];
    int moveScores[n];
    memcpy(boardState, chessBoard, sizeof(chessBoard));
    for(int i = 0; i < n; i++){
        move_y = moveList[0][i];
        move_x = moveList[1][i];
        moveTo_y = moveList[2][i];
        moveTo_x = moveList[3][i];
        if(move_y == 0 && move_x == 0 && moveTo_y == 0 && moveTo_x == 0){
            break;
        }
        playMove();
        moveScores[i] = staticEval_btm();
        memcpy(chessBoard, boardState, sizeof(chessBoard));
    }
    for(int i = 0; i < moveorder_exclusion_strength; i++){
        getMax(moveScores);
        moveHolder[0][i] = moveList[0][best_index];
        moveHolder[1][i] = moveList[1][best_index];
        moveHolder[2][i] = moveList[2][best_index];
        moveHolder[3][i] = moveList[3][best_index];
        moveScores[best_index] = negativeInfinity;
    }
    memset(moveList, 0, sizeof(moveList));
    for(int i = 0; i < moveorder_exclusion_strength; i++){
        moveList[0][i] = moveHolder[0][i];
        moveList[1][i] = moveHolder[1][i];
        moveList[2][i] = moveHolder[2][i];
        moveList[3][i] = moveHolder[3][i];
    }
    n = moveorder_exclusion_strength;
}
void move_filter_min(){
    int moveHolder[4][moveorder_exclusion_strength];
    int boardState[8][8];
    int moveScores[n];
    memcpy(boardState, chessBoard, sizeof(chessBoard));
    for(int i = 0; i < n; i++){
        move_y = moveList[0][i];
        move_x = moveList[1][i];
        moveTo_y = moveList[2][i];
        moveTo_x = moveList[3][i];
        if(move_y == 0 && move_x == 0 && moveTo_y == 0 && moveTo_x == 0){
            break;
        }
        playMove();
        moveScores[i] = staticEval_wtm();
        memcpy(chessBoard, boardState, sizeof(chessBoard));
    }
    for(int i = 0; i < moveorder_exclusion_strength; i++){
        getMin(moveScores);
        moveHolder[0][i] = moveList[0][best_index];
        moveHolder[1][i] = moveList[1][best_index];
        moveHolder[2][i] = moveList[2][best_index];
        moveHolder[3][i] = moveList[3][best_index];
        moveScores[best_index] = infinity;
    }
    memset(moveList, 0, sizeof(moveList));
    for(int i = 0; i < moveorder_exclusion_strength; i++){
        moveList[0][i] = moveHolder[0][i];
        moveList[1][i] = moveHolder[1][i];
        moveList[2][i] = moveHolder[2][i];
        moveList[3][i] = moveHolder[3][i];
    }
    n = moveorder_exclusion_strength;
}

// search (removes castling rights)
int search(int depth, int max_depth){
    if(depth % 2 == 0){
        generateMoves_white(1);
        if(depth == max_depth){
        } else{
            //move_filter_max();
        }
    } else{
        generateMoves_black(1);
        if(depth == max_depth){
        } else{
            //move_filter_min();
        }
    }
    memcpy(boardStates[depth], chessBoard, sizeof(chessBoard));
    for(int ms = 0; ms < n; ms++){
        move_y = moveList[0][depthProgress[depth]];
        move_x = moveList[1][depthProgress[depth]];
        moveTo_y = moveList[2][depthProgress[depth]];
        moveTo_x = moveList[3][depthProgress[depth]];
        if(move_y == 0 && move_x == 0 && moveTo_y == 0 && moveTo_x == 0){
            break;
        }
        playMove();
        if(depth == max_depth){
            avg_taker[max_depth - depth] = staticEval_btm();
            //cout << avg_taker[max_depth - depth] << " ";
            //cout << "- (" << move_y << " " << move_x << " " << moveTo_y << " " << moveTo_x << "), ";
        }
        depthProgress[depth]++;
        if(depth > 1){
            search(depth - 1, max_depth);
            return 0;
        }
        staticEval_wtm();
        memcpy(chessBoard, boardStates[depth], sizeof(chessBoard));
        TEST+=o;
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
    generateMoves_white(1);
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
    generateMoves_black(1);
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

        generateMoves_black(1);
        if(n == 0 && check_black() == true){
            printBoard();
            cout << staticEval_btm() << endl;
            cout << "Checkmate - white wins" << endl;
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

        generateMoves_white(1);
        if(n == 0 && check_white() == true){
            printBoard();
            cout << staticEval_wtm() << endl;
            cout << "Checkmate - black wins" << endl;
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