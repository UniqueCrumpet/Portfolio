#pragma once

#include "../../Engine/Input/InputDevice.h"

class KeyboardAndMouseInputDevice : public InputDevice
{
public:
	KeyboardAndMouseInputDevice();
	~KeyboardAndMouseInputDevice();

	//Functions
	void ProcessInputs() override;

};

