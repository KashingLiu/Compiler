#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#define DEFAULT 0
#define LETTER 1
#define NUMBER 2
#define ID0_IS_NUM 3
#define PLUS 4
#define MINUS 5
#define MULTIPLY 6
#define DIVIDE 7
#define COMMENT 8
#define LESS 9
#define LARGER 10
#define QUESTION 11
#define ASSIGN 12
#define STRING 13
#define CHAR 14

using namespace std;

map<char, string> symbol ={
        {'(',"1"},{')',"2"},{'[',"3"},{']',"4"},{'{',"5"},{'}',"6"},
        {'+',"7"},{':',"8"},{'.',"9"},{'!',"10"},{'?',"11"},
        {'=',"12"},{'>',"13"},{'{',"14"},{';',"15"},{'-',"16"},{'*',"17"},
        {'/',"18"},{'<',"19"}
        };
// IDN 100
// NUM 101
FILE * file;
int line;
string tmp;
static char current_state = DEFAULT;
bool is_boundary(char ch) {
    return ch=='('||ch==')'||ch==','||ch=='.'||ch==';'||ch==':'||ch=='{'||ch=='}'||ch=='['||ch==']';
}
bool is_keyword(string str) {
    return str=="main"||str=="void"||str=="int"||str=="double"||str=="char"||
    str=="float"||str=="printf"||str=="class"||str=="scanf"||str=="else"||
    str=="if"||str=="return"||str=="char"||str=="public"||str=="static"||
    str=="true"||str=="false"||str=="private"||str=="using"||str=="namespace";
}
void judge(char ch) {
    while (true) {
        switch (current_state)
        {
            case DEFAULT:
                if (ch == ' ' || ch == '\n' || ch == '\t') {
                    current_state = DEFAULT;
                    return;
                } else if (ch>='0'&& ch <= '9') {
                    tmp += ch;
                    current_state = NUMBER;
                    return;
                } else if ((ch>='a'&&ch<='z') || (ch>='A'&&ch<='Z')) {
                    tmp += ch;
                    current_state = LETTER;
                    return;
                } else if (is_boundary(ch)) {
                    tmp = "";
                    cout << "(" << symbol[ch] << " , " << ch << ")" << endl;
                    current_state = DEFAULT;
                    return;
                } else if (ch == '+') {
                    tmp += ch;
                    current_state = PLUS;
                    return;
                } else if (ch == '-') {
                    tmp += ch;
                    current_state = MINUS;
                    return;
                } else if (ch == '*') {
                    tmp += ch;
                    current_state = MULTIPLY;
                    return;
                } else if (ch == '/') {
                    tmp += ch;
                    current_state = DIVIDE;
                    return;
                } else if (ch == '<') {
                    tmp += ch;
                    current_state = LESS;
                    return;
                } else if (ch == '>') {
                    tmp += ch;
                    current_state = LARGER;
                    return;
                } else if (ch == '!') {
                    tmp += ch;
                    current_state = QUESTION;
                    return;
                } else if (ch == '=') {
                    tmp += ch;
                    current_state = ASSIGN;
                    return;
                } else if (ch == '\'') {
                    tmp += ch;
                    current_state = CHAR;
                    return;
                } else if (ch == '\"') {
                    tmp += ch;
                    current_state = STRING;
                    return;
                } else if (ch == '\xff') {
                    return;
                } else {
                    cout << "第 " << line << " 行 " << "unexpected string" << endl;
                    return;
                }
                break;
            case LETTER:
                if ((ch>='0'&& ch <= '9') || (ch>='a'&&ch<='z') || (ch>='A'&&ch<='Z')) {
                    tmp += ch;
                    current_state = LETTER;
                    return;
                } else {
                    if (!is_keyword(tmp)) {
                        cout << tmp << " is a identification" << endl;
                    } else {
                        cout << tmp << " is a key word" << endl;
                    }
                    tmp = "";
                    current_state = DEFAULT;
                    continue;
                }
                break;
            case NUMBER:
                if ((ch>='0'&& ch <= '9')) {
                    tmp += ch;
                    current_state = NUMBER;
                    return;
                } else if ((ch>='a'&&ch<='z') || (ch>='A'&&ch<='Z')) {
                    tmp += ch;
                    current_state = ID0_IS_NUM;
                    return;
                } else {
                    cout << tmp << " is a integer" << endl;
                    tmp = "";
                    current_state = DEFAULT;
                    continue;
                }
                break;
            case PLUS:
                if ((ch == '+' || ch == '=') && tmp=="+") {
                    tmp += ch;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    current_state = DEFAULT;
                    return;             //两个字符被识别出来用return
                } else {
                    current_state = DEFAULT;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    continue;
                }
                break;
            case MINUS:
                if ((ch == '-' || ch == '=') && tmp=="-") {
                    tmp += ch;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    current_state = DEFAULT;
                    return;             //两个字符被识别出来用return
                } else {
                    current_state = DEFAULT;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    continue;
                }
                break;
            case MULTIPLY:
                if ((ch == '=') && tmp=="*") {
                    tmp += ch;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    current_state = DEFAULT;
                    return;             //两个字符被识别出来用return
                } else {
                    current_state = DEFAULT;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    continue;
                }
                break;
            case DIVIDE:
                if ((ch == '=') && tmp=="/") {
                    tmp += ch;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    current_state = DEFAULT;
                    return;             //两个字符被识别出来用return
                } else if ((ch == '/') && tmp=="/") {
                    tmp = "";
                    current_state = COMMENT;
                    return;
                } else {
                    current_state = DEFAULT;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    continue;
                }
                break;
            case LESS:
                if ((ch == '=') && tmp=="<") {
                    tmp += ch;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    current_state = DEFAULT;
                    return;             //两个字符被识别出来用return
                } else if ((ch == '<') && tmp=="<") {
                    tmp += ch;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    current_state = DEFAULT;
                    return;             //两个字符被识别出来用return
                } else {
                    current_state = DEFAULT;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    continue;
                }
                break;
            case LARGER:
                if ((ch == '=') && tmp==">") {
                    tmp += ch;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    current_state = DEFAULT;
                    return;             //两个字符被识别出来用return
                } else if ((ch == '>') && tmp==">") {
                    tmp += ch;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    current_state = DEFAULT;
                    return;             //两个字符被识别出来用return
                } else {
                    current_state = DEFAULT;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    continue;
                }
                break;
            case QUESTION:
                if ((ch == '=') && tmp=="!") {
                    tmp += ch;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    current_state = DEFAULT;
                    return;             //两个字符被识别出来用return
                } else {
                    current_state = DEFAULT;
                    cout << tmp << " is not an operator" << endl;
                    tmp = "";
                    continue;
                }
                break;
            case ASSIGN:
                if ((ch == '=') && tmp=="=") {
                    tmp += ch;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    current_state = DEFAULT;
                    return;             //两个字符被识别出来用return
                } else {
                    current_state = DEFAULT;
                    cout << tmp << " is an operator" << endl;
                    tmp = "";
                    continue;
                }
                break;
            case CHAR:
                if (tmp == "\'" && ch == '\'') {
                    tmp = "";
                    current_state = DEFAULT;
                    return;
                } else if (ch == '\'' && tmp.length() == 2) {
                    tmp += ch;
                    cout << tmp << " is a char" << endl;
                    current_state = DEFAULT;
                    tmp = "";
                    return;
                } else if (ch == '\'' && tmp.length() > 2) {
                    tmp += ch;
                    if (tmp == R"('\n')" || tmp == R"('\t')"||tmp == R"('\0')") {
                        cout << tmp << " is a char" << endl;
                        current_state = DEFAULT;
                        tmp = "";
                        return;
                    } else {
                        tmp = "";
                        current_state = DEFAULT;
                        cout << "第 " << line << " 行 " << "ERROR! between \' and \' can only have one char" << endl;
                        return;
                    }
                } else {
                    tmp += ch;
                    current_state = CHAR;
                    return;
                }
                break;
            case STRING:
                if (tmp == "\"" && ch == '\"') {
                    tmp = "";
                    current_state = DEFAULT;
                    return;
                } else if (ch == '\"') {
                    cout << tmp.substr(1,tmp.length()-1) << " is a string" << endl;
                    current_state = DEFAULT;
                    tmp = "";
                    return;
                } else {
                    tmp += ch;
                    current_state = STRING;
                    return;
                }
                break;
            case COMMENT:
                current_state = (ch == '\n')?DEFAULT:COMMENT;
                return;
            case ID0_IS_NUM:
                if (ch!=' '&&ch!='\n'&&ch!='\t'&&ch!='\xff') {
                    tmp += ch;
                    current_state = ID0_IS_NUM;
                    return;
                } else {
                    cout << "第 " << line << " 行 " << tmp << " 标识符错误" << endl;
                    tmp = "";
                    current_state = DEFAULT;
                    return;
                }
                break;
        }
    }
}

void scan() {
//    char document[50];
    char ch;
//    cin >> document;
    line = 1;
    file = fopen("/Users/kashingliu/Desktop/testcifa/a.txt","rt");
    if (file == nullptr) {
        cout << "cannot find file" << endl;
        return;
    } else {
        while(!feof(file)) {
            ch = fgetc(file);
            judge(ch);
            if (ch == '\n') {
                line++;
            }
        }
    }

}

int main() {
    scan();
    return 0;
}