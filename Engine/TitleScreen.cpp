#include "TitleScreen.h"
#include "Surface.h"

void TitleScreen::Draw(Graphics & gfx)
{
	static const Surface title = Surface::FromFile(L"title.png");
	gfx.DrawSprite(x, y, title);
}
