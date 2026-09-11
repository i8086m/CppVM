#include <iostream>
#include <fstream>
#include <sstream>
#include "windows.h"
using namespace std;

string source = ""; /// file >> asm
string output = " "; /// asm << file
string token = ""; /// current opcode

string funcNames[256];
int funcArgs[256];
int funcCount = 0;

string labelNames[512];
string labelAddresses[512];
int labelCount = 0;

string modulesList[128];
int modulesCount = 0;

int i = 0;

///unsigned int MAXVAL = 2 << 32;
unsigned int MAXVAL = 0;

int errorCount = 0;

string toString(unsigned int from) {
    string to;
    stringstream itos;
    itos << from;
    itos >> to;
    return to;
}

string countTokens() {
    int tkns = 0;
    int tokenlen = 0;
    int i = 0;
    stringstream tknss;
    while (i < output.length()) {
        if (output[i] != (' ')) {
            tokenlen++;
        }
        else {
            if (tokenlen > 0) {
                tkns++;
            }
        }
        i++;
    }
    tknss << tkns;
    return tknss.str();
}

bool isFunction(string testToken) {
    bool wasDefined = false;
    for (int tc = 0; tc < funcCount; tc++) {
        if (funcNames[tc] == testToken) {
            wasDefined = true;
            break;
        }
    }
    return wasDefined;
}


bool replace(string& str, const string& from, const string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void replaceAll(string& str, const string& from, const string& to) {
    size_t pos = 0;
    while ((pos = str.find(from, pos)) != string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
}

void getToken() {
    token = "";
    while (i < source.length()) {
        if (source[i] != (' ') && source[i] != ('\t'))
            token += source[i];
        else if (token != "") {
            i++;
            return;
        }
        i++;
    }
}

void opcode() {
    int com = 0;
    if (token == "mov") {
        getToken();
        if (token == "a") {
            com = 1;
        } else if (token == "b") {
            com = 2;
        } else if (token == "c") {
            com = 3;
        } else if (isdigit(token[0])) {
            cout << "\nError: can't MOV to Integer\n";
            errorCount++;
        } else {
            cout << "\nError: can't MOV to Pointer\n";
            errorCount++;
            return;
        }
        getToken();
        if (token == "a") {
            if (com == 1) {
                cout << "Error: can't MOV Register to itself\n";
                errorCount++;
                return;
            }
            if (com == 2)
                output += "32 ";
            if (com == 3)
                output += "34 ";
        } else if (token == "b") {
            if (com == 1)
                output += "30 ";
            if (com == 2) {
                cout << "Error: can't MOV Register to itself\n";
                errorCount++;
                return;
            }
            if (com == 3)
                output += "35 ";
        } else if (token == "c") {
            if (com == 1)
                output += "31 ";
            if (com == 2)
                output += "33 ";
            if (com == 3) {
                cout << "Error: can't MOV Register to itself\n";
                errorCount++;
                return;
            }
        } else if (isdigit(token[0])) {
            if (com == 1)
                output += "43 " + token + " ";
            if (com == 2)
                output += "44 " + token + " ";
            if (com == 3)
                output += "45 " + token + " ";
        } else {
            if (com == 1)
                output += "43 " + token + " ";
            if (com == 2)
                output += "44 " + token + " ";
            if (com == 3)
                output += "45 " + token + " ";
        }
    }
    else if (token == "wipe") {
        output += "160 ";
    }
    else if (token == "push") {
        getToken();
        if (token == "a") {
            output += "161 ";
        } else if (token == "b") {
            output += "162 ";
        } else if (token == "c") {
            output += "163 ";
        } else {
            output += "167 " + token + " ";
        }

    }
    else if (token == "pop") {
        getToken();
        if (token == "a") {
            output += "164 ";
        } else if (token == "b") {
            output += "165 ";
        } else if (token == "c") {
            output += "166 ";
        } else {
            cout << "Error: POP can be used only on Register\n";
            errorCount++;
            return;
        }
    }
    else if (token == "kbhit") {
        output += "170 ";
    }
    else if (token == "ret") {
        output += "255 ";
    }
    else if (token == "put") {
        output += "10 ";
    }
    else if (token == "endl") {
        output += "13 ";
    }
    else if (token == "inc") {
        getToken();
        if (token == "a") {
            output += "1 ";
        } else if (token == "b") {
            output += "2 ";
        } else if (token == "c") {
            output += "3 ";
        } else {
            cout << "Error: INC can be used only on Register\n";
            errorCount++;
        }
    }
    else if (token == "dec") {
        getToken();
        if (token == "a") {
            output += "4 ";
        } else if (token == "b") {
            output += "5 ";
        } else if (token == "c") {
            output += "6 ";
        } else {
            cout << "Error: DEC can be used only on Register\n";
            errorCount++;
            return;
        }
    }
    else if (token == "cmp") {
        getToken();
        if (isdigit(token[0])) {
            output += "7 " + token + " ";
        } else if (token == "b") {
            output += "8 ";
        } else if (token == "c") {
            output += "9 ";
        } else {
            cout << "Warning: CMP with Label\n";
            output += "7 " + token + " ";
        }
    }
    else if (token == "jnz") {
        getToken();
        if (isdigit(token[0])) {
            output += "22 " + token + " ";
        } else if (token == "c") {
            output += "27 ";
        } else {
            output += "22 " + token + " ";
        }
    }
    else if (token == "nop") {
        output += "0 ";
    }
    else if (token == "puts") {
        output += "11 ";
    }
    else if (token == "putc") {
        output += "12 ";
    }
    else if (token == "cin") {
        output += "14 ";
    }
    else if (token == "getkey") {
        output += "15 ";
    }
    else if (token == "cls") {
        output += "16 ";
    }
    else if (token == "exch") {
        output += "18 ";
    }
    else if (token == "inf") {
        output += "250 ";
    }
    else if (token == "debug") {
        output += "251 ";
    }
    else if (token == "nodebug") {
        output += "252 ";
    }
    else if (token == "call") {
        getToken();
        if (token == "c")
            output += "17 ";
        else if (isdigit(token[0]))
            output += "19 " + token + " ";
        else {
            output += "19 " + token + " ";
        }
    }
    else if (token == "rjmp") {
        getToken();
        if (isdigit(token[0])) {
            output += "190 " + token + " ";
        } else {
            cout << "\nError: RJMP can't be used on Int\n";
            errorCount++;
            return;
        }
    }
    else if (token == "rjz") {
        getToken();
        if (isdigit(token[0])) {
            output += "191 " + token + " ";
        } else {
            cout << "\nError: RJZ can't be used on Int\n";
            errorCount++;
            return;
        }
    }
    else if (token == "rjnz") {
        getToken();
        if (isdigit(token[0])) {
            output += "192 " + token + " ";
        } else {
            cout << "\nError: RJNZ can't be used on Int\n";
            errorCount++;
            return;
        }
    }
    else if (token == "rjn") {
        getToken();
        if (isdigit(token[0])) {
            output += "193 " + token + " ";
        } else {
            cout << "\nError: RJN can't be used on Int\n";
            errorCount++;
            return;
        }
    }
    else if (token == "rjp") {
        getToken();
        if (isdigit(token[0])) {
            output += "194 " + token + " ";
        } else {
            cout << "\nError: RJP can't be used on Int\n";
            errorCount++;
            return;
        }
    }
    else if (token == "jmp") {
        getToken();
        if (isdigit(token[0])) {
            output += "20 " + token + " ";
        } else if (token == "c") {
            output += "25 ";
        } else if (token == "a" || token == "b") {
            cout << "\nError: JMP can't be used on a or b\n";
            errorCount++;
            return;
        } else {
            output += "20 " + token + " ";
        }
    }
    else if (token == "jz") {
        getToken();
        if (isdigit(token[0])) {
            output += "21 " + token + " ";
        } else if (token == "c") {
            output += "26 ";
        } else if (token == "a" || token == "b") {
            cout << "\nError: JZ can't be used on a or b\n";
            errorCount++;
            return;
        } else {
            output += "21 " + token + " ";
        }
    }
    else if (token == "jn") {
        getToken();
        if (isdigit(token[0])) {
            output += "23 " + token + " ";
        } else if (token == "c") {
            output += "28 ";
        } else if (token == "a" || token == "b") {
            cout << "\nError: JN can't be used on a or b\n";
            errorCount++;
            return;
        } else {
            output += "23 " + token + " ";
        }
    }
    else if (token == "jp") {
        getToken();
        if (isdigit(token[0])) {
            output += "24 " + token + " ";
        } else if (token == "c") {
            output += "29 ";
        } else if (token == "a" || token == "b") {
            cout << "\nError: JP can't be used on a or b\n";
            errorCount++;
            return;
        } else {
            output += "24 " + token + " ";
        }
    }
    else if (token == "pushif") {
        getToken();
        if (isdigit(token[0])) {
            cout << "\nError: PUSHIF can't be used on integer\n";
            errorCount++;
            return;
        } else if (token == "z") {
            output += "180 ";
        } else if (token == "nz") {
            output += "181 ";
        } else if (token == "n") {
            output += "182 ";
        } else if (token == "p") {
            output += "183 ";
        } else {
            cout << "\nError: PUSHIF can be used only on FLAGS\n";
            errorCount++;
            return;
        }
    }
    else if (token == "ld") {
        getToken();
        if (token == "a") {
            com = 1;
        } else if (token == "b") {
            com = 2;
        } else if (token == "c") {
            com = 3;
        } else if (isdigit(token[0])) {
            cout << "\nError: can't LD to Integer\n";
            errorCount++;
            return;
        } else {
            cout << "\nError: can't LD to Pointer\n";
            errorCount++;
            return;
        }
        getToken();
        if (token == "a") {
            if (com == 1)
                output += "60 ";
            if (com == 2)
                output += "63 ";
            if (com == 3)
                output += "66 ";
        } else if (token == "b") {
            if (com == 1)
                output += "61 ";
            if (com == 2)
                output += "64 ";
            if (com == 3)
                output += "67 ";
        } else if (token == "c") {
            if (com == 1)
                output += "62 ";
            if (com == 2)
                output += "65 ";
            if (com == 3)
                output += "68 ";
        } else if (isdigit(token[0])) {
            if (com == 1)
                output += "50 " + token + " ";
            if (com == 2)
                output += "51 " + token + " ";
            if (com == 3)
                output += "52 " + token + " ";
        } else {
            if (com == 1)
                output += "50 " + token + " ";
            if (com == 2)
                output += "51 " + token + " ";
            if (com == 3)
                output += "52 " + token + " ";
        }
    }
    else if (token == "wr") {
        getToken();
        if (token == "a") {
            com = 1;
        } else if (token == "b") {
            com = 2;
        } else if (token == "c") {
            com = 3;
        } else if (isdigit(token[0])) {
            cout << "\nError: can't WR to Integer\n";
            errorCount++;
            return;
        } else {
            cout << "\nError: can't LD to Pointer\n";
            errorCount++;
            return;
        }
        getToken();
        if (token == "a") {
            if (com == 1)
                output += "70 ";
            if (com == 2)
                output += "73 ";
            if (com == 3)
                output += "76 ";
        } else if (token == "b") {
            if (com == 1)
                output += "71 ";
            if (com == 2)
                output += "74 ";
            if (com == 3)
                output += "77 ";
        } else if (token == "c") {
            if (com == 1)
                output += "72 ";
            if (com == 2)
                output += "75 ";
            if (com == 3)
                output += "78 ";
        } else if (isdigit(token[0])) {
            if (com == 1)
                output += "53 " + token + " ";
            if (com == 2)
                output += "54 " + token + " ";
            if (com == 3)
                output += "55 " + token + " ";
        } else {
            if (com == 1)
                output += "53 " + token + " ";
            if (com == 2)
                output += "54 " + token + " ";
            if (com == 3)
                output += "55 " + token + " ";
        }
    }
    else if (token == "add") {
        getToken();
        if (token == "a") {
            com = 1;
        } else if (token == "b") {
            com = 2;
        } else if (token == "c") {
            com = 3;
        } else if (isdigit(token[0])) {
            cout << "\nError: can't ADD to Integer\n";
            errorCount++;
            return;
        } else {
            cout << "\nError: can't ADD to Pointer\n";
            errorCount++;
            return;
        }
        getToken();
        if (token == "a") {
            if (com == 1) {
                cout << "Error: can't ADD Register to itself\n";
                errorCount++;
                return;
            }
            if (com == 2)
                output += "112 ";
            if (com == 3)
                output += "114 ";
        } else if (token == "b") {
            if (com == 1)
                output += "110 ";
            if (com == 2) {
                cout << "Error: can't ADD Register to itself\n";
                errorCount++;
                return;
            }
            if (com == 3)
                output += "115 ";
        } else if (token == "c") {
            if (com == 1)
                output += "111 ";
            if (com == 2)
                output += "113 ";
            if (com == 3) {
                cout << "Error: can't ADD Register to itself\n";
                errorCount++;
                return;
            }
        } else if (isdigit(token[0])) {
            if (com == 1)
                output += "116 " + token + " ";
            if (com == 2)
                output += "117 " + token + " ";
            if (com == 3)
                output += "118 " + token + " ";
        } else {
            if (com == 1)
                output += "116 " + token + " ";
            if (com == 2)
                output += "117 " + token + " ";
            if (com == 3)
                output += "118 " + token + " ";
        }
    }
    else if (token == "sub") {
        getToken();
        if (token == "a") {
            com = 1;
        } else if (token == "b") {
            com = 2;
        } else if (token == "c") {
            com = 3;
        } else if (isdigit(token[0])) {
            cout << "\nError: can't SUB to Integer\n";
            errorCount++;
            return;
        } else {
            cout << "\nError: can't SUB to Pointer\n";
            errorCount++;
            return;
        }
        getToken();
        if (token == "a") {
            if (com == 1) {
                cout << "Error: can't SUB Register to itself\n";
                errorCount++;
                return;
            }
            if (com == 2)
                output += "122 ";
            if (com == 3)
                output += "124 ";
        } else if (token == "b") {
            if (com == 1)
                output += "120 ";
            if (com == 2) {
                cout << "Error: can't SUB Register to itself\n";
                errorCount++;
                return;
            }
            if (com == 3)
                output += "125 ";
        } else if (token == "c") {
            if (com == 1)
                output += "121 ";
            if (com == 2)
                output += "123 ";
            if (com == 3) {
                cout << "Error: can't SUB Register to itself\n";
                errorCount++;
                return;
            }
        } else if (isdigit(token[0])) {
            if (com == 1)
                output += "126 " + token + " ";
            if (com == 2)
                output += "127 " + token + " ";
            if (com == 3)
                output += "128 " + token + " ";
        } else {
            if (com == 1)
                output += "126 " + token + " ";
            if (com == 2)
                output += "127 " + token + " ";
            if (com == 3)
                output += "128 " + token + " ";
        }
    }
    else if (token == "mul") {
        getToken();
        if (token == "a") {
            com = 1;
        } else if (token == "b") {
            com = 2;
        } else if (token == "c") {
            com = 3;
        } else if (isdigit(token[0])) {
            cout << "\nError: can't MUL to Integer\n";
            errorCount++;
            return;
        } else {
            cout << "\nError: can't MUL to Pointer\n";
            errorCount++;
            return;
        }
        getToken();
        if (token == "a") {
            if (com == 1) {
                cout << "Error: can't MUL Register to itself\n";
                errorCount++;
                return;
            }
            if (com == 2)
                output += "132 ";
            if (com == 3)
                output += "134 ";
        } else if (token == "b") {
            if (com == 1)
                output += "130 ";
            if (com == 2) {
                cout << "Error: can't MUL Register to itself\n";
                errorCount++;
                return;
            }
            if (com == 3)
                output += "135 ";
        } else if (token == "c") {
            if (com == 1)
                output += "131 ";
            if (com == 2)
                output += "133 ";
            if (com == 3) {
                cout << "Error: can't MUL Register to itself\n";
                errorCount++;
                return;
            }
        } else if (isdigit(token[0])) {
            if (com == 1)
                output += "136 " + token + " ";
            if (com == 2)
                output += "137 " + token + " ";
            if (com == 3)
                output += "138 " + token + " ";
        } else {
            if (com == 1)
                output += "136 " + token + " ";
            if (com == 2)
                output += "137 " + token + " ";
            if (com == 3)
                output += "138 " + token + " ";
        }
    }
    else if (token == "div") {
        getToken();
        if (token == "a") {
            com = 1;
        } else if (token == "b") {
            com = 2;
        } else if (token == "c") {
            com = 3;
        } else if (isdigit(token[0])) {
            cout << "\nError: can't DIV to Integer\n";
            errorCount++;
            return;
        } else {
            cout << "\nError: can't DIV to Pointer\n";
            errorCount++;
            return;
        }
        getToken();
        if (token == "a") {
            if (com == 1) {
                cout << "Error: can't DIV Register to itself\n";
                errorCount++;
                return;
            }
            if (com == 2)
                output += "142 ";
            if (com == 3)
                output += "144 ";
        } else if (token == "b") {
            if (com == 1)
                output += "140 ";
            if (com == 2) {
                cout << "Error: can't DIV Register to itself\n";
                errorCount++;
                return;
            }
            if (com == 3)
                output += "145 ";
        } else if (token == "c") {
            if (com == 1)
                output += "141 ";
            if (com == 2)
                output += "143 ";
            if (com == 3) {
                cout << "Error: can't DIV Register to itself\n";
                errorCount++;
                return;
            }
        } else if (isdigit(token[0])) {
            if (com == 1)
                output += "146 " + token + " ";
            if (com == 2)
                output += "147 " + token + " ";
            if (com == 3)
                output += "148 " + token + " ";
        } else {
            if (com == 1)
                output += "146 " + token + " ";
            if (com == 2)
                output += "147 " + token + " ";
            if (com == 3)
                output += "148 " + token + " ";
        }
    }
    else if (token[token.length() - 1] == ':') {
        token.erase(token.length() - 1);
        cout << "Label " << token << " at " << countTokens() << endl;
        labelNames[labelCount] = token;
        labelAddresses[labelCount] = countTokens();
        labelCount += 1;
    }
    else if (isdigit(token[0])) {
        output += token + " ";
    }
    else if (isFunction(token)) {
        int funcID = 0;
        int argNum;
        string funcName;
        for (int x = 0; x < funcCount; x++) {
            if (funcNames[x] == token) {
                funcID = x;
                break;
            }
        }
        argNum = funcArgs[funcID];
        funcName = funcNames[funcID];
        cout << "found Function " << funcName << " and " << argNum << " args\n";
        while (argNum > 0) {
            getToken();
            if (token == "a") {
                output += "161 ";
            } else if (token == "b") {
                output += "162 ";
            } else if (token == "c") {
                output += "163 ";
            } else {
                output += "167 " + token + " ";
            }
            argNum--;
        }
        argNum = funcArgs[funcID];
        if (argNum == 1) {
            output += "164 ";
        } else if (argNum == 2) {
            output += "165 164 ";
        } else if (argNum == 3) {
            output += "166 165 164 ";
        }
        output += "19 " + funcName + " ";
    }
    else {
        if (token != "") {
            cout << "Error: undefined expression '" << token << "'\n";
            errorCount++;
        }
    }
}

bool readSource(string fileName) {
    string line;
    string directiveArg;
    ifstream in(fileName.c_str());
    string headers = "";
    if (in.is_open()) {
        while (getline(in, line)) {
            directiveArg = "";
            if (line.find("import ") == 0) {
                directiveArg = line;
                directiveArg.erase(0, 7);
                cout << "Requested for Module '" << directiveArg << "'\n";
                modulesCount++;
                modulesList[modulesCount] = directiveArg;
            } else if (line.find("header ") == 0) {
                directiveArg = line;
                directiveArg.erase(0, 7);
                cout << "Header '" << directiveArg << "'\n";
                headers += directiveArg + " ";
            } else if (line.find("def ") == 0) {
                int argNum = 0;
                string funcName = "";
                directiveArg = line;
                directiveArg.erase(0, 4);

                for (int x = 0; directiveArg[x] != ' ' && x < directiveArg.length(); x++) {
                    if (directiveArg[x] == ';') {
                        cout << "Preprocessor error: unexpected EOL while parsing Function\n";
                        errorCount++;
                        break;
                    }
                    funcName += directiveArg[x];
                }
                if (directiveArg[directiveArg.length()-1] == '0') {
                    argNum = 0;
                } else if (directiveArg[directiveArg.length()-1] == '1') {
                    argNum = 1;
                } else if (directiveArg[directiveArg.length()-1] == '2') {
                    argNum = 2;
                } else if (directiveArg[directiveArg.length()-1] == '3') {
                    argNum = 3;
                } else {
                    cout << "Preprocessor error: invalid number of arguments: " << directiveArg[directiveArg.length()-1] << "\n";
                    errorCount++;
                }
                cout << "Function " << funcName << " with " << argNum << " arguments\n";
                source += funcName + ": ";
                funcNames[funcCount] = funcName;
                funcArgs[funcCount] = argNum;
                funcCount++;
            } else {
                for (int x = 0; x < line.length(); x++) {
                    if (line[x] == '"') {
                        x++;
                        while (line[x] != '"') {
                            if (line[x] == '\\') {
                                x++;
                                if (line[x] == '0') {
                                    source += "0 ";
                                    x++;
                                } else if (line[x] == 'n') {
                                    source += "12 ";
                                    x++;
                                } else {
                                    cout << "Preprocessor error: unknown ASCII code in String\n";
                                    errorCount++;
                                    x++;
                                }
                                continue;
                            }
                            stringstream strCodes;
                            strCodes << (int)line[x];
                            source += strCodes.str() + " ";
                            x++;
                            if (x >= line.length()) {
                                cout << "Preprocessor error: unexpected EOL while parsing String\n";
                                errorCount++;
                                break;
                            }
                        }
                    } else if (line[x] == '-') {
                        stringstream negInt;
                        x++;
                        while (line[x] != ' ' && x < line.length()) {
                            negInt << line[x];
                            x++;
                        }
                        unsigned int realInt;
                        negInt >> realInt;
                        realInt = MAXVAL - realInt;
                        source += toString(realInt) + " ";
                    } else if (line[x] != ';') {
                        source += line[x];
                    } else {
                        break;
                    }
                }
            }
            source += " ";
        }
        source = headers + source;
        return true;
    } else {
        return false;
    }
}

void getMainFile() {
    int mainFileID = 0;
    string asmFiles[30];
    int asmFilesNum = 0;
    WIN32_FIND_DATA wfd;
    HANDLE const hFind = FindFirstFile("*", &wfd);
    setlocale(LC_ALL, "");
    if (INVALID_HANDLE_VALUE != hFind) {
        do {
            string fname = wfd.cFileName;
            if ((fname.find(".asm") == fname.length() - 4) && fname[0] != '_') {
                cout << "[" << asmFilesNum + 1 << "] " << fname << "\n";
                asmFiles[asmFilesNum] = fname;
                asmFilesNum++;
            }
        } while (0 != FindNextFile(hFind, &wfd));
        FindClose(hFind);
    }
    if (asmFilesNum > 1) {
        cout << "Enter source file ID: ";
        cin >> mainFileID;
        if (mainFileID <= asmFilesNum && mainFileID > 0) {
            cout << "\nAssembling '" << asmFiles[mainFileID - 1] << "'...";
            modulesList[0] = asmFiles[mainFileID - 1];
        } else {
            cout << "\nFatal error: Invalid source ID";
            exit(0);
        }
    } else {
        cout << "\nAssembling '" << asmFiles[0] << "'...";
        modulesList[0] = asmFiles[0];
    }
}

int main() {
    cout << "CVM Assembler X\n";

    /// FIND AVAILABLE SOURCE FILES
    cout << "\nLooking for *.asm files...\n";
    getMainFile();

    /// READ & PREPROCESS
    cout << "\nReading & Preprocessing...\n";
    for (int modulesRead = 0; modulesRead <= modulesCount; modulesRead++) {
        if (!readSource(modulesList[modulesRead])) {
            cout << "Fatal error: Can't read file '" << modulesList[modulesRead] << "'!\n";
            exit(0);
        }
    }

    /// ASSEMBLE
    cout << "Assembling...\n\n";
    while (i < source.length()) {
        getToken();
        opcode();
    }

    /// LABELS
    for (int x = 0; x < labelCount; x++) {
        replaceAll(output, " "+labelNames[x]+" ", " "+labelAddresses[x]+" ");
    }

    /// CONVERSION
    ofstream fout("bios.cvm");
    string wordBuffer = "";
    unsigned int oneInt = 0;
    for (int x = 0; x < output.length(); x++) {
        if (output[x] != (' ')) {
            if (isdigit(output[x])) {
                wordBuffer += output[x];
            } else {
                while (output[x] != (' ') && x < output.length()) {
                    wordBuffer += output[x];
                    x++;
                }
                cout << "Error: undefined expression '" << wordBuffer << "'\n";
                errorCount++;
            }
        } else if (wordBuffer != "") {
            stringstream strToInt;
            strToInt.str(wordBuffer);
            oneInt = 0;
            strToInt >> oneInt;
            wordBuffer = "";
            fout << ((oneInt&0xFF000000)>>24) << " ";
            fout << ((oneInt&0x00FF0000)>>16) << " ";
            fout << ((oneInt&0x0000FF00)>>8)  << " ";
            fout << ((oneInt&0x000000FF))     << "\n";
        }
    }
    fout.close();

    if (errorCount) {
        cout << "\nCompleted with " << errorCount << " errors";
        getchar();
    } else {
        cout << "\nResult:\n" << output;
    }
    return 0;
}
