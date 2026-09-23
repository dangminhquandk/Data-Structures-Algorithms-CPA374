#include <iostream>
#include <vector>
#include <string>

// Một hàm đơn giản để test stack memory
void systemCheck() {
    std::vector<std::string> components = {"CPU", "RAM", "SSD"};
    for (const auto& comp : components) {
        std::cout << "Checking: " << comp << "...\n";
    }
}

int main() {
    std::cout << "Hello, HUST Student!\n";
    std::cout << "Architecture: ARM64 (Apple Silicon)\n";
    
    systemCheck();

    return 0;
}