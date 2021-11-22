#include <iostream>
#include "raylib.h"

using namespace std;

void initGrid();
void chooseSymbols();
int checkWin();

int** grid = nullptr;
int width = 7;
int height = 6;
int tokenSize = 20;
int dividerWidth = 2;
int marginWidth = 10;
int marginHeight = 10;
int windowWidth = 0;
int windowHeight = 0;
bool currPlayer = 0;
bool shouldClose;

int main() {
    windowWidth = tokenSize * width + dividerWidth * (width-1) + marginWidth * 2;
    windowHeight = (tokenSize+1) * height + marginHeight + dividerWidth * height;
    InitWindow(windowWidth, windowHeight, "2D Platformer");
    SetExitKey(-1);

    while (!WindowShouldClose() && !shouldClose) {
        initGrid();
        ClearBackground(BLACK);

        while (true){
            for (int y = 0; y < height; y++){
                for (int x = 0; x < width; x++){
                    if (grid[x][y-1] == 1) DrawCircle(
                        marginWidth + (x-1)*dividerWidth + x * tokenSize + tokenSize/2, 
                        marginHeight + (y)*dividerWidth + (y+1) * tokenSize + tokenSize/2,
                        tokenSize/2, (Color){0xFF, 0x10, 0xF0, 255}
                        );
                    else if (grid[x][y-1] == 2) DrawCircle(
                        marginWidth + (x-1)*dividerWidth + x * tokenSize + tokenSize/2, 
                        marginHeight + (y)*dividerWidth + (y+1) * tokenSize + tokenSize/2,
                        tokenSize/2, (Color){0x39, 0xFF, 0x14, 255}
                        );
                    else DrawCircle(
                        marginWidth + (x-1)*dividerWidth + x * tokenSize + tokenSize/2, 
                        marginHeight + (y)*dividerWidth + (y+1) * tokenSize + tokenSize/2,
                        tokenSize/2, (Color){0, 0, 0, 255}
                        );
                }
            }
        }
    }
}

void initGrid() {
    grid = new int * [width];

    for (int i = 0; i < width; i++){
        grid [i] = new int [height];
    }
}

int checkWin(){
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            if (grid[x][y] && grid[x][y] < 3){
                bool possibleWin = true;
                for (int i = 0; i < 4; i++){
                    if (x+i > width-1) possibleWin = false;
                    if (grid[x+i][y] != grid[x][y]) possibleWin = false;
                } if (possibleWin) return grid[x][y];
                possibleWin = true;
                for (int i = 0; i < 4; i++){
                    if (x+i > width-1 || y+i > height-1) possibleWin = false;
                    if (grid[x+i][y+i] != grid[x][y]) possibleWin = false;
                } if (possibleWin) return grid[x][y];
                possibleWin = true;
                for (int i = 0; i < 4; i++){
                    if (x+i > width-1 || y-i < 0) possibleWin = false;
                    if (grid[x+i][y-i] != grid[x][y]) possibleWin = false;
                } if (possibleWin) return grid[x][y];
                possibleWin = true;
                for (int i = 0; i < 4; i++){
                    if (y+i > height-1) possibleWin = false;
                    if (grid[x][y+i] != grid[x][y]) possibleWin = false;
                } if (possibleWin) return grid[x][y];
            }
        }
    }
    return 0;
}
