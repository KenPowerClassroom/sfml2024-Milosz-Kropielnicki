#pragma once

const int BLOCKNUMWIDTH = 30, BLOCKNUMHEIGHT = 20, BLOCKSIZE = 16;
const int SCREENWIDTH = BLOCKSIZE * BLOCKNUMWIDTH;
int SCREENHEIGHT = BLOCKSIZE * BLOCKNUMHEIGHT;

int down = 0, left = 1, right = 2, up = 3;

int direction, snakeLength = 4; // Sets the initial movement direction and snake length

class Tick
{
public:
    enum tile
    {
        EMPTY = 0,
        APPLE = 1,
        SNAKE = 2
    };
    

private:
    tile grid[BLOCKNUMWIDTH][BLOCKNUMHEIGHT] = { EMPTY };

public:
    int cell(int x, int y)
    {
        return grid[x][y];
    }

    bool intersetion(int x, int y)
    {
        if (grid[x][y] == EMPTY)
        {

        }
    }

    void spawnSnake(int x, int y)
    {
        if (grid[x][y] == EMPTY)
        {
            grid[x][y] = SNAKE;
        }
    }

    void spawnApple(int x, int y)
    {
        if (grid[x][y] == EMPTY)
        {
            grid[x][y] = APPLE;
        }
    }
};
