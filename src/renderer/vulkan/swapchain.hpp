#ifndef SWAPCHAIN_HPP
#define SWAPCHAIN_HPP

#include <vector>
#include <vulkan/vulkan.hpp>

#include "queuefamilyindices.hpp"

namespace Obtain::Graphics::Vulkan {
	class Swapchain {
	public:
		Swapchain(
			vk::UniqueInstance &instance,
			vk::PhysicalDevice physicalDevice,
			vk::UniqueDevice &device,
			vk::SurfaceKHR surface,
			std::array<uint32_t, 2> windowSize,
			QueueFamilyIndices indices
		);
		~Swapchain();
		
		static void recreateSwapchain(Swapchain *swapchain);
		
	private:
		vk::UniqueSwapchainKHR swapchain;
		std::vector<vk::Image> images;
		std::vector<vk::ImageView> imageViews;
		vk::Format format;
		vk::Extent2D extent;
		
		vk::UniqueInstance &instance;
		vk::UniqueDevice &device;
		
		vk::SurfaceFormatKHR chooseSwapSurfaceFormat(
			const std::vector<vk::SurfaceFormatKHR>& availableFormats
		);
		vk::PresentModeKHR chooseSwapPresentMode(
			const std::vector<vk::PresentModeKHR> availablePresentModes
		);
		vk::Extent2D chooseSwapExtent(
			const vk::SurfaceCapabilitiesKHR& capabilities,
			std::array<uint32_t, 2> windowSize
		);
	};
}

#endif // SWAPCHAIN_HPP