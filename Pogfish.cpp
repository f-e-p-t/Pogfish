#include<iostream>
#include<cmath>
#include<string.h>
#include<unordered_map>
#include<random>
#include"movegen.cpp"
#include"heatmaps.cpp"
#include"moveordering.cpp"
using namespace std;

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

int64_t pieceCount(){
    int64_t pieceCount = 0;
    for(int64_t i = 0; i < 8; i++){ for(int64_t j = 0; j < 8; j++){
        if(chessBoard[i][j] != empty_square){ pieceCount++;}}
    }
    return pieceCount;
}

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
    bool alphaIncreased = false; 
    // For move in moveList
    for(int i = 0; i < 219; i++){
        assign(i);
        if(move_y == 0 && move_x == 0 && moveTo_y == 0 && moveTo_x == 0){ break;}
        playMove(0);
        int64_t boardHash = Hash(chessBoard, (depth + 1) % 2);
        if(i > 4 && !alphaIncreased && depth > 2){ // Late Move Reduction
            eval = -search(depth - 3, cap, -beta, -alpha);
        } else if(TTable[boardHash].depthEvaluated > 0 && TTable[boardHash].depthEvaluated >= depth){
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
            alphaIncreased = true;
            if(eval > alpha){
                bestMove[0] = moveList[0][i], bestMove[1] = moveList[1][i], bestMove[2] = moveList[2][i], bestMove[3] = moveList[3][i];
            }
        }
        if(eval >= beta){ return beta;}
        if(eval > alpha){ alpha = duoMax(eval, alpha);}
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