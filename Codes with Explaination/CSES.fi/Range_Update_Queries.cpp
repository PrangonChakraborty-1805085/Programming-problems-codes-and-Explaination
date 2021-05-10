
/// Here the idea is we will not traverse every index and increase their values by u.
/// rather we will go through a certain range and increase the range value by range size times value


/// For each increment query, we will iterate through the tree nodes and search for the particular range.
/// As a node represents total increments of all the values of the range from node_low to node_hi
/// So new node value will be ( present node value + total_increment for this range )
/// Here, if the value to be incremented is u and the node represents range from left to right
/// then total increment for this node is ( right - left + 1 )*u



/// For query of position k, we will start from tree index ( n + k ), where n is the total number of array elements
/// Assume that this is initial value
/// Then recursively, we will move to the parent and add the incremented value with this initial value till we reach the root of the segment tree
/// For this incremented value, we will not directly add the node value, because the node value represents the total increment of all the values under this node
/// So we will divide the node value by the length of the range.
/// Length of a range from l to r is ( r - l +1 )
/// Then we will add this value with the initial value
/// We will continue this addition process for all the nodes ,moving upwards of the segment tree, starting from ( n + k )till the root node.

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
const int MAX = 2e5 + 5;
vector<ll> tree;
vector<ll> vc;
int n, q;
ll new_query(int index,int n)
{
    ll divisor=1;
    ll new_value=vc[index];
    int current_index=n+index;
    while (current_index)
    {
        new_value+=(tree[current_index]/divisor);
        divisor*=2;
        current_index/=2;
    }
    return new_value;

}
void update(int current_node,int node_lo,int node_hi,int query_lo,int query_hi, ll value)
{
    /// if node range in totally inside query range
    if(node_lo>=query_lo && node_hi<=query_hi)
    {
        /// here this tree node has (node_hi-node_lo+1) elements
        /// each of this elements will increase by value
        /// so total increment corresponding to this tree node is (node_hi-node_lo+1)*value
        tree[current_node]+=((node_hi-node_lo+1)*value);
        return;
    }
    if(node_hi<query_lo || node_lo>query_hi) return;  /// here nothing to increase..so returning from this node
    int mid=(node_lo+(node_hi-node_lo)/2);
    update(2*current_node,node_lo,mid,query_lo,query_hi,value);   /// increase value in the right node range
    update(2*current_node+1,mid+1,node_hi,query_lo,query_hi,value); /// increase value in the left node range

}
void solve()
{
    cin >> n >> q;
    loop(i, 0, n)
    {
        ll inp;
        cin>>inp;
        vc.push_back(inp);
    }
    while (__builtin_popcount(n) != 1)
    {
        n++;
        vc.push_back(0);
    }
    //debug(n);
    tree.resize(2 * n);
    ///building the tree

    /// here we are storing the total increment of a certain range in a tree node
    /// initially all tree nodes have increment 0
    /// so storing 0 in all nodes

    loop(i, 1, (2 * n)) tree[i] = 0;
    while (q--)
    {
        int left, right, k, op;
        ll u;
        cin >> op;
        if (op == 1)
        {
            cin >> left >> right>>u;
            left--;
            right--;
            update(1,0,n-1,left,right,u);

        }
        else
        {
            cin>>k;
            k--;
            cout <<new_query(k,n) << newl;
        }
    }
    return;

}

int main()
{
    solve();
    return 0;
}
