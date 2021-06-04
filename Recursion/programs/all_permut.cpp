#include<iostream>
using namespace std;
void permut(string s,int i=0){
    if(i==s.length()-1){
        cout<<s<<" ";
        return;
    }
    for(int j=i;j<s.length();j++){
        swap(s[i],s[j]);
        permut(s,i+1);
        swap(s[i],s[j]);
    }
}
int main(){
    string s="abc";//n! permutations
    permut(s);
}