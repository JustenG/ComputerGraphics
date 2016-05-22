#pragma once
#include "global_includes.h"
#include <tuple>    
#include "Utilities\Utils.h"
#include <type_traits>

template<typename... TData>
class Data
{
public:
	Data(TData... data) {};
	~Data() {};

	uint GetDataType(uint index)
	{
		return Utils::GetTypeID<std::tuple_element<index, tuple>::type>();
	}

	uint Size()
	{
		return (uint)std::tuple_size<tuple>::value;
	}

	template<typename T>
	T& GetData(uint index)
	{
		return std::get<index>(tuple);
	}

private:
	std::tuple<TData...> tuple;

private:

};