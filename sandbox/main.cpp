#include <iostream>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <array>

#include "Window.h"
#include "graphics/Renderer.h"
#include "graphics/Shaders/Shader.h"
#include "graphics/Buffers/Buffers.h"

int main() {
	tg::Window window("test", 500, 500); window.center();
	tg::Renderer renderer(&window);

	tg::Shader basicShader("shaders/vertex.glsl", "shaders/fragment.glsl");

	//std::vector<GLfloat> vertices = {
	//	 0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f,
	//	 0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
	//	-0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f
	//};

	std::vector<GLfloat> vertices = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	std::vector<GLuint> indices = {
		0, 1, 2,
		2, 3, 0
	};

	tg::VertexArray vao;
	tg::VertexBuffer vbo(vertices);
	tg::IndexBuffer ibo(indices);

	GLsizei stride = sizeof(GLfloat) * 3;
	/*tg::VertexBufferLayout layout({
		{ tg::VertexAttributeType::Float3, stride },
		{ tg::VertexAttributeType::Float3, stride }
	});*/

	tg::VertexBufferLayout layout({
		{ tg::VertexAttributeType::Float3, stride }
	});

	vao.unbind();
	vbo.unbind();
	ibo.unbind();

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Gray
	//glClearColor(1.0f, 1.0f, 1.0, 1.0f); // White

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
		glClear(GL_COLOR_BUFFER_BIT);
		basicShader.use();

		vao.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		renderer.swapBuffers();
	}

	return 0;
}