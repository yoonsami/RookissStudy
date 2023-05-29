#pragma once

struct Pos
{
	bool operator==(Pos& other)
	{
		return y == other.y && x == other.x;
	}

	bool operator==(const Pos& other)
	{
		return y == other.y && x == other.x;
	}

	bool operator<(const Pos& other) const
	{
		if (y != other.y)
			return y < other.y;
		return x < other.x;
	}

	bool operator!=(Pos& other)
	{
		return !(*this == other);
	}

	Pos operator+(Pos& other)
	{
		Pos tmp;
		tmp.y = y + other.y;
		tmp.x = x + other.x;
		return tmp;
	}

	Pos& operator+=(Pos& other)
	{
		y += other.y;
		x += other.x;
		return *this;
	}

	int32 y = 0;
	int32 x = 0;
};

enum Dir
{
	DIR_UP = 0,
	DIR_LEFT =1,
	DIR_DOWN =2,
	DIR_RIGHT=3,

	DIR_COUNT=4
};

