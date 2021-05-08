#include "bits/stdc++.h"
using namespace std;
#define INF 2000000000
#define printcase(caseno) printf("Case %d: ", caseno)
typedef long long int ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
#define debug(x)                               \
    {                                          \
        cout << (#x) << " is " << (x) << endl; \
    }
#define getbit(n, i) (((n) & (1 << (i))) != 0)
#define setbit0(n, i) ((n) & (~(1 << (i))))
#define setbit1(n, i) ((n) | (1 << (i)))
#define togglebit(n, i) ((n) ^ (1 << (i)))
#define lastone(n) ((n) & (-(n)))
#define read freopen("debug\\in.txt", "r", stdin)
#define write freopen("debug\\out.txt", "w", stdout)
#define fi first
#define se second
#define PI (acos(-1))
#define fastread                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL)
#define mod (1000000007)
#define asz 500005
#define loop(i, a, b) for (int i = a; i < b; i++)
#define t            \
    int t;           \
    scanf("%d", &t); \
    for (int v = 1; v <= t; v++)
#define minheap priority_queue<int, vector<int>, greater<int>>
#define maxheap priority_queue<int>
#define pb push_back
#define newl "\n"
#define error(a, b) abs(b - a)
#define errorLimit 0.00000001
#define forallmap(m) for (auto it = mp.begin(); it != mp.end(); it++)
#define forallvec(vc) for (int i = 0; i < vc.size(); i++)
#define allvec(vc) vc.begin(), vc.end()
ll BIGMOD(ll a, ll p, ll m)
{
    ll result = 1;
    ll x = a;

    while (p)
    {
        if (p & 1) //p is odd
        {
            result = (result * x) % m;
        }
        x = (x * x) % m;
        p = p >> 1;
    }

    return result;
}

bool isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;

    return true;
}

void SieveOfEratosthenes(int n)
{
    bool prime[n + 1];
    memset(prime, true, sizeof(prime));

    for (int p = 2; p * p <= n; p++)
    {

        if (prime[p] == true)
        {
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
}
struct node
{
    ll present_weight;
    ll rides;
};
const ll MAX = 2e10;
void solve()
{
    int n;
    cin >> n;
    ll x;
    cin >> x;
    ll weight[n + 5];
    ll total = (1 << n);
    struct node dp[total];
    loop(i, 0, n) cin >> weight[i];
    dp[0].rides=1;
    dp[0].present_weight=0;
    loop(i, 1, total)
    {
        int cnt=0;
        ll sum=0;
        ll mini=MAX;
        loop(k,0,n)
        {
            if(getbit(i,k)){
                if(mini>weight[k]) mini=weight[k];
                sum+=weight[k];
                cnt++;
            }
        }
        dp[i].rides=cnt;
        dp[i].present_weight=mini;
    };
    loop(i, 0, total)
    {
        loop(j, 0, n)
        {
            if (getbit(i, j) == 0)
            {
               /*  I can either take this man or not
                  So I will store the previous condition where this man was 
                 already taken.
                 Then I will compare this value with newly calculated value.
                 If newly calculated value is lesser number of rides, then
                 I will update this state with new values.
                 Else I will keep the previous value and continue to the 
                 next index */
                ll earlier_rides_after_taking_this_j = dp[setbit1(i, j)].rides;
                ll earlier_present_weight = dp[setbit1(i, j)].present_weight;



                ll current_rides_for_this_i = dp[i].rides;
                ll current_present_weight = dp[i].present_weight;



                ll new_rides_after_taking_this_j;
                ll new_present_weight;


                 // calculating the total rides if we take this jth man
                 
                 /* If present weight in the lift exceeds x, then i have to
                  take another ride for this man. So adding 1 with the 
                  present ride count */

                if ((current_present_weight + weight[j]) > x)
                {
                    new_rides_after_taking_this_j = current_rides_for_this_i + 1;
                    new_present_weight = weight[j];
                }

                // no need to add 1.We can take him in the present ride
                else
                {
                    new_rides_after_taking_this_j = current_rides_for_this_i;
                    new_present_weight = current_present_weight + weight[j];
                }
                if (new_rides_after_taking_this_j > earlier_rides_after_taking_this_j)
                    continue;


                /* 
                Now this portion is little tricky. If previously calculated number of rides and present calculated number of rides are equal..then generally we didn't need to update anything , because the sense was as we need the same number of rides, why to update anything. And here many do wrong. They miss a case
                
                When the number of rides are equal, then we have to check if the weight present in the lift is less than it was in the previous condition. 
                
                We will always try to keep the present weight in the lift minimum because the less the present weight is, the more we can add people in the same ride. If the weight is more, then we can not add people and we will need more rides.

                So we will check if present weight is less than the previous one. If it is less, then we must update the state with the new rides and new present weight. This minimization of present weight will minimize the ride number in future calculation.

                Hope this makes sense 
                */

                else if (new_rides_after_taking_this_j == earlier_rides_after_taking_this_j)
                {
                    if (new_present_weight < earlier_present_weight)
                    {
                        /// yes take this man and update state
                        dp[setbit1(i, j)].rides = new_rides_after_taking_this_j;
                        dp[setbit1(i, j)].present_weight = new_present_weight;
                    }
                    else
                        continue;
                }
                else
                {
                    // yes take this man and update state
                    dp[setbit1(i, j)].rides = new_rides_after_taking_this_j;
                    dp[setbit1(i, j)].present_weight = new_present_weight;
                }
            }
        }
    }
    cout<<dp[total-1].rides<<newl;
}

int main()
{
   
    solve();
    return 0;
}
