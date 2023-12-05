#include "Level.h"

#include "Header.h"
#include "../Object/Object.h"

Level* Level::CurrentLevel = nullptr;

Level::Level()
{
	if(CurrentLevel != nullptr)
	{
		LOG("Level Reset Error");
	}
	CurrentLevel = this;
}

Level::~Level()
{
	if(CurrentLevel == this)
	{
		CurrentLevel = nullptr;
	}else
	{
		LOG("Level Release Error");
	}
}

void Level::Start()
{
	for (auto o : objs)
	{
		o->Start();
	}
}

std::shared_ptr<Object> Level::NewObject()
{
	auto ans = objs.emplace_back(std::make_shared<Object>());
	
	return ans;
}

std::shared_ptr<Object> Level::GetObjectPtr(Object* Object)
{
	for(auto& o : objs)
	{
		if(o.get() == Object)
		{
			return o;
		}
	}
	return nullptr;
}

Level* Level::GetCurrentLevel()
{
	return CurrentLevel;
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
