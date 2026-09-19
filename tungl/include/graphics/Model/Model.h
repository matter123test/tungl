#pragma once

#include <string_view>
#include <vector>
#include "graphics/Mesh/Mesh.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "graphics/Shaders/Shader.h"
#include "game/Camera/Camera3D.h"

namespace tg {
	class Model {
	public:
		Model(std::string_view path);
		~Model();

		// TODO: remove
		void debugDraw(const Shader& shader, const Camera3D &camera);

	private:
		std::string_view m_path;
		std::vector<Mesh> m_meshes;

		void generate(const aiScene* scene);
		void processMesh(const aiMesh* mesh);
	};
}