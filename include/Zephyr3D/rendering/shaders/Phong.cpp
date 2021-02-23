#include "Phong.h"
#include "../ICamera.h"
#include "../IRenderListener.h"
#include "../Texture.h"
#include "../../ZephyrEngine.h"

zephyr::rendering::Phong::Phong()
    : ShaderProgram(
        "Phong",
        ReadShaderFile("../../include/Zephyr3D/rendering/shaders/PhongVert.glsl"),
        ReadShaderFile("../../include/Zephyr3D/rendering/shaders/PhongFrag.glsl"),
        "") { }

void zephyr::rendering::Phong::Draw(const ICamera* camera) {
    glm::mat4 pv = camera->Projection() * camera->View();

    Uniform("directionalLight.direction", m_DirectionalLight.Direction);
    Uniform("directionalLight.ambient", m_DirectionalLight.Ambient);
    Uniform("directionalLight.diffuse", m_DirectionalLight.Diffuse);
    Uniform("directionalLight.specular", m_DirectionalLight.Specular);

    for (size_t i = 0; i < m_PointLights.size(); i++) {
        std::string index = std::to_string(i);
        Uniform("pointLights[" + index + "].position", m_PointLights[i].second.Position);
        Uniform("pointLights[" + index + "].constant", m_PointLights[i].second.Constant);
        Uniform("pointLights[" + index + "].linear", m_PointLights[i].second.Linear);
        Uniform("pointLights[" + index + "].quadratic", m_PointLights[i].second.Quadratic);
        Uniform("pointLights[" + index + "].ambient", m_PointLights[i].second.Ambient);
        Uniform("pointLights[" + index + "].diffuse", m_PointLights[i].second.Diffuse);
        Uniform("pointLights[" + index + "].specular", m_PointLights[i].second.Specular);
    }

    for (size_t i = 0; i < m_SpotLights.size(); i++) {
        std::string index = std::to_string(i);
        Uniform("spotLights[" + index + "].position", m_SpotLights[i].second.Position);
        Uniform("spotLights[" + index + "].direction", m_SpotLights[i].second.Direction);
        Uniform("spotLights[" + index + "].cutOff", m_SpotLights[i].second.CutOff);
        Uniform("spotLights[" + index + "].outerCutOff", m_SpotLights[i].second.OutterCutOff);
        Uniform("spotLights[" + index + "].constant", m_SpotLights[i].second.Constant);
        Uniform("spotLights[" + index + "].linear", m_SpotLights[i].second.Linear);
        Uniform("spotLights[" + index + "].quadratic", m_SpotLights[i].second.Quadratic);
        Uniform("spotLights[" + index + "].ambient", m_SpotLights[i].second.Ambient);
        Uniform("spotLights[" + index + "].diffuse", m_SpotLights[i].second.Diffuse);
        Uniform("spotLights[" + index + "].specular", m_SpotLights[i].second.Specular);
    }

    Uniform("pv", pv);
    Uniform("viewPosition", camera->LocalPosition());

    for (auto& drawable : m_Drawables) {
        auto user_pointer = static_cast<IRenderListener*>(drawable->UserPointer());
        user_pointer->OnDrawObject();
        drawable->Draw(*this);
    }
}

zephyr::rendering::Phong::DirectionalLight* zephyr::rendering::Phong::CreateDirectionalLight() {
    return &m_DirectionalLight;
}

void zephyr::rendering::Phong::DestroyDirectionalLight() {
    m_DirectionalLight.Direction = m_DirectionalLight.Ambient = m_DirectionalLight.Diffuse = m_DirectionalLight.Specular = glm::vec3(0.0f);
}

zephyr::rendering::Phong::PointLight* zephyr::rendering::Phong::CreatePointLight() {
    auto new_light = std::find_if(m_PointLights.begin(), m_PointLights.end(), [](const auto& pair) { return !pair.first; });

    if (new_light != m_PointLights.end()) {
        new_light->first = true;
        return &new_light->second;
    }

    return nullptr;
}

void zephyr::rendering::Phong::DestroyPointLight(const PointLight* light) {
    auto to_remove = std::remove_if(m_PointLights.begin(), m_PointLights.end(), [=](const auto& pair) { return &pair.second == light; });

    if (to_remove != m_PointLights.end()) {
        to_remove->first = false;
        to_remove->second.Position = to_remove->second.Ambient = to_remove->second.Diffuse = to_remove->second.Specular = glm::vec3(0.0f);
        to_remove->second.Constant = to_remove->second.Linear = to_remove->second.Quadratic = 0.0f;
    }
}

zephyr::rendering::Phong::SpotLight* zephyr::rendering::Phong::CreateSpotLight() {
    auto new_light = std::find_if(m_SpotLights.begin(), m_SpotLights.end(), [](const auto& pair) { return !pair.first; });

    if (new_light != m_SpotLights.end()) {
        new_light->first = true;
        return &new_light->second;
    }

    return nullptr;
}

void zephyr::rendering::Phong::DestroySpotLight(const SpotLight* light) {
    auto to_remove = std::remove_if(m_SpotLights.begin(), m_SpotLights.end(), [=](const auto& pair) { return &pair.second == light; });

    if (to_remove != m_SpotLights.end()) {
        to_remove->first = false;
        to_remove->second.Position = to_remove->second.Direction = to_remove->second.Ambient = to_remove->second.Diffuse = to_remove->second.Specular = glm::vec3(0.0f);
        to_remove->second.CutOff = to_remove->second.OutterCutOff = to_remove->second.Constant = to_remove->second.Linear = to_remove->second.Quadratic = 0.0f;
    }
}

void zephyr::rendering::Phong::Register(StaticModel* static_model) {
    assert(std::find(m_Drawables.begin(), m_Drawables.end(), static_model) == m_Drawables.end());
    m_Drawables.push_back(static_model);
}

void zephyr::rendering::Phong::Unregister(StaticModel* static_mocel) {
    auto to_erase = std::find(m_Drawables.begin(), m_Drawables.end(), static_mocel);
    if (to_erase != m_Drawables.end()) {
        m_Drawables.erase(to_erase);
    }
}


zephyr::rendering::Phong::StaticModel::StaticModel(const aiScene& raw_model, const std::string& directory) {
    m_StaticMeshes.reserve(raw_model.mNumMeshes);
    LoadNode(*raw_model.mRootNode, raw_model, directory, aiMatrix4x4());
}

void zephyr::rendering::Phong::StaticModel::Draw(const ShaderProgram& shader) const {
    for (auto it = m_StaticMeshes.begin(); it != m_StaticMeshes.end(); it++) {
        it->Draw(shader, m_Model);
    }
}

void zephyr::rendering::Phong::StaticModel::ModelMatrix(const glm::mat4& matrix_model) {
    m_Model = matrix_model;
}

glm::mat4 zephyr::rendering::Phong::StaticModel::ModelMatrix() const {
    return m_Model;
}

void zephyr::rendering::Phong::StaticModel::LoadNode(const aiNode& node, const aiScene& scene, const std::string& directory, const aiMatrix4x4& transform) {
    aiMatrix4x4 curr = transform * node.mTransformation;

    for (unsigned int i = 0; i < node.mNumMeshes; i++) {
        m_StaticMeshes.emplace_back(*scene.mMeshes[node.mMeshes[i]], scene, directory, curr);
    }

    for (unsigned int i = 0; i < node.mNumChildren; i++) {
        LoadNode(*node.mChildren[i], scene, directory, curr);
    }
}


zephyr::rendering::Phong::StaticModel::Mesh::Mesh(const aiMesh& mesh, const aiScene& scene, const std::string& directory, const aiMatrix4x4& transform)
    : m_Shininess(1.0f)
    , m_Transform(glm::transpose(glm::make_mat4(&transform.a1))) {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_Positions);
    glGenBuffers(1, &m_Normals);
    glGenBuffers(1, &m_TextureCoords);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_Positions);
    glBufferData(GL_ARRAY_BUFFER, mesh.mNumVertices * sizeof(aiVector3D), mesh.mVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, m_Normals);
    glBufferData(GL_ARRAY_BUFFER, mesh.mNumVertices * sizeof(aiVector3D), mesh.mNormals, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    // TODO multiple textures
    glBindBuffer(GL_ARRAY_BUFFER, m_TextureCoords);
    glBufferData(GL_ARRAY_BUFFER, mesh.mNumVertices * sizeof(aiVector3D), mesh.mTextureCoords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(aiVector3D), (void*)0);
    glEnableVertexAttribArray(2);

    std::vector<GLuint> indices;
    for (unsigned int i = 0; i < mesh.mNumFaces; i++) {
        const aiFace& face = mesh.mFaces[i];
        indices.insert(indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
    }
    m_IndicesCount = static_cast<GLsizei>(indices.size());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);

    if (mesh.mMaterialIndex >= 0) {
        const aiMaterial* material = scene.mMaterials[mesh.mMaterialIndex];

        if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString path;
            material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
            m_Diffuse = std::make_unique<Texture>(ZephyrEngine::Instance().Resources().LoadImage(directory + '/' + path.C_Str()), Texture::EType::Diffuse);
        }

        if (material->GetTextureCount(aiTextureType_SPECULAR) > 0) {
            aiString path;
            material->GetTexture(aiTextureType_SPECULAR, 0, &path);
            m_Specular = std::make_unique<Texture>(ZephyrEngine::Instance().Resources().LoadImage(directory + '/' + path.C_Str()), Texture::EType::Specular);
        }

        float strength = 1.0f;
        material->Get(AI_MATKEY_SHININESS, m_Shininess);
        material->Get(AI_MATKEY_SHININESS_STRENGTH, strength);
        m_Shininess *= strength;
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

zephyr::rendering::Phong::StaticModel::Mesh::Mesh(Mesh&& other) noexcept
    : m_VAO(std::exchange(other.m_VAO, 0))
    , m_Positions(std::exchange(other.m_Positions, 0))
    , m_Normals(std::exchange(other.m_Normals, 0))
    , m_TextureCoords(std::exchange(other.m_TextureCoords, 0))
    , m_EBO(std::exchange(other.m_EBO, 0))
    , m_Diffuse(std::move(other.m_Diffuse))
    , m_Specular(std::move(other.m_Specular)) {
    m_IndicesCount = other.m_IndicesCount;
    m_Shininess = other.m_Shininess;
}

zephyr::rendering::Phong::StaticModel::Mesh& zephyr::rendering::Phong::StaticModel::Mesh::operator=(Mesh&& other) noexcept {
    m_VAO = std::exchange(other.m_VAO, 0);
    m_Positions = std::exchange(other.m_Positions, 0);
    m_Normals = std::exchange(other.m_Normals, 0);
    m_TextureCoords = std::exchange(other.m_TextureCoords, 0);
    m_EBO = std::exchange(other.m_EBO, 0);
    m_Diffuse = std::move(other.m_Diffuse);
    m_Specular = std::move(other.m_Diffuse);
    m_IndicesCount = other.m_IndicesCount;
    m_Shininess = other.m_Shininess;

    return *this;
}

zephyr::rendering::Phong::StaticModel::Mesh::~Mesh() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_Positions);
    glDeleteBuffers(1, &m_Normals);
    glDeleteBuffers(1, &m_TextureCoords);
    glDeleteBuffers(1, &m_EBO);
}

void zephyr::rendering::Phong::StaticModel::Mesh::Draw(const ShaderProgram& shader, const glm::mat4& model) const {
    shader.Uniform("model", m_Transform * model);

    if (m_Diffuse) {
        glActiveTexture(GL_TEXTURE0);
        shader.Uniform("material.diffuse", 0);
        glBindTexture(GL_TEXTURE_2D, m_Diffuse->ID());
    }

    if (m_Specular) {
        glActiveTexture(GL_TEXTURE1);
        shader.Uniform("material.specular", 1);
        glBindTexture(GL_TEXTURE_2D, m_Specular->ID());
    }

    shader.Uniform("material.shininess", m_Shininess);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}