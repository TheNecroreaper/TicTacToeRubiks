#include "RubiksCube.h"
#include <time.h>

RubiksCubeTTT::RubiksCubeTTT(){
    srand(time(0));
    generateFaces();
}

void RubiksCubeTTT::generateFaces(){
    for(int face = 0; face < sizeof(cubeFaces); face++){
        generateFace(face);
    }
}

std::array<std::array<bool, 9>, 3> stalemates = {{
    {false, true, false,
     true, false, true,
     true, false, true},
    {true, true, false,
     true, true, false,
     false, false, true},
    {true, true, false,
     false, true, true,
     true, false, false}
}};

/*
 * Randomly choose a stalemate board and values
 */
void RubiksCubeTTT::generateFace(int face){
    int stalemateSelected = rand() % 3;
    for (int spaceIndex = 0; spaceIndex < 9; spaceIndex++){
        cubeFaces[face][spaceIndex] = stalemates[stalemateSelected][spaceIndex];
        if (face % 2 == 1) {
            cubeFaces[face][spaceIndex] = !cubeFaces[face][spaceIndex];
        }
    }
    for (int rotations = rand() % 4; rotations > 0; rotations--){
        rotateFaceC(face);
    }
}



std::array<bool, 9> RubiksCubeTTT::getFace(int face){
    return cubeFaces[face];
}

std::array<std::array<bool,9>, 6> RubiksCubeTTT::getFaces(){
    return cubeFaces;
}

/*
 * Rotates the cube and changes the front face
 * 1. Up 
 * 2. Down
 * 3. Left
 * 4. Right
 */
std::array<int, 4> verticalTop = {{4, 2, 5, 0}};
void RubiksCubeTTT::rotate(int dir){
    std::array<bool, 9> placeholderValues;
    switch(dir) {
        case 1: 
            placeholderValues = cubeFaces[0];
            cubeFaces[0] = cubeFaces[5];
            cubeFaces[5] = cubeFaces[2];
            cubeFaces[2] = cubeFaces[4];
            cubeFaces[4] = placeholderValues;
            rotateFaceC(3);
            rotateFaceCC(1);
            break;
        case 2:
            placeholderValues = cubeFaces[0];
            cubeFaces[0] = cubeFaces[4];
            cubeFaces[4] = cubeFaces[2];
            cubeFaces[2] = cubeFaces[5];
            cubeFaces[5] = placeholderValues;
            rotateFaceC(1);
            rotateFaceCC(3);
            break;
        case 3:
            placeholderValues = cubeFaces[0];
            cubeFaces[0] = cubeFaces[3];
            cubeFaces[3] = cubeFaces[2];
            cubeFaces[2] = cubeFaces[1];
            cubeFaces[1] = placeholderValues;
            rotateFaceC(4);
            rotateFaceCC(5);
            break;
        case 4:
            placeholderValues = cubeFaces[0];
            cubeFaces[0] = cubeFaces[1];
            cubeFaces[1] = cubeFaces[2];
            cubeFaces[2] = cubeFaces[3];
            cubeFaces[3] = placeholderValues;
            rotateFaceC(5);
            rotateFaceCC(4);
            break;
    }
}


/*
 * Rotates the cube based on the space hovered.
 * 1. Up 
 * 2. Down
 * 3. Left
 * 4. Right
 * Note contains a lot of spaghetti code
 */
void RubiksCubeTTT::rotateSections(int colRow, int dir){ 
    switch(dir) {
        case 1: 
            rotateSectionUp(colRow);
            break;
        case 2:
            rotateSectionDown(colRow);
            break;
        case 3:
            rotateSectionLeft(colRow);
            break;
        case 4:
            rotateSectionRight(colRow);
            break;
    }
}

void RubiksCubeTTT::rotateSectionUp(int col) {
    std::array<bool, 3> placeholderValues;
    placeholderValues[0] = cubeFaces[0][col];
    placeholderValues[1] = cubeFaces[0][col + 3];
    placeholderValues[2] = cubeFaces[0][col + 6];

    cubeFaces[0][col] = cubeFaces[5][col];
    cubeFaces[0][col + 3] = cubeFaces[5][col + 3];
    cubeFaces[0][col + 6] = cubeFaces[5][col + 6];

    cubeFaces[5][col] = cubeFaces[2][col];
    cubeFaces[5][col + 3] = cubeFaces[2][col + 3];
    cubeFaces[5][col + 6] = cubeFaces[2][col + 6];

    cubeFaces[2][col] = cubeFaces[4][col];
    cubeFaces[2][col + 3] = cubeFaces[4][col + 3];
    cubeFaces[2][col + 6] = cubeFaces[4][col + 6];

    cubeFaces[4][col] = placeholderValues[0];
    cubeFaces[4][col + 3] = placeholderValues[1];
    cubeFaces[4][col + 6] = placeholderValues[2];
    
    if (col == 0) rotateFaceC(3);
    if (col == 2) rotateFaceCC(1);
}

void RubiksCubeTTT::rotateSectionDown(int col) {
    std::array<bool, 3> placeholderValues;
    placeholderValues[0] = cubeFaces[0][col];
    placeholderValues[1] = cubeFaces[0][col + 3];
    placeholderValues[2] = cubeFaces[0][col + 6];

    cubeFaces[0][col] = cubeFaces[4][col];
    cubeFaces[0][col + 3] = cubeFaces[4][col + 3];
    cubeFaces[0][col + 6] = cubeFaces[4][col + 6];

    cubeFaces[4][col] = cubeFaces[2][col];
    cubeFaces[4][col + 3] = cubeFaces[2][col + 3];
    cubeFaces[4][col + 6] = cubeFaces[2][col + 6];

    cubeFaces[2][col] = cubeFaces[5][col];
    cubeFaces[2][col + 3] = cubeFaces[5][col + 3];
    cubeFaces[2][col + 6] = cubeFaces[5][col + 6];

    cubeFaces[5][col] = placeholderValues[0];
    cubeFaces[5][col + 3] = placeholderValues[1];
    cubeFaces[5][col + 6] = placeholderValues[2];

    if (col == 0) rotateFaceC(1);
    if (col == 2) rotateFaceCC(3);
}

void RubiksCubeTTT::rotateSectionLeft(int row) {
    std::array<bool, 3> placeholderValues;
    placeholderValues[0] = cubeFaces[0][row];
    placeholderValues[1] = cubeFaces[0][row + 3];
    placeholderValues[2] = cubeFaces[0][row + 6];

    cubeFaces[0][row] = cubeFaces[3][row];
    cubeFaces[0][row + 3] = cubeFaces[3][row + 3];
    cubeFaces[0][row + 6] = cubeFaces[3][row + 6];

    cubeFaces[3][row] = cubeFaces[2][row];
    cubeFaces[3][row + 3] = cubeFaces[2][row + 3];
    cubeFaces[3][row + 6] = cubeFaces[2][row + 6];

    cubeFaces[2][row] = cubeFaces[1][row];
    cubeFaces[2][row + 3] = cubeFaces[1][row + 3];
    cubeFaces[2][row + 6] = cubeFaces[1][row + 6];

    cubeFaces[1][row] = placeholderValues[0];
    cubeFaces[1][row + 3] = placeholderValues[1];
    cubeFaces[1][row + 6] = placeholderValues[2];

    if(row == 0) rotateFaceC(4);
    if(row == 2) rotateFaceCC(5);
}

void RubiksCubeTTT::rotateSectionRight(int row) {
    std::array<bool, 3> placeholderValues;
    placeholderValues[0] = cubeFaces[0][row];
    placeholderValues[1] = cubeFaces[0][row + 3];
    placeholderValues[2] = cubeFaces[0][row + 6];

    cubeFaces[0][row] = cubeFaces[1][row];
    cubeFaces[0][row + 3] = cubeFaces[1][row + 3];
    cubeFaces[0][row + 6] = cubeFaces[1][row + 6];

    cubeFaces[1][row] = cubeFaces[2][row];
    cubeFaces[1][row + 3] = cubeFaces[2][row + 3];
    cubeFaces[1][row + 6] = cubeFaces[2][row + 6];

    cubeFaces[2][row] = cubeFaces[3][row];
    cubeFaces[2][row + 3] = cubeFaces[3][row + 3];
    cubeFaces[2][row + 6] = cubeFaces[3][row + 6];

    cubeFaces[3][row] = placeholderValues[0];
    cubeFaces[3][row + 3] = placeholderValues[1];
    cubeFaces[3][row + 6] = placeholderValues[2];

    if(row == 0) rotateFaceC(5);
    if(row == 2) rotateFaceCC(4);
}


/*
 * Rotates a face clockwise
 * [0][1][2]     [6][3][0]
 * [3][4][5] --> [7][4][1]
 * [6][7][8]     [8][5][2]
 */
void RubiksCubeTTT::rotateFaceC(int face){
    std::array<bool,9> newPositions;
    newPositions[0] = cubeFaces[face][6];
    newPositions[1] = cubeFaces[face][3];
    newPositions[2] = cubeFaces[face][0];
    newPositions[3] = cubeFaces[face][7];
    newPositions[4] = cubeFaces[face][4];
    newPositions[5] = cubeFaces[face][1];
    newPositions[6] = cubeFaces[face][8];
    newPositions[7] = cubeFaces[face][5];
    newPositions[8] = cubeFaces[face][2];
    for (int spaceIndex = 0; spaceIndex < 9; spaceIndex++) {
        cubeFaces[face][spaceIndex] = newPositions[spaceIndex];
    }
}

/*
 * Rotates a face counterclockwise
 * [0][1][2]     [2][5][8]
 * [3][4][5] --> [1][4][7]
 * [6][7][8]     [0][3][6]
 */
void RubiksCubeTTT::rotateFaceCC(int face){
    std::array<bool,9> newPositions;
    newPositions[0] = cubeFaces[face][2];
    newPositions[1] = cubeFaces[face][5];
    newPositions[2] = cubeFaces[face][8];
    newPositions[3] = cubeFaces[face][1];
    newPositions[4] = cubeFaces[face][4];
    newPositions[5] = cubeFaces[face][7];
    newPositions[6] = cubeFaces[face][0];
    newPositions[7] = cubeFaces[face][3];
    newPositions[8] = cubeFaces[face][6];
    for (int spaceIndex = 0; spaceIndex < 9; spaceIndex++) {
        cubeFaces[face][spaceIndex] = newPositions[spaceIndex];
    }
}

/*
 * Standard tic tac toe board win check
 */
optional<bool> RubiksCubeTTT::checkFaceWin(int face){
    bool xWin = false;
    bool oWin = false;

    for(int start = 0; start < 3; start++){
        // check rows
        int startRow = 0 + start * 3;
        if (cubeFaces[face][startRow] == 
            cubeFaces[face][startRow + 1] == 
            cubeFaces[face][startRow + 2]){
            if (cubeFaces[face][startRow]){
                xWin = true;
            } else {
                oWin = true;
            }
        }
        // check columns
        if (cubeFaces[face][start] == 
            cubeFaces[face][start + 3] == 
            cubeFaces[face][start + 6]){
            if (cubeFaces[face][start]){
                xWin = true;
            } else {
                oWin = true;
            }
        }

    }

    // check diagonals
    if (cubeFaces[face][0] == 
        cubeFaces[face][4] == 
        cubeFaces[face][8]){
        if (cubeFaces[face][0]){
            xWin = true;
        } else {
            oWin = true;
        }
    }
    if (cubeFaces[face][2] == 
        cubeFaces[face][4] == 
        cubeFaces[face][6]){
        if (cubeFaces[face][2]){
            xWin = true;
        } else {
            oWin = true;
        }
    }

    if (xWin && !oWin) return true;
    else if (oWin && !xWin) return false;
    return NULL;
}

/*
 * Checks to see how many faces each player has won
 * If player wins 2 more faces than the other player
 * that player wins
 */
optional<bool> RubiksCubeTTT::winner(){
    int xWins = 0;
    int oWins = 0;
    for(int face = 0; face < sizeof(cubeFaces); face++){
        optional<bool> win = checkFaceWin(face);
        if (win.has_value()){
            if (win.value()){
                xWins++;
            } else {
                oWins++;
            }
        }
    }
    if(xWins > oWins + 1) return true;
    else if(oWins > xWins + 1) return false;
    return NULL;
}