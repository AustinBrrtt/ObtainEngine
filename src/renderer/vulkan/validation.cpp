#include "validation.hpp"

#include <iostream>

#ifdef NDEBUG
#define USE_VALIDATION_LAYERS false
#else
#define USE_VALIDATION_LAYERS true
#endif

namespace Obtain::Graphics::Vulkan {
	/******************************************
	 ***************** public *****************
	 ******************************************/
	const std::vector<const char*> Validation::validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};
	
	bool Validation::useValidation() {
		if (USE_VALIDATION_LAYERS && !areValidationLayersSupported()) {
			throw std::runtime_error("Validation layers not supported.");
		}
		
		return USE_VALIDATION_LAYERS;
	}
	
	vk::DebugUtilsMessengerEXT Validation::setupDebugMessenger(
		vk::UniqueInstance &instance,
		vk::DispatchLoaderDynamic loader
	) {
		vk::DebugUtilsMessengerCreateInfoEXT createInfo(
			vk::DebugUtilsMessengerCreateFlagsEXT(),
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
				vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
				vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
			vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
				vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
				vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
			debugCallback
		);
		return instance->createDebugUtilsMessengerEXT(createInfo, nullptr, loader);
	}

	/******************************************
	 ***************** private *****************
	 ******************************************/
	
	bool Validation::areValidationLayersSupported() {
		std::vector<vk::LayerProperties> availableLayers = vk::enumerateInstanceLayerProperties();
		
		for (const char* layerName : validationLayers) {
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}

			if (!layerFound) {
				return false;
			}
		}

		return true;
	}
	
	VKAPI_ATTR VkBool32 VKAPI_CALL Validation::debugCallback( 
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData
	) {
		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

		return VK_FALSE;
	}
}