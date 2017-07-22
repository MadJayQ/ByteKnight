#pragma once

class CRectangle
{
public:
	CRectangle(int _x, int _y, int _w, int _h)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}
	CRectangle()
	{
		x = 0; y = 0; w = 0; h = 0;
	}
	int x, y;
	int w, h;
};
