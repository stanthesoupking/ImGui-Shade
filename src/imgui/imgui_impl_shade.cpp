#include "imgui_impl_shade.hpp"

#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"

static Shade::ShadeApplication *app = nullptr;
static Shade::VulkanApplicationData *vkData = nullptr;

bool ImGui_ImplShade_Init(Shade::ShadeApplication *_app)
{
    app = _app;
    vkData = app->_getVulkanData();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForVulkan(app->_getGLFWWindow(), true);

    struct ImGui_ImplVulkan_InitInfo initInfo = {};
    initInfo.Instance = vkData->instance;
    initInfo.PhysicalDevice = vkData->physicalDevice;
    initInfo.Device = vkData->device;
    initInfo.QueueFamily = vkData->graphicsQueueFamilyIndex;
    initInfo.Queue = vkData->graphicsQueue;
    initInfo.PipelineCache = VK_NULL_HANDLE;
    initInfo.DescriptorPool = vkData->descriptorPool;                 // Note: may need to make custom descriptor pool for imgui
    initInfo.MinImageCount = vkData->swapChainFramebuffers.size(); // >= 2
    initInfo.ImageCount = vkData->swapChainFramebuffers.size();    // >= MinImageCount
    initInfo.MSAASamples = VK_SAMPLE_COUNT_1_BIT;                     // >= VK_SAMPLE_COUNT_1_BIT
    initInfo.Allocator = vkData->allocationCallbacks;
    initInfo.CheckVkResultFn = nullptr;

    ImGui_ImplVulkan_Init(&initInfo, vkData->renderPass);

    // Setup font
    VkCommandBuffer commandBuffer = app->_beginSingleTimeCommands();
    ImGui_ImplVulkan_CreateFontsTexture(commandBuffer);
    app->_endSingleTimeCommands(commandBuffer);

    return true;
}

void ImGui_ImplShade_Shutdown()
{
    ImGui_ImplVulkan_Shutdown();
}

void ImGui_ImplShade_NewFrame()
{
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
}

void ImGui_ImplShade_RenderDrawData(ImDrawData *drawData)
{
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), vkData->commandBuffers[vkData->currentImageIndex]);
}