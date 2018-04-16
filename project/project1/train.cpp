#include <iostream>
#include <stack>
#include <vector>
#include <windows.h>
using namespace std;
int main(){
	int n,m;
	cout<<"please input the number of train:"<<endl;
	cin>>n;
	int *train = new int[n * sizeof(int)];
	cout<<"input train number:"<<endl;
	for(int i=0;i<n;i++){
		cin>>m;
		train[i]=m;
	}
	vector< stack<int> > v;
	int count=1,k=0,total=0;
	bool suc=false;
	while(count<=n){
		if(k<n && train[k] == count){
			cout<<train[k]<<" will leave!"<<endl;;
			count++;
			k++;
		}
		else{
			if(k<n){
				int pos=1;
				for(auto &i:v){
					if( i.empty()||train[k]<i.top()){
						i.push(train[k]);
						cout<<train[k]<<" has been pushed in stack["<<pos<<"]!"<<endl;
						suc=true;
						k++;
						break;
					}
					pos++;
				}

				if(!suc){
					stack<int> st;
					st.push(train[k]);
					v.push_back(st);
					cout<<"here will build a new stack and "<<train[k]<<" will be pushed in!"<<endl;
					k++;
					total++;
				}
				suc=false;
			}
			for (int i = 0; i < v.size(); ++i){
				while(!v[i].empty() && v[i].top()==count){
					cout<<v[i].top()<<" will be poped from stack["<<i+1<<"] and leave!"<<endl;
					v[i].pop();
					count++;
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		cout<<i<<' ';
	}
	cout<<"use "<<total<<" stack"<<endl;
	delete []train;
	system("pause");
	return 0;
}