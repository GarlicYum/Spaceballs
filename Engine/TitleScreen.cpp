#include "TitleScreen.h"
#include "Surface.h"

void TitleScreen::DrawNormal(Graphics & gfx)
{
	static const Surface title = Surface::FromFile(L"titlenormal.png");
	gfx.DrawSpriteKey(x, y, title, title.GetPixel(0, 0));
}

void TitleScreen::DrawEasy(Graphics & gfx)
{
	static const Surface title = Surface::FromFile(L"titleeasy.png");
	gfx.DrawSpriteKey(x, y, title, title.GetPixel(0, 0));
}
