#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H

#include <vector>
#include <fstream>
#include <cstdint>

class LookupTable {
public:
    void generateLUT(const std::vector<uint32_t>& opcodes);
    void displayLUT(std::ofstream& outFile) const;

private:
    std::vector<uint32_t> lut;
};

#endif // LOOKUPTABLE_H
