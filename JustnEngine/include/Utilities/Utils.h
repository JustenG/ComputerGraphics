#pragma once
#include "global_includes.h"
#include <tuple>
#include <utility>
#include <type_traits>

#define GetVarName(VAR, STR) STR = #VAR; 

class Utils
{
public:

	template<typename T>
	static size_t GetTypeID()
	{
		return typeid(T).hash_code();
	};

	template <typename... TArgs>
	static std::vector<size_t> GetTypes()
	{
		std::vector<size_t> result = { typeid(TArgs).hash_code()... };
		return result;
	}

	template <typename T, typename U>
	static bool IsSameType()
	{
		if (GetTypeID<T>() == GetTypeID<U>())
			return true;
		else
			return false;
	}
};


namespace Tuple
{
	template<std::size_t I = 0, typename FuncT, typename... Ts>
	inline typename std::enable_if<I == sizeof...(Ts), void>::type
		for_each(std::tuple<Ts...> &, FuncT) // Unused arguments are given no names.
	{ }

	template<std::size_t I = 0, typename FuncT, typename... Ts>
	inline typename std::enable_if<I < sizeof...(Ts), void>::type
		for_each(std::tuple<Ts...>& t, FuncT f)
	{
		f(std::get<I>(t),I);
		for_each<I + 1, FuncT, Ts...>(t, f);
	}

	template<std::size_t I = 0, typename FuncT, typename... Ts1, typename... Ts2>
	inline typename std::enable_if<I == sizeof...(Ts1), void>::type
		for_each(std::tuple<Ts1...> &, std::tuple<Ts2...> &, FuncT) // Unused arguments are given no names.
	{ }

	template<std::size_t I = 0, typename FuncT, typename... Ts1, typename... Ts2>
	inline typename std::enable_if<I < sizeof...(Ts1), void>::type
		for_each(std::tuple<Ts1...>& t1, std::tuple<Ts2...>& t2, FuncT f)
	{
		f(std::get<I>(t1), std::get<I>(t2), I);
		for_each<I + 1, FuncT, Ts1..., Ts2...>(t1,t2, f);
	}

	template<std::size_t I = 0, typename FuncT, typename... Ts>
	inline typename std::enable_if<I == sizeof...(Ts), void>::type
		set_each(std::tuple<Ts...> &, FuncT) // Unused arguments are given no names.
	{ }
}