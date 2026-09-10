#include <iostream>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <array>

#include "Window.h"
#include "graphics/Renderer.h"
#include "graphics/Shaders/Shader.h"
#include "graphics/Buffers/Buffers.h"
#include "gui/DebugUI.h"

#include <utility>

int main() {
	tg::Window window("tungl", 1200, 900); window.center();
	tg::Renderer renderer(&window);

	tg::DebugInfo debugInfo{};
	tg::DebugUI debugUI(window.getHandle());

	tg::Shader basicShader("shaders/vertex.glsl", "shaders/fragment.glsl");

	//std::vector<GLfloat> vertices = {
	//	 0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f,
	//	 0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
	//	-0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f
	//};

	struct Color {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};

	struct Vertex {
		glm::vec3 position;
		Color color;
	};

	std::vector<Vertex> vertices = {
		{{0.5f, 0.5f, 0.0f},  {255, 0, 0}},
		{{0.5f, -0.5f, 0.0f}, {0, 255, 0}},
		{{-0.5f, -0.5f, 0.0f}, {0, 0, 255}},
		{{-0.5f, 0.5f, 0.0f}, {255, 255, 0}},
	};

	std::vector<GLuint> indices = {
		0, 1, 2,
		2, 3, 0
	};

	tg::VertexArray vao;
	tg::VertexBuffer vbo(vertices);
	tg::IndexBuffer ibo(indices);

	GLsizei stride = sizeof(Vertex);
	/*tg::VertexBufferLayout layout({
		{ tg::VertexAttributeType::Float3, stride },
		{ tg::VertexAttributeType::Float3, stride }
	});*/

	tg::VertexBufferLayout layout({
		{ tg::VertexAttributeType::Float3, stride },
		{ tg::VertexAttributeType::UByte4, stride, true }
	});

	vao.unbind();
	vbo.unbind();
	ibo.unbind();

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Gray
	//glClearColor(1.0f, 1.0f, 1.0, 1.0f); // White

	glm::mat4 projection = glm::ortho(
		static_cast<float>(0),
		static_cast<float>(window.getWidth()), 
		static_cast<float>(window.getHeight()),
		static_cast<float>(0)
	);

	glm::mat4 view(1.0f);
	glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(50, 50, 0));
	model = glm::scale(model, glm::vec3(100, 100, 1));

	while (window.isOpen()) {
		window.input().process();

		while (std::optional event = window.input().pollEvent()) {
			if (auto windowResizeEvent = event->getIf<tg::Event::WindowResized>()) {
				window.setSize(windowResizeEvent->width, windowResizeEvent->height);
				renderer.resizeViewport();

				projection = glm::ortho(
					static_cast<float>(0),
					static_cast<float>(window.getWidth()),
					static_cast<float>(window.getHeight()),
					static_cast<float>(0)
				);
			}

			if (auto keyEvent = event->getIf<tg::Event::KeyPressed>()) {
				if (keyEvent->keycode == tg::Key::Escape) {
					window.close();
				}
			}
		}

		// Process input here
		debugUI.processKeyEvents(&window);

		window.input().update();

		// Update here

		// Render here
		glClear(GL_COLOR_BUFFER_BIT);

		basicShader.use();

		basicShader.setMat4("projection", projection);
		basicShader.setMat4("view", view);
		basicShader.setMat4("model", model);

		vao.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		debugUI.draw(debugInfo);

		renderer.swapBuffers();
	}

	return 0;
}