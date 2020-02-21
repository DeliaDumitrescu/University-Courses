#include <iostream>

using namespace std;


void countSort(int v[], int n, int maxi, int result[])
{
    int frecv[maxi + 1] = {0}, ind = 0, i, j;

    for(i = 0; i < n ; i ++)
        frecv[ v[i] ] += 1;

    for(i = 1; i <= maxi; i ++)
        for(j = 0; j < frecv[i]; j ++)
            if(frecv[i]!=0)
                result[ ind ++ ] = i;



}



int main()
{
    int v[101], result[101], maxi=0, n, i;
    cin>>n;
    for(i = 0; i < n; i ++)
    {
        cin>>v[i];
        if(v[i] > maxi)
            maxi = v[i];
    }

    countSort(v, n, maxi, result);

    for(i = 0; i < n; i ++)
        cout<<result[i]<<" ";
    return 0;
}
