#ifdef _WIN32
#include <Windows.h>
#include <iostream>
#include <cstdlib>

extern int main();

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    try {
        return main();
    }
    catch (const std::exception& e) {
        return EXIT_FAILURE;
    }
    catch (...) {
        return EXIT_FAILURE;
    }
}
#endif
