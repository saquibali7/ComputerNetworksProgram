#include<bits/stdc++.h>
using namespace std;

int main() {
    cout<<"Hell"<<endl;
    int n;
    string s;
    int k,count=0,len,count1=0,len1;
    char enc[1000][1000];
    while(1){
        cout<<"1. Enter 1 for encryption of text "<<endl;
        cout<<"2. Enter 2 for decryption of text "<<endl;
        cout<<"3. Enter 3 for exit "<<endl;
        cin>>n;
        int a,b;
        string res="",dec="";
        switch(n){
            case 1:
            cout<<"Enter the string for encryption "<<endl;
            cin.ignore();
            getline(cin,s);
            cout<<"Enter the encryption key "<<endl;
            cin>>k;
            len=s.length();
            for(int i=0;i<1000;i++){
                for(int j=0;j<k;j++){
                    if(count>=len){
                        count++;
                        enc[i][j]='a';
                        continue;
                    }
                    if(s[count]!=' '){
                        enc[i][j]=s[count];
                    }
                    count++;
                }
                if(count>=len){
                    a=i;
                    break;
                }
            }
            for(int i=0;i<k;i++){
                for(int j=0;j<=a;j++){
                    res+=enc[j][i];
                }
            }
            len1=res.length();
            cout<<res<<endl;
            break;
            case 2:
            count1=0;
            while(dec.length() < len){
                dec+=enc[(count1+k)%len];
                count1++;
            }
            cout<<dec.substr(0,len)<<endl;
            break;
            case 3:
            exit(0);
            default:
            cout<<"You have enter wrong option "<<endl;
        }
    }
}