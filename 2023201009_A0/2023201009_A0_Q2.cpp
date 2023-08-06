#include<iostream>
using namespace std;

int main(){
    int n,s,j;
    cin>>n>>s>>j;
    int cir[n], jumps[j];
    for(int i=0;i<n;i++){
        cin>>cir[i];
    }
    for(int i=0;i<j;i++){
        cin>>jumps[i];
    }
    int ans[j+1];
    ans[0]=cir[s];
    cout<<ans[0];
    for(int i=0;i<j;i++){
        s=(jumps[i]%n+s)%n;
        ans[i+1]=cir[s];
        cout<<ans[i+1];
    }
    return 0;
}