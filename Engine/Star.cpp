#include "Star.h"
#include <random>

Star::Star()
{
	
}

void Star::Spawn( const Vec2 &Pos, float Size)
{
	position = Pos;
	size = Size;
}

void Star::Update(float dt)
{
	position.y += vy * dt;
	if ( position.y + size >= Graphics::ScreenHeight)
	{
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_real_distribution<float> xDist(3.0f, 795.0f);
		position = Vec2( xDist( rng ), 3.f );
	}
}

void Star::Draw(Graphics & gfx)
{
	const int x_int = int(position.x);
	const int y_int = int(position.y);
	gfx.PutPixel(x_int, y_int, Colors::Cyan);
	gfx.PutPixel(x_int+1, y_int, Colors::Cyan);
	gfx.PutPixel(x_int-1, y_int, Colors::Cyan);
	gfx.PutPixel(x_int, y_int+ 1, Colors::Cyan);
	gfx.PutPixel(x_int, y_int- 1, Colors::Cyan);
	gfx.PutPixel(x_int+2, y_int, Colors::Blue);
	gfx.PutPixel(x_int-2, y_int, Colors::Blue);
	gfx.PutPixel(x_int+ 1, y_int+1, Colors::Blue);
	gfx.PutPixel(x_int- 1, y_int+1, Colors::Blue);
	gfx.PutPixel(x_int+ 1, y_int- 1, Colors::Blue);
	gfx.PutPixel(x_int- 1, y_int- 1, Colors::Blue);
	gfx.PutPixel(x_int, y_int- 2, Colors::Blue);
	gfx.PutPixel(x_int, y_int+ 2, Colors::Blue);
}

void Star::DrawBig(Graphics & gfx)
{
	const int x_int = int(position.x);
	const int y_int = int(position.y);
	gfx.PutPixel(x_int, y_int, Colors::Cyan);
	gfx.PutPixel(x_int+1, y_int, Colors::Cyan);
	gfx.PutPixel(x_int+ 2, y_int, Colors::Cyan);
	gfx.PutPixel(x_int, y_int+ 1, Colors::Cyan);
	gfx.PutPixel(x_int+ 1, y_int+1, Colors::Cyan);
	gfx.PutPixel(x_int+ 2, y_int+1, Colors::Cyan);
	gfx.PutPixel(x_int, y_int+2, Colors::Cyan);
	gfx.PutPixel(x_int+ 1, y_int+2, Colors::Cyan);
	gfx.PutPixel(x_int+ 2, y_int+2, Colors::Cyan);
	gfx.PutPixel(x_int+1, y_int-1, Colors::Cyan);
	gfx.PutPixel(x_int+ 1, y_int- 2, Colors::Cyan);
	gfx.PutPixel(x_int+ 1, y_int+ 3, Colors::Cyan);
	gfx.PutPixel(x_int+ 1, y_int+ 4, Colors::Cyan);
	gfx.PutPixel(x_int+ 3, y_int+ 1, Colors::Cyan);
	gfx.PutPixel(x_int+ 4, y_int+ 1, Colors::Cyan);
	gfx.PutPixel(x_int- 1, y_int+ 1, Colors::Cyan);
	gfx.PutPixel(x_int- 2, y_int+ 1, Colors::Cyan);

	gfx.PutPixel(x_int, y_int- 1, Colors::Blue);
	gfx.PutPixel(x_int, y_int- 2, Colors::Blue);
	gfx.PutPixel(x_int, y_int+3, Colors::Blue);
	gfx.PutPixel(x_int, y_int+4, Colors::Blue);

	gfx.PutPixel(x_int- 1, y_int, Colors::Blue);
	gfx.PutPixel(x_int- 1, y_int- 1, Colors::Blue);
	gfx.PutPixel(x_int- 1, y_int+2, Colors::Blue);
	gfx.PutPixel(x_int- 1, y_int+3, Colors::Blue);
	gfx.PutPixel(x_int- 2, y_int, Colors::Blue);
	gfx.PutPixel(x_int- 2, y_int, Colors::Blue);
	gfx.PutPixel(x_int- 3, y_int+ 1, Colors::Blue);

	gfx.PutPixel(x_int+ 1, y_int- 3, Colors::Blue);
	gfx.PutPixel(x_int+ 1, y_int+ 5, Colors::Blue);
	gfx.PutPixel(x_int+ 2, y_int- 1, Colors::Blue);
	gfx.PutPixel(x_int+ 2, y_int- 2, Colors::Blue);
	gfx.PutPixel(x_int+ 2, y_int+ 3, Colors::Blue);
	gfx.PutPixel(x_int+ 2, y_int+ 4, Colors::Blue);
	gfx.PutPixel(x_int+ 3, y_int, Colors::Blue);
	gfx.PutPixel(x_int+ 3, y_int- 1, Colors::Blue);
	gfx.PutPixel(x_int+ 3, y_int+2, Colors::Blue);
	gfx.PutPixel(x_int+ 3, y_int+3, Colors::Blue);
	gfx.PutPixel(x_int+ 4, y_int, Colors::Blue);
	gfx.PutPixel(x_int+ 4, y_int+2, Colors::Blue);
	gfx.PutPixel(x_int+ 5, y_int+1, Colors::Blue);
}
