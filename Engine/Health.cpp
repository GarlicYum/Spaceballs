#include "Health.h"


Health::Health(int X, int Y, int hp)
	:
	x(X),
	y(Y),
	healthAmount(hp)
{}

void Health::Damage(int dmg)
{
	healthAmount -= dmg;
	ColorMeter();
}

void Health::Restore(int restore)
{
	healthAmount += restore;
	if (healthAmount > maxHealth)
	{
		healthAmount = maxHealth;
	}
	ColorMeter();
}

void Health::Draw(Graphics& gfx)
{
	gfx.DrawSquare(x, y, healthAmount, height, c);
}

bool Health::HasHealth() const
{
	return
		healthAmount > 0;
}

int Health::GetHealthAmount() const
{
	return healthAmount;
}

void Health::Reset()
{
	healthAmount = maxHealth;
	ColorMeter();
	timer = 0.0f;
}

bool Health::FillUp(int amount, int increment, float dt)
{
	ColorMeter();
	if (healthAmount < amount)
	{
		if ((timer += dt) >= newincrement)
		{
			healthAmount += increment;
			timer = 0.0f;
		}
	}
	else
	{
		return true;
	}
	return false;
}

void Health::ColorMeter()
{
	if (healthAmount <= 100)
	{
		c = Colors::Red;
	}
	else if (healthAmount <= 200)
	{
		c = Colors::Yellow;
	}
	else
	{
		c = Colors::Green;
	}
}
