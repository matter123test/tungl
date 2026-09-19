#include "graphics/Model/Model.h"
#include <spdlog/spdlog.h>


namespace tg {
	Model::Model(std::string_view path) : m_path(path)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(
			path.data(),
			aiProcess_Triangulate | aiProcess_FlipUVs
		);

		if (scene == nullptr) {
			spdlog::error("Failed to load model file: {}", m_path);
			return;
		}

		Model::generate(scene);

		spdlog::info("Loaded model: {}", m_path);
	}

	Model::~Model()
	{
		spdlog::info("Unloaded model: {}", m_path);
	}

	void Model::debugDraw(const Shader& shader, const Camera3D& camera)
	{
		shader.use();

		shader.setMat4("projection", camera.getProjection());
		shader.setMat4("view", camera.getView());

		for (const auto& mesh : m_meshes) {
			shader.setMat4("model", glm::mat4(1.0f));
			mesh.bind();
			glDrawElements(GL_TRIANGLES, mesh.getIndicesCount(), GL_UNSIGNED_INT, (GLvoid*)0);
		}
	}

	void Model::generate(const aiScene* scene)
	{
		for (int meshN = 0; meshN < scene->mNumMeshes; meshN++) {
			aiMesh* mesh = scene->mMeshes[meshN];
			Model::processMesh(mesh);
		}
	}

	void Model::processMesh(const aiMesh* mesh)
	{
		std::vector<Vertex> vertices{};
		std::vector<GLuint> indices{};

		// Process vertices
		for (int vertexN = 0; vertexN < mesh->mNumVertices; vertexN++) {
			glm::vec3 position(
				mesh->mVertices[vertexN].x,
				mesh->mVertices[vertexN].y,
				mesh->mVertices[vertexN].z
			);

			glm::vec3 normal(
				mesh->mNormals[vertexN].x,
				mesh->mNormals[vertexN].y,
				mesh->mNormals[vertexN].z
			);

			glm::vec2 uv(
				mesh->mTextureCoords[0][vertexN].x,
				mesh->mTextureCoords[0][vertexN].y
			);

			Vertex vertex(position, normal, uv);
			vertices.push_back(vertex);
		}

		// Process indices
		for (int indicesN = 0; indicesN < mesh->mNumFaces; indicesN++) {
			indices.push_back(mesh->mFaces[indicesN].mIndices[0]);
			indices.push_back(mesh->mFaces[indicesN].mIndices[1]);
			indices.push_back(mesh->mFaces[indicesN].mIndices[2]);
		}

		Mesh genMesh(vertices, indices);
		m_meshes.push_back(std::move(genMesh));
	}
}