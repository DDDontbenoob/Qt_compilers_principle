#ifndef GRAMMER_H
#define GRAMMER_H


/*
  文法类实现
*/
#include "lex.h"
#include "trie.h"
#include <unordered_map>
#include <iomanip>
#include <sstream>
#include <fstream>
//产生式类
class Production{
public:
  string left;//左部
  vector<string> right;//右部
  Production(const string& l,const vector<string>& r):left(l),right(r){}
  //打印
  void print()const{
    cout<<left<<"->";
    for(const auto& str:right)
      cout<<str;
    cout<<endl;
  }
  bool operator==(const Production& P)const{
      return left==P.left&&right==P.right;
  }
};
//项目类
class Item{
public:
  int prod_idx;//产生式编号
  int pnt_idx;//“点”的位置
  Item(int x,int y):prod_idx(x),pnt_idx(y){}
  bool operator==(const Item& I)const{
    return I.pnt_idx==pnt_idx&&I.prod_idx==prod_idx;
  }
};
typedef vector<Item> Items;//项集类
typedef vector<Items> Collection;//项集族
//为Item和Items特例化一个哈希模板
namespace std{
  template<>
  struct hash<Item>{
    typedef size_t result_type;
    typedef Item argument_type;
    size_t operator()(const Item& I)const{
      return hash<int>()(I.prod_idx)^hash<int>()(I.pnt_idx);
    }
  };
  template<>
  struct hash<Items>{
    typedef size_t result_type;
    typedef Items argument_type;
    size_t operator()(const Items& I)const{
      size_t res=0;
      for(const auto& i:I)
        res^=hash<Item>()(i);
      return res;
    }
  };

}

//文法类
class Grammer{
    friend class SLR;
    friend class SDT;
public:
    Grammer(ifstream& in);
    //打印first集合
    void print_first(ofstream& ofs);
    //打印follow集合
    void print_follow(ofstream& ofs);
    //打印所有产生式
    void print_allprod();
    //打印action表
    void print_actiontable(ofstream& os);
    //获取可打印的action表
    vector<vector<string>> get_printable_actiontable();
    //打印表
    void print_table(ofstream&os,const vector<vector<string>>& table);
    //构建action表
    void make_action();
    //构造项集族函数
    void make_collection();
    //构造goto函数
    Items Goto(const Items& I,const string& X);
    //构建项集的闭包
    Items closure(const Items& I);
    //为每一个非终结符构建first集
    void make_first();
    //获取文法字符串的first集，为构建follow集做准备
    unordered_set<string> get_firstXs(const vector<string>& Xs);
    //为每一个非终结符构建follow集
    void make_follow();
private:
    string start;//开始符号
    unordered_set<string> vset;//非终结符集合
    unordered_set<string> tset;//终结符集合
    vector<Production> pvec;//产生式数组
    Collection C;//项集族，应该用哈希表的，这样构建goto表的时候可以不用再生成额外的哈希表了，节省空间
    unordered_map<string,unordered_set<string>> first;//first集
    unordered_map<string,unordered_set<string>> follow;//follow集
public:
    unordered_map<int,unordered_map<string,int>> goto_table;//goto表
    unordered_map<int,unordered_map<string,string>> action_table;//action表
};


#endif // GRAMMER_H
