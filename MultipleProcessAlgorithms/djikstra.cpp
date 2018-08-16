#include <unistd.h>
#include <iostream>
#include <vector>
#include <thread>

#define TAM 10
#define vezes 2

using namespace std;

bool b[TAM];
bool c[TAM];
int turn;

void dijkstra(int id){
	int flag;
	for(int i = 0; i < vezes; i++){
		b[id] = false;
		
		while(true){
			if(turn != id){
				c[id] = true;
				if(b[turn])
					turn = id;
			}else{
				c[id] = false;
				flag = 1;
				for(int j=0; j<TAM; j++)
					if(j != id && !c[j]) flag = 0;
				if(flag) break;
			}
		}
		
		cout << id << " entrou na zona critica" << endl;
		cout << id << " saiu da zona critica" << endl;
		
		c[id] = b[id] = true;
	}
}

int main(){
	vector<thread> threads;
	srand(time(NULL));
	
	for(int i=0; i < TAM; i++)
		b[i] = c[i] = true;
	
	for(int i=0; i < TAM; i++)
		threads.push_back(thread(dijkstra, i));
	
	for (auto& th : threads) 
		th.join();
    
    return 0;
}
