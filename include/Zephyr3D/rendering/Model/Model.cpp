#include "Model.h"

zephyr::rendering::Model::Model(const RawModel& raw_model) {
    m_Meshes.reserve(raw_model.RawMeshes().size());

    for (auto it = raw_model.RawMeshes().begin(); it != raw_model.RawMeshes().end(); it++) {
        m_Meshes.emplace_back(*it);
    }
}
