#include <iostream>

using namespace std;


void countSort(int v[], int n, int maxi, int exp)
{
    int frecv[10] = {0}, result[n+1], ind = 0, i, j,k;

    for(i = 0; i < n ; i ++)
        frecv[ (v[i]/exp)%10 ] += 1;

    for(i = 1; i < 10; i++)
         frecv[i] += frecv[i-1];    //in frecv[i] vom avea pozitia fiecarei cifre in rezultat, poz = cate au fost pana la element + cate sunt ca el


      for(i = n - 1; i >= 0; i --)
      {
         result[frecv[(v[i]/exp)%10]-1] = v[i];
         frecv[ (v[i]/exp)%10 ]--;
      }

      for (i = 0; i < n; i++)
        v[i] = result[i];

}


void RadixSort(int v[], int n, int maxi)
{
    int i,copymaxi = maxi,exp = 0, p10;

    while(copymaxi > 0)
    {
        exp += 1;
        copymaxi = copymaxi / 10;

    }
    i = 1;
    p10 = 1;
    while( i <= exp )
    {
        countSort(v,n,maxi,p10);
        p10 = p10 * 10;
        i += 1;
    }


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


    RadixSort(v, n, maxi);

    for(i = 0; i < n; i ++)
        cout<<v[i]<<" ";
    return 0;
}
