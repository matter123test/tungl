#include <iostream>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <array>

#include "Window.h"
#include "graphics/Renderer.h"
#include "graphics/Shaders/Shader.h"

int main() {
	tg::Window window("test", 500, 500); window.center();
	tg::Renderer renderer(&window);

	tg::Shader basicShader("shaders/vertex.glsl", "shaders/fragment.glsl");

	std::array<GLfloat, 9> vertices = {
		 0.0f,  0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, nullptr);

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

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		renderer.swapBuffers();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	return 0;
}