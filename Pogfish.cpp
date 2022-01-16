#include<iostream>
#include<string.h>
#include<unordered_map>
#include<random>
#include<algorithm>
#include"movegen.cpp"
#include"heatmaps.cpp"
#include"arithmetic.cpp"
using namespace std;

string FEN = "8/2p3N1/6p1/5PB1/pp2Rn2/7k/P1p2K1P/3r4";
int64_t zobrist_keys[12][8][8] = {0};
int64_t side_key = 0;
struct TranspositionData{
    int64_t evaluation;
    int64_t depthEvaluated;
    int64_t best_move[4] = {0};
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
        int64_t endgamePiecePlacement(){
            int64_t placement = 0;
            for(int64_t i = 0; i <= 7; i++){ for(int64_t j = 0; j <= 7; j++){
                if(chessBoard[i][j] == white_king){ placement += endgameKingHeatmap_white[i][j];
                } else if(chessBoard[i][j] == black_king){ placement += endgameKingHeatmap_black[i][j];
                } else if(chessBoard[i][j] == white_pawn){ placement += endgamePawnHeatmap_white[i][j];
                } else if(chessBoard[i][j] == black_pawn){ placement += endgamePawnHeatmap_black[i][j];}
            }}
            return placement;
        }
};
Evaluation evaluation;

void order(int64_t boardHash){
    int64_t move_weights[n] = {0};

    for(int i = 0; i < n; i++){ if(value(chessBoard[moveList[i][2]][moveList[i][3]]) >= 100 && moveList[i][4] == 0){
        moveList[i][4] = value(chessBoard[moveList[i][2]][moveList[i][3]]) - value(chessBoard[moveList[i][0]][moveList[i][1]])/10;}
    }

    for(int i = 0; i < n; i++){ move_weights[i] = moveList[i][4];}
    sort(move_weights, move_weights + n, greater<int64_t>());

    for(int i = 0; i < n; i++){ for(int j = 0; j < n; j++){ 
        if(moveList[j][4] == move_weights[i]){ swap(moveList[i], moveList[j]); break;}
    }}
}

void assign(int64_t index){ move_y = moveList[index][0]; move_x = moveList[index][1]; moveTo_y = moveList[index][2]; moveTo_x = moveList[index][3];}

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
            if(value(chessBoard[eml[i][2]][eml[i][3]]) > value(chessBoard[eml[i][0]][eml[i][1]])){
                responses[i] = value(chessBoard[eml[i][2]][eml[i][3]]) - value(chessBoard[eml[i][0]][eml[i][1]]);
            }
        }
        eval += evaluation.material() + getMax(responses, o);
        if(opening){
            eval += evaluation.development();
        }
        if(endgame){
            eval += evaluation.endgamePiecePlacement();
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
            if(value(chessBoard[eml[i][2]][eml[i][3]]) > value(chessBoard[eml[i][0]][eml[i][1]])){
                responses[i] = value(chessBoard[eml[i][2]][eml[i][3]]) - value(chessBoard[eml[i][0]][eml[i][1]]);
            }
        }
        eval += evaluation.material() - getMax(responses, o);
        if(opening){
            eval += evaluation.development();
        }
        if(endgame){
            eval += evaluation.endgamePiecePlacement();
        }
        return eval;    
    }
}


int search(int64_t depth, int64_t alpha, int64_t beta){
    if(depth == 0){
        int64_t eval = staticEval(1, 0);
        TEST++;
        return eval;
    }
    int64_t boardHash = Hash(chessBoard, (depth + 1) % 2);
    generateMoves((depth + 1) % 2, 1);
    order(boardHash);
    if(n == 0){
        if(check((depth + 1) % 2)){ 
            return -(1000000 + depth);
        }
        return 0;
    }
    memcpy(boardStates[depth], chessBoard, sizeof(chessBoard));
    int64_t eval;
    int64_t bestMove[4] = {0};;
    if(TTable[boardHash].depthEvaluated >= depth){ return TTable[boardHash].evaluation;}
    // For move in moveList
    for(int i = 0; i < 219; i++){
        assign(i);
        if(move_y == 0 && move_x == 0 && moveTo_y == 0 && moveTo_x == 0){ break;}
        playMove(0);
        eval = -search(depth - 1, -beta, -alpha);
        memcpy(chessBoard, boardStates[depth], sizeof(chessBoard));
        memcpy(chessBoard_CC, chessBoard, sizeof(chessBoard));
        generateMoves((depth + 1) % 2, 1);
        order(boardHash);
        if(eval > alpha){
            bestMove[0] = moveList[i][0]; bestMove[1] = moveList[i][1]; bestMove[2] = moveList[i][2]; bestMove[3] = moveList[i][3];
        }
        alpha = duoMax(eval, alpha);
        if(eval >= beta){
            TTable[boardHash].evaluation = alpha; TTable[boardHash].depthEvaluated = depth;
            for(int j = 0; j < 4; j++){ TTable[boardHash].best_move[j] = bestMove[j];}
            return beta;
        }
    }
    TTable[boardHash].evaluation = alpha; TTable[boardHash].depthEvaluated = depth;
    for(int j = 0; j < 4; j++){ TTable[boardHash].best_move[j] = bestMove[j];}
    return alpha;
}


int64_t getMove_white(){
    generateMoves(1, 1);
    isLegalMove = false;
    cout << "White's move ---> "; cin >> move_y; cin >> move_x; cin >> moveTo_y; cin >> moveTo_x;
    for(int64_t i = 0; i < n; i++){
        if(move_y == moveList[i][0] && move_x == moveList[i][1] && moveTo_y == moveList[i][2] && moveTo_x == moveList[i][3]){ playMove(1); isLegalMove = true; return 0;}      
    }
    cout << "Illegal Move!" << endl;
    return 0;
}
int64_t getMove_black(){
    generateMoves(0, 1);
    isLegalMove = false;
    cout << "Black's move ---> "; cin >> move_y; cin >> move_x; cin >> moveTo_y; cin >> moveTo_x;
    for(int64_t i = 0; i < n; i++){
        if(move_y == moveList[i][0] && move_x == moveList[i][1] && moveTo_y == moveList[i][2] && moveTo_x == moveList[i][3]){ playMove(1); isLegalMove = true; return 0;}      
    }
    cout << "Illegal Move!" << endl;
    return 0;
}
class Engine{
    public:
        void move_white(int64_t _depth){
            int64_t boardHash = Hash(chessBoard, 1);
            int64_t sdepth = _depth;
            cout << "Evaluated at " << search(sdepth, -1000000000000, 1000000000000) << " with ";
            cout << TEST << " positions searched. Played - " << TTable[boardHash].best_move[0] << " " << TTable[boardHash].best_move[1] << " ";
            cout << TTable[boardHash].best_move[2] << " " << TTable[boardHash].best_move[3] << " " << endl;
            move_y = TTable[boardHash].best_move[0];
            move_x = TTable[boardHash].best_move[1];
            moveTo_y = TTable[boardHash].best_move[2];
            moveTo_x = TTable[boardHash].best_move[3];
            playMove(1);
            TEST = 0;
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

    //generateMoves(1, 1);
    //order(Hash(chessBoard, 1));
    //for(int i = 0; i < 60; i++){
    //    for(int j = 0; j < 5; j++){
    //        cout << moveList[i][j] << " ";
    //    } cout << endl;
    //}

    while(move_move <= 5949){
        if(move_move == 15){ opening = false; middlegame = true;}
        if(pieceCount() < 15){ opening = false; middlegame = false; endgame = true;}
        cout << "Move - " << move_move << endl;
        engine.move_white(6);
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

        generateMoves(1, 1);
        if(n == 0 && check(1) == true){ printBoard(); cout << "Checkmate - black wins" << endl; break;
        } else if(n == 0 && check(1) == false){ printBoard(); cout << "Stalemate - draw" << endl; break;
        }

        printBoard();
        move_move++;
    }
}