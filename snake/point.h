#pragma once

struct Point
{
	int x = 0;
	int	y = 0;
};

bool operator==(const Point& lhs, const Point& rhs);