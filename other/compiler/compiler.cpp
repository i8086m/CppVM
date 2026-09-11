#include <iostream>
#include <sstream>
#include <stack>
#include <fstream>
using namespace std;

//
//
// replace("push a\nmov a c\n", "")
//
//

int i = 0;
string token;
string source = "";
string output = "";
string output_vars = "";

string itos(int itos_int) {
    stringstream itos_ss;
    string itos_string;
    itos_ss << itos_int;
    itos_ss >> itos_string;
    return itos_string;
}

int stoi(string stoi_string) {
    stringstream stoi_ss;
    int stoi_int = 0;
    stoi_ss << stoi_string;
    stoi_ss >> stoi_int;
    return stoi_int;
}

bool isNumber(const string& s) {
    string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int getPriority(string tkn) {
    if (tkn == "+" || tkn == "-") {
        return 5;
    } else if (tkn == "*" || tkn == "/") {
        return 7;
    } else if (tkn == "++" || tkn == "--") {
        return 9;
    } else if (tkn == "U&" || tkn == "U*" || tkn == "U-") {
        return 11;
    } else if (tkn == "==" || tkn == "!=") {
        return 3;
    } else if (tkn == "<" || tkn == ">") {
        return 3;
    } else if (tkn == "<=" || tkn == ">=") {
        return 3;
    } else if (tkn == "=") {
        return 2;
    } else {
        return 0;
    }
}

bool unarCheck(string tkn) {
    string unarAllowed[] = {"(", "+", "-", "*", "/", "&", "[", "=", "==", "<", ">", "<=", ">=", "and", "or", "none", "{"};
    for (int x=0; x<17; x++) {
        if (unarAllowed[x] == tkn) {
            return true;
        }
    }
    return false;
}

bool isOp(string tkn) {
    if (tkn == "+") {
        return true;
    }
    if (tkn == "-") {
        return true;
    }
    if (tkn == "++") {
        return true;
    }
    if (tkn == "--") {
        return true;
    }
    if (tkn == "*") {
        return true;
    }
    if (tkn == "/") {
        return true;
    }
    if (tkn == "==") {
        return true;
    }
    if (tkn == "=") {
        return true;
    }
    if (tkn == "<") {
        return true;
    }
    if (tkn == ">") {
        return true;
    }
    if (tkn == "!=") {
        return true;
    }
    if (tkn == ">=") {
        return true;
    }
    if (tkn == ">=") {
        return true;
    }
    if (tkn == "&") {
        return true;
    }
    if (tkn == "$") {
        return true;
    }
    if (tkn == "U&") {
        return true;
    }
    if (tkn == "U*") {
        return true;
    }
    if (tkn == "U-") {
        return true;
    }
    return false;
}

string convert(string expr) {
    stack <string> st;
    int ii = 0;
    string reslt = "";
    while (ii < expr.length()) {

        string tkn = "";
        while (ii < expr.length()) {
            if (expr[ii] != (' ')) {
                tkn += expr[ii];
            } else if (tkn != "") {
                break;
            }
            ii++;
        }
        //cout << "got! token '" << tkn << "'\n";

        if (tkn == "(") {
            st.push(tkn);
        } else if (tkn == ")") {
            do {
                if (st.empty()) {
                    cout << "!!! Error !!!\n";
                    return 0;
                } else if (st.top() == "(") {
                    st.pop();
                    break;
                } else {
                    reslt += st.top() + " ";
                    st.pop();
                }
            } while (true);
        } else if (isOp(tkn)) {
            do {
                if (st.empty() || st.top() == "(") {
                    st.push(tkn);
                    break;
                } else if (getPriority(st.top()) < getPriority(tkn)) {
                    st.push(tkn);
                    break;
                } else {
                    reslt += st.top() + " ";
                    st.pop();
                }
            } while (true);
        } else {
            reslt += tkn + " ";
        }

        ii++;
    }

    while (!st.empty()) {
        reslt += st.top() + " ";
        st.pop();
    }
    return reslt;
}


void doExpression(string expr) {
    stack <string> st;
    string tkn = "";
    string a, b, c;
    cout << "memes " << expr << endl;
    for (int x=0; x<expr.length(); x++) {
        tkn = "";
        while (expr[x] != ' ') {
            tkn += expr[x];
            x++;
        }
        while (expr[x] == ' ') {
            x++;
        }
        x--;
        //cout << "Token '" << tkn << "'\n";
        if (isOp(tkn)) {

            if (tkn == "+") {
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                if (isNumber(a)) {
                    output += "mov b " + a + "\n";
                } else if (a == "__STACK") {
                    output += "pop b\n";
                } else {
                    output += "ld b _var_" + a + "\n";
                }
                if (isNumber(b)) {
                    output += "mov a " + b + "\n";
                } else if (b == "__STACK") {
                    output += "pop a\n";
                } else {
                    output += "ld a _var_" + b + "\n";
                }
                output += "add a b\npush a\n";
                st.push("__STACK");
            }

            else if (tkn == "-") {
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();

                if (isNumber(a)) {
                    output += "mov b " + a + "\n";
                } else if (a == "__STACK") {
                    output += "pop b\n";
                } else {
                    output += "ld b _var_" + a + "\n";
                }
                if (isNumber(b)) {
                    output += "mov a " + b + "\n";
                } else if (b == "__STACK") {
                    output += "pop a\n";
                } else {
                    output += "ld a _var_" + b + "\n";
                }
                output += "sub a b\npush a\n";
                st.push("__STACK");
            }

            else if (tkn == "*") {
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                if (isNumber(a)) {
                    output += "mov b " + a + "\n";
                } else if (a == "__STACK") {
                    output += "pop b\n";
                } else {
                    output += "ld b _var_" + a + "\n";
                }
                if (isNumber(b)) {
                    output += "mov a " + b + "\n";
                } else if (b == "__STACK") {
                    output += "pop a\n";
                } else {
                    output += "ld a _var_" + b + "\n";
                }
                output += "mul a b\npush a\n";
                st.push("__STACK");
            }

            else if (tkn == "/") {
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                if (isNumber(a)) {
                    output += "mov b " + a + "\n";
                } else if (a == "__STACK") {
                    output += "pop b\n";
                } else {
                    output += "ld b _var_" + a + "\n";
                }
                if (isNumber(b)) {
                    output += "mov a " + b + "\n";
                } else if (b == "__STACK") {
                    output += "pop a\n";
                } else {
                    output += "ld a _var_" + b + "\n";
                }
                output += "div a b\npush a\n";
                st.push("__STACK");
            }

            else if (tkn == "++") {
                a = st.top();
                st.pop();
                if (isNumber(a)) {
                    output += "mov a " + a + "\n";
                } else if (a == "__STACK") {
                    output += "pop a\n";
                } else {
                    output += "ld a _var_" + a + "\n";
                }
                output += "inc a\n";
                if (isNumber(a)) {
                } else if (a == "__STACK") {
                } else {
                    output += "wr a _var_" + a + "\n";
                }
                output += "push a\n";
                st.push("__STACK");
            }

            else if (tkn == "--") {
                a = st.top();
                st.pop();
                if (isNumber(a)) {
                    output += "mov a " + a + "\n";
                } else if (a == "__STACK") {
                    output += "pop a\n";
                } else {
                    output += "ld a _var_" + a + "\n";
                }
                output += "dec a\n";
                if (isNumber(a)) {
                } else if (a == "__STACK") {
                } else {
                    output += "wr a _var_" + a + "\n";
                }
                output += "push a\n";
                st.push("__STACK");
            }

            else if (tkn == "U-") {
                a = st.top();
                st.pop();

                if (isNumber(a)) {
                    output += "mov b " + a + "\n";
                } else if (a == "__STACK") {
                    output += "pop b\n";
                } else {
                    output += "ld b _var_" + a + "\n";
                }
                output += "mov a 0\n";
                output += "sub a b\npush a\n";
                st.push("__STACK");
            }

            else if (tkn == "U*") {
                a = st.top();
                st.pop();

                if (isNumber(a)) {
                    output += "mov b " + a + "\n";
                } else if (a == "__STACK") {
                    output += "pop b\n";
                } else {
                    output += "mov b _var_" + a + "\n";
                }
                output += "ld a b\npush a\n";
                st.push("__STACK");
            }

            else if (tkn == "U&") {
                a = st.top();
                st.pop();

                if (isNumber(a)) {
                    cout << "Error! Can't get ADDRESS of NUMBER";
                } else if (a == "__STACK") {
                    cout << "Error! Can't get ADDRESS of EXPRESSION";
                } else {
                    output += "mov a _var_" + a + "\n";
                }
                output += "push a\n";
                st.push("__STACK");
            }

            else if (tkn == "=") {
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                if (isNumber(a)) {
                    output += "mov b " + a + "\n"; /// CANT ASSING TO INT
                } else if (a == "__STACK") {
                    output += "pop b\n";
                } else {
                    output += "ld b _var_" + a + "\n";
                }
                if (isNumber(b)) {
                    output += "mov a " + a + "\n";
                } else if (b == "__STACK") {
                    output += "pop a\n";
                } else {
                    output += "mov a _var_" + b + "\n";
                }
                output += "wr b a\n";
            }

            else if (tkn == "==") {
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                if (isNumber(a)) {
                    output += "mov b " + a + "\n";
                } else if (a == "__STACK") {
                    output += "pop b\n";
                } else {
                    output += "ld b _var_" + a + "\n";
                }
                if (isNumber(b)) {
                   output += "mov a " + a + "\n";
                } else if (b == "__STACK") {
                    output += "pop a\n";
                } else {
                    output += "ld a _var_" + b + "\n";
                }
                output += "cmp b\npushif z\n";
            }

            else if (tkn == "!=") {
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                if (isNumber(a)) {
                    output += "mov b " + a + "\n";
                } else if (a == "__STACK") {
                    output += "pop b\n";
                } else {
                    output += "ld b _var_" + a + "\n";
                }
                if (isNumber(b)) {
                   output += "mov a " + a + "\n";
                } else if (b == "__STACK") {
                    output += "pop a\n";
                } else {
                    output += "ld a _var_" + b + "\n";
                }
                output += "cmp b\npushif nz\n";
            }

            else if (tkn == "<") {
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                if (isNumber(a)) {
                    output += "mov b " + a + "\n";
                } else if (a == "__STACK") {
                    output += "pop b\n";
                } else {
                    output += "ld b _var_" + a + "\n";
                }
                if (isNumber(b)) {
                   output += "mov a " + a + "\n";
                } else if (b == "__STACK") {
                    output += "pop a\n";
                } else {
                    output += "ld a _var_" + b + "\n";
                }
                output += "cmp b\npushif n\n";
            }

            else if (tkn == ">") {
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                if (isNumber(a)) {
                    output += "mov b " + a + "\n";
                } else if (a == "__STACK") {
                    output += "pop b\n";
                } else {
                    output += "ld b _var_" + a + "\n";
                }
                if (isNumber(b)) {
                   output += "mov a " + a + "\n";
                } else if (b == "__STACK") {
                    output += "pop a\n";
                } else {
                    output += "ld a _var_" + b + "\n";
                }
                output += "cmp b\npushif p\n";
            }

        } else {
            //cout << "not op " << tkn << endl;
            st.push(tkn);
        }
    }
}

string operators[] = {"+", "-", "*", "/", "++", "--", "&", "$", "=", "==", "<", ">", "<=", ">=", "||", "&&", "(", ")", ",", ";", "{", "}", "!=", "!"};
bool doesMatch(string tkn) {
    for (int x=0; x<24; x++) {
        if (operators[x].find(tkn) != -1) {
            ///cout << "token " << tkn << " is matching " << operators[x] << " operator\n";
            return true;
        }
    }
    return false;
}

string lastTkn = "none";
string getToken() {
    string tkn = "";
    while (source[i] == ' ') {
        i++;
    }
    if (isalpha(source[i]) || isdigit(source[i]) || source[i] == '_') {
        while (isalpha(source[i]) || isdigit(source[i]) || source[i] == '_') {
            tkn += source[i];
            i++;
        }
    } else {
        do {
            //cout << source[i] << endl;
            tkn += source[i];
            i++;
        } while (doesMatch(tkn + source[i]));
    }
    cout << "just got a " << tkn << " token!\n";
    if (tkn == "*" || tkn == "&" || tkn == "-") {
        cout << "debil" << tkn<<lastTkn;
        if (unarCheck(lastTkn)) {
            cout << "got unary operator " << tkn << "\n";
            lastTkn = tkn;
            return "U" + tkn;
        }
    }
    lastTkn = tkn;
    /// if (doesMatch(tkn)) return tkn; else raiseError();
    return tkn;
}

int main() {
    ifstream in("source.cvx"); // Read file
    string line;
    if (in.is_open()) {
        while (getline(in, line)) {
            for (int x=0; x<line.length(); x++) {
                if (line[x] != '\t') {
                    source += line[x];
                }
            }
            source += " ";
        }
    }

    cout << "Compiling " << source << "\n";

    string expression =  "";
    stack <string> end_id;
    stack <string> end_type; // to ELSE work properly
    string lastif = "none";
    int ifcount = 0;

    while (i < source.length()) {
        token = getToken();
        if (token == ";") {
            cout << "found expr " << expression << endl;
            doExpression(convert(expression));
            expression = "";
            lastTkn = "none";
        }
        else if (token == "var") {
            if (expression == "") {
                //cout << "new var " << expression << endl;
                expression = getToken();
                output_vars += "_var_" + expression + ": 0\n";
                expression += " ";
            } else {
                cout << "Error! Expected semicolon";
            }
        }
        else if (token == "dim") {
            cout << "lol" << expression << endl;
            if (expression == "") {
                //cout << "new var " << expression << endl;
                expression = getToken();
                output_vars += "_var_" + expression + ":";
                expression = getToken();    /// Add check is >0 or not
                for (int x=0; x<stoi(expression); x++) {
                    output_vars += " 0";
                }
                output_vars += "\n";
                expression = "";
            } else {
                cout << "Error! Expected semicolon";
            }
        }
        else if (token == "put") {
            if (expression == "") {
                output += "ld a _var_" + getToken() + "\n";
                output += "puts\nendl\n";
            } else {
                cout << "Error! Expected semicolon";
            }
        }
        else if (token == "get") {
            if (expression == "") {
                output += "cin\n";
                output += "wr a _var_" + getToken() + "\n";
            } else {
                cout << "Error! Expected semicolon";
            }
        }
        else if (token == "if") {
            token = getToken();
            int depth = 0;
            if (token == "(") {
                depth += 1;
            } else {
                cout << "Error: Expected '(' token\n";
                //exit(0);
            }
            while (i < source.length() && depth > 0) {
                token = getToken();
                if (token == "(") {
                    depth += 1;
                    expression += token + " ";
                } else if (token == ")") {
                    depth -= 1;
                } else {
                    expression += token + " ";
                }
            }
            if (expression == "") {
                cout << "Error: No condition\n";
                //exit(0);
            } else {
                token = getToken();
                if (token == "{") {
                    cout << "found condition " << expression << endl;
                    doExpression(convert(expression));
                    expression = "";
                    output += "pop a\ncmp 0\njz _else_" + itos(ifcount) + "\n";
                    end_id.push(itos(ifcount));
                    end_type.push("if");
                } else {
                    cout << "Error: Expected '{' token\n";
                    //exit(0);
                }
            }
            ifcount++;
        }
        else if (token == "while") {
            token = getToken();
            int depth = 0;
            if (token == "(") {
                depth += 1;
            } else {
                cout << "Error: Expected '(' token\n";
                //exit(0);
            }
            output += "_while_" + itos(ifcount) + "_begin:\n";
            while (i < source.length() && depth > 0) {
                token = getToken();
                if (token == "(") {
                    depth += 1;
                    expression += token + " ";
                } else if (token == ")") {
                    depth -= 1;
                } else {
                    expression += token + " ";
                }
            }
            if (expression == "") {
                cout << "Error: No condition\n";
                //exit(0);
            } else {
                token = getToken();
                if (token == "{") {
                    //cout << "found condition " << expression << endl;
                    doExpression(convert(expression));
                    expression = "";
                    output += "pop a\ncmp 0\njz _while_" + itos(ifcount) + "\n";
                    end_id.push(itos(ifcount));
                    end_type.push("while");
                } else {
                    cout << "Error: Expected '{' token\n";
                    //exit(0);
                }
            }
            ifcount++;
        }
        else if (token == "}") {
                token = getToken();
                lastif = end_id.top();
                if (token == ";") {
                    if (end_type.top() == "if") {
                        output += "_else_" + end_id.top() + ":\n";
                        end_id.pop();
                        end_type.pop();
                    } else if (end_type.top() == "else"){
                        output += "_else_" + end_id.top() + "_end:\n";
                        end_id.pop();
                        end_type.pop();
                    } else if (end_type.top() == "while"){
                        output += "jmp _while_" + end_id.top() + "_begin\n";
                        output += "_while_" + end_id.top() + ":\n";
                        end_id.pop();
                        end_type.pop();
                    }
                } else if (token == "else") {
                    if (end_type.top() == "if") {
                        token = getToken();
                        if (token == "{") {
                            output += "jmp _else_" + end_id.top() + "_end\n";
                            output += "_else_" + end_id.top() + ":\n";
                            end_type.pop();
                            end_type.push("else");
                        } else {
                            cout << "Error: Expected '{' token\n";
                        }
                    } else if (end_type.top() == "while") {
                        cout << "Error: else after while\n";
                    } else if (end_type.top() == "else") {
                        cout << "Error: else after else\n";
                    }
                } else {
                    cout << "Error: Expected ';' or 'else' token\n";
                }
        }
        else {
            expression += token + " ";
        }
    }

    output += "ret\n; vars\n" + output_vars;
    cout << output << endl;
    ofstream fout("output.asm");
    fout << output;
    fout.close();
    return 0;
}
