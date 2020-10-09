#include "TestComponent.h"

#include <Zephyr3D/Engine.h>

void TestComponent::Initialize()
{
    RegisterUpdateCall();
}

void TestComponent::Update()
{
    if (zephyr::Engine::Instance().GetInput().AnyKeyPressed())
    {
        std::cout << "Send\n";
        out.Send(VocalClass());
    }
}
