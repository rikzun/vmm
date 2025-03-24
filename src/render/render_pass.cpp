#include "render.h"
#include "render_utils.h"

void Render::createRenderPass() {
    vk::AttachmentDescription attachment {};
    attachment.loadOp = vk::AttachmentLoadOp::eClear;
    attachment.storeOp = vk::AttachmentStoreOp::eStore;
    attachment.initialLayout = vk::ImageLayout::eUndefined; //maybe get from other func
    attachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;
    attachment.samples = vk::SampleCountFlagBits::e1;
    attachment.format = vk::Format::eB8G8R8A8Unorm; // store globally
    
    vk::AttachmentReference attachmentRef {};
    attachmentRef.attachment = 0;
    attachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal; //?

    vk::SubpassDescription subpass {};
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &attachmentRef;

    vk::RenderPassCreateInfo createInfo {};
    createInfo.attachmentCount = 1;
    createInfo.pAttachments = &attachment;
    createInfo.subpassCount = 1;
    createInfo.pSubpasses = &subpass;

    m_RenderPass = VK_ERROR_CHECK(
        m_LogicalDevice.createRenderPass(createInfo),
        "createRenderPass"
    );
}