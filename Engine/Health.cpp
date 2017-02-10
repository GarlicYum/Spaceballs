#include "Health.h"


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
