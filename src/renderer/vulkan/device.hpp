#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <vulkan/vulkan.hpp>

#include "queuefamilyindices.hpp"
#include "swapchainsupportdetails.hpp"

namespace Obtain::Graphics::Vulkan {
	class Device {
		public:
			Device(vk::Instance instance, std::vector<char*> deviceExtensions,
				bool enableValidationLayers, std::vector<char*> validationLayers,
				vk::SurfaceKHR surface
			);
			~Device();
		private:
			vk::UniqueDevice device;
			vk::PhysicalDevice physicalDevice;
			
			vk::PhysicalDevice choosePhysicalDevice(vk::Instance instance, vk::SurfaceKHR surface);
			vk::SampleCountFlagBits getMaxUsableSampleCount();
			static bool checkDeviceExtensionSupport(vk::PhysicalDevice device);
			static int rateDeviceSuitability(vk::PhysicalDevice device, vk::SurfaceKHR surface);
	};
}

#endif // DEVICE_HPP