#include <iostream>
#include <vector>
#define forn(i,n,b) for(int i=b;i<n;i++)
using namespace std;

int main(int argc, char *argv[]) {
	int n;
	cin>>n;
	vector<int> procesos(n);
	forn(i,n,0){
		cin>>procesos[i];
	}	
	int cantvalor=0;int movimientos=0;	int cantceros=0;
	forn(i,n,1){
		if(procesos[i-1]!=procesos[i] and procesos[i-1]!=0){
			movimientos+=min(cantceros,cantvalor);
			cantvalor=0;
		}
		if(procesos[i-1]!=procesos[i] and procesos[i]!=0)
		cantvalor=1;
		
		if(procesos[i-1]==procesos[i] and procesos[i]!=0)
			cantvalor++;
		if(procesos[i]==0)
			cantceros++;
	
	}		
	cout<<movimientos;	
	return 0;
}

