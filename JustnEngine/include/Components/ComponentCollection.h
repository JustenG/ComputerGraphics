#pragma once
#include "global_includes.h"
#include "Components\IComponentCollection.h"

template<typename TContainer>
class ComponentCollection : public IComponentCollection
{
public:
	//TODO:
	//Need to change components data binder in-oreder to not loose pointers when copyed
	ComponentCollection() { m_container.reserve(1000); };
	~ComponentCollection() {};

	TContainer& operator[](std::size_t index) { return m_container[index]; };
	TContainer& Back() { return m_container.back(); };
	uint Size() { return m_container.size(); };

	std::vector<TContainer>* GetContainer() { return &m_container; };

private:

	std::vector<TContainer> m_container;

};

