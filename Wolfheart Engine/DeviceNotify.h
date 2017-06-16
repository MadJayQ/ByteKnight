#pragma once

namespace Graphics
{
	class IDeviceNotify
	{
	public:
		virtual void OnDeviceLost() = 0;
		virtual void OnDeviceRestored() = 0;
	};
}
