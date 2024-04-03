#pragma once

struct Vector2
{
	int x, y;

	bool operator==(Vector2 const& other)
	{
		return (x == other.x) && (y == other.y);
	}
};
