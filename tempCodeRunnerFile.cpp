int search(int depth, int depth_cap){
    if(depth % 2 == 0){
        generateMoves_white(1);
    } else{
        generateMoves_black(1);
    }
    memcpy(boardStates[depth], chessBoard, sizeof(chessBoard));
    for(int i = 0; i < n; i++){
        move_y = moveList[0][depthProgress[depth]];
        move_x = moveList[1][depthProgress[depth]];
        moveTo_y = moveList[2][depthProgress[depth]];
        moveTo_x = moveList[3][depthProgress[depth]];
        if(move_y == 0 && move_x == 0 && moveTo_y == 0 && moveTo_x == 0){
            break;
        }
        depthProgress[depth]++;
        playMove();
        if(depth % 2 == 0 && depth != 1){
            generateMoves_black(2);
            if(o == 0){
                if(check_black()){
                    moveScores[depth][branchIndex[depth]] = infinity;
                } else{
                    moveScores[depth][branchIndex[depth]] = 0;
                }
                branchIndex[depth]++;
            }
        } else if(depth % 2 == 1 && depth != 1){
            generateMoves_white(2);
            if(o == 0){
                if(check_white()){
                    moveScores[depth][branchIndex[depth]] = -infinity;
                } else{
                    moveScores[depth][branchIndex[depth]] = 0;
                }
                branchIndex[depth]++;
            }
        }
        if(depth > 1 && o != 0){
            search(depth - 1, depth_cap);
            return 0;
        }
        if(depth == 1){
            moveScores[1][i] = staticEval(1);
            TEST+=o;
            // Pruning
            if(branchIndex[depth + 1] != 0){
                if(moveScores[1][i] <= getMax(moveScores[depth + 1], branchIndex[depth + 1])){
                    break;
                }
            }
        }
        memcpy(chessBoard, boardStates[depth], sizeof(chessBoard));
    }
    if(depth < depth_cap){
        depthProgress[depth] = 0;
        if(depth % 2 == 0){
            moveScores[depth + 1][branchIndex[depth + 1]] = getMax(moveScores[depth], n);
        } else{
            moveScores[depth + 1][branchIndex[depth + 1]] = getMin(moveScores[depth], n);
        }
        branchIndex[depth + 1]++;
        branchIndex[depth] = 0;
        depth++;
        memset(moveScores[depth - 1], 0, sizeof(moveScores[depth - 1]));
        memcpy(chessBoard, boardStates[depth], sizeof(chessBoard));
        search(depth, depth_cap);
    }
    return 0;
}