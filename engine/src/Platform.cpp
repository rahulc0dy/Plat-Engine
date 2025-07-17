#ifdef _WIN32
#include <Windows.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <cstdlib>

extern int main();

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    try {
        return main();
    }
    catch (const std::exception& e) {
        spdlog::critical("Unhandled exception in main(): {}", e.what());
        return EXIT_FAILURE;
    }
    catch (...) {
        spdlog::critical("Unhandled unknown exception in main()");
        return EXIT_FAILURE;
    }
}
#endif
