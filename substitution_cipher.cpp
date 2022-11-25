#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    unordered_map<int,int> m;
    unordered_map<char,int> m1;
    unordered_map<int, char> m2;
    int count=1;
    char temp=97;
    for(int i=1;i<=26;i++){
        m1[temp++]=i;
    }
    temp=97;
    for(int i=1;i<=26;i++){
        m2[i]=temp;
        temp++;
    }
    string s,enc,dec;
    int key;
    while(1){
        cout<<"Entern Your Choice "<<endl;
        cout<<"1. For encryption enter 1 "<<endl;
        cout<<"2. For decryption enter 2 "<<endl;
        cout<<"3. Enter 3 for exit "<<endl;
        cin>>n;
        switch(n){
            case 1:
            enc="";
            cout<<"Enter the string for encryption : ";
            cin.ignore();
            getline(cin,s);
            cout<<s<<endl;
            cout<<"Enter the encryption key : ";
            cin>>key;
            key = key%26;
            for(int i=0;i<s.length();i++){
                if(s[i]>=65 && s[i]<=90){
                    m[i]=1;
                    s[i]+=32;
                }
                if(m2[(m1[s[i]]+key)%26]<=0){
                    enc+=(m2[(m1[s[i]]+key)%26 + 26]);
                }
                if(s[i]>=97 && s[i]<=122){
                    enc+=m2[(m1[s[i]]+key)%26];
                    
                } else {
                    enc+=s[i];
                }
                if(m[i]==1){

                }
            }
            cout<<enc<<endl;
            break;
            case 2:
            dec="";
            for(int i=0;i<enc.length();i++){
                if(enc[i]>=97 && enc[i]<=122){
                    if(m2[(m1[enc[i]]-key)%26]<=0){
                        dec+=(m2[(m1[enc[i]]-key)%26 + 26] );
                    }
                    else {
                        dec+=m2[(m1[enc[i]]-key)%26];
                    }
                } else {
                    dec+=enc[i];
                }
                if(m[i]==1){
                    dec[i]-=32;
                }
            }
            cout<<dec<<endl;
            break;
            case 3:
            exit(0);
            default:
            cout<<"Wrong Option"<<endl;
        }
    }


    return 0;
}