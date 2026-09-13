#pragma once

#include "Camera.h"

namespace tg {
	class Camera2D : public Camera {
	public:
		Camera2D(Window* window, glm::vec2 position);
		~Camera2D() override = default;

		// Inherited via Camera
		void processEvents(double deltaTime) override;
		void updateProjection() override;

	private:
		// The view will only be updated via processEvents()
		void updateView() override;
	};
}