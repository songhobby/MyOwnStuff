#include <sstream>
#include <iostream>

int main() {
    unsigned char x;
    std::stringstream ss;
    std::stringstream s;
    s << "f";
    ss << std::hex <<s.rdbuf();
    ss >> x;
    // output it as a signed type
    std::cout << static_cast<unsigned int>(x) << std::endl;
}
