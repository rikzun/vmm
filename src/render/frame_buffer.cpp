#include "render.h"
#include "render_utils.h"

void Render::createFrameBuffers() {
    vk::Extent2D extent = getWindowSize(m_Window);

    vk::FramebufferCreateInfo createInfo {};
    createInfo.height = extent.height;
    createInfo.width = extent.width;
    createInfo.renderPass = m_RenderPass;
    createInfo.layers = 1;
    createInfo.attachmentCount = 1;

    for (auto& imageView : m_SwapchainImagesViews) {
        createInfo.pAttachments = &imageView;

        vk::Framebuffer frameBuffer = VK_ERROR_CHECK(
            m_LogicalDevice.createFramebuffer(createInfo),
            "createFramebuffer"
        );

        m_FrameBuffers.push_back(frameBuffer);
    }
}