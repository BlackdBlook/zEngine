#include "Level.h"
#include "../Object/Object.h"
Level::Level()
{
	
}

Level::~Level()
{
}

void Level::Start()
{
	for (auto o : objs)
	{
		o->Start();
	}
}

void Level::Update(float DeltaTime)
{
	for (auto o : objs)
	{
		o->Update(DeltaTime);
	}
}

void Level::Draw()
{
	for (auto o : objs)
	{
		o->Draw();
	}
}
