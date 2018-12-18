#include <iostream>
//#include "renderer/vulkan/vulkanrenderer.hpp"
#include "renderer/vulkan/vulkanrenderer.hpp"

// Temporary constants for testing
const std::string gameTitle = "The Game 2: Return of the Game";
const std::array<uint32_t, 3> version = {0, 0, 1};

int main() {
	auto renderer = new Obtain::Graphics::Vulkan::VulkanRenderer(gameTitle, version);
	
	try {
		renderer->run();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		delete(renderer);
		return EXIT_FAILURE;
	}
	
	delete(renderer);
	return EXIT_SUCCESS;
}
