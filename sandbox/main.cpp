#include <iostream>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <array>

#include "Window.h"
#include "graphics/Renderer.h"
#include "graphics/Shaders/Shader.h"
#include "graphics/Buffers/VertexArray.h"
#include "graphics/Buffers/VertexBuffer.h"
#include "graphics/Buffers/VertexBufferLayout.h"

int main() {
	tg::Window window("test", 500, 500); window.center();
	tg::Renderer renderer(&window);

	tg::Shader basicShader("shaders/vertex.glsl", "shaders/fragment.glsl");

	std::vector<GLfloat> vertices = {
		 0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f
	};

	tg::VertexArray vao;
	tg::VertexBuffer vbo(vertices);

	GLsizei stride = sizeof(GLfloat) * 6;
	tg::VertexBufferLayout layout({
		{ tg::VertexAttributeType::Float3, stride },
		{ tg::VertexAttributeType::Float3, stride }
	});

	vao.unbind();
	vbo.unbind();

	while (window.isOpen()) {
		window.input().process();

		while (std::optional event = window.input().pollEvent()) {
			if (auto windowResizeEvent = event->getIf<tg::Event::WindowResized>()) {
				window.setSize(windowResizeEvent->width, windowResizeEvent->height);
				renderer.resizeViewport();
			}

			if (auto keyEvent = event->getIf<tg::Event::KeyPressed>()) {
				if (keyEvent->keycode == tg::Key::Escape) {
					window.close();
				}
			}
		}

		window.input().update();

		// Update here

		// Render here
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		basicShader.use();

		vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		renderer.swapBuffers();
	}

	return 0;
}