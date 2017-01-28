#include "Star.h"

void Star::Spawn(int X, int Y, int Size)
{
	x = X;
	y = Y;
	size = Size;
}

void Star::Update()
{
	y++;
	if (y + size >= Graphics::ScreenHeight)
	{
		y = 3;
	}
}

void Star::Draw(Graphics & gfx)
{
	gfx.PutPixel(x, y, Colors::Cyan);
	gfx.PutPixel(x +1, y, Colors::Cyan);
	gfx.PutPixel(x -1, y, Colors::Cyan);
	gfx.PutPixel(x, y + 1, Colors::Cyan);
	gfx.PutPixel(x, y - 1, Colors::Cyan);
	gfx.PutPixel(x +2, y, Colors::Blue);
	gfx.PutPixel(x -2, y, Colors::Blue);
	gfx.PutPixel(x + 1, y +1, Colors::Blue);
	gfx.PutPixel(x - 1, y +1, Colors::Blue);
	gfx.PutPixel(x + 1, y - 1, Colors::Blue);
	gfx.PutPixel(x - 1, y - 1, Colors::Blue);
	gfx.PutPixel(x, y - 2, Colors::Blue);
	gfx.PutPixel(x, y + 2, Colors::Blue);
}

void Star::DrawBig(Graphics & gfx)
{
	gfx.PutPixel(x, y, Colors::Cyan);
	gfx.PutPixel(x +1, y, Colors::Cyan);
	gfx.PutPixel(x + 2, y, Colors::Cyan);
	gfx.PutPixel(x, y+ 1, Colors::Cyan);
	gfx.PutPixel(x + 1, y +1, Colors::Cyan);
	gfx.PutPixel(x + 2, y +1, Colors::Cyan);
	gfx.PutPixel(x, y +2, Colors::Cyan);
	gfx.PutPixel(x + 1, y +2, Colors::Cyan);
	gfx.PutPixel(x + 2, y +2, Colors::Cyan);
	gfx.PutPixel(x+1, y -1, Colors::Cyan);
	gfx.PutPixel(x + 1, y - 2, Colors::Cyan);
	gfx.PutPixel(x + 1, y + 3, Colors::Cyan);
	gfx.PutPixel(x + 1, y + 4, Colors::Cyan);
	gfx.PutPixel(x + 3, y + 1, Colors::Cyan);
	gfx.PutPixel(x + 4, y + 1, Colors::Cyan);
	gfx.PutPixel(x - 1, y + 1, Colors::Cyan);
	gfx.PutPixel(x - 2, y + 1, Colors::Cyan);

	gfx.PutPixel(x, y - 1, Colors::Blue);
	gfx.PutPixel(x, y - 2, Colors::Blue);
	gfx.PutPixel(x, y +3, Colors::Blue);
	gfx.PutPixel(x, y +4, Colors::Blue);

	gfx.PutPixel(x - 1, y, Colors::Blue);
	gfx.PutPixel(x - 1, y - 1, Colors::Blue);
	gfx.PutPixel(x - 1, y +2, Colors::Blue);
	gfx.PutPixel(x - 1, y +3, Colors::Blue);
	gfx.PutPixel(x - 2, y, Colors::Blue);
	gfx.PutPixel(x - 2, y, Colors::Blue);
	gfx.PutPixel(x - 3, y + 1, Colors::Blue);

	gfx.PutPixel(x + 1, y - 3, Colors::Blue);
	gfx.PutPixel(x + 1, y + 5, Colors::Blue);
	gfx.PutPixel(x + 2, y - 1, Colors::Blue);
	gfx.PutPixel(x + 2, y - 2, Colors::Blue);
	gfx.PutPixel(x + 2, y + 3, Colors::Blue);
	gfx.PutPixel(x + 2, y + 4, Colors::Blue);
	gfx.PutPixel(x + 3, y, Colors::Blue);
	gfx.PutPixel(x + 3, y - 1, Colors::Blue);
	gfx.PutPixel(x + 3, y +2, Colors::Blue);
	gfx.PutPixel(x + 3, y +3, Colors::Blue);
	gfx.PutPixel(x + 4, y, Colors::Blue);
	gfx.PutPixel(x + 4, y +2, Colors::Blue);
	gfx.PutPixel(x + 5, y +1, Colors::Blue);
}
