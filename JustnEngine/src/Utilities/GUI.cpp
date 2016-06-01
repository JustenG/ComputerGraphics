#include "Utilities\GUI.h"
#include "all_includes.h"
#include <algorithm>    // std::find
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include <Gizmos.h>

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw_gl3.h"

#include "Components\ComponentManager.h"
#include "Entitys\EntityManager.h"
#include "Assets\AssetManager.h"

#include "Components\Camera.h"


GUI::GUI()
{
	m_entityManager = EntityManager::GetInstance();
	m_componentManager = ComponentManager::GetInstance();
	m_assetManager = AssetManager::GetInstance();

	m_isImGuiActive = true;
	m_isGizmosActive = true;
}

GUI::~GUI()
{
	Gizmos::destroy();
	ImGui_ImplGlfwGL3_Shutdown();
}

void GUI::Init(GLFWwindow* window, int width, int height)
{
	//Initialise GUI
	ImGui_ImplGlfwGL3_Init(window, true);

	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize.x = (float)width;
	io.DisplaySize.y = (float)height;

	//Create Gizmos
	Gizmos::create();
}

void GUI::Update()
{
	if (m_isImGuiActive) UpdateImGui();
	if (m_isGizmosActive) UpdateGizmos();
}

void GUI::UpdateImGui()
{
	//ImGui
	//-------------------------------------------------
	//-------------------------------------------------
	//Clear ImGui
	ImGui_ImplGlfwGL3_NewFrame();

	//Update ImGui
	DrawHierarchy();
	DrawComponents();
	

	//-------------------------------------------------
	//-------------------------------------------------
}

void GUI::DrawHierarchy()
{
	ImGui::Begin("Hierarchy");

	//Reset selected object to nullptr
	m_selectedObject = nullptr;

	for (int i = 0; i < m_entityManager->GetEntityCount(); ++i)
	{
		GameObject* object = &(m_entityManager->GetEntitys()->data())[i];
		DrawGameObject(object);
	}
	if (m_selectedObject != nullptr)
	{
		// Update selection state. Process outside of tree loop to avoid visual inconsistencies during the clicking-frame.
		if (ImGui::GetIO().KeyCtrl)
			m_selectedObjects.push_back(m_selectedObject);  // CTRL+click to toggle
		else
		{
			m_selectedObjects.clear();
			m_selectedObjects.push_back(m_selectedObject);    // Click to single-select
		}
	}

	ImGui::End();
}

void GUI::DrawGameObject(GameObject* object)
{
	Transform* objTrans = object->GetComponent<Transform>();
	if (objTrans->GetParent() != nullptr)	return;

	std::string name(object->GetName());
	uint childCount = objTrans->GetChildren().size();

	ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;

	if (childCount == 0)
	{
		//No Childern, Keep open
		node_flags |= ImGuiTreeNodeFlags_AlwaysOpen;

		//If selected
		if (std::find(m_selectedObjects.begin(), m_selectedObjects.end(), object) != m_selectedObjects.end())
			node_flags |= ImGuiTreeNodeFlags_Selected;

		//Push Tree Node
		ImGui::TreeNodeEx((void*)object, node_flags, name.c_str());
		
		//If item clicked
		if (ImGui::IsItemClicked())	m_selectedObject = object;

		//Pop Tree Node
		ImGui::TreePop();
	}
	else
	{
		//Push Tree Node
		bool node_open = ImGui::TreeNodeEx((void*)object, node_flags, name.c_str());

		//If item clicked
		if (ImGui::IsItemClicked())	m_selectedObject = object;

		//If Opened
		if (node_open)
		{
			for (int i = 0; i < childCount; ++i)
			{
				GameObject* child = objTrans->GetChildren()[i]->GetGameObject();
				DrawGameObject(child);
			}

		}
		//Pop Tree Node
		ImGui::TreePop();
	}
	return;
}

void GUI::DrawComponents()
{
	ImGui::Begin("Inspector");

	if (m_selectedObjects.size() <= 0 || m_selectedObjects.size() > 1)
	{
		ImGui::End();
		return;
	}

	//TODO
	//Make a componenet displayer 

	BaseComponent*			component = m_selectedObjects[0]->GetComponent<Camera>();
	if (component != nullptr)
	{
		BaseData* componentData = component->ToData();
		componentData->Render();
		component->FromData(componentData);
		delete componentData;
	}

	//Transform*			component = m_selectedObjects[0]->GetComponent<Transform>();
	//Camera*				component = m_selectedObjects[0]->GetComponent<Camera>();
	//Light*				component = m_selectedObjects[0]->GetComponent<Light>();
	//MeshRenderer*		component = m_selectedObjects[0]->GetComponent<MeshRenderer>();
	//Terrain*			component = m_selectedObjects[0]->GetComponent<Terrain>();
	ImGui::End();



}

void GUI::UpdateGizmos()
{
	//Gizmos
	//-------------------------------------------------
	//-------------------------------------------------
	Gizmos::clear();
	Gizmos::addTransform(mat4(1));

	//Draw Grid
	//---------------------------
	int gridScale = 5;
	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10) * gridScale, vec3(-10 + i, 0, -10) * gridScale, i == 10 * gridScale ? vec4(1, 1, 1, 1) : vec4(0, 0, 0, 1));
		Gizmos::addLine(vec3(10, 0, -10 + i) * gridScale, vec3(-10, 0, -10 + i) * gridScale, i == 10 * gridScale ? vec4(1, 1, 1, 1) : vec4(0, 0, 0, 1));
	}
	//---------------------------

	//-------------------------------------------------
	//-------------------------------------------------
}

void GUI::Render()
{
	//Render ImGui
	//-----------------------------------------------
	//-----------------------------------------------
	if (m_isImGuiActive) ImGui::Render();
	//-----------------------------------------------
	//-----------------------------------------------

	//Render Gizmos
	//-----------------------------------------------
	//-----------------------------------------------
	if (m_isGizmosActive)
	{
		if (m_componentManager->GetMainCamera() != nullptr)
		{
			mat4 projectionView = m_componentManager->GetMainCamera()->GetProjectionView();
			Gizmos::draw(projectionView);
		}
	}
	//-----------------------------------------------
	//-----------------------------------------------
}

template<>
void GUI::RenderData<int>(int& value, string name)
{
	ImGui::DragInt(name.c_str(), &value);
}
template<>
void GUI::RenderData<float>(float& value, string name)
{
	ImGui::DragFloat(name.c_str(), &value);
}
template<>
void GUI::RenderData<bool>(bool& value, string name)
{
	ImGui::Checkbox(name.c_str(), &value);
}
template<>
void GUI::RenderData<vec2>(vec2& value, string name)
{
	ImGui::DragFloat2(name.c_str(), glm::value_ptr(value));
}
template<>
void GUI::RenderData<ivec2>(ivec2& value, string name)
{
	ImGui::DragInt2(name.c_str(), glm::value_ptr(value));
}
template<>
void GUI::RenderData<vec3>(vec3& value, string name)
{
	ImGui::DragFloat3(name.c_str(), glm::value_ptr(value));
}