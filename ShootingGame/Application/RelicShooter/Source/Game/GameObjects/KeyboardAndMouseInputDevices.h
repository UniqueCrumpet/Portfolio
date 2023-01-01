#pragma once

#include "../../Engine/Input/InputDevice.h"

class KeyboardAndMouseInputDevices : public InputDevice
{
public:
	KeyboardAndMouseInputDevices();
	~KeyboardAndMouseInputDevices();

	//Functions
	void ProcessInputs() override;

};

