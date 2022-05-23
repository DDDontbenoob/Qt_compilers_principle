#ifndef SDT_H
#define SDT_H


#include "slr.h"
/*S的属性类*/
struct AttrS{
    mutable string begin;
    string next;

};
/*C的属性*/
struct AttrC{
    string true_entry;
    string false_entry;

};
/*实现SDT的类*/
class SDT{
public:
    SDT(SLR& slr,ostringstream& ofs);
    void start();
    void actionP();
    void actionL();
    void actionS(const AttrS& S);
    void actionC(const AttrC& C);
    string actionE();
    string actionT();
    string actionF();
    //返回label号
    string newlabel();
    //返回临时变量
    string newtemp();
    //确定label位置
    void label(const string& L);
private:
    SLR& slr;//引用一个SLR类
    ostringstream& ofs;//引用一个输出流
    vector<Production>& pvec;
    vector<int> prod_vec;//最左派生产生式栈，尾部为栈顶
    vector<string> id_stack;//标识符栈，栈顶为当前id的词法值
    int code_line;//三地址码行号
    int label_idx;//label的序号
    int var_idx;
};

#endif // SDT_H
