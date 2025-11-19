#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int blockNumWidth = 30, blockNumHeight = 20, blockSize = 16;
int screenWidth = blockSize * blockNumWidth;
int screenHeight = blockSize * blockNumHeight;

int down = 0, left = 1, right = 2, up = 3;

int direction, snakeLength = 4;

struct Snake 
{
    int x,y;
}   snakeChar[100];

struct Fruit
{
    int x,y;
}   fruit;

void Tick()
 {
    for (int i = snakeLength; i > 0; --i)
    {
        snakeChar[i].x = snakeChar[i-1].x; 
        snakeChar[i].y = snakeChar[i-1].y;
    }

    if (direction == down)
    {
        snakeChar[0].y += 1;
    }
    else if (direction == left)
    {
        snakeChar[0].x -= 1;
    }
    else if (direction == right)
    {
        snakeChar[0].x += 1;
    }
    else
    {
        snakeChar[0].y -= 1;
    }

    if ((snakeChar[0].x == fruit.x) && (snakeChar[0].y == fruit.y)) 
    {
        snakeLength++;
        fruit.x = rand() % blockNumWidth;
        fruit.y = rand() % blockNumHeight;
    }

    if (snakeChar[0].x > blockNumWidth)
    {
        snakeChar[0].x = 0;
    }
    if (snakeChar[0].x < 0)
    {
        snakeChar[0].x = blockNumWidth;
    }
    if (snakeChar[0].y > blockNumWidth)
    {
        snakeChar[0].y = 0;
    }
    if (snakeChar[0].y < 0)
    {
        snakeChar[0].y = blockNumHeight;
    }
 
    for (int i = 1; i < snakeLength; i++)
    {
        if (snakeChar[0].x == snakeChar[i].x && snakeChar[0].y == snakeChar[i].y)
        {
            snakeLength = i;
        }
    }
 }

int snake()
{  
    srand(time(0));

    RenderWindow window(VideoMode(screenWidth, screenHeight), "Snake Game!");

    Texture emptyTileTexture, occupiedTileTexture;
    emptyTileTexture.loadFromFile("images/snake/white.png");
    occupiedTileTexture.loadFromFile("images/snake/red.png");

    Sprite emptyTileSprite(emptyTileTexture);
    Sprite occupiedTileSprite(occupiedTileTexture);

    Clock clock;
    float timer = 0, delay = 0.1;

    fruit.x = 10;
    fruit.y = 10; 
    
    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time; 

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)      
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            direction = left;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            direction = right;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            direction = up;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            direction = down;
        }

        if (timer > delay)
        {
            timer = 0;
            Tick();
        }

        ////// draw  ///////
           window.clear();
        
        for (int i = 0; i < blockNumWidth; i++)
        {
            for (int j = 0; j < blockNumHeight; j++)
            {
                emptyTileSprite.setPosition(i * blockSize, j * blockSize);
                window.draw(emptyTileSprite);
            }
        }

        for (int i = 0; i < snakeLength; i++)
        {
            occupiedTileSprite.setPosition(snakeChar[i].x * blockSize, snakeChar[i].y * blockSize);
            window.draw(occupiedTileSprite); 
        }
   
        occupiedTileSprite.setPosition(fruit.x * blockSize, fruit.y * blockSize);
        window.draw(occupiedTileSprite);    

        window.display();
    }

    return 0;
}
