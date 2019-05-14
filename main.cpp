#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<cmath>
using namespace std;
struct token//词法 token结构体
{
    int code;//编码
    int num;//递增编号
    token *next;
};
token *token_head,*token_tail;//token队列
struct str//词法 string结构体
{
    int num;//编号
    string  word;//字符串内容
    str *next;
};
str *string_head,*string_tail;
/*********************下面是与词法分析相关的一些函数的声明***************************/
void scan();//按字符读取源文件
void cifa_main();//词法分析主程序
int judge(char ch);//判断输入字符的类型
void out1(char ch);//写入token.txt
void out3(char ch,string word);//写入string.txt
void input1(token *temp);//插入结点到队列token
void input3(str *temp);//插入结点到队列string
void output();//输出三个队列的内容
void outfile();//输出三个队列的内容到相应文件中	
/*********************下面是一些全局变量的声明***************************/

FILE *fp;//文件指针
int wordcount;//标志符计数
int err;//标志词法分析结果正确或错误
int nl;//读取行数
int yuyi_linshi;//语义临时变量
string E_name,T_name,F_name,M_name,id_name,id1_name,id2_name,errword;//用于归约时名称传递和未声明变量的输出
int id_num,id1_num,id2_num,id_left,id_while,id_then,id_do;//用于记录一些特殊的字符位置信息
/****************************主程序开始**************************/

int main()
{
    cout<<"************************"<<endl;
    cout<<"*  说明：              *"<<endl;
    cout<<"*	词法分析  ******"<<endl;
    cout<<"************************"<<endl;
    cifa_main();//词法
    cout<<endl;
    system("pause");
    return(0);
}
/****************************以上是主程序，以下是词法**************************/
void cifa_main()
{
    token_head=new token;
    token_head->next= nullptr;
    token_tail=new token;
    token_tail->next= nullptr;
    string_head=new str;
    string_head->next= nullptr;
    string_tail=new str;
    string_tail->next= nullptr;//初始化三个队列的首尾指针
    id_num=0;
    wordcount=0;//初始化字符计数器
    err=0;//初始化词法分析错误标志
    nl=1;//初始化读取行数
    scan();
    if(err==0)
    {
        char m;
        output();
        cout<<"词法分析正确完成!"<<endl<<endl<<"如果将结果保存到文件中请输入 y ，否则请输入其它字母：";
        cin>>m;
        cout<<endl;
        if(m=='y')
        {
            outfile();
            cout<<"结果成功保存在token.txt和sting.txt两个文件中，请打开查看"<<endl;
            cout<<endl;
        }
    }
}
void scan()
{
    cout<<endl;
    system("pause");
    cout<<endl;
    char ch;
    string word;
    char document[50];
    int flag=0;
    cout<<"请输入源文件路径及名称:";
    cin>>document;
    cout<<endl;
    cout<<"************************"<<endl;
    cout<<"*			词法分析  *"<<endl;
    cout<<"************************"<<endl;
    if((fp=fopen(document,"rt"))== nullptr)
    {
        err=1;
        cout<<"无法找到该文件!"<<endl;
        return;
    }
    while(!feof(fp))
    {
        word="";
        ch=fgetc(fp);
        flag=judge(ch);
        if(flag==1)
            out1(ch);
        else if(flag==3)
            out3(ch,word);
        else if(flag==4 || flag==5 ||flag==6)
            continue;
        else
        {
            cout<<nl<<"行  "<<"错误:非法字符!  "<<ch<<endl;
            err=1;
        }
    }
    fclose(fp);
}
int judge(char ch)
{
    int flag=0;
    if(ch=='=' || ch=='+' || ch=='*' || ch=='>' || ch==':' || ch==';' || ch=='{' || ch=='}' || ch=='(' || ch==')')
        flag=1;//界符
    else if(('a'<=ch && ch<='z') || ('A'<=ch && ch<='Z'))
        flag=3;//字母
    else if(ch==' ')
        flag=4;//空格
    else if(feof(fp))
        flag=5;//结束
    else if(ch=='\n')
    {
        flag=6;//换行
        nl++;
    }
    else
        flag=0;//非法字符
    return(flag);
}
void out1(char ch)
{
    int id;
    switch(ch)
    {
        case '=' : id=1;break;
        case '+' : id=2;break;
        case '*' : id=3;break;
        case '>' : id=4;break;
        case ':' : id=5;break;
        case ';' : id=6;break;
        case '{' : id=7;break;
        case '}' : id=8;break;
        case '(' : id=9;break;
        case ')' : id=10;break;//界符编码
        default : id=0;
    }
    token *temp;
    temp=new token;
    temp->code=id;
    temp->num=-1;
    temp->next= nullptr;
    input1(temp);
    return;
}
void out3(char ch,string word)
{
    token *temp;
    temp=new token;
    temp->code=-1;
    temp->num=-1;
    temp->next= nullptr;
    str *temp1;
    temp1=new str;
    temp1->num=-1;
    temp1->word="";
    temp1->next= nullptr;
    int flag=0;
    word=word+ch;
    ch=fgetc(fp);
    flag=judge(ch);
    if(flag==1 || flag==4 || flag==5 || flag==6)
    {
        if(word=="and" || word=="if" || word=="then" || word=="while" || word=="do" || word=="int")
        {
            if(word=="and")
                temp->code=31;
            else if(word=="if")
                temp->code=32;
            else if(word=="then")
                temp->code=33;
            else if(word=="while")
                temp->code=35;
            else if(word=="do")
                temp->code=36;
            else if(word=="int")
                temp->code=37;//关键字编码
            input1(temp);
            if(flag==1)
                out1(ch);
            else if(flag==4 || flag==5 || flag==6)
                return;
        }
        else if(flag==1)
        {
            wordcount++;
            temp->code=25;
            temp->num=wordcount;
            input1(temp);
            temp1->num=wordcount;
            temp1->word=word;
            input3(temp1);
            out1(ch);
        }
        else if(flag==4 || flag==5 || flag==6)
        {
            wordcount++;
            temp->code=25;
            temp->num=wordcount;
            input1(temp);
            temp1->num=wordcount;
            temp1->word=word;
            input3(temp1);
        }
        return;
    }
    else if(flag==2 || flag==3)
        out3(ch,word);//形成字符串
    else
    {
        err=1;
        cout<<nl<<"行  "<<"错误:非法字符!  "<<ch<<endl;
        return;
    }
}
void input1(token *temp)
{
    if(token_head->next == nullptr)
    {
        token_head->next=temp;
        token_tail->next=temp;
    }
    else
    {
        token_tail->next->next=temp;
        token_tail->next=temp;
    }
}
void input3(str *temp)
{
    if(string_head->next == nullptr)
    {
        string_head->next=temp;
        string_tail->next=temp;
    }
    else
    {
        string_tail->next->next=temp;
        string_tail->next=temp;
    }
}
void output()
{
    cout<<"token表内容如下："<<endl;
    token *temp1;
    temp1=new token;
    temp1=token_head->next;
    while(temp1!= nullptr)
    {
        cout<<temp1->code;
        if(temp1->num == -1)
        {
            cout<<endl;
        }
        else
        {
            cout<<"   "<<temp1->num<<endl;
        }
        temp1=temp1->next;
    }
    cout<<"符号表内容如下："<<endl;
    str *temp3;
    temp3=new str;
    temp3=string_head->next;
    while(temp3!= nullptr)
    {
        cout<<temp3->num<<"   "<<temp3->word<<endl;
        temp3=temp3->next;
    }
}
void outfile()
{
    ofstream fout1("/Users/kashingliu/Desktop/testcifa/token.txt");//写文件
    ofstream fout3("/Users/kashingliu/Desktop/testcifa/string.txt");
    token *temp1;
    temp1=new token;
    temp1=token_head->next;
    while(temp1!= nullptr)
    {
        fout1<<temp1->code;
        if(temp1->num == -1)
            fout1<<endl;
        else
            fout1<<"   "<<temp1->num<<endl;
        temp1=temp1->next;
    }
    str *temp3;
    temp3=new str;
    temp3=string_head->next;
    while(temp3!= nullptr)
    {
        fout3<<temp3->num<<"   "<<temp3->word<<endl;
        temp3=temp3->next;
    }
}
