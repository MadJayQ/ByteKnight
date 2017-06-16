#pragma once

#include "DeviceNotify.h"

namespace Graphics
{
	class EngineDeviceMessageHandler : public IDeviceNotify
	{
	public:
		explicit EngineDeviceMessageHandler() {} //no implicit creation
		~EngineDeviceMessageHandler() {}

		virtual void OnDeviceLost() override;
		virtual void OnDeviceRestored() override;
	};
}
