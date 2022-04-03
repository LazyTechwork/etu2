#pragma once

#include <Windows.h>
#include <string>
#include <ctime>
#include <chrono>
#include <iostream>

#define SYMBOL_OK "✓"

class Loader {
    COORD loaderPosition{};
    uint8_t loaderState = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> chrono = std::chrono::high_resolution_clock::now();

public:
    explicit Loader(const std::wstring &description);

    void loop();

    void stop();
};
