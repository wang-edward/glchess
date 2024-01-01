#pragma once

// System Headers
#include <assimp/importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

// Standard Headers
#include <map>
#include <memory>
#include <vector>

    // Vertex Format
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

class Mesh {
    // Private Member Containers
    std::vector<std::unique_ptr<Mesh>> mSubMeshes;
    std::vector<GLuint> mIndices;
    std::vector<Vertex> mVertices;
    std::map<GLuint, std::string> mTextures;

    // Private Member Variables
    GLuint mVertexArray;
    GLuint mVertexBuffer;
    GLuint mElementBuffer;

    // Private Member Functions
    void parse(const std::string & path, const aiNode *node, const aiScene *scene);
    void parse(const std::string & path, const aiMesh *mesh, const aiScene *scene);
    std::map<GLuint, std::string> process(const std::string &path,
                                          aiMaterial *material,
                                          aiTextureType type);

public:

    // Implement Default Constructor and Destructor
     Mesh() { glGenVertexArrays(1, & mVertexArray); }
    ~Mesh() { glDeleteVertexArrays(1, & mVertexArray); }

    // Disable Copying and Assignment
    Mesh(const Mesh &other) = delete;
    Mesh &operator=(const Mesh &other) = delete;
    // Implement Custom Constructors
    Mesh(std::string const & filename);
    Mesh(std::vector<Vertex> const & vertices,
         std::vector<GLuint> const & indices,
         std::map<GLuint, std::string> const & textures);

    // Public Member Functions
    void draw(GLuint shader);
};
