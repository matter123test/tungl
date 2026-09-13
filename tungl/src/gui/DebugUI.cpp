#include "gui/DebugUI.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <spdlog/spdlog.h>
#include <format>

namespace tg {
	DebugUI::DebugUI(GLFWwindow *window_handler) {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		
		ImGui::StyleColorsClassic();

		ImGui_ImplGlfw_InitForOpenGL(window_handler, true);
		ImGui_ImplOpenGL3_Init();

		spdlog::info("Created DebugUI");
	}

	DebugUI::~DebugUI() {
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		spdlog::info("Destroyed DebugUI");
	}

	void DebugUI::processKeyEvents(Window* window)
	{
		if (window->input().isKeyPressed(Key::I)) {
			m_showDebugInfo = !m_showDebugInfo;
		}
	}

	void DebugUI::draw(const DebugInfo& info) const {
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		if (m_showDebugInfo) {
			ImGui::SetNextWindowPos({ 0, 0 });
			ImGui::SetNextWindowSize({ 300, 200 });
			ImGui::Begin("Test", nullptr, ImGuiWindowFlags_NoDecoration);

			ImGui::Text(std::format("Frametime: {:.2f}ms", info.frametimeMs).c_str());
			ImGui::Text(std::format("Camera X: {:.1f} Y: {:.1f} Z: {:.1f}", info.cameraPos.x, info.cameraPos.y, info.cameraPos.z).c_str());
			ImGui::Text(std::format("Front X: {:.1f} Y: {:.1f} Z: {:.1f}", info.cameraFront.x, info.cameraFront.y, info.cameraFront.z).c_str());


			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}