
# 并查集模版代码

```cpp
class UnionFind {
public:
    UnionFind(int n) {

        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        //nums.resize(n, 1);
    }

    // 将节点 p 和 q 连通
    void Union(int p, int q) {
        int pa = find(p), qa = find(q);
        if(pa == qa) return;

        /* 小树挂在大树上
        if(nums[pa] > nums[qa]) {
            parent[qa] = pa;
            nums[pa] += nums[qa]; 
        }
        else {
            parent[pa] = qa;
            nums[qa] += nums[pa];
        }
        */

        parent[pa] = qa;


    }


    // 查找某个节点的父节点
    int find(int x) {
        
        if(x != parent[x]) {
            
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

private:
    vector<int> parent; // 每个节点的父节点
    //vector<int> nums;   // 以索引 i 节点为根的树中含有的节点数
};
```