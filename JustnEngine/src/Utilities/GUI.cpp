#include "Utilities\GUI.h"
#include "all_includes.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw_gl3.h"

#include "Components\ComponentManager.h"
#include "Entitys\EntityManager.h"
#include "Assets\AssetManager.h"

#include "Components\Camera.h"

#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include <Gizmos.h>


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
	ImGui::Begin("GameObjects");
	for (int i = 0; i < m_entityManager->GetEntityCount(); ++i)
	{
		GameObject* object = &(m_entityManager->GetEntitys()->data())[i];
		PrintObject(object);
	}


	//TEST
	//------------------------------------------
	//------------------------------------------
	ShowHelpMarker("Click to select, CTRL+Click to toggle, double-click to open");
	static int selection_mask = 0x02;   // Dumb representation of what may be user-side selection state. You may carry selection state inside or outside your objects in whatever format you see fit.

	int node_clicked = -1;
	for (int i = 0; i < 5; i++)
	{
		ImGuiTreeNodeFlags node_flags = ((selection_mask & (1 << i)) ? ImGuiTreeNodeFlags_Selected: 0) | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		bool opened = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Child %d", i);
		if (ImGui::IsItemClicked())
			node_clicked = i;
		if (opened)
		{
			ImGui::Text("blah blah");
			ImGui::TreePop();
		}
	}
	if (node_clicked != -1)
	{
		// Update selection state. Process outside of tree loop to avoid visual inconsistencies during the clicking-frame.
		if (ImGui::GetIO().KeyCtrl)
			selection_mask ^= (1 << node_clicked);  // CTRL+click to toggle
		else
			selection_mask = (1 << node_clicked);   // Click to single-select
	}
	//------------------------------------------
	//------------------------------------------

	ImGui::End();



	//-------------------------------------------------
	//-------------------------------------------------
}

void GUI::PrintObject(GameObject* object)
{
	std::string name(object->GetName());

	Transform* parent = object->GetComponent<Transform>();

	if (ImGui::TreeNode(name.c_str()))
	{
		if (parent->GetChildren().size() > 0)
		{
			for (int i = 0; i < parent->GetChildren().size(); ++i)
			{
				GameObject* child = parent->GetChildren()[i]->GetGameObject();
				PrintObject(child);
			}
		}
		ImGui::TreePop();
	}
	return;
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