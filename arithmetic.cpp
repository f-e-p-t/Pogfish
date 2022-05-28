#include<iostream>
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

int64_t pieceCount(){
    int64_t pieceCount = 0;
    for(int64_t i = 0; i < 8; i++){ for(int64_t j = 0; j < 8; j++){
        if(board.chessBoard[i][j] != empty_square){ pieceCount++;}}
    }
    return pieceCount;
}

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