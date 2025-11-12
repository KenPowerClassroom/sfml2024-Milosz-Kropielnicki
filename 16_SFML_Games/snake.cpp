#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int N = 30, M = 20; // Dictates the amount of movement blocks
int sz = 16;    // Sprite/Texture pixel size(?)
int w = sz*N;   // width, sz(?) * N blocks
int h = sz*M;   // height, sz(?) * M blocks

int dir,num=4;  // The direction amount, I guess?

// The snake
// x,y are movement directions
// s is the actual snake object
// The array declaration dictates the max length of the snake
struct Snake 
{
    int x,y;
}   s[100];

// The Fruit
// x,y are spawn locations
// f is the actual fruit object
struct Fruit
{
    int x,y;
}   f;

void Tick()
 {
    // i is index
    // Somehow relates to the end point/tail of the snake
    for (int i = num; i > 0; --i)
    {
        s[i].x = s[i-1].x; 
        s[i].y = s[i-1].y;
    }

    // Changes snake direction based on input
    if (dir == 0)
    {
        s[0].y += 1;
    }
    if (dir == 1)
    {
        s[0].x -= 1;
    }
    if (dir == 2)
    {
        s[0].x += 1;
    }
    if (dir == 3)
    {
        s[0].y -= 1;
    }

    // if snake head is in the same position as fruit
    // Increases num by 1
    // Consequently, increases the for loop count at the beginning of Tick()
    //Finally, randomizes fruit position
    if ((s[0].x == f.x) && (s[0].y == f.y)) 
    {
        num++;
        f.x = rand()%N;
        f.y = rand()%M;
    }

    // Border wrapping checks
    if (s[0].x > N)
    {
        s[0].x = 0;
    }
    if (s[0].x < 0)
    {
        s[0].x = N;
    }
    if (s[0].y > M)
    {
        s[0].y = 0;
    }
    if (s[0].y < 0)
    {
        s[0].y = M;
    }
 
    // i = index
    // If the snake head hits the snake index body, num is set to index
    // Consequently, for loop at the start is affected
    for (int i = 1; i < num; i++)
    {
        if (s[0].x == s[i].x && s[0].y == s[i].y)
        {
            num = i;
        }
    }
 }

int snake()
{  
    srand(time(0));

    // Renders the window using the width and height set at the top
    RenderWindow window(VideoMode(w, h), "Snake Game!");

    // Creates Textures t1 and t2
    // t1 is set to the white blocks (for empty squares)
    // t2 us set to the red blocks (for snake/fruit)
    Texture t1,t2;
    t1.loadFromFile("images/snake/white.png");
    t2.loadFromFile("images/snake/red.png");

    // Creates Sprites sprite 1 and sprite 2
    // sprite1 is set the white block texture
    // sprite2 is set the red block texture
    Sprite sprite1(t1);
    Sprite sprite2(t2);

    // Sets up a clock
    Clock clock;
    float timer=0, delay=0.1;

    // Base(?) fruit position
    f.x=10;
    f.y=10; 
    
    while (window.isOpen())
    {
        // Sets time to the elapsed seconds of the clock
        // Resets clock
        // Takes the time, saves it to the timer, then adds additional time to the timer
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time; 

        // Creates event called e
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)      
                window.close();
        }

        // Checks user key presses
        // Sets direction based on key press
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            dir = 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            dir = 2;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            dir = 3;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            dir = 0;
        }

        // If timer exceeds delay, reset the timer and call Tick()
        if (timer > delay)
        {
            timer = 0;
            Tick();
        }

        ////// draw  ///////
           window.clear();
        
        // Draws the white (empty) boxes
        // Draws them based on the predetermined repeat values set into N and M at the top
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                sprite1.setPosition(i * sz, j * sz);    // Sets the sprite position based off of the texture size * index
                window.draw(sprite1);
            }
        }

        for (int i = 0; i < num; i++)
        {
            sprite2.setPosition(s[i].x * sz, s[i].y * sz);  // Sets the snake sprite position based off of the texture size
            window.draw(sprite2); 
        }
   
        sprite2.setPosition(f.x * sz, f.y * sz);    // Draws fruit
        window.draw(sprite2);    

        window.display();
    }

    return 0;
}
