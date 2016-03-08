#include "Assets/Material.h"

#include "FBXFile.h"

Material::Material()
{


}

Material::~Material()
{

}

void Material::LoadIfExists(TextureSlots slot, FBXMaterial* pMaterial, unsigned int uiTextureType)
{
	if (pMaterial->textures[uiTextureType])
	{
		//m_pTextures[slot] = new Texture();
		//m_pTextures[slot]->LoadTexture(strAdditionalPath + pMaterial->textures[uiTextureType]->path);
		//m_pTextures[slot]->SetTextureSlot(slot);
	}
}

