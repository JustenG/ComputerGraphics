#include "Assets/Asset.h"

Asset::Asset()
{

}

void Asset::Bind()
{
	onBind();
}

void Asset::Unbind()
{
	onUnbind();
}
