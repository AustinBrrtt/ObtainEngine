//
// Created by austin on 5/2/19.
//

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vulkan/vulkan.hpp>
#include "device.hpp"

namespace Obtain::Graphics::Vulkan {
	class Image {
	public:
		Image(std::unique_ptr<Device> &device, uint32_t width, uint32_t height,
		      vk::Format format, vk::ImageTiling tiling, const vk::ImageAspectFlags &aspectMask,
		      const vk::ImageUsageFlags &usageFlags, const vk::MemoryPropertyFlags &propertyFlags);

		static Image createTextureImage(std::unique_ptr<Device> &device, vk::UniqueCommandPool &pool,
		                                const std::string &file);

		static Image createDepthImage(std::unique_ptr<Device> &device, const vk::Extent2D &extent,
		                              vk::UniqueCommandPool &pool);

		vk::UniqueImageView &getView();

		void transitionLayout(vk::UniqueCommandPool &commandPool, const vk::Queue &graphicsQueue,
		                      const vk::ImageLayout &oldLayout, const vk::ImageLayout &newLayout);

		void copyFromBuffer(vk::UniqueCommandPool &commandPool, const vk::Queue &graphicsQueue,
		                    Buffer &buffer, uint32_t width, uint32_t height);

		bool hasStencilComponent();

		vk::Format &getFormat();
	private:
		std::unique_ptr<Device> &device;
		vk::UniqueImage image;
		vk::UniqueDeviceMemory memory;
		vk::UniqueImageView view;
		vk::Format format;

		static const vk::AccessFlags accessMaskForLayout(const vk::ImageLayout &layout);
		static const vk::PipelineStageFlags pipelineStageForLayout(const vk::ImageLayout &layout);
		static const vk::ImageAspectFlags aspectMaskForLayout(const vk::ImageLayout &layout);

		static const vk::Format findSupportedFormat(std::unique_ptr<Device> &device,
		                                            const std::vector<vk::Format> &candidates, vk::ImageTiling tiling,
		                                            vk::FormatFeatureFlags features);
	};
}


#endif // IMAGE_HPP
