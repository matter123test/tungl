#include "Window.h"
#include "graphics/Renderer.h"
#include <iostream>
#include <glad/glad.h>
#include <spdlog/spdlog.h>


int main() {
	tg::Window window("test", 500, 500); window.center();
	tg::Renderer renderer(&window);

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

		renderer.swapBuffers();
	}

	return 0;
}