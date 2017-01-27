#include "Star.h"

void Star::DrawSmall(Graphics & gfx, int x, int y)
{
	gfx.PutPixel(x, y, Colors::Cyan);
	gfx.PutPixel(x +1, y, Colors::Blue);
	gfx.PutPixel(x - 1, y, Colors::Blue);
	gfx.PutPixel(x, y + 1, Colors::Blue);
	gfx.PutPixel(x, y - 1, Colors::Blue);

}

void Star::DrawMid(Graphics & gfx)
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
