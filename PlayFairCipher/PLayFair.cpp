#include<bits/stdc++.h>
using namespace std;

char table[5][5];

pair<int,int> idx(char a){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(table[i][j]==a){
                return {i,j};
            }
        }
    }
    return {-1,-1};
}

int main(){
    unordered_set<char> se;
    string message,key;
    cout<<"Enter your message : ";
    cin>>message;
    cout<<"Enter the key : ";    
    cin>>key;
    int k=0,p=97;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(k<key.length()){
                table[i][j]=key[k];
                se.insert(key[k]);
                k++;
            } else {
                while(p==106 || se.find(p)!=se.end()){
                    p++;
                }
                table[i][j]=p;
                se.insert(p);
            }
        }
    }
    vector<string> enc;
    string temp="";
    for(int i=0;i<message.length();i++){
        temp+=message[i];
        if(temp.length()==2){
            if(temp[0]==temp[1]){
                string temp1="";
                temp1+=temp[0];
                temp1+='x';
                temp=temp1;
            }
            enc.push_back(temp);
            temp="";
        }
    }
    if(temp.length()==1){
        temp+='x';
        enc.push_back(temp);
    }
    string encryption="";
    for(int i=0;i<enc.size();i++){
        pair<int,int> w1 = idx(enc[i][0]);
        pair<int,int> w2 = idx(enc[i][1]);
        if(w1.second == w2.second){
            encryption+=table[(w1.first+1)%5][w1.second];
            encryption+=table[(w2.first+1)%5][w2.second];
        } else if(w1.first == w2.first){
            encryption+=table[w1.first][(w1.second+1)%5];
            encryption+=table[w2.first][(w2.second+1)%5];
        } else {
            encryption+=table[w1.first][w2.second];
            encryption+=table[w2.first][w1.second];
        }
    }    
    cout<<"Encrypted text : "<<encryption<<endl;
}