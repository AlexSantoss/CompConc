#include <unistd.h>
#include <iostream>
#include <vector>
#include <thread>

#define vezes 100

using namespace std;

bool b[2];
bool c[2];
int turn;

void dijkstra(int id){
	for(int i = 0; i < vezes; i++){
		b[id] = false;
		
		while(true){
			if(turn != id){
				c[id] = true;
				if(b[turn])
					turn = id;
			}else{
				c[id] = false;
				if(c[1-id]) break;
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
	
	for(int i=0; i < 2; i++)
		b[i] = c[i] = true;
	
	for(int i=0; i < 2; i++)
		threads.push_back(thread(dijkstra, i));
	
	for (auto& th : threads) 
		th.join();
    
    return 0;
}
