#ifndef LEX_H
#define LEX_H


#include <sstream>
#include <QString>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>
using namespace std;
enum Type{IDN,DEC,OCT,HEX,ADD,SUB,MUL,DIV,GT,LT,EQ,GE,LE,NEQ,SLP,SRP,SEMI,ILOCT,ILHEX,NONE};//种别值枚举类型
//
bool isdigit(char c);
bool isalpha(char c);
bool ishexdig(char c);
bool isilhex(char c);
bool isoctdig(char c);
bool isiloct(char c);
vector<string> string_split(const string& str, const string& splits);//字符分割函数
//词法单元类
class Token{
public:
    Type type;//类型
    string name;//单词名称
    string type_name;//类型名称
    Token()=default;
    Token(const Type& t,string  name,string type_name):type(t),name(std::move(name)),type_name(std::move(type_name)){}
    //打印Token
    void print(){
        cout<<'['<<type_name<<','<<name<<']'<<endl;
    }
};
//打印词法分析结果
void print_lexres(const vector<Token*>&);
//返回词法分析结果
vector<Token*> getLexRes(istringstream& in);
//返回一个token
Token* TokenScan(istringstream& in);

#endif // LEX_H
