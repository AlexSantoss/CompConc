#include <iostream>
#include <vector>
#include <thread>

#define nProcessos 10
#define vezes 2

using namespace std;

bool b[nProcessos];
bool c[nProcessos];
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
				for(int j=0; j<nProcessos; j++)
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
	
	for(int i=0; i < nProcessos; i++)
		b[i] = c[i] = true;
	
	for(int i=0; i < nProcessos; i++)
		threads.push_back(thread(dijkstra, i));
	
	for (auto& th : threads) 
		th.join();
    
    return 0;
}
