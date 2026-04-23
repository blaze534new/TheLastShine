#include<iostream>
#include<string>
using namespace std;

struct armi{
    string nome;
    int dado;
    string tipo;
};
// yo

class player {
private:
    int HP, FOR, DES, VIG, INT, SAG;
public:
    player(int h, int f, int d, int v, int i, int s);
    ~player();


};

player::player(int h, int f, int d, int v, int i, int s){
    HP = h;
    FOR = f;
    DES = d;
    VIG = v;
    INT = i;
    SAG = s;
}

player::~player(){}

class enemy {
private:
    int HP, FOR, DES, VIG;
public:
    enemy(int h, int f, int d, int v);
    ~enemy();


};

enemy::enemy(int h, int f, int d, int v){
    HP = h;
    FOR = f;
    DES = d;
    VIG = v;
}

enemy::~enemy(){}


void combattimenti(player p, enemy e, armi a, armi b){

}

int main(){
    armi gladio = {"Gladio", 6, "leggero"};
    armi lancia = {"Lancia", 8, "pesante"};
    armi ascia = {"Ascia", 12, "pesante"};
    armi spada_lunga = {"Spada", 10, "due mani"};
}