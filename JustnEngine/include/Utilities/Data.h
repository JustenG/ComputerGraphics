#pragma once
#include "global_includes.h"
#include <tuple>    
#include "Utilities\Utils.h"
#include <type_traits>

template<typename... TData>
class DataBinder
{
public:
	DataBinder() {};
	DataBinder(TData...& data) 
	{
		//TODO
		//Set all m_data to data
	};
	~Data() {};

	std::tuple<TData...*>& GetData()
	{
		return m_data;
	};

	void SetData(TData...& data)
	{
		m_data = data;
	};


private:
	std::tuple<TData...*> m_data;

};

template<typename... TArgs>
auto CreateDataType(TArgs&&... values)->DataBinder<std::remove_reference_t<decltype(values)>...> {};

class BaseData
{
public:
	BaseData() {};
	~BaseData() {};

	virtual void Render() {}; // Renders all children in ImGUIList

private:
	std::vector<BaseData*> children;
};

template<typename... TData>
class Data : public BaseData
{
public:
	Data(TData...) {}; // Add each TData using TData.ToData() or default to (FloatData, Vec3Data, etc)
	~Data() {};
};

//Data Types
class FloatData : BaseData
{
	float value;
	void Render() override {}; // Renders float value
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
