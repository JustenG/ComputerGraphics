#pragma once
#include "global_includes.h"
#include <type_traits>

class Utils
{
public:
	template<typename T>
	static size_t GetTypeID();

	template <typename... TArgs>
	static std::vector<size_t> GetTypes();

	template <typename T, typename U>
	static bool IsSameType();
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

template <typename T, typename U>
bool Utils::IsSameType()
{
	if (GetTypeID<T>() == GetTypeID<U>())
		return true;
	else
		return false;
}
