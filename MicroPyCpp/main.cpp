#include <iostream>

#include "token.hpp"
#include "jsonReader.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    JsonReader reader = JsonReader(argv[1]);
    Root root = reader.readFile();
    // root.print();

    return 0;
}