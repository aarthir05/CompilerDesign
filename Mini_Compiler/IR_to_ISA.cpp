#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

// Memory rows (cycling through these for reuse)
vector<int> memoryRows = {0, 4, 8, 12, 16};
int rowIndex = 0; // Keeps track of which row to use next

// Get next row and cycle back when needed
int getNextRow() {
    int row = memoryRows[rowIndex];
    rowIndex = (rowIndex + 1) % memoryRows.size(); // Cycle back after last row
    return row;
}

// Convert LLVM IR to custom ISA
void convertToISA(const string& irFile, const string& isaFile) {
    ifstream inFile(irFile);
    ofstream outFile(isaFile);
    
    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error opening files!" << endl;
        return;
    }

    string line;
    regex loadRegex(R"(load.*ptr\s(.*),)"); 
    regex storeRegex(R"(store.*ptr\s(.*),)");
    regex mulRegex(R"(mul)");
    regex addRegex(R"(add)");
    regex brRegex(R"(br\slabel\s%)");
    
    vector<string> isaInstructions;
    bool inLoop = false;
    int loopIterations = 4; // Default loop count

    while (getline(inFile, line)) {
        if (regex_search(line, loadRegex)) {
            int row = getNextRow();
            isaInstructions.push_back("MEM READ ROW " + to_string(row));
        } 
        else if (regex_search(line, storeRegex)) {
            int row = getNextRow();
            isaInstructions.push_back("MEM WRITE ROW " + to_string(row));
        } 
        else if (regex_search(line, mulRegex) || regex_search(line, addRegex)) {
            isaInstructions.push_back("EXE 16");
        }
        else if (regex_search(line, brRegex)) { // Detect loop branch
            if (!inLoop) {
                isaInstructions.push_back("LOOP " + to_string(loopIterations));
                inLoop = true;
            }
        }
        else if (line.find("!llvm.loop") != string::npos) { // End loop
            if (inLoop) {
                isaInstructions.push_back("END LOOP");
                inLoop = false;
            }
        }
    }

    for (const string& instr : isaInstructions) {
        outFile << instr << endl;
    }

    inFile.close();
    outFile.close();
    cout << "Conversion complete! Check " << isaFile << endl;
}

int main() {
    string irFile = "matmul.ll";  // Input LLVM IR file
    string isaFile = "output.isa"; // Output ISA file
    convertToISA(irFile, isaFile);
    return 0;
}
