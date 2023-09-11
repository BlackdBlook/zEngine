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

void Level::Update()
{
	for (auto o : objs)
	{
		o->Update();
	}
}

void Level::Draw()
{
	for (auto o : objs)
	{
		o->Draw();
	}
}
