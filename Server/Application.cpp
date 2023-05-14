#include "Application.h"

Application::Application() = default;
Application::~Application() = default;

void Application::run() {
    server.run();
}