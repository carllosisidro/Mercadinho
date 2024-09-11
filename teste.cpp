#include <locale.h>
#include <iostream>
#include <fstream>
using namespace std;


















int main(){
    int escolha;
string produto;
double codigo, valor;
int menu;

ofstream produtos;

produtos.open("protudos.txt");


cout<<"menu"<<endl;
cout<<"1) adionar produto digite : "<<endl;
cout<<"2) ver produtos cadastrados: "<<endl;
cin>>escolha;



switch(escolha)
{
    case 1:
    system("cls");
    cout<<"adionar produto: "<<endl;
    cout<<"produto: "<<endl;
    produtos>>produto;
    cout<<"codigo do produto: "<<endl;
    cin>>codigo;
    cout<<"valor: "<<endl;
    cin>>valor;
cout<<"produto cadatrado";
break;

    case 2:
    system("cls");
    cout<<"produto: "<<produto<<"codigo: "<<codigo<<"valor: R$"<<valor<<endl;
break;


    default:
       cout<<"valor errado";
}


produtos.close();
return 0;




}