#include "gui/DebugUI.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <format>

namespace sandbox {
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

	void DebugUI::processKeyEvents(tg::Window* window)
	{
		if (window->input().isKeyPressed(tg::Key::I)) {
			m_showDebugInfo = !m_showDebugInfo;
		}
	}

	const char* items[] = {"Basic", "Texture UV", "Normals"};
	int currentItemIndex = 0;

	void DebugUI::draw(const DebugInfo& info) const {
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		if (m_showDebugInfo) {
			ImGui::SetNextWindowPos({ 0, 0 });
			ImGui::SetNextWindowSize({ 300, 200 });
			ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoDecoration);

			ImGui::Text(std::format("FPS: {}", info.fps).c_str());
			ImGui::Text(std::format("Frametime: {:.2f}ms", info.frametimeMs).c_str());
			ImGui::Text(std::format("Camera X: {:.1f} Y: {:.1f} Z: {:.1f}", info.cameraPos.x, info.cameraPos.y, info.cameraPos.z).c_str());
			ImGui::Text(std::format("Front X: {:.1f} Y: {:.1f} Z: {:.1f}", info.cameraFront.x, info.cameraFront.y, info.cameraFront.z).c_str());

			if (ImGui::Checkbox("wireframe ", &info.isWireframe)) {
				if (info.isWireframe) {
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				}
				else {
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				}
			}

			if (ImGui::SliderFloat("speed", &info.cameraSpeed, 0.0f, 100.0f)) {
				info.changeCameraSpeed(info.cameraSpeed);
			}

			if (ImGui::Combo("Shading", &currentItemIndex, items, 3)) {
				spdlog::info("Item: {}", items[currentItemIndex]);
			}

			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}