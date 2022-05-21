#include<iostream>
#include<string.h>
#include<unordered_map>
#include<random>
#include<algorithm>
#include"movegen.cpp"
#include"heatmaps.cpp"
#include"arithmetic.cpp"
#include"quiescence.cpp"
using namespace std;

const string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

int64_t zobrist_keys[12][8][8] = {0};
int64_t side_key = 0;
struct TranspositionData{
    int64_t evaluation = 0;
    int64_t depthEvaluated = 0;
    int64_t best_move[5] = {0};
    bool isCutNode = false;
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

// maybe
struct KillerData{
    bool hasKiller = 0;
    int64_t killer_move[5] = {0};
};
std::unordered_map<int64_t, KillerData> KTable;

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

// ----------------------------------------------------------------------- Search & Evaluation -----------------------------------------------------------------------

class Evaluation{
    public:
        int64_t material(){
            int64_t material_eval = 0;
            for(int64_t i = 0; i < 8; i++){ for(int64_t j = 0; j < 8; j++){
                    if(board.chessBoard[i][j] <= 6 && board.chessBoard[i][j] != 0){
                        material_eval += value(board.chessBoard[i][j]);
                    } else if(board.chessBoard[i][j] >= 11){
                        material_eval -= value(board.chessBoard[i][j]);
                    }
                }}
            return material_eval;
        }
        int64_t absoluteMaterial(){
            int64_t material = 0;
            for(int64_t i = 0; i < 8; i++){ for(int64_t j = 0; j < 8; j++){
                material += value(board.chessBoard[i][j]);
            }}
            return material;
        }
        int64_t development(){
            int64_t development = 0;
            for(int i = 0; i < 8; i++){ for(int j = 0; j < 8; j++){
                if(board.chessBoard[i][j] == white_pawn){ development += openingPawnHeatmap_white[i][j];
                } else if(board.chessBoard[i][j] == black_pawn){ development += openingPawnHeatmap_black[i][j];
                } else if(board.chessBoard[i][j] == white_knight){ development += openingKnightHeatmap_white[i][j];
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

void order(int64_t list[219][5], int64_t _count, int64_t boardHash){
    int64_t move_weights[219] = {0};

    if(TTable[boardHash].depthEvaluated > 0){ for(int i = 0; i < _count; i++){
        if(equal(begin(list[i]), end(list[i]), begin(TTable[boardHash].best_move))){ list[i][4] += 1100;}
    }}

    for(int i = 0; i < _count; i++){ if(board.chessBoard[list[i][2]][list[i][3]] != empty_square){
        list[i][4] += value(board.chessBoard[list[i][2]][list[i][3]]) - value(board.chessBoard[list[i][0]][list[i][1]])/10;}
    }

    for(int i = 0; i < _count; i++){ move_weights[i] = list[i][4];}
    sort(move_weights, move_weights + _count, greater<int64_t>());

    for(int i = 0; i < _count; i++){ for(int j = 0; j < _count; j++){ 
        if(list[j][4] == move_weights[i]){ swap(list[i], list[j]); break;}
    }}
}

int64_t quiescence(int64_t alpha, int64_t beta){
    int64_t stabiliser = 0; int64_t eval = 0;
    if(board.side){ stabiliser = evaluation.material();}
    else{ stabiliser = -evaluation.material();}
    if(stabiliser >= beta){ return beta;}
    if(stabiliser > alpha){ alpha = stabiliser;}
    List moves = generateCaptures(board.side);
    order(moves.list, moves.count, 0);
    int64_t boardState[8][8] = {0};
    memcpy(boardState, board.chessBoard, sizeof(board.chessBoard));
    for(int i = 0; i < moves.count; i++){
        board.playMove(0, moves.list[i]);
        eval = -quiescence(-beta, -alpha);
        board.unplayMove(boardState);
        if(eval > alpha){ alpha = eval;}
        if(eval >= beta){ return beta;}
    }
    return alpha;
}

int64_t staticEval(){
    int64_t eval = 0;
    if(board.side){ eval += quiescence(-1000000000000, 1000000000000);}
    else{ eval -= quiescence(-1000000000000, 1000000000000);}
    if(board.opening){
        eval += evaluation.development();
    }
    if(board.endgame){
        eval += evaluation.endgamePiecePlacement();
    }
    return eval;
}


int64_t search(int64_t depth, int64_t alpha, int64_t beta){
    if(depth == 0){
        int64_t eval = 0;
        if(board.side){ eval = staticEval();}
        else{ eval = -staticEval();}
        return eval;
    }
    int64_t boardHash = Hash(board.chessBoard, board.side);
    List moves = generateMoves(board.side);
    order(moves.list, moves.count, boardHash);
    if(moves.count == 0){
        if(check(board.side)){
            return -(1000000 + depth);
        }
        return 0;
    }
    int64_t boardState[8][8] = {0}; memcpy(boardState, board.chessBoard, sizeof(board.chessBoard));
    int64_t eval = 0; int64_t alphaIncreased = 0; int64_t bestMove[4] = {0};
    if(TTable[boardHash].depthEvaluated > depth /* && !TTable[boardHash].isCutNode*/){ return TTable[boardHash].evaluation;}
    for(int i = 0; i < moves.count; i++){
        board.playMove(0, moves.list[i]);
        if(alphaIncreased > 5 && depth > 2){ // LMR
            eval = -search(depth - 2, -beta, -alpha);
        } else{
            eval = -search(depth - 1, -beta, -alpha);
        }
        board.unplayMove(boardState);
        if(eval > alpha){
            alpha = eval;
            alphaIncreased = 0;
            bestMove[0] = moves.list[i][0]; bestMove[1] = moves.list[i][1]; bestMove[2] = moves.list[i][2]; bestMove[3] = moves.list[i][3];
        } else{ alphaIncreased++;}
        if(eval >= beta){
            TTable[boardHash].evaluation = alpha; TTable[boardHash].depthEvaluated = depth; TTable[boardHash].isCutNode = true;
            memcpy(TTable[boardHash].best_move, bestMove, sizeof(bestMove));
            return beta;
        }
    }
    TTable[boardHash].evaluation = alpha; TTable[boardHash].depthEvaluated = depth;
    memcpy(TTable[boardHash].best_move, bestMove, sizeof(bestMove));
    return alpha;
}


bool getMove(){
    int64_t _move[4];
    List moves = generateMoves(board.side);
    if(board.side){ cout << "White's ";}
    else{ cout << "Black's ";}
    cout << "move ---> "; cin >> _move[0]; cin >> _move[1]; cin >> _move[2]; cin >> _move[3];
    for(int64_t i = 0; i < moves.count; i++){
        if(_move[0] == moves.list[i][0] && _move[1] == moves.list[i][1] && _move[2] == moves.list[i][2] && _move[3] == moves.list[i][3]){ board.playMove(1, _move); return true;}      
    }
    cout << "Illegal Move!" << endl;
    return false;
}
class Engine{
    public:
        int64_t searchDepth = 8;
        int64_t _alpha = 0; int64_t _beta = 0;
        int64_t prevResult = 0;
        const int64_t windowWidth = 25;
        void move(int64_t _depth){
            int64_t boardHash = Hash(board.chessBoard, board.side);
            _alpha = prevResult - windowWidth;
            _beta = prevResult + windowWidth;
            cout << "Iterations finished. Evaluated at ";
            int64_t eval = search(_depth, _alpha, _beta);
            if(eval <= _alpha || eval >= _beta){
                cout << "(research required) ";
                _alpha = -1000000000000;
                _beta = 1000000000000;
                eval = search(_depth, _alpha, _beta);
            }
            cout << eval << " with ";
            cout << nodes << " positions searched. Played - " << TTable[boardHash].best_move[0] << " " << TTable[boardHash].best_move[1] << " ";
            cout << TTable[boardHash].best_move[2] << " " << TTable[boardHash].best_move[3] << " " << endl;
            int64_t _move[4];
            _move[0] = TTable[boardHash].best_move[0]; _move[1] = TTable[boardHash].best_move[1];
            _move[2] = TTable[boardHash].best_move[2]; _move[3] = TTable[boardHash].best_move[3];
            board.playMove(1, _move);
            nodes = 0;
            //this->cringe(); board.side = 0;
            TTable.clear();
        }
        void iterate(int64_t _depth){
            _alpha = prevResult - windowWidth;
            _beta = prevResult + windowWidth;
            if(_depth == 1){
                prevResult = search(_depth, -1000000000000, 1000000000000);
            } else{
                prevResult = search(_depth, _alpha, _beta);
                if(prevResult <= _alpha || prevResult >= _beta){
                    _alpha = -1000000000000;
                    _beta = 1000000000000;
                    prevResult = search(_depth, _alpha, _beta);
                }
            }
        nodes = 0;
        }
        void cringe(){
            int64_t boardHash = 0;
            int64_t boardState[8][8] = {0};
            int64_t _move[4] = {0};
            memcpy(boardState, board.chessBoard, sizeof(board.chessBoard));
            for(int i = 0; i < searchDepth; i++){
                boardHash = Hash(board.chessBoard, board.side);
                if(TTable[boardHash].depthEvaluated > 0){
                    cout << "depth - " << TTable[boardHash].depthEvaluated << " played - " << TTable[boardHash].best_move[0] << " ";
                    cout << TTable[boardHash].best_move[1] << " " << TTable[boardHash].best_move[2] << " " << TTable[boardHash].best_move[3] << endl;
                    for(int j = 0; j < 4; j++){ _move[j] = TTable[boardHash].best_move[j];}
                } else{
                    cout << "line ends" << endl;
                }
                board.playMove(0, _move);
            }
            board.unplayMove(boardState);
        }
};
Engine engine;

int main(void){

    board.side = 1;
    List gameEnd;
    bool isLegalMove = 0;

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
    board.printBoard();
    board.opening = 1;
    board.middlegame = 1;
    board.endgame = 0;
    
    for(int64_t move_move = 1; move_move <= 5949; move_move++){
        if(move_move == 23){ board.opening = false; board.middlegame = true;}
        //if(!board.endgame && evaluation.absoluteMaterial() < 3100){ board.opening = false; board.middlegame = false; board.endgame = true; engine.searchDepth += 2;}
        cout << "Move - " << move_move << endl;
        //do{
        //    if(getMove()){
        //        isLegalMove = true;
        //    }
        //} while(!isLegalMove);
        //isLegalMove = false;
        for(int64_t i = 1; i < engine.searchDepth; i++){ engine.iterate(i);}
        engine.move(engine.searchDepth);
        engine.prevResult = 0;

        gameEnd = generateMoves(board.side);
        if(gameEnd.count == 0 && check(board.side) == true){ board.printBoard(); cout << "Checkmate" << endl; break;
        } else if(gameEnd.count == 0 && !check(board.side)){ board.printBoard(); cout << "Stalemate" << endl; break;
        }

        board.printBoard();

        do{
            if(getMove()){
                isLegalMove = true;
            }
        } while(!isLegalMove);
        isLegalMove = false;
        //for(int i = 1; i < engine.searchDepth; i++){ engine.iterate(i);}
        //engine.move(engine.searchDepth);
        engine.prevResult = 0;

        gameEnd = generateMoves(board.side);
        if(gameEnd.count == 0 && check(board.side)){ board.printBoard(); cout << "Checkmate" << endl; break;
        } else if(gameEnd.count == 0 && !check(board.side)){ board.printBoard(); cout << "Stalemate" << endl; break;
        }

        board.printBoard();
    }
}