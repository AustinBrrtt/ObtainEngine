#ifndef VALIDATION_HPP
#define VALIDATION_HPP

#include <vulkan/vulkan.hpp>

namespace Obtain::Graphics::Vulkan {
	class Validation {
	public:
		static const std::vector<const char*> validationLayers;
		
		static bool useValidation();
		static vk::DebugUtilsMessengerEXT setupDebugMessenger(
			vk::UniqueInstance &instance,
			vk::DispatchLoaderDynamic loader
		);

	private:
		static bool areValidationLayersSupported();
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback( 
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData
		);
	};
}

#endif // VALIDATION_HPP