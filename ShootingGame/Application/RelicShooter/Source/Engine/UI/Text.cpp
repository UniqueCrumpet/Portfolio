#include "Text.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/Assets/AssetManager.h"
#include "../../Engine/Renderer/RenderManager.h"

Text::Text()
	:m_Initialised(false)
{

}

Text::~Text()
{
	C_SysContext::Get<RenderManager>()->RemoveRenderObject(this);
}

void Text::Initialise(const char* pfilename, const char* ptext, sf::Color pColor, sf::Text::Style style)
{
	const auto pAssetManager = C_SysContext::Get<AssetManager>();
	setFont(*pAssetManager->GetFont(pfilename));

	setString(ptext); //Set the Text
	setCharacterSize(75); // in pixels, not points!
	setFillColor(pColor);
	setStyle(style);

	C_SysContext::Get<RenderManager>()->AddRenderObject(this);
	m_Initialised = true;
}
