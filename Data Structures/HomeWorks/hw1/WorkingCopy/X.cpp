#include<iostream>
using namespace std;    
void printX(int x) {
    char chars[x];
    int pointerLocation = 0;  
    for (int i = 0; i < x; i++) {
        chars[i] = '*';
        chars[x - 1 - i] = '*';
        for (int j = 0; j < x; j++) {
            if (j == i || j == (x - 1 - i)) {
                continue;
            }
            chars[j] = getCharMidF();
        }
        for(int i=0;i<sizeof(chars)/sizeof(char);i++)
        {
            cout<<chars[i];
        }
        cout<<endl;
    }

}

int main()
{
    printX(15);
}