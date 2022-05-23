#include "sdt.h"

SDT::SDT(SLR& slr,ostringstream& ofs):slr(slr),ofs(ofs),pvec(slr.G.pvec){
        prod_vec=slr.get_leftmostderivation();
        id_stack=slr.get_idstack();
        label_idx=0;
        var_idx=0;
    }
    //返回label号
    string SDT::newlabel(){
        return "L"+ to_string(label_idx++);
    }
    //返回临时变量
    string SDT::newtemp(){
        return "t"+ to_string(var_idx++);
    }
    //确定label位置
    void SDT::label(const string& L){
        ofs<<L<<':';
    }
void SDT::start() {
    actionP();
}

void SDT::actionP() {
    int pidx=prod_vec.back();
    prod_vec.pop_back();
    const auto& p=pvec[pidx];
    if(p==Production("P",{"L",""})){
        actionL();
    }
    else{
        actionL();
        actionP();
    }
}

void SDT::actionL() {
    int pidx=prod_vec.back();
    prod_vec.pop_back();
    /*L产生式只有一个*/
    AttrS S;
    S.next=newlabel();
    actionS(S);
    label(S.next);
}

void SDT::actionS(const AttrS& S) {
    int pidx=prod_vec.back();
    prod_vec.pop_back();
    const auto& p=pvec[pidx];
    if(p==Production("S",{"id","=","E",""})){
        string val1=id_stack.back();
        id_stack.pop_back();
        string val2=actionE();
        ofs<<val1<<":="<<val2<<endl;

    }
    else if(p==Production("S",{"if","C","then","S",""})){
        AttrC C;
        C.true_entry=newlabel();
        C.false_entry=S.next;
        actionC(C);
        label(C.true_entry);
        AttrS S1;
        S1.next=S.next;
        actionS(S1);
    }
    else if(p==Production("S",{"if","C","then","S","else","S",""})){
        AttrC C;
        C.true_entry=newlabel();
        C.false_entry=newlabel();
        actionC(C);
        label(C.true_entry);
        AttrS S1,S2;
        S1.next=S2.next=S.next;
        actionS(S1);
        ofs<<"goto "<<S1.next<<endl;
        label(C.false_entry);
        actionS(S2);
    }
    else if(p==Production("S",{"while","C","do","S",""})){
        S.begin=newlabel();
        AttrC C;
        C.true_entry=newlabel();
        C.false_entry=S.next;
        AttrS S1;
        S1.next=S.begin;
        label(S.begin);
        actionC(C);
        label(C.true_entry);
        actionS(S1);
        ofs<<"goto "<<S.begin<<endl;
    }
}

void SDT::actionC(const AttrC& C) {
    int pidx=prod_vec.back();
    prod_vec.pop_back();
    const auto& p=pvec[pidx];
    if(p==Production("C",{"E",">","E",""})){
        string val1=actionE();
        string val2=actionE();
        ofs<<"if "<<val1<<'>'<<val2<<" goto "<<C.true_entry<<endl;
        ofs<<"goto "<<C.false_entry<<endl;
    }
    else if(p==Production("C",{"E","<","E",""})){
        string val1=actionE();
        string val2=actionE();
        ofs<<"if "<<val1<<'<'<<val2<<" goto "<<C.true_entry<<endl;
        ofs<<"goto "<<C.false_entry<<endl;
    }
    else if(p==Production("C",{"E","=","E",""})){
        string val1=actionE();
        string val2=actionE();
        ofs<<"if "<<val1<<'='<<val2<<" goto "<<C.true_entry<<endl;
        ofs<<"goto "<<C.false_entry<<endl;
    }
}

string SDT::actionE() {
    int pidx=prod_vec.back();
    prod_vec.pop_back();
    const auto& p=pvec[pidx];
    string t;
    if(p==Production("E",{"E","+","T",""})){
        t=newtemp();
        string val1=actionE();
        string val2=actionT();
        ofs<<t<<":="<<val1<<'+'<<val2<<endl;
    }
    else if(p==Production("E",{"E","-","T",""})){
        t=newtemp();
        string val1=actionE();
        string val2=actionT();
        ofs<<t<<":="<<val1<<'-'<<val2<<endl;
    }
    else if(p==Production("E",{"T",""})){
        t=actionT();
    }
    return t;
}

string SDT::actionT() {
    int pidx=prod_vec.back();
    prod_vec.pop_back();
    const auto& p=pvec[pidx];
    string t;
    if(p==Production("T",{"F",""})){
        t=actionF();
    }
    else if(p==Production("T",{"T","*","F",""})){
        t=newtemp();
        string val1=actionT();
        string val2=actionF();
        ofs<<t<<":="<<val1<<'*'<<val2<<endl;
    }
    else if(p==Production("T",{"T","/","F",""})){
        t=newtemp();
        string val1=actionT();
        string val2=actionF();
        ofs<<t<<":="<<val1<<'/'<<val2<<endl;
    }
    return t;
}

string SDT::actionF() {
    int pidx=prod_vec.back();
    prod_vec.pop_back();
    const auto& p=pvec[pidx];
    string t;
    if(p==Production("F",{"(","E",")",""})){
        t=actionE();
    }
    else if(p==Production("F",{"id",""})){
        t=id_stack.back();
        id_stack.pop_back();
    }
    else if(p==Production("F",{"int8",""})){
        t=id_stack.back();
        id_stack.pop_back();
    }
    else if(p==Production("F",{"int10",""})){
        t=id_stack.back();
        id_stack.pop_back();
    }
    else if(p==Production("F",{"int16",""})){
        t=id_stack.back();
        id_stack.pop_back();
    }
    return t;
}
