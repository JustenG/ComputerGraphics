#pragma once
#include "global_includes.h"
#include "Utilities\Utils.h"
#include <tuple>    
#include <type_traits>
#include <glm/glm.hpp>

//BaseData
//----------------------------------------
//----------------------------------------
class BaseData
{
public:
	BaseData() {};
	~BaseData() {};

	virtual void Render() {}; // Renders all children in ImGUIList
	std::vector<BaseData*>& GetChildren() { return m_children; };

protected:
	std::vector<BaseData*> m_children;
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
	Data() {};
	Data(TData... data) { AddDataValue(data)...; };
	~Data() {};

	template<typename T>
	void AddDataValue(T x)
	{
		DataConverter::CreateData(x);
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

	BaseData* Get() 
	{ 
		Data<TData...>* data = new Data<TData...>();
		auto function = [data](const auto& tupleElement, uint index) { data->AddDataValue(*tupleElement); };
		Tuple::for_each(m_tupleData, function);
		return data;
	};

	void Set(BaseData* newData)
	{
		auto function = [newData](const auto& tupleElement, uint index)
		{ 
			*tupleElement = DataConverter::GetPrimitive<decltype(*tupleElement)>(newData->GetChildren()[index]); 
		};
		Tuple::for_each(m_tupleData, function);
	};

private:
	std::tuple<TData*...> m_tupleData;
};
//----------------------------------------
//----------------------------------------


//Data Types
//----------------------------------------
//----------------------------------------
class NullData : BaseData
{
public:
	int value;
	void Render() override {}; // Renders float value
};
class FloatData : BaseData
{
public:
	float value;
	void Render() override; // Renders float value
};
class IntData : BaseData
{
public:
	int value;
	void Render() override; // Renders int value
};
class UIntData : BaseData
{
public:
	uint value;
	void Render() override; // Renders uint value
};
class BoolData : BaseData
{
public:
	bool value;
	void Render() override; // Renders bool value
};
class Vector2Data : BaseData
{
public:
	glm::vec2 value;
	void Render() override; // Renders Vec3 value
};
class Vector2iData : BaseData
{
public:
	glm::ivec2 value;
	void Render() override; // Renders Vec3 value
};
class Vector3Data : BaseData
{
public:
	glm::vec3 value;
	void Render() override; // Renders Vec3 value
};
//----------------------------------------
//----------------------------------------

//Data Converter
//----------------------------------------
//----------------------------------------
class DataConverter
{
public:
	template<typename TPrimitive, typename TData>
	static BaseData* CreateBaseData(const TPrimitive value)
	{
		TData* data = new TData();
		data->value = value;
		return (BaseData*)data;
	}

	template<typename TPrimitive>
	static BaseData* CreateData(const TPrimitive value);

	template<typename TPrimitive> 
	static TPrimitive GetPrimitive(const BaseData* data);
};
template<typename TPrimitive>
BaseData* DataConverter::CreateData(const TPrimitive value)
{
	NullData* nullData = new NullData();
	return (BaseData*)nullData;
}

template<typename TPrimitive>
TPrimitive DataConverter::GetPrimitive(const BaseData* data)
{
	TPrimitive val = (TPrimitive)0;
	return val;
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



	//DataConverter Doesnt Work
	//------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------
	//static std::map<uint, std::function<BaseData*(const void*)>> createDataMap;

	//template<typename Primitive, typename Data>
	//static BaseData* BindPrimitive()
	//{
	//	createDataMap[Utils::GetTypeID<Primitive>()] = CreateData<Primitive, Data>;
	//}
	//static void Init()
	//{
	//	if (DataConverter::createDataMap.size() > 0)
	//		return;

	//	DataConverter::BindPrimitive<float, FloatData>();
	//	DataConverter::BindPrimitive<int, IntData>();
	//	DataConverter::BindPrimitive<uint, UIntData>();
	//	DataConverter::BindPrimitive<bool, BoolData>();
	//	DataConverter::BindPrimitive<glm::vec3, Vector3Data>();
	//}
	//------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------