#include <iostream>
#include <vector>
#include <thread>

//Algoritmo de Lamport (Bakery) para resolver o problema de exclusao mutua, onde mais de um processo nao pode entrar na regiao
//critica ao mesmo tempo

//numero de processos
#define nProcess 10

//numero de vezes que cada processo vai tentar entrar na zona critica
#define vezes 2

using namespace std;

//array com as senhas dos processos
int senha[nProcessos];

//true=processo esta escolhendo uma senha
bool escolhendoSenha[nProcessos];

//maior senha ate o momento
int maximo;

void lamport(int id){

    //for para executar as tentativas
	for(int i = 0; i < vezes; i++){

	    //momento em que o processo escolhe uma nova senha
		escolhendoSenha[id] = true;
		senha[id] = ++maximo;
		escolhendoSenha[id] = false;

		//para cada processo
		for(int j=0; j < nProcessos; j++){
		    //aguarda o processo j escolher uma senha
			while( escolhendoSenha[j] );

			//aguarda o processo j se ele possuir uma senha menor ou a senha for igual e j < id
			while((id != j) && (senha[j] != 0) && ( (senha[j] < senha[id]) || (senha[j] == senha[id] && id > j) ) );
		}

		//inicio da zona critica
		cout << id << " entrou na zona critica" << endl;
		cout << "senha" << senha[id] << endl;
		cout << id << " saiu da zona critica" << endl << endl;

		//saindo do processo
		senha[id] = 0;
	}
}

int main(){
	vector<thread> threads;

	//inicializa os arrays
	for(int i=0; i < nProcessos; i++){
		escolhendoSenha[i] = false;
		senha[i] = 0;
	}

    //cria os processos
	for(int i=0; i < nProcessos; i++)
		threads.push_back(thread(lamport, i));

    //faz a main esperar todos os processos para terminar
	for (auto& th : threads) 
		th.join();
    
    return 0;
}
