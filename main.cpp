#include <iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int MAX=2e7;
struct edge{
    int v;
    int weight1;
    int weight2;
    int next;
}edges[MAX];
struct edge_2{
    int u,v,w;
};
int head[MAX]={0};
int dfs[MAX]={0};
int low[MAX]={0};
int cnt;
int n,m;
void add_edge(int u, int v, int weight1, int weight2){
    edges[cnt].v=v;
    edges[cnt].weight1=weight1;
    edges[cnt].weight2=weight2;
    edges[cnt].next=head[u];
    head[u]=cnt++;
}
void init(){
    cnt=0;
    for(int i=0;i<=n;++i) head[i]=-1;
}
int dfs_clock=1;
edge_2 weight[MAX];//保存最终权重
//fa表示走来的边
void isBridge(int idx,int fa){
     dfs[idx]=low[idx]=dfs_clock++;
     for(auto ed=head[idx];ed!=-1;ed=edges[ed].next){
         if(dfs[edges[ed].v]==0) {
             isBridge(edges[ed].v, ed/2);
             low[idx] = min(low[edges[ed].v], low[idx]);
             //更改桥的权重
             if (low[edges[ed].v] > dfs[idx]) {
                 weight[ed / 2]. w = edges[ed].weight2;
             }
         }
         else if(ed/2!=fa){
             low[idx] = min(low[idx], dfs[edges[ed].v]);
         }

     }
}
//并查集
int fa[MAX];
void makeSet(int size) {
    for (int i = 1; i <=size; i++) fa[i] = i;  // i 就在它本身的集合里
}
int find(int x) {
    if (x != fa[x])  // x 不是自身的父亲，即 x 不是该集合的代表
        fa[x] = find(fa[x]);  // 查找 x 的祖先直到找到代表，于是顺手路径压缩
    return fa[x];
}
std::vector<int> Size(MAX, 1);  // 记录并初始化子树的大小为 1
void unionSet(int xx, int yy) {
//    int xx = find(x), yy = find(y);
//    if (xx == yy) return;
    if (Size[xx] > Size[yy])  // 保证小的合到大的里
        swap(xx, yy);
    fa[xx] = yy;
    Size[yy] += Size[xx];
}



int main() {
    cin>>n>>m;
    init();
    int u,v,w1,w2;
    for(size_t i=0;i<m;++i){
        cin>>u>>v>>w1>>w2;
        add_edge(u,v,w1,w2);
        add_edge(v,u,w1,w2);
        weight[i]={u,v,w1};
    }
    isBridge(1, -1);
    sort(weight,weight+m,[](const edge_2 &a,const edge_2 &b){return a.w<b.w;});

    makeSet(n);
    long long answer=0;
    for(int i=0;i<m;++i){
        u=weight[i].u;
        v=weight[i].v;
       int uu= find(u);
       int vv= find(v);
        if(uu!=vv) {
            unionSet(uu,vv);
            answer+=weight[i].w;
        }
    }
    cout<<answer;
}
