#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <sstream>

std::string generateRandomString(size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result;
    result.resize(length);

    for (size_t i = 0; i < length; ++i) {
        result[i] = charset[rand() % (sizeof(charset) - 1)];
    }

    return result;
}

std::string generateHexValue() {
    std::stringstream ss;
    ss << std::hex << (rand() % 0xFFFFFFFF);
    return ss.str();
}

std::string generateJunkCode(int lines, size_t minNameLength, size_t maxNameLength) {
    std::string junkCode = "#include <ntifs.h>\n\n";

    for (int i = 0; i < lines; ++i) {
        std::string funcName = generateRandomString(minNameLength + rand() % (maxNameLength - minNameLength + 1));
        junkCode += "void " + funcName + "() {\n";
        junkCode += "    for (int i = 0; i < 1000; i++) {\n";
        junkCode += "        // Junk code\n";
        junkCode += "    }\n";
        junkCode += "}\n\n";
    }

    for (int i = 0; i < lines; ++i) {
        std::string varName = generateRandomString(minNameLength + rand() % (maxNameLength - minNameLength + 1));
        junkCode += "ULONG_PTR " + varName + " = 0x" + generateHexValue() + ";\n";
    }

    std::string structName = generateRandomString(minNameLength + rand() % (maxNameLength - minNameLength + 1));
    junkCode += "\ntypedef struct _" + structName + " {\n";
    for (int i = 0; i < lines; ++i) {
        std::string memberName = generateRandomString(minNameLength + rand() % (maxNameLength - minNameLength + 1));
        junkCode += "    ULONG_PTR " + memberName + ";\n";
    }
    junkCode += "} " + structName + ";\n\n";

    junkCode += structName + " " + generateRandomString(minNameLength + rand() % (maxNameLength - minNameLength + 1)) + " = {\n";
    for (int i = 0; i < lines; ++i) {
        junkCode += "    0x" + generateHexValue() + ",\n";
    }
    junkCode += "};\n";

    std::string namespaceName = "junkCode_" + generateRandomString(minNameLength + rand() % (maxNameLength - minNameLength + 1));
    std::string className = generateRandomString(minNameLength + rand() % (maxNameLength - minNameLength + 1));
    junkCode += "\nnamespace " + namespaceName + " {\n";
    junkCode += "    class " + className + " {\n";
    junkCode += "    public:\n";
    for (int i = 0; i < lines; ++i) {
        std::string methodName = generateRandomString(minNameLength + rand() % (maxNameLength - minNameLength + 1));
        junkCode += "        void " + methodName + "() {\n";
        std::string var1 = generateRandomString(minNameLength + rand() % (maxNameLength - minNameLength + 1));
        std::string var2 = generateRandomString(minNameLength + rand() % (maxNameLength - minNameLength + 1));
        std::string var3 = generateRandomString(minNameLength + rand() % (maxNameLength - minNameLength + 1));
        std::string var4 = generateRandomString(minNameLength + rand() % (maxNameLength - minNameLength + 1));
        std::string var5 = generateRandomString(minNameLength + rand() % (maxNameLength - minNameLength + 1));
        junkCode += "            int " + var1 + " = " + std::to_string(rand() % 100000) + ";\n";
        junkCode += "            int " + var2 + " = " + std::to_string(rand() % 100000) + ";\n";
        junkCode += "            int " + var3 + " = " + std::to_string(rand() % 100000) + ";\n";
        junkCode += "            int " + var4 + " = " + std::to_string(rand() % 100000) + ";\n";
        junkCode += "            int " + var5 + " = " + std::to_string(rand() % 100000) + ";\n";
        junkCode += "            if (" + var2 + " > " + std::to_string(rand() % 100000) + ")\n";
        junkCode += "                " + var3 + " = " + std::to_string(rand() % 100000) + ";\n";
        junkCode += "            else if (" + var4 + " <= " + std::to_string(rand() % 100000) + ")\n";
        junkCode += "                " + var5 + "++;\n";
        junkCode += "            else\n";
        int divisor = rand() % 100000 + 1;
        junkCode += "                " + var1 + " = (" + std::to_string(rand() % 100000) + " / " + std::to_string(divisor) + ");\n";
        junkCode += "        }\n";
    }
    junkCode += "    };\n";
    junkCode += "}\n";

    return junkCode;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int numFiles, numLines;
    size_t minNameLength, maxNameLength;
    std::cout << "Enter the number of files to generate: ";
    std::cin >> numFiles;
    std::cout << "Enter the number of lines of junk code per file: ";
    std::cin >> numLines;
    std::cout << "Enter the minimum length of names (functions, variables, etc.): ";
    std::cin >> minNameLength;
    std::cout << "Enter the maximum length of names (functions, variables, etc.): ";
    std::cin >> maxNameLength;

    for (int i = 0; i < numFiles; ++i) {
        std::string fileName = generateRandomString(8) + ".cpp";
        std::ofstream outFile(fileName);
        if (outFile.is_open()) {
            outFile << generateJunkCode(numLines, minNameLength, maxNameLength);
            outFile.close();
            std::cout << "Generated file: " << fileName << std::endl;
        }
        else {
            std::cerr << "Error creating file: " << fileName << std::endl;
        }
    }

    return 0;
}
