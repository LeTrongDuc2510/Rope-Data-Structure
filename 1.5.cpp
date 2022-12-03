
#include<iostream>
#include<cstring>
#include<cmath>


using namespace std; 
int a=0,temp=0;

long int decimalToBinary(int n)
{
    if (n==0) return a;
    else 
    {   
        a = a + (pow(10,temp)*(n%2));
        temp++;
        if(n%2==1) n--; 
        return decimalToBinary(n/2);
    }
}

int main()
{

    cout<<decimalToBinary(20);

    system("Pause");
    return 0;
}