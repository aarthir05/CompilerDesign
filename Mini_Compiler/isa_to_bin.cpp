#include <iostream>
#include <fstream>
#include <bitset>
#include <regex>
#include <sstream>

using namespace std;

// Convert instruction to 24-bit binary format
string encodeInstruction(const string& instr, int param) {
    bitset<2> typeBits;       // 2-bit instruction type
    bitset<6> pointerBits(0); // 6-bit pointer value
    bitset<1> readBit(0);     // 1-bit read flag
    bitset<1> writeBit(0);    // 1-bit write flag
    bitset<9> rowBits(0);     // 9-bit memory row address
    bitset<5> reserved(0);    // 5-bit reserved field

    if (instr == "MEM READ") {
        typeBits = bitset<2>("00"); // PROG-type instruction
        readBit = 1;
        rowBits = bitset<9>(param);
    } 
    else if (instr == "MEM WRITE") {
        typeBits = bitset<2>("00"); // PROG-type instruction
        writeBit = 1;
        rowBits = bitset<9>(param);
    } 
    else if (instr == "EXE") {
        typeBits = bitset<2>("01"); // EXE instruction
        pointerBits = bitset<6>(param);
    } 
    else if (instr == "LOOP") {
        typeBits = bitset<2>("00"); // PROG instruction
        pointerBits = bitset<6>(param);
    } 
    else if (instr == "END LOOP") {
        typeBits = bitset<2>("10"); // END instruction
    } 
    else {
        cerr << "Unknown instruction: " << instr << endl;
        return "";
    }

    // Construct final 24-bit binary string
    stringstream binaryInstr;
    binaryInstr << typeBits << pointerBits << readBit << writeBit << rowBits << reserved;
    return binaryInstr.str();
}

void convertToTextISA(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error opening files!" << endl;
        return;
    }

    string line;
    regex memReadRegex(R"(MEM READ ROW (\d+))");
    regex memWriteRegex(R"(MEM WRITE ROW (\d+))");
    regex exeRegex(R"(EXE (\d+))");
    regex loopRegex(R"(LOOP (\d+))");
    regex endLoopRegex(R"(END LOOP)");

    while (getline(inFile, line)) {
        smatch match;
        string binaryInstr;

        if (regex_search(line, match, memReadRegex)) {
            binaryInstr = encodeInstruction("MEM READ", stoi(match[1]));
        } 
        else if (regex_search(line, match, memWriteRegex)) {
            binaryInstr = encodeInstruction("MEM WRITE", stoi(match[1]));
        } 
        else if (regex_search(line, match, exeRegex)) {
            binaryInstr = encodeInstruction("EXE", stoi(match[1]));
        } 
        else if (regex_search(line, match, loopRegex)) {
            binaryInstr = encodeInstruction("LOOP", stoi(match[1]));
        } 
        else if (regex_search(line, endLoopRegex)) {
            binaryInstr = encodeInstruction("END LOOP", 0);
        }

        if (!binaryInstr.empty()) {
            outFile << binaryInstr << endl;  // Write 24-bit instruction as text
        }
    }

    inFile.close();
    outFile.close();
    cout << "Conversion complete! Check " << outputFile << endl;
}

int main() {
    string inputISA = "output.isa";  // Input ISA file
    string outputText = "output_bin.txt"; // Output text file with 24-bit instructions
    convertToTextISA(inputISA, outputText);
    return 0;
}
