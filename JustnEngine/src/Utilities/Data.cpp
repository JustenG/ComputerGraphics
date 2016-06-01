#include "Utilities\Data.h"
#include "Utilities\GUI.h"

//Data Types
//----------------------------------------
//----------------------------------------
void IntData::Render()		{ GUI::RenderData(value, Name);			BaseData::Render(); }
void UIntData::Render()		{ GUI::RenderData((int&)value, Name);	BaseData::Render(); }
void FloatData::Render()	{ GUI::RenderData(value,Name);			BaseData::Render(); }
void BoolData::Render()		{ GUI::RenderData(value,Name);			BaseData::Render(); }
void Vector2Data::Render()	{ GUI::RenderData(value,Name);			BaseData::Render(); }
void Vector2iData::Render() { GUI::RenderData(value,Name);			BaseData::Render(); }
void Vector3Data::Render()	{ GUI::RenderData(value,Name);			BaseData::Render(); }
//----------------------------------------
//----------------------------------------


template<> float		DataConverter::GetPrimitive <float>(const BaseData* data) { return ((FloatData*)data)->value; }
template<> int			DataConverter::GetPrimitive <int>(const BaseData* data) { return ((IntData*)data)->value; }
template<> uint			DataConverter::GetPrimitive <uint>(const BaseData* data) { return ((UIntData*)data)->value; }
template<> bool			DataConverter::GetPrimitive <bool>(const BaseData* data) { return ((BoolData*)data)->value; }
template<> glm::vec2	DataConverter::GetPrimitive <glm::vec2>(const BaseData* data) { return ((Vector2Data*)data)->value; }
template<> glm::ivec2	DataConverter::GetPrimitive <glm::ivec2>(const BaseData* data) { return ((Vector2iData*)data)->value; }
template<> glm::vec3	DataConverter::GetPrimitive <glm::vec3>(const BaseData* data) { return ((Vector3Data*)data)->value; }

template<> 
BaseData* DataConverter::CreateData <float>(const float data) { return DataConverter::CreateBaseData<float, FloatData>(data); }
template<> 
BaseData* DataConverter::CreateData <int>(const int data) { return DataConverter::CreateBaseData<int, IntData>(data); }
template<> 
BaseData* DataConverter::CreateData <uint>(const uint data) { return DataConverter::CreateBaseData<uint, UIntData>(data); }
template<>
BaseData* DataConverter::CreateData <bool>(const bool data){ return DataConverter::CreateBaseData<bool, BoolData>(data); }
template<>
BaseData* DataConverter::CreateData <glm::vec2>(const glm::vec2 data) { return DataConverter::CreateBaseData<glm::vec2, Vector2Data>(data); }
template<>
BaseData* DataConverter::CreateData <glm::ivec2>(const glm::ivec2 data) { return DataConverter::CreateBaseData<glm::ivec2, Vector2iData>(data); }
template<>
BaseData* DataConverter::CreateData <glm::vec3>(const glm::vec3 data) { return DataConverter::CreateBaseData<glm::vec3, Vector3Data>(data); }
//----------------------------------------
//----------------------------------------
