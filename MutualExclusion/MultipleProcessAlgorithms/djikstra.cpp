#include <iostream>
#include <vector>
#include <thread>

//Algoritmo de Djikstra para resolver o problema de exclusao mutua, onde mais de um processo nao pode entrar na regiao
//critica ao mesmo tempo

//numero de processos
#define nProcess 10

//numero de vezes que cada processo vai tentar entrar na zona critica
#define vezes 2

using namespace std;

//true = nao quer entrar na regiao critica
//false = quer entrar na regiao critica
bool b[nProcess];

//true = nao passou nos testes para entrar na regiao critica
//false = ta proximo de entrar ou dentro da regiao critica
bool c[nProcess];

//quem possui a vez
int turn;

void dijkstra(int id){
    //flag para sair do loop. se mantem 1 se todos os outros processos mantem tem o valor true no array c
	int flag;

	//for para executar as tentativas
	for(int i = 0; i < vezes; i++){

	    //inicio dos teste pra saber se podera entrar na zona critica
		b[id] = false;
		
		while(true){

		    //testa se o processo atual possui a vez
			if(turn != id){
				c[id] = true;
				//pega a vez se o processo que tinha vez nao quer mais entrar na regiao critica
				if(b[turn])
					turn = id;
			}else{
				c[id] = false;
				flag = 1;

				//procura se algum processo ta na regiao critica ou se nesse else. se nao encontrar, sai do while
				for(int j=0; j<nProcess; j++)
					if(j != id && !c[j]) flag = 0;
				if(flag) break;
			}
		}

		//inicio da zona critica
		cout << id << " entrou na zona critica" << endl;
		cout << id << " saiu da zona critica" << endl;

		//saida da zona critica
		c[id] = b[id] = true;
	}
}

int main(){
	vector<thread> threads;

	//inicializa os arrays
	for(int i=0; i < nProcess; i++)
		b[i] = c[i] = true;

	//cria os processos
	for(int i=0; i < nProcess; i++)
		threads.push_back(thread(dijkstra, i));

	//faz a main esperar todos os processos para terminar
	for (auto& th : threads) 
		th.join();
    
    return 0;
}
