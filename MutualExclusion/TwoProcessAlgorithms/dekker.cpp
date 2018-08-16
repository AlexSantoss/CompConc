#include <iostream>
#include <vector>
#include <thread>

#define vezes 100

using namespace std;

bool wants[2];
int turn;

void dekker(int id){
	for(int i = 0; i < vezes; i++){
		
		wants[id] = true;
		
		while(wants[1-id]){
			wants[id] = false;
			while(turn != id);
			wants[id] = true;
		}
		
		cout << id << " entrou na zona critica" << endl;
		cout << id << " saiu da zona critica" << endl;
		
		turn = 1-id;
		wants[id] = false;
	}
}

int main(){
	vector<thread> threads;
	
	for(int i=0; i < 2; i++)
		wants[i] = false;
	
	for(int i=0; i < 2; i++)
		threads.push_back(thread(dekker, i));
	
	for (auto& th : threads) 
		th.join();
    
    return 0;
}
