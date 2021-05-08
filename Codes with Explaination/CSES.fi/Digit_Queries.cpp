#include "bits/stdc++.h"
using namespace std;
#define INF 2000000000
#define printcase(caseno)  printf("Case %d: ",caseno)
typedef long long int ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
#define debug(x) { cout<< (#x) << " is " << (x) << endl; }
#define getbit(n,i) (((n)&(1<<(i)))!=0)
#define setbit0(n,i) ((n)&(~(1<<(i))))
#define setbit1(n,i) ((n)|(1<<(i)))
#define togglebit(n,i) ((n)^(1<<(i)))
#define lastone(n) ((n)&(-(n)))
#define read freopen("debug\\in.txt","r",stdin)
#define write freopen("debug\\out.txt","w",stdout)
#define fi first
#define se second
#define PI (acos(-1))
#define fastread ios_base::sync_with_stdio(false);cin.tie(NULL)
#define mod (1000000007)
#define asz 500005
#define loop(i,a,b) for(int i=a;i<b;i++)
#define t int t;scanf("%d",&t);for(int v=1;v<=t;v++)
#define minheap priority_queue<int,vector<int>,greater<int> >
#define maxheap priority_queue<int>
#define pb push_back
#define newl "\n"
#define error(a,b) abs(b-a)
#define errorLimit 0.00000001
#define forallmap(m) for(auto it=mp.begin();it!=mp.end();it++)
#define forallvec(vc)  for(int i=0;i<vc.size();i++)
#define allvec(vc)    vc.begin(),vc.end()
ll BIGMOD ( ll a, ll p, ll m )
{
    ll result = 1;
    ll x = a;
     
    while ( p )
    {
        if ( p & 1 ) //p is odd
        {
            result = ( result * x ) % m;
        }
        x = ( x * x ) % m;
        p = p >> 1;
    }
 
    return result;
}

bool isPrime(int n) 
{ 
    if (n <= 1)  return false; 
    if (n <= 3)  return true; 
    if (n%2 == 0 || n%3 == 0) return false; 
  
    for (int i=5; i*i<=n; i=i+6) 
        if (n%i == 0 || n%(i+2) == 0) 
           return false; 
  
    return true; 
} 

void SieveOfEratosthenes(int n) 
{ 
    bool prime[n+1]; 
    memset(prime, true, sizeof(prime)); 
  
    for (int p=2; p*p<=n; p++) 
    { 

        if (prime[p] == true) 
        { 
            for (int i=p*p; i<=n; i += p) 
                prime[i] = false; 
        } 
    } 
}
ll arr[20];
const ll MAX=1e18;
void precalc(){
    arr[0]=0;
    ll number=9;
    for(int i=1;i<=17;i++)
    {
        arr[i]=i*number;
        number*=10;
    }
    //arr[17]=MAX-arr[16];   /// if we calculate the number of 17 digits number,it will exceed 10^18.. so taking number before 10^18
    
}
void solve()
{
   ll k;
   cin>>k;
   precalc();
   int i;
   //loop(i,0,18) debug(arr[i]);
   //debug((int)log10(arr[17])+1);
   for( i=0;i<=17;i++)
   {
       if(k<arr[i]) break;
       k-=arr[i];
   }
   int digits=i;
   ll lowest_number=1;
   loop(l,1,digits) lowest_number*=10;
   --lowest_number;
   ll to_be_added=k/digits;
  // debug(to_be_added);
   ll remainder=k%digits;
   ll new_number=lowest_number+to_be_added;
   if(remainder==0)
   {
       cout<<(new_number%10)<<newl;
   }
   else
   {
       new_number++;
       int division_times=digits-remainder;
       while (division_times--)
       {
           new_number/=10;
       }
       cout<<new_number%10<<newl;
       
   }



}

int main()
{
   //fastread;
    // solve();
     t
     {
         solve();
     }
  return 0;
}
