#include "input.h"

#include <iostream>

#include "render/view/camera.h"
#include "game/application.h"
#include "game/voxels.h"
#include "util/config.h"

bool Input::mouseDown[16];
bool Input::keysDown[512];
float Input::lastMouseX;
float Input::lastMouseY;
bool Input::hideMouse = true;

void Input::keyCallback(GLFWwindow *win, int key, int scan, int act, int mod) {
    if (key >= 512) std::cout << "Invalid keycode: " << key << std::endl;

    if (act == GLFW_PRESS) {
        keysDown[key] = true;

        Input::fireKeyPress(key);
    }
    else if (act == GLFW_RELEASE) keysDown[key] = false;
}

void Input::clickCallback(GLFWwindow *win, int key, int act, int mod) {
    if (key >= 16) std::cout << "Invalid mouse code: " << key << std::endl;

    if (act == GLFW_PRESS) mouseDown[key] = true;
    else if (act == GLFW_RELEASE) mouseDown[key] = false;
}

void Input::mouseCallback(GLFWwindow *win, double x, double y) {
    float dx = (lastMouseX - (float) x) * Config::mouseSen;
    float dy = (lastMouseY - (float) y) * Config::mouseSen;

    lastMouseX = (float) x;
    lastMouseY = (float) y;

    Camera &cam = Voxels::get().camera();
    cam.rotate(dx, dy);
}

bool Input::isKeyDown(int keyId) {
    return keysDown[keyId];
}

bool Input::isMouseDown(int keyId) {
    return mouseDown[keyId];
}

void Input::fireKeyPress(int keyId) {
    if (keyId == GLFW_KEY_E) {
        hideMouse = !hideMouse;
        glfwSetInputMode(
            Application::window, GLFW_CURSOR,
            hideMouse ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL
        );
    }
}
