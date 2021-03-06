#ifndef CubeSpawner_t
#define CubeSpawner_t

#include <Zephyr3D/cbs/Object.h>
#include <Zephyr3D/cbs/components/Component.h>
#include <Zephyr3D/cbs/components/Transform.h>
#include <Zephyr3D/cbs/connections/PropertyIn.h>

#include <vector>

class CubeSpawner : public zephyr::cbs::Component {
public:
    CubeSpawner(class zephyr::cbs::Object& object, ID_t id, float offset);

    void Initialize() override;
    void Update() override;

    zephyr::cbs::PropertyIn<zephyr::cbs::Transform*> TransfromIn{this};

private:
    float m_Offset;
    std::vector<zephyr::cbs::Object*> m_Objects;
};

#endif
