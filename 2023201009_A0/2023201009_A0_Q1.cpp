#include<iostream>
#include<string>
using namespace std;

int main(){
    int t;
    cin>>t;
    string s1[t];
    string s2[t];

    for(int i=0;i<t;i++){
        cin>>s1[i]>>s2[i];
    }

    for(int i=0;i<t;i++){
        int freq[26]={0};
        int l1=s1[i].length(), l2=s2[i].length();
        if(l1!=l2) {
            cout<<"NO"<<endl;
            continue;
            }
        for(int j=0;j<l1;j++){
            freq[s1[i][j]-'a']++;
            freq[s2[i][j]-'a']--;
        }
        bool flag=false;
        for(int j=0;j<26;j++){
            if(freq[j]!=0) {
                cout<<"NO"<<endl;
                flag=true;
                break;
            }
        }
        if(!flag) cout<<"YES"<<endl;

    }
    return 0;

}