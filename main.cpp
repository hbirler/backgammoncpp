#include "main.h"

using namespace std;

int main()
{
    freopen("out.txt","w",stdout);
    int i = 5;
    tavla mytav;
    cout<<mytav.str()<<endl;
    cout<<"Success"<<endl;
    
    vector<tavla> vs;
    mytav.next_states(2,3, vs);
    
    cout<<vs.size()<<endl;
    
    for(auto& t: vs)
    {
        cout<<t.str()<<endl;
    }
    
    
    //int qwer;
    //cin>>qwer;
    
    return 0;
}