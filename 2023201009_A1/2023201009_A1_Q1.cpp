#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int exp_len;

// function to add two integer strings
string removeZeroes(string a){
    int n=a.length();
    int i=0;
    while(i<n && a[i]=='0') i++;
    if(i==n) return "0";
    return a.substr(i);
}

string add(string a, string b){
    int n=a.length(), m=b.length(), r=max(n,m)+1;
    int i=n-1, j=m-1, k=r-1;
    string res(r,'0');
    int cur,carry=0;
    while(i>=0 && j>=0){
        cur=(a[i]-'0')+(b[j]-'0')+carry;
        carry=cur/10;
        cur%=10;
        res[k]='0'+cur;
        i--;
        j--;
        k--;
    }

    while(i>=0){
        cur=(a[i]-'0')+carry;
        carry=cur/10;
        cur%=10;
        res[k]='0'+cur;
        i--;
        k--;
    }
    while(j>=0){
        cur=(b[j]-'0')+carry;
        carry=cur/10;
        cur%=10;
        res[k]='0'+cur;
        j--;
        k--;
    }
    if(carry) res[k]=carry+'0';
    return removeZeroes(res);
}

string subtract(string a, string b){
    int n=a.length(), m=b.length(), r=max(n,m);
    int i=n-1, j=m-1, k=r-1;
    string res(r,'0');
    int cur,borrow=0;
    while(i>=0 && j>=0){
        cur=(a[i]-'0')-(b[j]-'0')-borrow;
        if(cur<0){
            cur+=10;
            borrow=1;
        }
        else borrow=0;
        res[k]='0'+cur;
        i--;
        j--;
        k--;
    }

    while(i>=0){
        cur=(a[i]-'0')-borrow;
        if(cur<0){
            cur+=10;
            borrow=1;
        }
        else borrow=0;
        res[k]='0'+cur;
        i--;
        k--;
    }
    return removeZeroes(res);
}

string multiply(string a, string b){
    int n=a.length(), m=b.length(), r=m+n;
    int i=n-1, j=m-1, k=r-1;
    string res(r,'0');
    int cur,carry=0;

    for(int i=n-1;i>=0;i--){
        k=r-n+i;
        carry=0;
        for(int j=m-1;j>=0;j--){
            cur=(a[i]-'0')*(b[j]-'0')+(res[k]-'0')+carry;
            carry=cur/10;
            cur%=10;
            res[k--]='0'+cur;
        }
        if(carry) res[k]='0'+carry;
    }
    return removeZeroes(res);
}

string divideBy2(string a){
    int n=a.length();
    string res;
    int cur,rem=0;
    for(int i=0;i<n;i++){
        cur=rem*10+(a[i]-'0');
        res.push_back('0'+cur/2);
        rem=cur%2;
    }
    return res;
}
bool compare(string a, string b){
    int n=a.length(),m=b.length();
    if(n<m) return true;
    if(m<n) return false;
    for(int i=0;i<n;i++){
        if(a[i]<b[i]) return true;
        else if(b[i]<a[i]) return false;
    }
    return true;
}

string division(string a, string b){
    time_t start = time(&start);
    if(a==b) return "1";
    if(compare(a,b)) {
        return "0";}
    int n=a.length(), m=b.length(), r=max(m,n);
    string res;
    string mid;
    string low="1", high=a;
    string one="1";

    int i=0;
    while(compare(low,high)){
        mid=(divideBy2(add(low,high)));
        if(compare((multiply(b,mid)),a)){
            res=mid;
            low=add(mid,one);
        }
        else{
            high=subtract(mid,one);
        }
    }
    time_t end = time(&end);
    cout << endl << end-start << " seconds" <<endl;
    return res;
}


int priority(char c){
    if(c=='*' || c=='/') return 2;
    else if(c=='+' || c=='-') return 1;
    return 0;
}

// function to convert infix to postfix
// it returns a string pointer to a string array
string* postfix(string s){
    int n=s.length();
    char stack[n];
    string* pfix= new string[n+1]; //dynamically created string array
    int p_curInd=0; //pfix array current free index
    int s_curInd=0; //stack array current free index
    string cur;
    int zero=int('0'), nine=int('9');

    for(int i=0;i<n;i++){
        if(s[i]<='9' && s[i]>='0') cur.push_back(s[i]); //if s[i] is digit, add it to cur string
        else{
            
            if(!cur.empty()) {
                // if cur string contains a number add it to pfix array
                pfix[p_curInd++]=cur;
                cur="";
            }
            while(s_curInd>0 && priority(s[i])<=priority(stack[s_curInd-1])){
                // while the stack.top's priority is less than equal to current operator,
                // pop the the top and add it to pfix array
                // using push_back b/c can't assing char operator to string
                pfix[p_curInd++].push_back(stack[--s_curInd]);
                stack[s_curInd]='\0';
            }
            // add the cur element s[i] to stack
            stack[s_curInd++]=s[i];
        }
    }
    if(!cur.empty()) {
        // if cur string contains a number add it to pfix array
        pfix[p_curInd++]=cur;
        cur="";
    }
    while(s_curInd>0){
        pfix[p_curInd++].push_back(stack[--s_curInd]);
    }
    pfix[p_curInd]+='\0';
    exp_len=p_curInd+1;
    return pfix;
}

// function to evaluate postfix expression
string evaluate(string* exp){
    int i=0;
    string stack[exp_len];
    int s_curInd=0;
    while(exp[i][0]!='\0'){
        if(exp[i]=="+"){
            string res= add(stack[s_curInd-2], stack[s_curInd-1]);
            s_curInd-=1;
            stack[s_curInd-1]=res;
        }
        else if(exp[i]=="-"){
            string res=subtract(stack[s_curInd-2], stack[s_curInd-1]);
            s_curInd-=1;
            stack[s_curInd-1]=res;
        }
        else if(exp[i]=="*"){
            string res=multiply(stack[s_curInd-2], stack[s_curInd-1]);
            s_curInd-=1;
            stack[s_curInd-1]=res;
        }
        else if(exp[i]=="/"){
            string res=division(stack[s_curInd-2], stack[s_curInd-1]);
            s_curInd-=1;
            stack[s_curInd-1]=res;
        }
        else{
            stack[s_curInd++]=exp[i];
        }
        i++;
    }
    return stack[0];
}

bool modulo2(string& a){
    int n=a.length();
    if((a[n-1]-'0')%2) return true;
    return false;
}

string exponent(string& x, long long y){
    string cur=x,res="1";
    while(y>0){
        if(y&1) res=multiply(res,cur);
        cur=multiply(cur,cur);
        y>>=1;
    }
    return res;
}

string modulo(string a, string b){
    string q=division(a,b);
    return subtract(a,multiply(q,b));
}
string gcd(string a, string b){
    if(b=="0") return a;
    return gcd(b, modulo(a,b));
}

string factorial(string n){
    string i="2",cur="1",end=add(n,"1");
    while(i!=end){
        cur=multiply(cur,i);
        i=add(i,"1");
    }
    return cur;
}

int main(){
    int op_type;
    cin>>op_type;
    if(op_type==1){
        string exp;
        cin>>exp;
        string* pfix=postfix(exp);
        string ans=evaluate(pfix);
        cout<<ans<<endl;
        delete[] pfix;
    }

    else if(op_type==2){
        string x;
        long long y;
        cin>>x>>y;
        string ans = exponent(x,y);
        cout<<ans<<endl;       

    }

    else if(op_type==3){
        string x,y;
        cin>>x>>y;
        string ans= gcd(x,y);
        cout<<ans<<endl;
    }

    else if(op_type==4){
        string x;
        cin>>x;
        string ans= factorial(x);
        cout<<ans<<endl;
    }


    return 0;
}