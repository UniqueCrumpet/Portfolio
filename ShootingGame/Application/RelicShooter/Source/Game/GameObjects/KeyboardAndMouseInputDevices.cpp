#include "KeyboardAndMouseInputDevices.h"
#include "../..//Engine/Renderer/Sprite.h"

KeyboardAndMouseInputDevices::KeyboardAndMouseInputDevices()
{
}

KeyboardAndMouseInputDevices::~KeyboardAndMouseInputDevices()
{
}

void KeyboardAndMouseInputDevices::ProcessInputs()
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

	bool leftThumb = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
	m_DigitalInputs[E_DigitalInput_LeftThumb].SetPressed(leftThumb);

	bool a = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	m_DigitalInputs[E_DigitalInput_A].SetPressed(a);

	bool x = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
	m_DigitalInputs[E_DigitalInput_X].SetPressed(x);
		
}