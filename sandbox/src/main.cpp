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
#include "game/Camera/Camera.h"
#include "graphics/glDebug.h"
#include "graphics/Texture/Texture2D.h"
#include "graphics/Model/Model.h"


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

	sandbox::DebugInfo debugInfo{};

	sandbox::DebugUI debugUI(window.getHandle());

	tg::Shader normalsShader("shaders/shading/normals/vertex.glsl", "shaders/shading/normals/fragment.glsl");
	tg::Shader textureUVShader("shaders/shading/texture_uv/vertex.glsl", "shaders/shading/texture_uv/fragment.glsl");

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

	tg::Texture2D texture2DA("textures/feet_29.jpg");
	tg::Texture2D texture2DB("textures/ksp_flag.jpg");

	tg::Camera camera(glm::vec3(-3.7, 2.8, 3.1));
	camera.lookAt(glm::vec3(0.5, -0.4, -0.7));

	tg::Model cubeModel("models/cube.obj");
	//tg::Model cubeModel(R"(C:\Users\dust\Desktop\oldTungGl\resources\models\triple_t\Tung Tung Tung Sahur.glb)");

	glm::vec3 position(0.0, 0.0, -5);
	glm::mat4 model = glm::translate(glm::mat4(1.0), position);
	model = glm::scale(model, glm::vec3(1, 1, 1));

	std::chrono::steady_clock::time_point start, end;

	double frameCurrent = glfwGetTime();
	double frameLast = frameCurrent;
	double deltaTime = 0;

	double elapsedTime = 0.0;
	int frameCount = 0;

	std::function<void(float)> changeSpeedFunction = [&](float speed) {
		camera.m_MovementSpeed = speed;
	};

	debugInfo.cameraInfo.changeSpeedFunction = changeSpeedFunction;

	camera.updateProjection(window);

	while (window.isOpen()) {
		frameCurrent = glfwGetTime();
		deltaTime = frameCurrent - frameLast;
		frameLast = frameCurrent;

		window.input().process();

		while (std::optional event = window.input().pollEvent()) {
			if (auto windowResizeEvent = event->getIf<tg::Event::WindowResized>()) {
				window.setSize(windowResizeEvent->width, windowResizeEvent->height);
				renderer.resizeViewport();

				camera.updateProjection(window);
			}

			if (auto keyEvent = event->getIf<tg::Event::KeyPressed>()) {
				if (keyEvent->keycode == tg::Key::Escape) {
					window.close();
				}
			}

			if (auto mouseMoved = event->getIf<tg::Event::MouseMoved>()) {
				camera.processMouseMovedEvent(*mouseMoved);
			}
		}

		camera.processKeyPressedEvent(window.input(), deltaTime);

		debugUI.processKeyEvents(&window);

		if (window.input().isKeyPressed(tg::Key::M)) {
			cursorHidden = !cursorHidden;
			window.setCursorHidden(cursorHidden);
		}

		window.input().update();

		// Update here

		// Render here
		start = std::chrono::steady_clock::now();
		renderer.clear();

		basicShader.use();

		basicShader.setMat4("projection", camera.m_Projection);
		basicShader.setMat4("view", camera.m_View);
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

		cubeModel.debugDraw(textureUVShader, camera);

		end = std::chrono::steady_clock::now();

		// Fps counter
		frameCount++;
		elapsedTime += deltaTime;

		if (elapsedTime >= 0.5f) {
			//spdlog::info("fps: {}", frameCount / elapsedTime);
			debugInfo.fps = frameCount / elapsedTime;
			debugInfo.frametimeMs = std::chrono::duration<double, std::milli>(end - start).count();

			elapsedTime = 0;
			frameCount = 0;
		}

		// Update debug info
		debugInfo.cameraInfo.position = camera.m_Position;
		debugInfo.cameraInfo.direction = camera.m_Front;
		debugInfo.cameraInfo.yaw = camera.m_Yaw;
		debugInfo.cameraInfo.pitch = camera.m_Pitch;

		//camera.setSpeed(debugInfo.cameraSpeed);
		debugUI.draw(debugInfo);
		renderer.swapBuffers();
	}

	return 0;
}