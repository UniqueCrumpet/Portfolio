#include "KeyboardAndMouseInputDevice.h"
#include "../..//Engine/Renderer/Sprite.h"

KeyboardAndMouseInputDevice::KeyboardAndMouseInputDevice()
{
}

KeyboardAndMouseInputDevice::~KeyboardAndMouseInputDevice()
{
}

void KeyboardAndMouseInputDevice::ProcessInputs()
{
	//Keyboard movements
	bool dpadLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	m_DigitalInputs[E_DigitalInput_DpadLeft].SetPressed(dpadLeft);

	bool dpadRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	m_DigitalInputs[E_DigitalInput_DpadRight].SetPressed(dpadRight);

	bool dpadUp = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	m_DigitalInputs[E_DigitalInput_DpadUp].SetPressed(dpadUp);

	bool dpadDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	m_DigitalInputs[E_DigitalInput_DpadDown].SetPressed(dpadDown);
		
}