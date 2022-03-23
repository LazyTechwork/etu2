#include <iostream>
#include <conio.h>
#include "../cli_tools/ArgsParser.h"

int main(int argc, char *argv[]) {
    auto args = ArgsParser(argc, argv);
    std::string filename;
    bool encode = false;
    if (args.has("encode")) {
        filename = args.get("encode");
        encode = true;
    } else if (args.has("e")) {
        filename = args.get("e");
        encode = true;
    } else if (args.has("decode")) {
        filename = args.get("decode");
    } else if (args.has("d")) {
        filename = args.get("d");
    } else {
        std::cout << "Insufficient arguments (expected 2)" << std::endl;
        return -1;
    }
    return 0;
}
