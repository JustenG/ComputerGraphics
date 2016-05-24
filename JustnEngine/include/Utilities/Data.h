#pragma once
#include "global_includes.h"
#include <tuple>    
#include "Utilities\Utils.h"
#include <type_traits>
#include <functional>
#include <glm/glm.hpp>
#include <glm/ext.hpp>


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
//Data Binder
//----------------------------------------
//----------------------------------------
template<typename... TData>
class DataBinder
{
public:
	DataBinder(TData&... data) { m_tupleData = std::make_tuple(data...); };
	~DataBinder() {};

	std::tuple<TData*...>& GetData() { return m_tupleData; };
	void SetData(TData&... data) { m_tupleData = data; };
	uint Size() { return (uint)std::tuple_size<TData...>::value; };

	BaseData* MakeBaseData() 
	{ 
		Make::BaseDataObject(m_tupleData);
		return m_tupleData;
	};
private:
	std::tuple<TData*...> m_tupleData;	
};
//----------------------------------------
//----------------------------------------

//Data Converter
//----------------------------------------
//----------------------------------------
static std::map<uint, std::function<BaseData*()>> dataMap;

template<typename Primitive, typename Data>
BaseData* BindPrimitive()
{
	dataMap[Utils::GetTypeID<Primitive>()] = CreateData<Primitive, Data>;
}

template<typename TPrimitive, typename TData>
BaseData* CreateData(const TPrimitive& value)
{
	auto* data = new TData();
	data->value = value;
	return (BaseData*)data;
}
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
		auto found = std::find(dataMap.begin(), dataMap.end(), Utils::GetTypeID<T>());
		if (found != dataMap.end())
			children.add(found->second(x));
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
	BaseData* BaseDataObject(TData... data)
	{
		return (BaseData*)(new Data<TData...>(data...));
	}

	template<typename... TArgs>
	auto CreateDataBinderType(TArgs&&... values)->DataBinder<std::remove_reference_t<decltype(values)>...>;
}
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
