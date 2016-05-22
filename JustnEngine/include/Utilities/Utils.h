#pragma once
#include "global_includes.h"

class Utils
{
public:
	template<typename T>
	static size_t GetTypeID();

	template <typename... TArgs>
	static std::vector<size_t> GetTypes();
};

template<typename T>
size_t Utils::GetTypeID()
{
	return typeid(T).hash_code();
}

template <typename... TArgs>
std::vector<size_t> Utils::GetTypes()
{
	std::vector<size_t> result = { typeid(TArgs).hash_code()... };
	return result;
}