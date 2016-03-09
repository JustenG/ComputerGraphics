#include "Assets\Material.h"

#include "FBXFile.h"
#include "Assets\Texture.h"

Material::Material()
{


}

Material::~Material()
{

}

void Material::onBind()
{
	for (int i = 0; i < TextureSlots::TextureTypes_Count; ++i)
	{
		if (m_pTextures[i])	m_pTextures[i]->Bind();
	}
}

void Material::onUnbind()
{
	for (int i = 0; i < TextureSlots::TextureTypes_Count; ++i)
	{
		if (m_pTextures[i])	m_pTextures[i]->Unbind();
	}
}

void Material::LoadIfExists(TextureSlots slot, FBXMaterial* pMaterial, unsigned int uiTextureType)
{
	if (pMaterial->textures[uiTextureType])
	{
		m_pTextures[slot] = new Texture();
		m_pTextures[slot]->LoadTexture(pMaterial->textures[uiTextureType]->path);
		m_pTextures[slot]->SetTextureSlot(slot);
	}
}

