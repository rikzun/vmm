#include "render.h"

Render::Render(SDL_Window* window, Logger& logger) : m_Logger(logger) { m_Window = window; }
Render::~Render() {}

void Render::init() {
    try {
        m_Logger.info("Vulkan init");

        Render::createInstance();
        Render::createDebugMessenger();
        Render::createSurface();
        Render::selectPhysicalDevice();
        Render::selectQueueFamilyIndexes();
        Render::createLogicalDevice();
        Render::createSwapchain();
        Render::selectSwapcianResources();
        Render::createSyncObjects();
        Render::createCommandPool();
        Render::createCommandBuffers();
        Render::createRenderPass();
        Render::createFrameBuffers();
        Render::createShaderModules();
        Render::createPipeline();
    } catch(const std::runtime_error& error) {
        m_Logger.error(error.what());
    }
}

vk::Extent2D getWindowSize(SDL_Window* window) {
    int width, height;
    SDL_GetWindowSizeInPixels(window, &width, &height);

    return vk::Extent2D {
        static_cast<uint32_t>(width),
        static_cast<uint32_t>(height)
    };
}