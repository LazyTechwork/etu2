#include "Loader.h"

const std::string loaderStates[] = {"⠙", "⠸", "⠴", "⠦", "⠇", "⠋"};

Loader::Loader(const std::wstring &description) {
    std::wcout << std::flush << description << ' ' << std::flush;

    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
    this->loaderPosition = csbiInfo.dwCursorPosition;
}

void Loader::loop() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration<double, std::milli>(currentTime - this->chrono).count() < 90)
        return;

    if (++(this->loaderState) > 5)
        this->loaderState = 0;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), this->loaderPosition);
    std::cout << loaderStates[this->loaderState];
    this->chrono = currentTime;
}

void Loader::stop() {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), this->loaderPosition);
    std::cout << SYMBOL_OK << std::endl;
}
