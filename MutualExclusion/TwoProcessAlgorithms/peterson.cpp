#include <iostream>
#include <vector>
#include <thread>

//Algoritmo de Peterson feita baseada na de Dekker para resolver o problema de exclusao mutua, onde mais de um processo
//nao pode estar na regiao critica ao mesmo tempo. Funcional apenas para dois processos

//numero de vezes que cada processo vai tentar entrar na zona critica
#define vezes 100

using namespace std;

//true = deseja entrar na regiao critica
//false = nao deseja
bool wants[2];

//quem tem preferencia
int turn;

void peterson(int id){
    //for para executar as tentativas
    for(int i = 0; i < vezes; i++){

        //declara que deseja entrar na regiao critica
        wants[id] = true;
        //declara preferencia para o outro processo
        turn = 1-id;
        //aguarda ate que o outro processo nao tenha interesse na regiao critica ou que ele devolva a preferencia
        while(wants[1-id] && turn == 1-id);

        //regiao critica
        cout << id << " entrou na zona critica" << endl;
        cout << id << " saiu da zona critica" << endl;

        //declara que nao deseja entrar na regiao critica
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
        threads.push_back(thread(peterson, i));

    //faz a main esperar todos os processos para terminar
    for (auto& th : threads)
        th.join();

    return 0;
}
