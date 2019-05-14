#include <iostream>
#include <algorithm>
#include <vector>
#define DEFAULT 0
#define LETTER 1
#define NUMBER 2
#define ID0_IS_NUM 3
//#define DEFAULT 3
//#define DEFAULT 4

using namespace std;
//static string digital = "1234567890";
static string keyword[] = {"main", "void", "int", "double", "char", "float", "printf",
                           "class", "scanf", "else", "if", "return" ,"char","public",
                           "static","true", "false", "private"};
FILE * file;
int line;
string tmp;
static char current_state = DEFAULT;
//static string a =
void judge(char ch) {
    while (true) {
        switch (current_state) {
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
                } else if (ch == '\xff') {
                    return;
                } else {
                    cout << "unexpected string" << endl;
                    return;
                }
                break;
            case LETTER:
                if ((ch>='0'&& ch <= '9') || (ch>='a'&&ch<='z') || (ch>='A'&&ch<='Z')) {
                    tmp += ch;
                    current_state = LETTER;
                    return;
                } else {
                    int flag = 0;
                    for (int i = 0; i < keyword->length(); ++i) {
                        if (keyword[i] == tmp) {
                            flag = 1;
                            break;
                        }
                    }
                    if (flag == 0) {
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
            case ID0_IS_NUM:
                if (ch!=' '&&ch!='\n'&&ch!='\t'&&ch!='\xff') {
                    tmp += ch;
                    current_state = ID0_IS_NUM;
                    return;
                } else {
                    cout << tmp << " 标识符错误" << endl;
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
    file = fopen("/Users/kashingliu/Desktop/testcifa/a.txt","rt");
    if (file == nullptr) {
        cout << "cannot find file" << endl;
        return;
    } else {
        while(!feof(file)) {
            ch = fgetc(file);
            judge(ch);
        }
    }

}

int main() {

    line = 1;
    scan();
    return 0;
}