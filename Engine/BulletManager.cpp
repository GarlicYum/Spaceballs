#include "BulletManager.h"
#include "Graphics.h"

const Bullet & BulletManager::GetBullet( int Idx ) const
{
	return bullets[ Idx ];
}

Bullet & BulletManager::GetBullet( int Idx )
{
	return bullets[ Idx ];
}

int BulletManager::GetNumBullets() const
{
	return nBullets;
}

void BulletManager::FireBullet( const Vec2 &CannonPosition )
{
	if( shotsFired == false )
	{
		for( int i = 0; i < nBullets; ++i )
		{
			auto &bullet = bullets[ i ];
			if( !bullet.HasSpawned() )
			{
				bullet = Bullet( CannonPosition );
				gun.Play( 0.5F, 0.5F );
				shotsFired = true;
				break;
			}
		}
	}
}

void BulletManager::UpdateBullets( float Dt )
{
	for( int i = 0; i < nBullets; i++ )
	{
		auto &bullet = bullets[ i ];
		if( bullet.HasSpawned() )
		{
			bullet.Update( Dt );
		}
	}
}

void BulletManager::DrawBullets( Graphics &Gfx )
{
	for( int i = 0; i < nBullets; i++ )
	{
		auto &bullet = bullets[ i ];
		if( bullet.HasSpawned() )
		{
			bullet.Draw( Gfx );
		}
	}
}

void BulletManager::ResetShotsFired()
{
	shotsFired = false;
}
