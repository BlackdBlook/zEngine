#include "Component.h"

#include "Engine/Object/Object.h"

bool Component::operator==(Component* c)
{
    return false;
}

bool Component::operator==(const char* c)
{
    return false;
}

void Component::OnAttached()
{
}

void Component::OnDettached()
{
}
