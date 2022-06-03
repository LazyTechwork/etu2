#include <iostream>
#include <cmath>
#include <conio.h>
#include <Windows.h>
#include "../cli_tools/ArgsParser.h"
#include "../writers/BitmapWriter.h"

int main(int argc, char *argv[]) {
    setlocale(0, "ru_RU.utf8");
    SetConsoleOutputCP(CP_UTF8);
    system("cls");

    auto args = ArgsParser(argc, argv);
    float low = 0;
    if (args.has("tr")) {
        try {
            low = std::stof(args.get("tr").c_str());
        } catch (std::invalid_argument exception) {
            std::cout << "-tr must be float in range 0-1" << std::endl;
            return -3;
        }

        if (low < 0.0 || low > 1.0) {
            std::cout << "-tr must be in range 0-1" << std::endl;
            return -1;
        }
    } else {
        std::cout << "Insufficient arguments (expected 2)" << std::endl;
        return -1;
    }

    FILE *file = fopen(argv[1], "rb");
    std::cout << argv[1];

    if (file == nullptr) {
        std::wcout << "Cannot open file at " << argv[1] << std::endl;
        return -1;
    }

    unsigned long analysis[16][16];
    unsigned long bytes_total = 0;
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            analysis[i][j] = 0;
        }
    }
    // x coordinate is for (byte) / 16
    // y coordinate is for (byte) - ((byte) / 16)

    // Setting seek cursor at the start of the file
    fseek(file, 0, SEEK_SET);

    uint8_t buf;
    int x, y;
    while (fread(&buf, sizeof(uint8_t), 1, file) == sizeof(uint8_t)) {
        x = buf - buf / 0x10;
        y = buf - (x * 0x10);
        ++analysis[x][y];
        ++bytes_total;
    }
    // Closing file
    fclose(file);

    const char hex_abc[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    HANDLE h;
    const uint8_t COLOR_WHITE = 15, COLOR_GREEN = 10;
    auto render = [&](bool process = false) {
        h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, COLOR_WHITE);

        std::cout << std::flush;
        system("cls");

        // Hotkey help
        std::cout << "Use 'n' for numeric style and 'p' for percentage style" << std::endl
                  << std::endl << "To exit press 'q'\n\n" << std::flush;

        // Table head row
        std::cout << " +";
        for (char b: hex_abc)
            std::cout << "\t0" << b;
        std::cout << std::endl;

        // Creating rows
        float processed;
        for (int i = 0; i < 16; ++i) {
            std::cout << " " << hex_abc[i] << "0";
            for (int j = 0; j < 16; ++j) {
                processed = (float) analysis[i][j] / bytes_total;
                SetConsoleTextAttribute(h, processed >= low ? COLOR_GREEN : COLOR_WHITE);
                std::cout << "\t" << (process ? round(processed * 100.0) / 100.0 : analysis[i][j]);
            }
            SetConsoleTextAttribute(h, COLOR_WHITE);
            std::cout << std::endl;
        }
    };

    int key = 'p';
    do {
        if (key != -1 && (key == 'p' || key == 'n'))
            render(key == 'p');
    } while ((key = _getch()) != 'q');

    return 0;
}
