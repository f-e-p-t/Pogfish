#include<iostream>
#include<string.h>
#include<unordered_map>
#include<random>
#include<algorithm>
#include"movegen.cpp"
#include"heatmaps.cpp"
#include"arithmetic.cpp"
using namespace std;

string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
int64_t zobrist_keys[12][8][8] = {0};
int64_t side_key = 0;
struct TranspositionData{
    int64_t evaluation;
    int64_t depthEvaluated;
    int64_t best_move[5] = {0};
};
std::unordered_map<int64_t, TranspositionData> TTable;
int64_t Hash(int64_t position[8][8], bool side){
    int64_t hash = 0;
    for(int i = 0; i < 8; i++){ for(int j = 0; j < 8; j++){
        if(board.chessBoard[i][j] != empty_square){
            hash ^= zobrist_keys[i][j][pieceIndex(board.chessBoard[i][j])];
        }}
    }
    if(side == 1){ hash ^= side_key;}
    return hash;
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
        } else if(FEN[fenpos] == 'p'){ board.chessBoard[pos/8][pos % 8] = black_pawn; pos++;
        } else if(FEN[fenpos] == 'n'){ board.chessBoard[pos/8][pos % 8] = black_knight; pos++;
        } else if(FEN[fenpos] == 'b'){ board.chessBoard[pos/8][pos % 8] = black_bishop; pos++;
        } else if(FEN[fenpos] == 'r'){ board.chessBoard[pos/8][pos % 8] = black_rook; pos++;
        } else if(FEN[fenpos] == 'q'){ board.chessBoard[pos/8][pos % 8] = black_queen; pos++;
        } else if(FEN[fenpos] == 'k'){ board.chessBoard[pos/8][pos % 8] = black_king; pos++;
        } else if(FEN[fenpos] == 'P'){ board.chessBoard[pos/8][pos % 8] = white_pawn; pos++;
        } else if(FEN[fenpos] == 'N'){ board.chessBoard[pos/8][pos % 8] = white_knight; pos++;
        } else if(FEN[fenpos] == 'B'){ board.chessBoard[pos/8][pos % 8] = white_bishop; pos++;
        } else if(FEN[fenpos] == 'R'){ board.chessBoard[pos/8][pos % 8] = white_rook; pos++;
        } else if(FEN[fenpos] == 'Q'){ board.chessBoard[pos/8][pos % 8] = white_queen; pos++;
        } else if(FEN[fenpos] == 'K'){ board.chessBoard[pos/8][pos % 8] = white_king; pos++;
        }
        fenpos++;
    }
    memcpy(board.CC, board.chessBoard, sizeof(board.chessBoard));
}
void printBoard(){
    cout << "-----------------------------------------" << endl;
    for(int64_t y_pos = 0; y_pos < 8; y_pos++){
        cout << "|";
        for(int64_t x_pos = 0; x_pos < 8; x_pos++){
            if(board.chessBoard[y_pos][x_pos] == white_pawn){ cout << "  P |";
            } else if(board.chessBoard[y_pos][x_pos] == white_knight){ cout << "  N |";
            } else if(board.chessBoard[y_pos][x_pos] == white_bishop){ cout << "  B |";
            } else if(board.chessBoard[y_pos][x_pos] == white_rook){ cout << "  R |";
            } else if(board.chessBoard[y_pos][x_pos] == white_queen){ cout << "  Q |";
            } else if(board.chessBoard[y_pos][x_pos] == white_king){ cout << "  K |";
            } else if(board.chessBoard[y_pos][x_pos] == black_pawn){ cout << "  p |";
            } else if(board.chessBoard[y_pos][x_pos] == black_knight){ cout << "  n |";
            } else if(board.chessBoard[y_pos][x_pos] == black_bishop){ cout << "  b |";
            } else if(board.chessBoard[y_pos][x_pos] == black_rook){ cout << "  r |";
            } else if(board.chessBoard[y_pos][x_pos] == black_queen){ cout << "  q |";
            } else if(board.chessBoard[y_pos][x_pos] == black_king){ cout << "  k |";
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
                    if(board.chessBoard[i][j] <= 6 && board.chessBoard[i][j] != 0){
                        material_eval += value(board.chessBoard[i][j]);
                    } else if(board.chessBoard[i][j] >= 11){
                        material_eval -= value(board.chessBoard[i][j]);
                    }
                }
            }
            return material_eval;
        }
        int64_t development(){
            int64_t development = 0;
            for(int i = 0; i < 8; i++){ for(int j = 0; j < 8; j++){
                if(board.chessBoard[i][j] == white_knight){ development += openingKnightHeatmap_white[i][j];
                } else if(board.chessBoard[i][j] == black_knight){ development += openingKnightHeatmap_black[i][j];
                } else if(board.chessBoard[i][j] == white_bishop){ development += openingBishopHeatmap_white[i][j];
                } else if(board.chessBoard[i][j] == black_bishop){ development += openingBishopHeatmap_black[i][j];
                } else if(board.chessBoard[i][i] == white_rook){ development += openingRookHeatmap_white[i][j];
                } else if(board.chessBoard[i][j] == black_rook){ development += openingRookHeatmap_black[i][j];}
            }}
            return development;
        }
        int64_t endgamePiecePlacement(){
            int64_t placement = 0;
            for(int64_t i = 0; i <= 7; i++){ for(int64_t j = 0; j <= 7; j++){
                if(board.chessBoard[i][j] == white_king){ placement += endgameKingHeatmap_white[i][j];
                } else if(board.chessBoard[i][j] == black_king){ placement += endgameKingHeatmap_black[i][j];
                } else if(board.chessBoard[i][j] == white_pawn){ placement += endgamePawnHeatmap_white[i][j];
                } else if(board.chessBoard[i][j] == black_pawn){ placement += endgamePawnHeatmap_black[i][j];}
            }}
            return placement;
        }
};
Evaluation evaluation;

List order(List moves, int64_t boardHash){
    int64_t move_weights[moves.count] = {0};
    if(TTable[boardHash].depthEvaluated > 0){ for(int i = 0; i < moves.count; i++){
        if(equal(begin(moves.list[i]), end(moves.list[i]), begin(TTable[boardHash].best_move))){ moves.list[i][4] += 1000;}
    }}

    for(int i = 0; i < moves.count; i++){ if(value(board.chessBoard[moves.list[i][2]][moves.list[i][3]]) >= 100){
        moves.list[i][4] += value(board.chessBoard[moves.list[i][2]][moves.list[i][3]]) - value(board.chessBoard[moves.list[i][0]][moves.list[i][1]])/10;}
    }

    for(int i = 0; i < moves.count; i++){ move_weights[i] = moves.list[i][4];}
    sort(move_weights, move_weights + moves.count, greater<int64_t>());

    for(int i = 0; i < moves.count; i++){ for(int j = 0; j < moves.count; j++){ 
        if(moves.list[j][4] == move_weights[i]){ swap(moves.list[i], moves.list[j]); break;}
    }}
    return moves;
}

int64_t staticEval(int64_t dtm){
    int64_t eval = 0;
    List moves = generateMoves(board.side);
    if(moves.count == 0){
        if(check(board.side)){
            return (-1000000 - dtm);
        } else{
            return 0;
        }
    }
    int64_t bestResponse = 0;
    int64_t captureValue = 0;
    int64_t recapturePenalty = 0;
    for(int64_t i = 0; i < moves.count; i++){
        captureValue = value(board.chessBoard[moves.list[i][2]][moves.list[i][3]]);
        recapturePenalty = value(board.chessBoard[moves.list[i][0]][moves.list[i][1]]);
        if(captureValue > recapturePenalty){
            if(captureValue - recapturePenalty > bestResponse){ bestResponse = captureValue - recapturePenalty;}
        }
    }
    eval += evaluation.material();
    if(board.side){ eval += bestResponse;}
    else{ eval -= bestResponse;}
    if(opening){
        eval += evaluation.development();
    }
    if(endgame){
        eval += evaluation.endgamePiecePlacement();
    }
    return eval;
}


int64_t search(int64_t depth, int64_t cap, int64_t alpha, int64_t beta){
    if(depth == 0){
        int64_t eval = 0;
        if(board.side){ eval = staticEval(0);}
        else{ eval = -staticEval(0);}
        TEST++;
        return eval;
    }
    int64_t boardHash = Hash(board.chessBoard, board.side);
    List moves = generateMoves(board.side);
    moves = order(moves, boardHash);
    if(moves.count == 0){
        if(check(board.side)){
            return -(1000000 + depth);
        }
        return 0;
    }
    int64_t boardState[8][8] = {0}; memcpy(boardState, board.chessBoard, sizeof(board.chessBoard));
    int64_t eval = 0; int64_t alphaIncreased = 0; int64_t bestMove[4] = {0};
    if(TTable[boardHash].depthEvaluated > depth){ return TTable[boardHash].evaluation;}
    for(int i = 0; i < moves.count; i++){
        board.playMove(0, moves.list[i]);
        if(alphaIncreased > 5 && depth > 2){ // LMR
            eval = -search(depth - 2, cap, -beta, -alpha);
        } else{
            eval = -search(depth - 1, cap, -beta, -alpha);
        }
        board.unplayMove(boardState);
        if(eval > alpha){
            alphaIncreased = 0;
            bestMove[0] = moves.list[i][0]; bestMove[1] = moves.list[i][1]; bestMove[2] = moves.list[i][2]; bestMove[3] = moves.list[i][3];
        } else{ alphaIncreased++;}
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


int64_t getMove(){
    int64_t _move[4];
    List moves = generateMoves(board.side);
    isLegalMove = false;
    if(board.side){ cout << "White's ";}
    else{ cout << "Black's ";}
    cout << "move ---> "; cin >> _move[0]; cin >> _move[1]; cin >> _move[2]; cin >> _move[3];
    for(int64_t i = 0; i < moves.count; i++){
        if(_move[0] == moves.list[i][0] && _move[1] == moves.list[i][1] && _move[2] == moves.list[i][2] && _move[3] == moves.list[i][3]){ board.playMove(1, _move); isLegalMove = true; return 0;}      
    }
    cout << "Illegal Move!" << endl;
    return 0;
}
class Engine{
    public:
        int64_t _alpha = 0;
        int64_t _beta = 0;
        int64_t prevResult = 0;
        const int64_t windowWidth = 50;
        void move(int64_t _depth){
            int64_t boardHash = Hash(board.chessBoard, board.side);
            _alpha = prevResult - windowWidth;
            _beta = prevResult + windowWidth;
            cout << "Iterations finished. Evaluated at ";
            int64_t eval = search(_depth, _depth, _alpha, _beta);
            if(eval <= _alpha || eval >= _beta){
                cout << "(research required) ";
                eval = search(_depth, _depth, -1000000000000, 1000000000000);
            }
            cout << eval << " with ";
            cout << TEST << " positions searched. Played - " << TTable[boardHash].best_move[0] << " " << TTable[boardHash].best_move[1] << " ";
            cout << TTable[boardHash].best_move[2] << " " << TTable[boardHash].best_move[3] << " " << endl;
            int64_t _move[4];
            _move[0] = TTable[boardHash].best_move[0]; _move[1] = TTable[boardHash].best_move[1];
            _move[2] = TTable[boardHash].best_move[2]; _move[3] = TTable[boardHash].best_move[3];
            board.playMove(1, _move);
            TEST = 0;
            TTable.clear();
        }
        void iterate(int64_t _depth){
            int64_t sdepth = _depth;
            _alpha = prevResult - windowWidth;
            _beta = prevResult + windowWidth;
            if(_depth == 1){
                prevResult = search(_depth, _depth, -1000000000000, 1000000000000);
            } else{
                prevResult = search(_depth, _depth, _alpha, _beta);
                if(prevResult <= _alpha || prevResult >= _beta){
                    prevResult = search(_depth, _depth, -1000000000000, 1000000000000);
                }
            }
            TEST = 0;
        }
};
Engine engine;

int main(void){

    board.side = 1;
    List gameEnd;

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

    //List dsuga = generateMoves(board.side);
    //dsuga = order(dsuga, Hash(board.chessBoard, board.side));
    //cout << dsuga.count << endl;
    //for(int i = 0; i < 60; i++){
    //    for(int j = 0; j < 5; j++){
    //        cout << dsuga.list[i][j] << " ";
    //    } cout << endl;
    //}

    while(move_move <= 5949){
        if(move_move == 15){ opening = false; middlegame = true;}
        if(pieceCount() < 15){ opening = false; middlegame = false; endgame = true;}
        cout << "Move - " << move_move << endl;
        //do{
        //    getMove();
        //} while(!isLegalMove);
        for(int i = 1; i < 8; i++){ engine.iterate(i);}
        engine.move(8);
        TTable.clear(); engine.prevResult = 0;

        gameEnd = generateMoves(0);
        if(gameEnd.count == 0 && check(0) == true){ printBoard(); cout << "Checkmate - white wins" << endl; break;
        } else if(gameEnd.count == 0 && check(0) == false){ printBoard(); cout << "Stalemate - draw" << endl; break;
        }

        printBoard();

        do{
            getMove();
        } while(!isLegalMove);
        //for(int i = 1; i < 8; i++){ engine.iterate(i);}
        //engine.move(8);
        TTable.clear(); engine.prevResult = 0;

        gameEnd = generateMoves(1);
        if(gameEnd.count == 0 && check(1) == true){ printBoard(); cout << "Checkmate - black wins" << endl; break;
        } else if(gameEnd.count == 0 && check(1) == false){ printBoard(); cout << "Stalemate - draw" << endl; break;
        }

        printBoard();
        move_move++;
    }
}