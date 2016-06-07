#pragma once
#include "Assets\Asset.h"

struct FBXMaterial;
class Texture;

class Material : public Asset
{
public:
	enum TextureSlots
	{
		DiffuseTexture = 0,
		AmbientTexture,
		GlowTexture,
		SpecularTexture,
		GlossTexture,
		NormalTexture,
		AlphaTexture,
		DisplacementTexture,

		LightMapTexture,
		PerlinTexture,
		TextureTypes_Count,



	};

	Material();
	~Material();

	template<typename T>
	void InitializeFromLoaderMaterial(T* pMaterial)
	{
		LoadIfExists(TextureSlots::DiffuseTexture,		pMaterial, TextureSlots::DiffuseTexture);
		LoadIfExists(TextureSlots::AmbientTexture,		pMaterial, TextureSlots::AmbientTexture);
		LoadIfExists(TextureSlots::GlowTexture,			pMaterial, TextureSlots::GlowTexture);
		LoadIfExists(TextureSlots::SpecularTexture,		pMaterial, TextureSlots::SpecularTexture);
		LoadIfExists(TextureSlots::GlossTexture,		pMaterial, TextureSlots::GlossTexture);
		LoadIfExists(TextureSlots::NormalTexture,		pMaterial, TextureSlots::NormalTexture);
		LoadIfExists(TextureSlots::AlphaTexture,		pMaterial, TextureSlots::AlphaTexture);
		LoadIfExists(TextureSlots::DisplacementTexture, pMaterial, TextureSlots::DisplacementTexture);
	}

	void LoadTexture(Texture* texture, TextureSlots slot);

private:

	void onBind() override;
	void onUnbind() override;

	void LoadIfExists(TextureSlots slot, FBXMaterial* pMaterial, unsigned int FBXTextureType);

	Texture* m_pTextures[TextureSlots::TextureTypes_Count];

};

