#include "Assets\Material.h"

#include "FBXFile.h"
#include "Assets\Texture.h"

Material::Material()
{
	memset(m_pTextures, 0, sizeof(Texture*) * TextureSlots::TextureTypes_Count);
}

Material::~Material()
{

}

void Material::onBind()
{
	for (int i = 0; i < TextureSlots::TextureTypes_Count; ++i)
	{
		if (m_pTextures[i])
			m_pTextures[i]->Bind();
	}
}

void Material::onUnbind()
{
	for (int i = 0; i < TextureSlots::TextureTypes_Count; ++i)
	{
		if (m_pTextures[i])
			m_pTextures[i]->Unbind();
	}
}

void Material::LoadIfExists(TextureSlots slot, FBXMaterial* pMaterial, unsigned int uiTextureType)
{
	if (pMaterial->textures[uiTextureType])
	{
		std::string name(GetFileName() + "_Texture" + std::to_string(slot));
		m_pAssetManager->LoadTexture(pMaterial->textures[uiTextureType]->path, name);

		LoadTexture(m_pAssetManager->GetAsset<Texture>(name),slot);
	}
}

void Material::LoadTexture(Texture* texture, TextureSlots slot)
{
	m_pTextures[slot] = texture;
	m_pTextures[slot]->SetTextureSlot(slot);
}
