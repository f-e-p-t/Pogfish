#include<iostream>
using namespace std;

int64_t value(int64_t piece){
    int64_t pieceValue = 0;
    switch(piece){
        case 1: pieceValue = 100; break;
        case 2: pieceValue = 300; break;
        case 3: pieceValue = 300; break;
        case 4: pieceValue = 500; break;
        case 5: pieceValue = 900; break;
        case 6: pieceValue = 0; break;
        case 11: pieceValue = 100; break;
        case 12: pieceValue = 300; break;
        case 13: pieceValue = 300; break;
        case 14: pieceValue = 500; break;
        case 15: pieceValue = 900; break;
        case 16: pieceValue = 0; break;
        default: pieceValue = 0;
    }
    return pieceValue;
}

void order(){
    int64_t pieceValue = 0;
    for(int i = 0; i < n; i++){ pieceValue = value(chessBoard[moveList[2][i]][moveList[3][i]]); if(pieceValue >= 100){
        for(int j = 0; j < i; j++){ if(pieceValue > value(chessBoard[moveList[2][j]][moveList[3][j]])){
        swap(moveList[0][j], moveList[0][i]), swap(moveList[1][j], moveList[1][i]);
        swap(moveList[2][j], moveList[2][i]), swap(moveList[3][j], moveList[3][i]);
        }}
    }}
}