#include <iostream>
#include <vector>
#include <thread>

//Algoritmo de Dekker para resolver o problema de exclusao mutua, onde mais de um processo nao pode entrar na regiao
//critica ao mesmo tempo. Funcional apenas para dois processos

//numero de vezes que cada processo vai tentar entrar na zona critica
#define vezes 100

using namespace std;

//true = deseja entrar na regiao critica
//false = nao deseja
bool wants[2];

//quem tem preferencia
int turn;

void dekker(int id){
	//for para executar as tentativas
	for(int i = 0; i < vezes; i++){

	    //sinaliza que o processo deseja entrar
		wants[id] = true;

		//enquanto o outro processo deseja entrar tambem, fica nesse loop
		while(wants[1-id]){
		    //cede a vez
			wants[id] = false;
			//aguarda o outro processo passar a prioridade
			while(turn != id);
			//pede para entrar na regiao critica novamente
			wants[id] = true;
		}

		//regiao critica
		cout << id << " entrou na zona critica" << endl;
		cout << id << " saiu da zona critica" << endl;

		//passa a prioridade para o outro
		turn = 1-id;
		wants[id] = false;
	}
}

int main(){
	vector<thread> threads;

	//inicializa o array
	for(int i=0; i < 2; i++)
		wants[i] = false;

	//cria os processos
	for(int i=0; i < 2; i++)
		threads.push_back(thread(dekker, i));

	//faz a main esperar todos os processos para terminar
	for (auto& th : threads) 
		th.join();
    
    return 0;
}
