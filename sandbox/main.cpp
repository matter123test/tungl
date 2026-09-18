#include <iostream>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <array>
#include <chrono>

#include "Window.h"
#include "graphics/Renderer.h"
#include "graphics/Shaders/Shader.h"
#include "graphics/Buffers/Buffers.h"
#include "gui/DebugUI.h"
#include "graphics/Mesh/Mesh.h"
#include "game/Camera/Camera3D.h"

#include <stb_image.h>
#include <string_view>
#include <filesystem>
#include <graphics/Buffers/Buffer.h>
#include <graphics/glDebug.h>

class Texture : public tg::Buffer {
public:
	Texture(std::string_view filePath) : m_path(filePath) {
		if (!std::filesystem::exists(filePath)) {
			spdlog::error("File: {} does not exist", filePath);
			return;
		}

		int nChannels;

		stbi_set_flip_vertically_on_load(true);
		m_data = stbi_load(filePath.data(), &m_width, &m_height, &nChannels, 0);

		if (!m_data) {
			spdlog::error("Failed to load image: {}", filePath);
			return;
		}

		glGenTextures(1, &m_id);
		spdlog::info("Created texture id: {} file: {}", m_id, m_path);
	}

	~Texture() {
		spdlog::info("Destroyed texture id: {} file: {}", m_id, m_path);

		glDeleteTextures(1, &m_id);
	}

protected:
	int m_width = 0;
	int m_height = 0;

	uint8_t* m_data = nullptr;

	std::string_view m_path;
};

class Texture2D : public Texture {
public:
	Texture2D(std::string_view filePath) : Texture(filePath) {
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, m_data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(m_data);

		Texture2D::unbind();
	}

	~Texture2D() = default;

	// Inherited via tg::Buffer
	void bind() const override
	{
		TG_ASSERT(m_id == 0);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void unbind() const override
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};

int main() {
#ifdef _DEBUG
	std::string title("tungl DEBUG");
#else // _DEBUG
	std::string title("tungl RELEASE");
#endif

	tg::Window window(title, 1200, 900); window.center();
	tg::Renderer renderer(&window);

	bool cursorHidden = true;
	bool isWireframe = false;

	window.setCursorAtCenter();
	window.setCursorHidden(cursorHidden);

	tg::DebugInfo debugInfo{};
	tg::DebugUI debugUI(window.getHandle());

	tg::Shader basicShader("shaders/textured/multi/vertex.glsl", "shaders/textured/multi/fragment.glsl");

	struct Color {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};

	std::vector<tg::Vertex> vertices = {
		{{0.5f, 0.5f, 0.0f},   {}, {1.0f, 1.0f}},
		{{0.5f, -0.5f, 0.0f},  {}, {1.0f, 0.0f}},
		{{-0.5f, -0.5f, 0.0f}, {}, {0.0f, 0.0f}},
		{{-0.5f, 0.5f, 0.0f},  {}, {0.0f, 1.0f}},
	};

	std::vector<GLuint> indices = {
		0, 1, 2,
		2, 3, 0
	};

	tg::Mesh mesh(vertices, indices);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Gray
	//glClearColor(1.0f, 1.0f, 1.0, 1.0f); // White

	Texture2D texture2DA("textures/feet_29.jpg");
	Texture2D texture2DB("textures/ksp_flag.jpg");

	tg::Camera3D camera(&window, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 1));

	glm::vec3 position(0.0, 0.0, -5);
	glm::mat4 model = glm::translate(glm::mat4(1.0), position);
	model = glm::scale(model, glm::vec3(1, 1, 1));

	std::chrono::steady_clock::time_point start, end;

	double frameCurrent = glfwGetTime();
	double frameLast = frameCurrent;
	double deltaTime = 0;

	double elapsedTime = 0.0;
	int frameCount = 0;

	while (window.isOpen()) {
		frameCurrent = glfwGetTime();
		deltaTime = frameCurrent - frameLast;
		frameLast = frameCurrent;

		window.input().process();

		while (std::optional event = window.input().pollEvent()) {
			if (auto windowResizeEvent = event->getIf<tg::Event::WindowResized>()) {
				window.setSize(windowResizeEvent->width, windowResizeEvent->height);
				renderer.resizeViewport();

				camera.updateProjection();
			}

			if (auto keyEvent = event->getIf<tg::Event::KeyPressed>()) {
				if (keyEvent->keycode == tg::Key::Escape) {
					window.close();
				}
			}
		}

		camera.processEvents(deltaTime);
		debugUI.processKeyEvents(&window);

		if (window.input().isKeyPressed(tg::Key::M)) {
			cursorHidden = !cursorHidden;
			window.setCursorHidden(cursorHidden);
		}

		window.input().update();

		// Update here

		// Render here
		start = std::chrono::steady_clock::now();
		glClear(GL_COLOR_BUFFER_BIT);

		basicShader.use();

		basicShader.setMat4("projection", camera.getProjection());
		basicShader.setMat4("view", camera.getView());
		basicShader.setMat4("model", model);

		basicShader.setInt("u_TextureSpecular1", 1);
		glActiveTexture(GL_TEXTURE1);
		texture2DA.bind();

		basicShader.setInt("u_TextureSpecular2", 2);
		glActiveTexture(GL_TEXTURE2);
		texture2DB.bind();
		
		mesh.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		end = std::chrono::steady_clock::now();

		// Fps counter
		frameCount++;
		elapsedTime += deltaTime;

		if (elapsedTime >= 0.5f) {
			//spdlog::info("fps: {}", frameCount / elapsedTime);
			debugInfo.fps = frameCount / elapsedTime;
			elapsedTime = 0;
			frameCount = 0;
		}

		// Update debug info
		debugInfo.frametimeMs = std::chrono::duration<double, std::milli>(end - start).count();
		debugInfo.cameraPos = camera.getPosition();
		debugInfo.cameraFront = camera.getFront();

		camera.setSpeed(debugInfo.cameraSpeed);
		debugUI.draw(debugInfo);
		renderer.swapBuffers();
	}

	return 0;
}