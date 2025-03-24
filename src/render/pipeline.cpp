#include "render.h"
#include "render_utils.h"
#include <vulkan/vulkan_enums.hpp>
#include <vulkan/vulkan_structs.hpp>



void Render::createPipeline() {
    vk::PipelineLayoutCreateInfo layoutCreateInfo {};
    auto pipelineLayout = VK_ERROR_CHECK(
        m_LogicalDevice.createPipelineLayout(layoutCreateInfo),
        "createPipelineLayout"
    );





    vk::PipelineShaderStageCreateInfo vertexStage {};
    vertexStage.pName = "main";
    vertexStage.stage = vk::ShaderStageFlagBits::eVertex;
    vertexStage.module = m_Shaders[0];

    vk::PipelineShaderStageCreateInfo fragmentStage {};
    fragmentStage.pName = "main";
    fragmentStage.stage = vk::ShaderStageFlagBits::eFragment;
    fragmentStage.module = m_Shaders[1];

    vk::PipelineShaderStageCreateInfo stages[] = { vertexStage, fragmentStage };

    vk::PipelineVertexInputStateCreateInfo vertexCreateInfo {};

    vk::PipelineColorBlendAttachmentState colorAttachment {};
    colorAttachment.blendEnable = vk::False;
    colorAttachment.colorWriteMask =
        vk::ColorComponentFlagBits::eR |
        vk::ColorComponentFlagBits::eG |
        vk::ColorComponentFlagBits::eB |
        vk::ColorComponentFlagBits::eA;

    vk::PipelineColorBlendStateCreateInfo colorCreateInfo {};
    colorCreateInfo.attachmentCount = 1;
    colorCreateInfo.pAttachments = &colorAttachment;

    vk::PipelineRasterizationStateCreateInfo rasterizationStageCreateInfo {};
    rasterizationStageCreateInfo.frontFace = vk::FrontFace::eClockwise;
    rasterizationStageCreateInfo.cullMode = vk::CullModeFlagBits::eBack;
    rasterizationStageCreateInfo.polygonMode = vk::PolygonMode::eFill;
    rasterizationStageCreateInfo.lineWidth = 1.0f;

    vk::Rect2D scissor {};
    vk::Viewport viewport {};

    vk::PipelineViewportStateCreateInfo viewportCreateInfo {};
    viewportCreateInfo.scissorCount = 1;
    viewportCreateInfo.pScissors = &scissor;
    viewportCreateInfo.viewportCount = 1;
    viewportCreateInfo.pViewports = &viewport;

    vk::DynamicState dynamicStates[] {
        vk::DynamicState::eViewport,
        vk::DynamicState::eScissor
    };

    vk::PipelineDynamicStateCreateInfo dynamicStateCreateInfo {};
    dynamicStateCreateInfo.dynamicStateCount = 2;
    dynamicStateCreateInfo.pDynamicStates = dynamicStates;

    vk::PipelineMultisampleStateCreateInfo mulsisampleState {};
    mulsisampleState.rasterizationSamples = vk::SampleCountFlagBits::e1;

    vk::PipelineInputAssemblyStateCreateInfo assemblyState {};
    assemblyState.topology = vk::PrimitiveTopology::eTriangleList;

    vk::GraphicsPipelineCreateInfo createInfo;
    createInfo.pVertexInputState = &vertexCreateInfo;
    createInfo.pColorBlendState = &colorCreateInfo;
    createInfo.stageCount = 2;
    createInfo.pStages = stages;
    createInfo.pRasterizationState = &rasterizationStageCreateInfo;
    createInfo.layout = pipelineLayout;
    createInfo.renderPass = m_RenderPass;
    createInfo.pViewportState = &viewportCreateInfo;
    createInfo.pDynamicState = &dynamicStateCreateInfo;
    createInfo.pMultisampleState = &mulsisampleState;
    createInfo.pInputAssemblyState = &assemblyState;

    m_Pipeline = VK_ERROR_CHECK(
        m_LogicalDevice.createGraphicsPipeline(nullptr, createInfo),
        "createGraphicsPipeline"
    );
//     vk::PipelineShaderStageCreateInfo vertShaderStageInfo{};
//     vertShaderStageInfo.stage = vk::ShaderStageFlagBits::eVertex;
//     vertShaderStageInfo.module = m_Shaders[0];
//     vertShaderStageInfo.pName = "main";

//     vk::PipelineShaderStageCreateInfo fragShaderStageInfo{};
//     fragShaderStageInfo.stage = vk::ShaderStageFlagBits::eFragment;
//     fragShaderStageInfo.module = m_Shaders[1];
//     fragShaderStageInfo.pName = "main";

//     vk::PipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

//     vk::PipelineVertexInputStateCreateInfo vertexInputInfo{};

//     vk::PipelineInputAssemblyStateCreateInfo inputAssembly{};
//     inputAssembly.topology = vk::PrimitiveTopology::eTriangleList;
//     inputAssembly.primitiveRestartEnable = VK_FALSE;

//     vk::PipelineViewportStateCreateInfo viewportState{};
//     viewportState.viewportCount = 1;
//     viewportState.scissorCount = 1;

//     vk::PipelineRasterizationStateCreateInfo rasterizer{};
//     rasterizer.depthClampEnable = VK_FALSE;
//     rasterizer.rasterizerDiscardEnable = VK_FALSE;
//     rasterizer.polygonMode = vk::PolygonMode::eFill;
//     rasterizer.lineWidth = 1.0f;
//     rasterizer.cullMode = vk::CullModeFlagBits::eBack;
//     rasterizer.frontFace = vk::FrontFace::eCounterClockwise;
//     rasterizer.depthBiasEnable = VK_FALSE;

//     vk::PipelineMultisampleStateCreateInfo multisampling{};
//     multisampling.sampleShadingEnable = VK_FALSE;
//     multisampling.rasterizationSamples = vk::SampleCountFlagBits::e1;

//     vk::PipelineColorBlendAttachmentState colorBlendAttachment{};
//     colorBlendAttachment.colorWriteMask = vk::ColorComponentFlagBits::eR |
//                                           vk::ColorComponentFlagBits::eG |
//                                           vk::ColorComponentFlagBits::eB |
//                                           vk::ColorComponentFlagBits::eA;
//     colorBlendAttachment.blendEnable = VK_FALSE;

//     vk::PipelineColorBlendStateCreateInfo colorBlending{};
//     colorBlending.logicOpEnable = VK_FALSE;
//     colorBlending.attachmentCount = 1;
//     colorBlending.pAttachments = &colorBlendAttachment;
//     colorBlending.blendConstants[0] = 0.0f;
//     colorBlending.blendConstants[1] = 0.0f;
//     colorBlending.blendConstants[2] = 0.0f;
//     colorBlending.blendConstants[3] = 0.0f;

//     std::vector<vk::DynamicState> dynamicStates = {
//         vk::DynamicState::eViewport,
//         vk::DynamicState::eScissor
//     };

//     vk::PipelineDynamicStateCreateInfo dynamicStateInfo{};
//     dynamicStateInfo.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
//     dynamicStateInfo.pDynamicStates = dynamicStates.data();

//     vk::PipelineLayoutCreateInfo pipelineLayoutInfo{};
//     pipelineLayoutInfo.setLayoutCount = 0;
//     pipelineLayoutInfo.pushConstantRangeCount = 0;

//     if (m_LogicalDevice.createPipelineLayout(&pipelineLayoutInfo, nullptr, &m_PipelineLayout) != vk::Result::eSuccess) {
//         throw std::runtime_error("Failed to create pipeline layout!");
//     }

//     std::vector<vk::Format> b = {vk::Format::eB8G8R8A8Unorm};

//     vk::PipelineRenderingCreateInfoKHR renderingInfo{};
//     renderingInfo.colorAttachmentCount = 1;
//     renderingInfo.pColorAttachmentFormats = b.data();

//     vk::GraphicsPipelineCreateInfo pipelineInfo{};
//     pipelineInfo.stageCount = 2;
//     pipelineInfo.pStages = shaderStages;
//     pipelineInfo.pVertexInputState = &vertexInputInfo;
//     pipelineInfo.pInputAssemblyState = &inputAssembly;
//     pipelineInfo.pViewportState = &viewportState;
//     pipelineInfo.pRasterizationState = &rasterizer;
//     pipelineInfo.pMultisampleState = &multisampling;
//     pipelineInfo.pColorBlendState = &colorBlending;
//     pipelineInfo.pDynamicState = &dynamicStateInfo;
//     pipelineInfo.layout = m_PipelineLayout;
//     pipelineInfo.pNext = &renderingInfo;

//     if (m_LogicalDevice.createGraphicsPipelines(nullptr, 1, &pipelineInfo, nullptr, &m_Pipeline) != vk::Result::eSuccess) {
//         throw std::runtime_error("Failed to create graphics pipeline!");
//     }
}