#include "MainWindow.h"
#include "Mine.h"
#include "Ship.h"
#include "Surface.h"



//detects if the mine collides with a ship, passing in reference to the ship so mine knows its location
//returns a bool, this function will get called in mines update function
bool Mine::DetectCollision(Ship& ship)
{
	const float mRight = x + width;
	const float mBottom = y + height;
	const float sRight = ship.GetWidth() + ship.GetX();
	const float sBottom = ship.GetHeight() + ship.GetY();
	
	return
		mRight >= ship.GetX() &&
		x <= sRight &&
		mBottom >= ship.GetY() &&
		y <= sBottom;
}

//updates the mine, takes ship as argument so it can call the detectcollision function
void Mine::Update(Ship& ship, float dt, ShieldManager shieldM)
{
	if (ship.HasHealth()) //updates mines if ship has health
	{
		if (!isDetonated)
		{
			y += vy * dt;
		}

		//if mine is detonated it stops moving and explosion counter starts counting,
		//when the counter reaches explosion end then the explosion will no longer be displayed on screen
		else
		{
			explosionCounter++;
			framecount++;
			if (framecount > 1)
			{
				framecount = 0;
				curframe++;
			}
		}
		if (DetectCollision(ship))
		{
			isDetonated = true;
			if (!isDamaged)      //if not isdamaged then the ship will take damage and isdamaage becomes true
			{                      // this way the damanage is dealt only one time
				if (shieldM.GetShield().GetisActive() == false)
				{
					ship.Damage(damage);
				}

				explosion.Play(0.8F, 1.0F);
			}
			isDamaged = true;

		}
	
		GotShot(ship, ship.GetnBullets());

		if (!isDetonated && DetectShield(shieldM))
		{
			isDetonated = true;
			explosion.Play(0.8F, 1.0F);
		}
	}
}

void Mine::Draw(Graphics& gfx, Ship& ship, Animation& animation)
{
	if (ship.HasHealth())
	{
		if (!isDetonated && (y < gfx.ScreenHeight))
		{
			static const Surface mine = Surface::FromFile(L"mine.png");
			gfx.DrawSpriteKey(int(x), int(y), mine, mine.GetPixel(0, 0));
		}

		else if (isDetonated && explosionCounter < explosionEnd)
		{
			gfx.DrawSpriteKey(int(x), int(y), animation.GetExplo()[curframe], animation.GetExplo()[curframe].GetPixel(0, 0));
		}
	}
}

//rng will determine the mines x pos, gets set in mine manager
void Mine::SetPos(float X)
{
	x = X;
}

//this will get used in mine manager to not update mine if it isn't active
bool Mine::isActive()
{
	return
		explosionCounter < explosionEnd;
}

void Mine::GotShot(Ship & ship, int nBullets)
{
	for (int i = 0; i < nBullets; i++)
	{
		const float bRight = ship.GetBullets()[i].GetX() + ship.GetBullets()[i].GetBulletSize();
		const float bLeft = ship.GetBullets()[i].GetX() - ship.GetBullets()[i].GetBulletSize();
		const float bBottom = ship.GetBullets()[i].GetY() + ship.GetBullets()[i].GetBulletSize();
		const float bTop = ship.GetBullets()[i].GetY() - ship.GetBullets()[i].GetBulletSize();
		const float mRight = x + width;
		const float mBottom = y + height;
		if (mRight >= bLeft &&
			x <= bRight &&
			mBottom >= bTop &&
			y <= bBottom)
		{
			ship.GetBullets()[i].SetHasSpawned(false);
		}
	}
}

bool Mine::DetectShield(ShieldManager& shieldM)
{
	if (shieldM.GetShield().GetisActive())
	{
		const float sRight = shieldM.GetShield().GetX() + float (shieldM.GetShield().GetSize());
		const float sLeft = shieldM.GetShield().GetX() - float(shieldM.GetShield().GetSize());
		const float sBottom = shieldM.GetShield().GetY() + float(shieldM.GetShield().GetSize());
		const float sTop = shieldM.GetShield().GetY() - float(shieldM.GetShield().GetSize());
		const float mRight = x + width;
		const float mBottom = y + height;
	
		if (mRight >= sLeft &&
			x <= sRight &&
			mBottom >= sTop &&
			y <= sBottom)
		{
			return true;
		}
	}
	return false;

}


	

