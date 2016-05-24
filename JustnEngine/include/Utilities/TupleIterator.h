#pragma once
#include <tuple>
#include <utility>

template<std::size_t N>
struct tuple_functor
{
	template<typename T, typename F>
	static void iterator(std::size_t i, T&& tupleType, F&& function)
	{
		const std::size_t I = (N - 1);
		switch (i)
		{
		case I:
			std::forward<F>(function)(std::get<I>(std::forward<T>(tupleType)));
			break;

		default:
			tuple_functor<I>::run(i, std::forward<T>(tupleType), std::forward<F>(function));
		}
	}
};

template<>
struct tuple_functor<0>
{
	template<typename T, typename F>
	static void run(std::size_t, T, F) {}
};
