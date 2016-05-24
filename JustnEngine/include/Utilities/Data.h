#pragma once
#include "global_includes.h"
#include <tuple>    
#include "Utilities\Utils.h"
#include <type_traits>
#include <functional>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Utilities\TupleIterator.h"

//BaseData
//----------------------------------------
//----------------------------------------
class BaseData
{
public:
	BaseData() {};
	~BaseData() {};

	virtual void Render() {}; // Renders all children in ImGUIList

protected:
	std::vector<BaseData*> children;
};
//----------------------------------------
//----------------------------------------

//Data Variadic Interface
//----------------------------------------
//----------------------------------------
template<typename... TData>
class Data : public BaseData
{
public:
	Data(TData... data) { AddDataValue(data)...; };
	~Data() {};

	template<typename T>
	void AddDataValue(T x)
	{
		auto found = std::find(DataMap.begin(), DataMap.end(), Utils::GetTypeID<T>());
		if (found != DataMap.end())
			children.add(found->second(x));
		else
			x->ToData();
	}
};
//----------------------------------------
//----------------------------------------

//Data Binder
//----------------------------------------
//----------------------------------------
template<typename... TData>
class DataBinder
{
public:
	DataBinder(TData&... data) { m_tupleData = std::make_tuple(&data...); };
	~DataBinder() {};

	//TODO
	//BaseData* Get() 
	//{ 
	//	BaseData* data = new Data<TData...>();

	//	const size_t tupleSize = sizeof...(TData);
	//	auto fTuple = std::forward_as_tuple(...); //Cant Get Data
	//	auto function = [](const auto& elem) { data->AddDataValue(elem); };
	//	for (int i = 0; i < Size(); ++i)
	//	{
	//		tuple_functor<tupleSize>::iterator(i, fTuple, function);
	//	}
	//	return m_tupleData; 
	//};
	template<typename... Ts>
	BaseData* Get(Ts... rawData) 
	{ 
		BaseData* data = new Data(rawData...);
		return data;
	};
	void Set(BaseData* data) { m_tupleData = data; };

	uint Size() { return (uint)std::tuple_size<TData...>::value; };
private:
	std::tuple<TData*...> m_tupleData;	
};
//----------------------------------------
//----------------------------------------

//Data Types
//----------------------------------------
//----------------------------------------
class FloatData : BaseData
{
	float value;
	void Render() override {}; // Renders float value
};
class IntData : BaseData
{
	int value;
	void Render() override {}; // Renders int value
};
class UIntData : BaseData
{
	uint value;
	void Render() override {}; // Renders uint value
};
class BoolData : BaseData
{
	bool value;
	void Render() override {}; // Renders bool value
};
class Vector3Data : BaseData
{
	glm::vec3 value;
	void Render() override {}; // Renders Vec3 value
};
//----------------------------------------
//----------------------------------------

//Data Converter
//----------------------------------------
//----------------------------------------
class DataConverter
{
public:
	static std::map<uint, std::function<BaseData*()>> DataMap;

	template<typename Primitive, typename Data>
	static BaseData* BindPrimitive()
	{
		DataMap[Utils::GetTypeID<Primitive>()] = CreateData<Primitive, Data>;
	}

	template<typename TPrimitive, typename TData>
	static BaseData* CreateData(const TPrimitive& value)
	{
		auto* data = new TData();
		data->value = value;
		return (BaseData*)data;
	}

	static void Init()
	{
		if (DataConverter::DataMap.size() > 0)
			return;

		DataConverter::BindPrimitive<float, FloatData>();
		DataConverter::BindPrimitive<int, IntData>();
		DataConverter::BindPrimitive<uint, UIntData>();
		DataConverter::BindPrimitive<bool, BoolData>();
		DataConverter::BindPrimitive<glm::vec3, Vector3Data>();
	}
};
//----------------------------------------
//----------------------------------------


//Maker Tools
//----------------------------------------
//----------------------------------------
namespace Make
{
	template<typename... TData>
	BaseData* NewData(TData... data)
	{
		return new Data<TData...>(data...);
	}

	template<typename... TArgs>
	auto CreateDataBinderType(TArgs&&... values)->DataBinder<std::remove_reference_t<TArgs>...> {};

}
//----------------------------------------
//----------------------------------------






	//template<typename T>
	//T& GetDataAtIndex(uint index)
	//{
	//	return std::get<index>(m_data);
	//}

	//template<typename T>
	//void SetDataAtIndex(T value, uint index)
	//{
	//	std::get<index>(m_data) = value;
	//}

	//uint Size()
	//{
	//	return (uint)std::tuple_size<m_data>::value;
	//}

	//uint GetDataType(uint index)
	//{
	//	return Utils::GetTypeID<std::tuple_element<index, m_data>::type>();
	//}
