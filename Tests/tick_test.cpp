#include "pch.h"

const int WIDTH = 30;
const int HEIGHT = 20;
const int BLOCK_SIZE = 16;

#include "../16_SFML_Games/Tick.h"

TEST(Tick, HasEmptyGrid)
{
	Tick grid;

	EXPECT_EQ(Tick::tile::EMPTY, grid.cell(0, 0));
	EXPECT_EQ(Tick::tile::EMPTY, grid.cell(WIDTH, HEIGHT));
	EXPECT_EQ(Tick::tile::APPLE, grid.cell(10, 10));
}

TEST(Tick, AppleHasSpawned)
{
	Tick grid;

	grid.spawnApple(5, 5);
	EXPECT_EQ(Tick::tile::APPLE, grid.cell(5, 5));
}

TEST(Tick, SnakeHasSpawned)
{
	Tick grid;

	for (int i = 1; i < 5; i++)
	{
		grid.spawnSnake(i, 10);
	}

	EXPECT_EQ(Tick::tile::SNAKE, grid.cell(1, 10));
	EXPECT_EQ(Tick::tile::SNAKE, grid.cell(2, 10));
	EXPECT_EQ(Tick::tile::SNAKE, grid.cell(3, 10));
	EXPECT_EQ(Tick::tile::SNAKE, grid.cell(4, 10));
	EXPECT_EQ(Tick::tile::SNAKE, grid.cell(5, 10));

	EXPECT_EQ(Tick::tile::EMPTY, grid.cell(6, 10));
}

TEST(Tick, SnakeIntersectsApple)
{
	Tick grid;

	grid.spawnApple(5, 5);

	for (int i = 1; i < 5; i++)
	{
		grid.intersetion(i, 5);
	}

	EXPECT_EQ(Tick::tile::SNAKE, grid.cell(1, 5));
	EXPECT_EQ(Tick::tile::SNAKE, grid.cell(2, 5));
	EXPECT_EQ(Tick::tile::SNAKE, grid.cell(3, 5));
	EXPECT_EQ(Tick::tile::SNAKE, grid.cell(4, 5));
	EXPECT_EQ(Tick::tile::INTERSECTION, grid.cell(5, 5));
}