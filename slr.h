#ifndef SLR_H
#define SLR_H
/*
  SLR文法分析器类
*/
#include "grammer.h"
#include <algorithm>
#include <queue>

class SLR{
friend class SDT;
public:
  SLR(Grammer& G);
  //根据最左规约序列，返回最左派生序列栈
  vector<int> get_leftmostderivation();
  //返回id_stack
  vector<string> get_idstack();
  //打印分析结果
  void print();
  //开始语法分析函数
  void start();
  //根据词法分析结果，构造输入串
  void make_input(const vector<Token*>& tkvec);
private:
  vector<int> st_stk;//状态栈
  vector<string> sgn_stk;//符号栈
  vector<string> in_stk;//输入栈，栈底是$符号
  Grammer& G;//引用一个文法
  vector<int> which_prod;//记录规约过程中使用的产生式，最左规约对应最右派生，后面要用它构建分析树结构
  vector<string> id_stack;
};

#endif // SLR_H
