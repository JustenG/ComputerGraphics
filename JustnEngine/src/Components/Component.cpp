#include "Components\Component.h"

Component::Component()
{
}

Component::~Component()
{
}

void Component::SetTransformIndex(int transformIndex)
{
	m_transformIndex = transformIndex;
}
int Component::GetTransformIndex()
{
	return m_transformIndex;
}