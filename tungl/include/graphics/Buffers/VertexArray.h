#pragma once
#include "Buffer.h"

namespace tg {
	class VertexArray : public Buffer {
	public:
		VertexArray();
		~VertexArray() override;

		// Inherited via Buffer
		void bind() const override;
		void unbind() const override;
	};
}