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
	DataBinder(TData&... data) { m_tupleData = std::make_tuple(&data...); };
	~DataBinder() {};

	BaseData* Get() 
	{ 
		Data<TData...>* data = new Data<TData...>();
		auto function = [data](const auto& tupleElement, uint index) { data->AddDataValue(tupleElement); };
		Tuple::for_each(m_tupleData, function);
		return data;
	};

	void Set(BaseData* data) 
	{ 
		auto function = [GetDataMap, data](const auto& tupleElement, uint index) { tupleElement = GetData<decltype(tupleElement)>(data->children[index]);};
		Tuple::for_each(m_tupleData, function);
	};

	uint Size() { return (uint)std::tuple_size<TData...>::value; };
private:
	std::tuple<TData*...> m_tupleData;
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
		auto found = std::find(CreateDataMap.begin(), CreateDataMap.end(), Utils::GetTypeID<T>());
		if (found != CreateDataMap.end())
			children.add(found->second(x));
		else
			x->ToData();
	}
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

	static std::map<uint, std::function<BaseData*()>> CreateDataMap;
	static std::map<uint, std::function<void*()>> GetDataMap;

	template<typename Primitive, typename Data>
	static BaseData* BindPrimitive()
	{
		CreateDataMap[Utils::GetTypeID<Primitive>()] = CreateData<Primitive, Data>;
		CreateDataMap[Utils::GetTypeID<Primitive>()] = GetPrimitive<Primitive, Data>;
	}

	template<typename TPrimitive, typename TData>
	static BaseData* CreateData(const TPrimitive& value)
	{
		auto* data = new TData();
		data->value = value;
		return (BaseData*)data;
	}

	template<typename TPrimitive, typename TData>
	static TPrimitive* GetData(const TData& data)
	{
		return (TPrimitive*)GetDataMap[Utils::GetTypeID<TPrimitive>()](data);
	}

	template<typename TPrimitive, typename TData>
	static void* GetPrimitive(const TData& data)
	{
		return (void*)(((TData*)data)->value);
	}

	static void Init()
	{
		if (DataConverter::CreateDataMap.size() > 0)
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
	BaseData* BaseDataObject(TData... data)
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
