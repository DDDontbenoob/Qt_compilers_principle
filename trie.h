#ifndef TRIE_H
#define TRIE_H
//字典树实现
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <functional>
using namespace std;
class Trie{
public:
  Trie():root(new char){}
  Trie(const vector<string>& words):root(new char){
    make_trie(words);
  }
  //根据字典树来匹配输入字符串，返回单词数组
  vector<string> get_words(const string& in_string);
  //输入单词组，构建字典树
  void make_trie(const vector<string>& words);
private:
  unordered_map<shared_ptr<char>,unordered_map<char,shared_ptr<char>>> trie_map;
  shared_ptr<char> root;
};
#endif // TRIE_H
