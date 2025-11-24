#include "TwoSAT.h"

TwoSAT::TwoSAT(int n)
{
    N=n;

    g=new Vec[2*n];
    gr=new Vec[2*n];

    used.resize(2*n);
    comp.resize(2*n);
    assignment.resize(n);

    for (int i=0;i<2*n;i++){
        used[i]=0;
        comp[i]=-1;
    }
}

TwoSAT::~TwoSAT()
{
    delete[] g;
    delete[] gr;
}

int TwoSAT::var(int x, bool val)
{
    return 2*x + (val?0:1);
}

void TwoSAT::addImp(int a, int b)
{
    g[a].push(b);
    gr[b].push(a);
}

void TwoSAT::addOr(int a, int b)
{
    addImp(a ^ 1, b);
    addImp(b ^ 1, a);
}

void TwoSAT::setTrue(int a)
{
    addOr(a, a);
}

void TwoSAT::dfs1(int v)
{
    used[v] = 1;

    for (int i = 0; i < g[v].size(); i++)
    {
        int to = g[v][i];
        if (!used[to]) dfs1(to);
    }

    order.push(v);
}

void TwoSAT::dfs2(int v, int c)
{
    comp[v]=c;

    for (int i=0; i<gr[v].size();i++)
    {
        int to = gr[v][i];
        if (comp[to] == -1) dfs2(to,c);
    }
}

bool TwoSAT::solve()
{
    for(int i=0;i<2*N;i++) used[i] = 0;

    order.clear();

    for(int i=0; i<2*N; i++) if (!used[i]) dfs1(i);

    for(int i=0; i<2*N; i++) comp[i] = -1;

    int j = 0;

    for (int i = order.size() - 1; i >= 0; i--){
        int v = order[i];
        if (comp[v] == -1) dfs2(v, j++);
    }

    for (int i=0; i<N; i++)
    {
        if (comp[2*i] == comp[2*i+1]) return false;

        assignment[i] = (comp[2*i]>comp[2*i+1]) ? 1 : 0;
    }

    return true;
}
