#include <catch2/catch.hpp>

#include <Zephyr3D/ZephyrEngine.h>
#include <Zephyr3D/core/math/glm2bt.h>
#include <Zephyr3D/core/Enum.h>
#include <Zephyr3D/core/debugging/Logger.h>
#include <bullet/btBulletCollisionCommon.h>

#include <iostream>
#include <windows.h>

SCENARIO("engine start up", "[ZephyrEngine]") {
    GIVEN("engine instance") {
        zephyr::ZephyrEngine::Instance();

        WHEN("engine is initialized") {
            zephyr::ZephyrEngine::Instance().Initialize(800u, 600u, "CoreTest");

            THEN("application context is created") {
                REQUIRE(glfwGetCurrentContext() != nullptr);
            }
        }
    }

    zephyr::ZephyrEngine::Instance().Destroy();
}

SCENARIO("engine shut down", "[ZephyrEngine]") {
    GIVEN("initialized engine instance") {
        zephyr::ZephyrEngine::Instance().Initialize(800u, 600u, "CoreTest");

        WHEN("engine is destroyed") {
            zephyr::ZephyrEngine::Instance().Destroy();

            THEN("application context is destroyed") {
                REQUIRE(glfwGetCurrentContext() == nullptr);
            }
        }
    }
}

SCENARIO("window response to os event", "[WindowManager]") {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    GIVEN("window with certain size") {
        zephyr::WindowManager window;
        window.Initialize(640u, 480u, "test");

        REQUIRE(window.Handle() != nullptr);
        REQUIRE(window.ShouldClose() == false);
        REQUIRE(window.Width() == 640u);
        REQUIRE(window.Height() == 480u);

        WHEN("window is streched out") {
            glfwSetWindowSize(window.Handle(), 800u, 600u);

            THEN("the size of window changes") {
                REQUIRE(window.Width() == 800u);
                REQUIRE(window.Height() == 600u);
            }
        }

        REQUIRE(window.ShouldClose() == false);

        WHEN("window is closed") {
            glfwSetWindowShouldClose(window.Handle(), 1);

            THEN("window should close") {
                REQUIRE(window.ShouldClose() == true);
            }
        }
    }

    glfwTerminate();
}

SCENARIO("input managers response to os events", "[InputManager]") {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    GLFWwindow* window = glfwCreateWindow(640u, 480u, "test", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    GIVEN("input manager") {
        zephyr::InputManager input;
        input.Initialize();

        WHEN("no key pressed") {

            THEN("input manager doesn't register any events") {
                REQUIRE(input.AnyKeyPressed() == false);
                REQUIRE(input.AnyKeyHold() == false);
                REQUIRE(input.AnyKeyReleased() == false);
            }
        }

        WHEN("left control is pressed") {
            keybd_event(VK_CONTROL, 0x9d, 0, 0);
            glfwPollEvents();
            input.Update(window);

            THEN("input manager registers key pressed") {
                REQUIRE(input.AnyKeyPressed() == true);
                REQUIRE(input.AnyKeyHold() == false);
                REQUIRE(input.AnyKeyReleased() == false);
                REQUIRE(input.KeyState(GLFW_KEY_LEFT_CONTROL) == zephyr::IInput::EKeyState::PRESSED);
            }
        }

        WHEN("left control is holded for two frames") {
            keybd_event(VK_CONTROL, 0x9d, 0, 0);
            glfwPollEvents();
            input.Update(window);
            keybd_event(VK_CONTROL, 0x9d, 0, 0);
            glfwPollEvents();
            input.Update(window);

            THEN("input manager registers key holded") {
                REQUIRE(input.AnyKeyPressed() == false);
                REQUIRE(input.AnyKeyHold() == true);
                REQUIRE(input.AnyKeyReleased() == false);
                REQUIRE(input.KeyState(GLFW_KEY_LEFT_CONTROL) == zephyr::IInput::EKeyState::HOLD);
            }
        }

        WHEN("left control is released") {
            keybd_event(VK_CONTROL, 0x9d, 0, 0);
            glfwPollEvents();
            input.Update(window);
            keybd_event(VK_CONTROL, 0x9d, KEYEVENTF_KEYUP, 0);
            glfwPollEvents();
            input.Update(window);

            THEN("input manager registers key released") {
                REQUIRE(input.AnyKeyPressed() == false);
                REQUIRE(input.AnyKeyHold() == false);
                REQUIRE(input.AnyKeyReleased() == true);
                REQUIRE(input.KeyState(GLFW_KEY_LEFT_CONTROL) == zephyr::IInput::EKeyState::RELEASED);
            }
        }
    }

    glfwTerminate();
}

SCENARIO("clock measures time between updates", "[Clock]") {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    GLFWwindow* window = glfwCreateWindow(640u, 480u, "test", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    GIVEN("clock") {
        zephyr::Clock clock;

        float lower_limit = static_cast<float>(glfwGetTime());
        clock.Initialize();

        WHEN("one second passed") {
            Sleep(1000);
            clock.Update();
            float upper_limit = static_cast<float>(glfwGetTime());

            THEN("clock is updated accordingly") {
                REQUIRE(clock.CurrentTime() >= 1.0f + lower_limit);
                REQUIRE(clock.CurrentTime() <= upper_limit);
                REQUIRE(clock.DeltaTime() >= 1.0f);
                REQUIRE(clock.DeltaTime() <= upper_limit - lower_limit);
            }
        }
    }

    glfwTerminate();
}

SCENARIO("vectors can be converted between glm and bullet types", "[glm2bt]") {
    GIVEN("glm::vec3(1.0f, 2.0f, 3.0f)") {
        glm::vec3 glm_v(1.0f, 2.0f, 3.0f);

        THEN("btVector3 is the same") {
            btVector3 bt_v = zephyr::Vector3(glm_v);

            REQUIRE(glm_v.x == bt_v.x());
            REQUIRE(glm_v.y == bt_v.y());
            REQUIRE(glm_v.z == bt_v.z());
        }
    }

    GIVEN("btVector3(3.0f, 2.0f, 1.0f)") {
        btVector3 bt_v(3.0f, 2.0f, 1.0f);

        THEN("glm::vec3 is the same") {
            glm::vec3 glm_v = zephyr::Vector3(bt_v);

            REQUIRE(bt_v.x() == glm_v.x);
            REQUIRE(bt_v.y() == glm_v.y);
            REQUIRE(bt_v.z() == glm_v.z);
        }
    }
}

SCENARIO("quaternions can be converted between glm and bullet types", "[glm2bt]") {
    GIVEN("glm::quat(1.0f, 2.0f, 3.0f, 4.0f)") {
        glm::quat glm_q(1.0f, 2.0f, 3.0f, 4.0f);

        THEN("btQuaternion is the same") {
            btQuaternion bt_q = zephyr::Quaternion(glm_q);

            REQUIRE(glm_q.x == bt_q.x());
            REQUIRE(glm_q.y == bt_q.y());
            REQUIRE(glm_q.z == bt_q.z());
            REQUIRE(glm_q.w == bt_q.w());
        }
    }

    GIVEN("btQuaternion(1.0f, 2.0f, 3.0f, 4.0f)") {
        btQuaternion bt_q(1.0f, 2.0f, 3.0f, 4.0f);

        THEN("glm::quat is the same") {
            glm::quat glm_q = zephyr::Quaternion(bt_q);

            REQUIRE(bt_q.x() == glm_q.x);
            REQUIRE(bt_q.y() == glm_q.y);
            REQUIRE(bt_q.z() == glm_q.z);
            REQUIRE(bt_q.w() == glm_q.w);
        }
    }
}

SCENARIO("bit operations can be performed on enums", "[Enum]") {
    GIVEN("enum") {
        enum TestEnum {
            first  = 1,
            second = 2,
            third  = 4
        };

        EnableBitMaskOperators<TestEnum>();

        THEN("bitwise NOT can be performed") {
            REQUIRE(~1 == ~TestEnum::first);
        }

        THEN("bitwise OR can be performed") {
            REQUIRE((2 | 4) == (TestEnum::second | TestEnum::third));
        }

        THEN("bitwise AND can be performed") {
            REQUIRE((2 & 4) == (TestEnum::second & TestEnum::third));
        }

        THEN("bitwise XOR can be performed") {
            REQUIRE((2 ^ 4) == (TestEnum::second ^ TestEnum::third));
        }
    }
}
