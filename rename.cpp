#include<bits/stdc++.h>
#include<pthread.h>
using namespace std;
int x[100000];

struct range{
    int l;
    int r;
};

void* merSort(void *p)
{
    void* v;
    range *ranP = (range *)p;
    if(ranP->l==ranP->r)
        return v;

    int mid = (ranP->l+ranP->r)/2;

    pthread_t th1,th2;
    range *ran1 , *ran2;
    ran1 = (range *)malloc(sizeof(range));
    ran2 = (range *)malloc(sizeof(range));
    ran1->l = ranP->l;
    ran1->r = mid;
    ran2->l = mid+1;
    ran2->r = ranP->r;

    if(pthread_create(&th1,NULL,&merSort,ran1))
    {
        printf("Error Creating Sub-thread Thread\n");
        return v;
    }
    if(pthread_create(&th2,NULL,&merSort,ran2))
    {
        printf("Error Creating Sub-thread Thread\n");
        return v;
    }
    int l = ranP->l;
    int r = ranP->r;
    pthread_join(th1,NULL);
    free(ran1);
    pthread_join(th2,NULL);
    free(ran2);
    int mer[r-l+1],ind=0 , i=l , j=mid+1;
    for(;i<=mid && j<=r;ind++)
        if(x[i]<=x[j])
            mer[ind]=x[i] , i++;
        else
            mer[ind]=x[j] , j++;

    for(;i<=mid;ind++)
        mer[ind] = x[i] , i++;
    for(;j<=r;ind++)
        mer[ind] = x[j] , j++;
    for(int i=l,j=0;i<=r;i++,j++)
        x[i] = mer[j];
    return v;

}
int main()
{
    printf("ENTER FILE NAME : ");
    char name[1000]; scanf("%s",name);
    if(!freopen(name, "r", stdin)){
        cout << "File NOT Found" << endl;
        return 0;
    }
    freopen ("Output_fil.txt","w",stdout);
    int n; cin >> n;
    for(int i=0;i<n;i++)
        cin >> x[i];
    pthread_t th;
    range ran{0,n-1};
    if(pthread_create(&th,NULL,&merSort,&ran))
    {
        printf("Error Creating Main Thread\n");
        return 0;
    }
    pthread_join(th,NULL);
    for(int i=0;i<n;i++)
        cout << x[i] << " ";
}

