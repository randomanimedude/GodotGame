#pragma once

#include "Bullet.h"

class Bullet;

class BulletBehavior
{
public:
	virtual void DoStuff(Bullet* bullet) = 0;
};

class GoodBullet : public BulletBehavior
{
public:
	virtual void DoStuff(Bullet* bullet);
};

class BadBullet : public BulletBehavior
{
public:
	virtual void DoStuff(Bullet* bullet);
};

