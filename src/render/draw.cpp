#include "render.h"
#include <vulkan/vulkan_structs.hpp>

void Render::draw() {
	uint32_t imageIndex = m_LogicalDevice.acquireNextImageKHR(m_Swapchain, UINT64_MAX, m_ImageAvailableSemaphore, nullptr).value;
	vk::CommandBuffer commandBuffer = m_CommandBuffers[imageIndex];
	vk::Image image = m_SwapchainImages[imageIndex];
	vk::Extent2D window = getWindowSize(m_Window);

	vk::CommandBufferBeginInfo beginInfo {};
	beginInfo.flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit;
	commandBuffer.begin(beginInfo);

	vk::ClearValue clearValue {};
	clearValue.color = { 1.0f, 0.0f, 1.0f, 1.0f };

	vk::RenderPassBeginInfo renderPassBeginInfo {};
	renderPassBeginInfo.renderPass = m_RenderPass;
	renderPassBeginInfo.renderArea.extent = window;
	renderPassBeginInfo.framebuffer = m_FrameBuffers[imageIndex];
	renderPassBeginInfo.clearValueCount = 1;
	renderPassBeginInfo.pClearValues = &clearValue;

	// vk::ImageMemoryBarrier imageMemoryBarrier {};
	// imageMemoryBarrier.image = image;
	// imageMemoryBarrier.oldLayout = vk::ImageLayout::eUndefined;
	// imageMemoryBarrier.newLayout = vk::ImageLayout::eTransferDstOptimal;
	// imageMemoryBarrier.srcAccessMask = vk::AccessFlagBits::eTransferRead;
	// imageMemoryBarrier.dstAccessMask = vk::AccessFlagBits::eTransferWrite;
	// imageMemoryBarrier.subresourceRange = vk::ImageSubresourceRange{
	// 	vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1
	// };

	// commandBuffer.pipelineBarrier(
	// 	vk::PipelineStageFlagBits::eTransfer,
	// 	vk::PipelineStageFlagBits::eTransfer,
	// 	vk::DependencyFlagBits::eByRegion,
	// 	nullptr, nullptr, imageMemoryBarrier
	// );

	commandBuffer.beginRenderPass(renderPassBeginInfo, vk::SubpassContents::eInline);

	vk::Rect2D scissor {};
	scissor.extent = window;

	vk::Viewport viewport {};
	viewport.width = window.width;
	viewport.height = window.height;
	viewport.maxDepth = 1.0f;

	commandBuffer.setScissor(0, 1, &scissor);
	commandBuffer.setViewport(0, 1, &viewport);
	commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, m_Pipeline);

	commandBuffer.draw(3, 1, 0, 0);

	// imageMemoryBarrier.oldLayout = vk::ImageLayout::eTransferDstOptimal;
	// imageMemoryBarrier.newLayout = vk::ImageLayout::ePresentSrcKHR;
	// imageMemoryBarrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
	// imageMemoryBarrier.dstAccessMask = vk::AccessFlagBits::eTransferRead;
	// commandBuffer.pipelineBarrier(
	// 	vk::PipelineStageFlagBits::eTransfer,
	// 	vk::PipelineStageFlagBits::eTransfer,
	// 	vk::DependencyFlagBits::eByRegion,
	// 	nullptr, nullptr, imageMemoryBarrier
	// );

	commandBuffer.endRenderPass();

	


	commandBuffer.end();

	vk::PipelineStageFlags waitStage = vk::PipelineStageFlagBits::eColorAttachmentOutput;

	vk::SubmitInfo submitInfo {};
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &m_SubmitSemaphore;
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &m_ImageAvailableSemaphore;
	submitInfo.pWaitDstStageMask = &waitStage;
	m_GraphicQueue.submit(submitInfo);

	vk::PresentInfoKHR presentInfo {};
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &m_Swapchain;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &m_SubmitSemaphore;
	m_GraphicQueue.presentKHR(presentInfo);

	m_LogicalDevice.waitIdle();
}