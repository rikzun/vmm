#include "render.h"

void Render::createSyncObjects() {
    m_ImageAvailableSemaphore = VK_ERROR_CHECK(
        m_LogicalDevice.createSemaphore(vk::SemaphoreCreateInfo {}),
        "m_ImageAvailableSemaphore"
    );

    m_SubmitSemaphore = VK_ERROR_CHECK(
        m_LogicalDevice.createSemaphore(vk::SemaphoreCreateInfo {}),
        "m_SubmitSemaphore"
    );

    m_RenderFinishedFence = VK_ERROR_CHECK(
        m_LogicalDevice.createFence(vk::FenceCreateInfo { vk::FenceCreateFlagBits::eSignaled }),
        "m_RenderFinishedFence"
    );
}