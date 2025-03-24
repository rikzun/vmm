#include "render.h"

void Render::selectQueueFamilyIndexes() {
    m_Logger.info("Select Queue Family indexes");

    std::vector<vk::QueueFamilyProperties> queueFamilies = m_PhysicalDevice.getQueueFamilyProperties();
    if (queueFamilies.empty()) throw std::runtime_error("Queue Family getting returned no results");

    uint32_t localQueueGraphicFamilyIndex = UINT32_MAX;
    uint32_t localQueuePresentFamilyIndex = UINT32_MAX;

	for (uint32_t i = 0; i < queueFamilies.size(); i++) {
		const vk::QueueFamilyProperties& queueFamily = queueFamilies[i];

		if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
            if (localQueueGraphicFamilyIndex == UINT32_MAX) {
                m_Logger.info(std::format("Graphic index {}", i));
                localQueueGraphicFamilyIndex = i;
            }

            if (localQueuePresentFamilyIndex == UINT32_MAX) {
                if (m_PhysicalDevice.getSurfaceSupportKHR(i, m_Surface).result == vk::Result::eSuccess) {
                    m_Logger.info(std::format("Present index {}", i));
                    localQueuePresentFamilyIndex = i;
                }
            }
		}
	}

    if (localQueueGraphicFamilyIndex == UINT32_MAX && localQueuePresentFamilyIndex == UINT32_MAX) {
        throw std::runtime_error("Suitable Queue Family was not found");
    }

    m_QueueGraphicFamilyIndex = localQueueGraphicFamilyIndex;
    
    m_QueuePresentFamilyIndex = localQueuePresentFamilyIndex == UINT32_MAX
        ? localQueueGraphicFamilyIndex
        : localQueuePresentFamilyIndex;
}