#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int blockNumWidth = 30, blockNumHeight = 20, blockSize = 16;
int screenWidth = blockSize * blockNumWidth;
int screenHeight = blockSize * blockNumHeight;

int down = 0, left = 1, right = 2, up = 3;

int direction, snakeLength = 4; // Sets the initial movement direction and snake length

// The snake
// x,y are movement directions
// snakeChar is the actual snake object
// The array declaration dictates the max length of the snake
struct Snake 
{
    int x,y;
}   snakeChar[100];

// The Fruit
// x,y are spawn locations
// fruit is the actual fruit object
struct Fruit
{
    int x,y;
}   fruit;

void Tick()
 {
    // for loop that dictates the current length of the snake
    // Sets the current index x,y positions to be the previous index's x,y positions
    for (int i = snakeLength; i > 0; --i)
    {
        snakeChar[i].x = snakeChar[i-1].x; 
        snakeChar[i].y = snakeChar[i-1].y;
    }

    // Changes snake direction based on input
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

    // if snake head is in the same position as fruit
    // Increases snakeLength by 1
    // Consequently, increases the for loop count at the beginning of Tick()
    //Finally, randomizes fruit position
    if ((snakeChar[0].x == fruit.x) && (snakeChar[0].y == fruit.y)) 
    {
        snakeLength++;
        fruit.x = rand() % blockNumWidth;
        fruit.y = rand() % blockNumHeight;
    }

    // Border wrapping checks/logic
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
 
    // For loop that checks if the snake has collided with itself
    // If the snake head hits the snake index body, snakeLength is set to index body
    // Consequently, for loop at the start is affected
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

    // Renders the window using the screenWidth and screenHeight set at the top
    RenderWindow window(VideoMode(screenWidth, screenHeight), "Snake Game!");

    // Creates Textures emptyTileTexture and occupiedTileTexture
    // emptyTile is set to the white blocks (for empty squares)
    // occupiedTile us set to the red blocks (for snake/fruit)
    Texture emptyTileTexture, occupiedTileTexture;
    emptyTileTexture.loadFromFile("images/snake/white.png");
    occupiedTileTexture.loadFromFile("images/snake/red.png");

    // Creates Sprites emptyTileSprite and occupiedTileSprite
    // emptyTileSprite is set the white block texture
    // occupiedTileSprite is set the red block texture
    Sprite emptyTileSprite(emptyTileTexture);
    Sprite occupiedTileSprite(occupiedTileTexture);

    // Sets up a clock
    Clock clock;
    float timer = 0, delay = 0.1;

    // Base fruit position
    fruit.x = 10;
    fruit.y = 10; 
    
    while (window.isOpen())
    {
        // Sets time to the elapsed seconds of the clock
        // Resets clock
        // Takes the time, saves it to the timer, then adds additional time to the timer
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time; 

        // Creates event called event
        // event is used to check if the window should be closed
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)      
                window.close();
        }

        // Checks user key presses
        // Sets direction based on key press
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

        // If timer exceeds delay, reset the timer and call Tick()
        // Used to slow the tick rate of the game, easing the resources required to run the game
        if (timer > delay)
        {
            timer = 0;
            Tick();
        }

        ////// draw  ///////
           window.clear();
        
        // Draws the white (empty) boxes
        // Draws them based on the predetermined repeat values set into N and M at the top
        for (int i = 0; i < blockNumWidth; i++)
        {
            for (int j = 0; j < blockNumHeight; j++)
            {
                emptyTileSprite.setPosition(i * blockSize, j * blockSize); // Sets the sprite position based off of the texture size * index
                window.draw(emptyTileSprite);
            }
        }

        for (int i = 0; i < snakeLength; i++)
        {
            occupiedTileSprite.setPosition(snakeChar[i].x * blockSize, snakeChar[i].y * blockSize); // Sets the snake sprite position based off of the texture size
            window.draw(occupiedTileSprite); 
        }
   
        occupiedTileSprite.setPosition(fruit.x * blockSize, fruit.y * blockSize); // Draws fruit
        window.draw(occupiedTileSprite);    

        window.display();
    }

    return 0;
}
