#include "MineManager.h"
#include "Ship.h"

//constructor sets x pos for all the mines
MineManager::MineManager( Sound &Explosion, const Surface &MineSurface, AnimationFrames &ExplosionFrames )
{
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist(0.0f, 700.0f);
	for (int i = 0; i < nMinesMax; i++)
	{		
		mine.emplace_back<Mine>( Mine{ xDist( rng ), MineSurface, Explosion, ExplosionFrames } );
	}
}

//updates the active mines, take ship as argument since it's needed in mines update function
void MineManager::Update( float Dt )
{
	for (int i = 0; i < nMines; i++)
	{		
		mine[ i ].Update( Dt );
 	}

	//when mine counter reaches newMine a new mine will be drawn on screen
	//unless nMines == nMinesMax because that's the end of the array, there are no more mines to be drawn
	mineCounter ++;
	SpawnMine();
}

//Draws the mines 
void MineManager::Draw( Graphics & gfx )
{
	for (int i = 0; i < nMines; i++)
	{
		mine[ i ].Draw( gfx );
	}
}

void MineManager::SpawnMine()
{
	if( mineCounter == newMine && nMines != nMinesMax )
	{
		nMines++;
		mineCounter = 0;
	}
}

Mine & MineManager::GetMine( int Idx )
{
	return mine[ Idx ];
}

const Mine & MineManager::GetMine( int Idx ) const
{
	return mine[ Idx ];
}

int MineManager::GetMineCount() const
{
	return nMines;
}



