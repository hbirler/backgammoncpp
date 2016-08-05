#include "main.h"

using namespace std;

int main()
{
    network net;
    
    for(int ind = 0; ; ind++)
    {
        learn_game(net);
        cout<<ind<<endl;
    }
    
    
    int qwer;
    cin>>qwer;
    
    return 0;
}