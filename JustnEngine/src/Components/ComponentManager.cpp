#include "Components\ComponentManager.h"
#include "Components\Transform.h"
#include "Components\Camera.h"
#include "Components\Light.h"
#include "Components\MeshRenderer.h"
#include "Components\Terrain.h"

ComponentManager* ComponentManager::m_instance = new ComponentManager();

ComponentManager::ComponentManager()
{
	m_transformsInline = false;
	m_mainCameraIndex = -1;
}

ComponentManager::~ComponentManager()
{
}

ComponentManager * ComponentManager::GetInstance() 
{
	if (!m_instance) 
		m_instance = new ComponentManager();

	return m_instance;
};

void ComponentManager::UpdateAllComponents()
{
	if (!m_transformsInline)
	{
		ReorderTransforms();
	}

	for (size_t i = 0; i < Transforms.size(); ++i)
	{
		Transforms[i].Update();
	}
	for (size_t i = 0; i < Transforms.size(); ++i)
	{
		if (ParentIndexBuffer[i] == -1)
			Transforms[i].UpdateWorldTransform();
		else
			Transforms[i].UpdateWorldTransform(Transforms[ParentIndexBuffer[i]].GetMatrix());
	}

	for (int i = 0; i < (int)Cameras.size(); ++i)
	{
		int index = Cameras[i].GetTransformIndex();
		Transform transform = Transforms[index];
		Cameras[i].Update(transform);
	}
	for (int i = 0; i < Lights.size(); ++i)
	{
		int index = Lights[i].GetTransformIndex();
		Transform transform = Transforms[index];
		Lights[i].Update(transform);
	}

}

void ComponentManager::RenderAllComponents()
{
	for (int i = 0; i < (int)Lights.size(); ++i)
	{
		Lights[i].Bind();

		for (int j = 0; j < (int)MeshRenderers.size(); ++j)
		{
			int index = MeshRenderers[i].GetTransformIndex();
			Transform transform = Transforms[index];

			MeshRenderers[j].Render(Lights[i]);
		}
		for (int j = 0; j < (int)Terrains.size(); ++j)
		{
			int index = Terrains[i].GetTransformIndex();
			Transform transform = Transforms[index];

			Terrains[j].Render(Lights[i]);
		}


		Lights[i].Unbind();
	}


	for (int i = 0; i < (int)Cameras.size(); ++i)
	{
		Cameras[i].Bind();

		for (int j = 0; j < (int)MeshRenderers.size(); ++j)
		{
			int index = MeshRenderers[i].GetTransformIndex();
			Transform transform = Transforms[index];

			MeshRenderers[j].Render(Transforms[index],Cameras[i],Lights,0);
		}
		for (int j = 0; j < (int)Terrains.size(); ++j)
		{
			int index = Terrains[i].GetTransformIndex();
			Transform transform = Transforms[index];

			Terrains[j].Render(Transforms[index], Cameras[i], Lights, 0);
		}

		Cameras[i].Unbind();
	}
}

void ComponentManager::RequestTransformUpdate()
{
	m_transformsInline = false;
}

void ComponentManager::AddChildren(Transform* parent, short &parentsIndex)
{
	//Add Children To Buffer or Update
	for (size_t i = 0; i < parent->GetChildren().size(); i++)
	{
		TransformsBuffer.push_back(*parent->GetChildren()[i]);
		ParentIndexBuffer.push_back(parentsIndex);
	}

	for (size_t i = 0; i < parent->GetChildren().size(); i++)
	{
		++parentsIndex;
		if (parent->GetChildren()[i]->GetChildren().size() > 0)
			AddChildren(parent->GetChildren()[i], parentsIndex);
	}
}

void ComponentManager::ReorderTransforms()
{
	short index = 0;
	for (size_t i = 0; i < Transforms.size(); ++i)
	{
		if (Transforms[i].GetParent() == nullptr)
		{
			TransformsBuffer.push_back(Transforms[i]);
			ParentIndexBuffer.push_back(-1);
			AddChildren(&Transforms[i], index);
			++index;
		}
	}
	Transforms = TransformsBuffer;
	TransformsBuffer.empty();
	m_transformsInline = true;
}

void ComponentManager::SetMainCamera(int index)
{
	m_mainCameraIndex = index;
	Cameras[m_mainCameraIndex].SetResolution(m_mainCameraResolution);
	Cameras[m_mainCameraIndex].SetToMain();
}

Camera* ComponentManager::GetMainCamera()
{
	if (m_mainCameraIndex == -1)
		return nullptr;
	else
		return &Cameras[m_mainCameraIndex];
}

// Set Component
//-------------------------------------------------------------------
template<>
int ComponentManager::AddComponent<Transform>()
{
	Transforms.emplace_back();
	return Transforms.size()-1;
}
template<>
int ComponentManager::AddComponent<Camera>()
{
	Cameras.emplace_back();

	if (Cameras.size() == 1)
		SetMainCamera(0);

	return Cameras.size() - 1;
}
template<>
int ComponentManager::AddComponent<Light>()
{
	Lights.emplace_back();
	return Lights.size() - 1;
}
template<>
int ComponentManager::AddComponent<MeshRenderer>()
{
	MeshRenderers.emplace_back();
	return MeshRenderers.size() - 1;
}
template<>
int ComponentManager::AddComponent<Terrain>()
{
	Terrains.emplace_back();
	return Terrains.size() - 1;
}
//-------------------------------------------------------------------

// Get Component
//-------------------------------------------------------------------
template<>
Transform* ComponentManager::GetComponent<Transform>(int index)
{
	return &Transforms[index];
}
template<>
Camera* ComponentManager::GetComponent<Camera>(int index)
{
	return &Cameras[index];
}
template<>
Light* ComponentManager::GetComponent<Light>(int index)
{
	return &Lights[index];
}
template<>
MeshRenderer* ComponentManager::GetComponent<MeshRenderer>(int index)
{
	return &MeshRenderers[index];
}
template<>
Terrain* ComponentManager::GetComponent<Terrain>(int index)
{
	return &Terrains[index];
}
//-------------------------------------------------------------------