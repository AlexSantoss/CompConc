#include <iostream>
#include <vector>
#include <thread>

#define vezes 100
#define nProcessos 10

using namespace std;

int senha[nProcessos];
bool escolhendoSenha[nProcessos];
int maximo;

void lamport(int id){
	for(int i = 0; i < vezes; i++){
		
		escolhendoSenha[id] = true;
		senha[id] = 1+maximo;
		maximo++;
		escolhendoSenha[id] = false;
		
		for(int j=0; j < nProcessos; j++){
			while( escolhendoSenha[j] );
			while( (senha[j] != 0) && ( (senha[j] < senha[id]) || (senha[j] == senha[id] && id > j) ) );
		}
		
		cout << id << " entrou na zona critica" << endl;
		cout << "senha" << senha[id] << endl;
		cout << id << " saiu da zona critica" << endl << endl;
		
		senha[id] = 0;
	}
}

int main(){
	vector<thread> threads;
	
	for(int i=0; i < nProcessos; i++){
		escolhendoSenha[i] = false;
		senha[i] = 0;
	}
	
	for(int i=0; i < nProcessos; i++)
		threads.push_back(thread(lamport, i));
	
	for (auto& th : threads) 
		th.join();
    
    return 0;
}
