#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>>t;

    while(t--){
        int n;
        cin>>n;
        string s, st="";
        cin>>s;

        for(int i=0;i<n;i+=2){
            string ss = s.substr(i, 2);

            if(ss=="00") st += 'A';
            else if(ss=="01") st += 'T';
            else if(ss=="11") st += 'G';
            else if(ss=="10") st += 'C';
        }

        cout<<st<<endl;
    }

    // string s = "101010";
    // cout<<s.substr(0,2)<<endl<<s.substr(2,2)<<endl<<s.substr(4,2);
    return 0;

}