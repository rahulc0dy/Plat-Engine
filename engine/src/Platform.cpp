#ifdef _WIN32
#include <Windows.h>
#include <spdlog/spdlog.h>
#include <iostream>

extern int main();

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    try {
        return main();
    }
    catch (const std::exception& e) {
        spdlog::critical("Exception: {}", e.what());
        return EXIT_FAILURE;
    }
}
#endif
