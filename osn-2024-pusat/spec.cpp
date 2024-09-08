#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace tcframe;
using namespace std;
using namespace __gnu_pbds;

template<class T>
using ost = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

class ProblemSpec : public BaseProblemSpec {
protected:
    const int mxN = 100'000;
    const int mnW = 1;
    const int mxW = 1'000'000'000;
    const vector<int> poin = {6, 11, 11, 20, 22, 13, 17};

    int N;
    vector<int> P, W, D, child;
    long long ans;

    void InputFormat() {
        LINE(N);
        LINE(P % SIZE(N - 1));
        LINE(W % SIZE(N));
        LINE(D % SIZE(N));
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= N && N <= mxN);
        CONS(checkParents());
        CONS(eachElementBetween(W, mnW, mxW));
        CONS(checkChild());
    }

    void Subtask1() {
        Points(poin[0]);
        CONS(eachElementBetween(D, 0, 0));
    }

    void Subtask2() {
        Points(poin[1]);
        CONS(checkSubtask2());
    }

    void Subtask3() {
        Points(poin[2]);
        CONS(eachElementBetween(P, 1, 1));
    }

    void Subtask4() {
        Points(poin[3]);
        CONS(1 <= N && N <= 100);
        CONS(eachElementBetween(W, 1, 1));
    }

    void Subtask5() {
        Points(poin[4]);
        CONS(1 <= N && N <= 2000);
    }

    void Subtask6() {
        Points(poin[5]);
        CONS(checkSubtask6());
    }

    void Subtask7() {
        Points(poin[6]);
        // no additional constraint
    }

private:
    void getChild() {
        child.clear();
        child.resize(N, 0);
        for (int i : P) {
            child[i - 1]++;
        }
    }

    bool checkParents() {
        for (int i = 0; i < N - 1; i++) {
            if (P[i] < 1 || P[i] > i + 1) {
                return false;
            }
        }
        return true;
    }

    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        for (int x : v) {
            if (x < lo || x > hi) {
                return false;
            }
        }
        return true;
    } 

    bool checkChild() {
        getChild();
        for (int i = 0; i < N; i++) {
            if (D[i] < 0 || D[i] > child[i]) {
                return false;
            }
        }
        return true;
    }

    bool checkSubtask2() {
        getChild();
        for (int i = 0; i < N; i++) {
            if (D[i] != 0 && D[i] != child[i]) {
                return false;
            }
        }
        return true;
    }

    bool checkSubtask6() {
        getChild();
        for (int i = 0; i < N; i++) {
            if (child[i] == 0 && D[i] == 0) continue;
            if (child[i] == 2 && D[i] == 1) continue;
            return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({5, 7});
        Input({
            "6",
            "1 1 3 3 3",
            "5 3 2 4 1 6",
            "1 0 2 0 0 0"
        });
        Output({
            "15"
        });
    }

    void SampleTestCase2() {
        Subtasks({1, 2, 3, 5, 7});
        Input({
            "3",
            "1 1",
            "2 6 5",
            "0 0 0"
        });
        Output({
            "13"
        });
    }

    void TestGroup1() {
        Subtasks({1, 2, 3, 4, 5, 6, 7});
        CASE(N = 1, P = {}, W = {1}, D = {0});
    }

    void TestGroup2() {
        Subtasks({1, 2, 3, 5, 7});
        CASE(N = 2,
             P = {1},
             W = {123, 789},
             D = {0, 0});
    }

    void TestGroup3() {
        Subtasks({1, 2, 4, 5, 7});

        CASE(N = 9,
             P = {1, 1, 1, 2, 2, 2, 4, 4},
             W = vector<int>(9, 1),
             D = vector<int>(9, 0));

        CASE(N = 100,
             P = randomTree(N),
             W = vector<int>(N, 1),
             D = vector<int>(N, 0));

        CASE(N = 100,
             P = heavyTree(N, 2),
             W = vector<int>(N, 1),
             D = vector<int>(N, 0));

        CASE(N = 100,
             P = lineTree(N),
             W = vector<int>(N, 1),
             D = vector<int>(N, 0));

        CASE(N = 100,
             P = sqrtTree(N),
             W = vector<int>(N, 1),
             D = vector<int>(N, 0));

        CASE(N = 100,
             P = heavySqrtTree(N, 2),
             W = vector<int>(N, 1),
             D = vector<int>(N, 0));
    }

    void TestGroup4() {
        Subtasks({1, 2, 5, 7});

        CASE(N = 5,
             P = {1, 1, 1, 3},
             W = {1, 2, 3, 4, 5},
             D = {0, 0, 0, 0, 0});

        CASE(N = 2000,
             P = randomTree(N),
             W = randomArray(N, mnW, mxW),
             D = vector<int>(N, 0));

        CASE(N = 2000,
             P = heavyTree(N, 2),
             W = randomArray(N, mxW / 2, mxW),
             D = vector<int>(N, 0));

        CASE(N = 2000,
             P = lineTree(N),
             W = randomArray(N, mxW / 2, mxW),
             D = vector<int>(N, 0));

        CASE(N = 2000,
             P = sqrtTree(N),
             W = randomArray(N, mxW / 2, mxW),
             D = vector<int>(N, 0));

        CASE(N = 2000,
             P = heavySqrtTree(N, 2),
             W = randomArray(N, mxW / 2, mxW),
             D = vector<int>(N, 0));

        CASE(N = 2000,
             P = lineRandomTree(N),
             W = randomArray(N, mxW / 2, mxW),
             D = vector<int>(N, 0));
    }

    void TestGroup5() {
        Subtasks({1, 2, 3, 7});

        CASE(N = mxN,
             P = vector<int>(N - 1, 1),
             W = randomArray(N, mxW / 2, mxW),
             D = vector<int>(N, 0));
    }

    void TestGroup6() {
        Subtasks({1, 2, 7});

        CASE(N = mxN,
             P = lineTree(N),
             W = randomArray(N, mxW / 2, mxW),
             D = vector<int>(N, 0));

        CASE(N = mxN,
             P = heavyTree(N, 2),
             W = randomArray(N, mxW / 2, mxW),
             D = vector<int>(N, 0));
    }

    void TestGroup7() {
        Subtasks({2, 4, 5, 7});

        CASE(N = 100,
             P = randomTree(N),
             W = vector<int>(N, 1),
             D = randomD(N, true));

        CASE(N = 100,
             P = heavyTree(N, 2),
             W = vector<int>(N, 1),
             D = dMax(N));

        CASE(N = 100,
             P = lineTree(N),
             W = vector<int>(N, 1),
             D = dMax(N));

        CASE(N = 100,
             P = sqrtTree(N),
             W = vector<int>(N, 1),
             D = dMax(N));

        CASE(N = 100,
             P = heavySqrtTree(N, 2),
             W = vector<int>(N, 1),
             D = dMax(N));
    }

    void TestGroup8() {
        Subtasks({2, 5, 7});

        CASE(N = 5,
             P = {1, 1, 1, 3},
             W = {1, 2, 3, 4, 5},
             D = {0, 0, 1, 0, 0});

        CASE(N = 2000,
             P = randomTree(N),
             W = randomArray(N, mxW / 2, mxW);
             D = randomD(N, true));

        CASE(N = 2000,
             P = lineTree(N),
             W = randomArray(N, mxW / 2, mxW),
             D = dMax(N));

        CASE(N = 2000,
             P = heavyTree(N, 2),
             W = randomArray(N, mxW / 2, mxW),
             D = dMax(N));

        CASE(N = 2000,
             P = sqrtTree(N),
             W = randomArray(N, mxW / 2, mxW),
             D = dMax(N));

        CASE(N = 2000,
             P = heavySqrtTree(N, 2),
             W = randomArray(N, mxW / 2, mxW),
             D = dMax(N));
    }

    void TestGroup9() {
        Subtasks({2, 7});

        CASE(N = mxN,
             P = randomTree(N),
             W = randomArray(N, mxW / 2, mxW),
             D = randomD(N, true));

        CASE(N = mxN,
             P = lineTree(N),
             W = randomArray(N, mxW / 2, mxW),
             D = randomD(N, true));

        CASE(N = mxN,
             P = heavyTree(N, 2),
             W = randomArray(N, mxW / 2, mxW),
             D = randomD(N, true));

        CASE(N = mxN,
             P = sqrtTree(N),
             W = randomArray(N, mnW, mxW),
             D = randomD(N, true));

        CASE(N = mxN,
             P = heavySqrtTree(N, 2),
             W = randomArray(N, mnW, mxW),
             D = randomD(N, true));
    }

    void TestGroup10() {
        Subtasks({2, 3, 7});

        CASE(N = mxN,
             P = vector<int>(N - 1, 1),
             W = randomArray(N, mxW / 2, mxW),
             D = dMax(N));
    }

    void TestGroup11() {
        Subtasks({3, 5, 7}); 

        CASE(N = 10,
             P = {1, 1, 1, 1, 1, 1, 1, 1, 1},
             W = {5, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 
             D = {6, 0, 0, 0, 0, 0, 0, 0, 0, 0});

        CASE(N = 10,
             P = {1, 1, 1, 1, 1, 1, 1, 1, 1},
             W = {100, 1, 2, 3, 4, 5, 6, 7, 8, 9},
             D = {6, 0, 0, 0, 0, 0, 0, 0, 0, 0});

        CASE(N = 2000,
             P = vector<int>(N - 1, 1),
             W = randomArray(N, mxW / 2, mxW);
             D = randomD(N, false));
    }

    void TestGroup12() {
        Subtasks({3, 7});

        CASE(N = mxN,
             P = vector<int>(N - 1, 1),
             W = randomArray(N, mxW / 2, mxW);
             D = randomD(N, false));
    }

    void TestGroup13() {
        Subtasks({4, 5, 6, 7});

        CASE(N = 9,
             P = {1, 1, 2, 2, 3, 3, 4, 4},
             W = vector<int>(N, 1),
             D = {1, 1, 1, 1, 0, 0, 0, 0, 0}); 

        CASE(N = 15,
             P = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7},
             W = vector<int>(N, 1),
             D = {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0});

        CASE(N = rnd.nextInt(20, 97) | 1,
             P = binaryTree(N),
             W = vector<int>(N, 1),
             D = dMid(N));

        CASE(N = 99,
             P = binaryTree(N),
             W = vector<int>(N, 1),
             D = dMid(N));

        CASE(N = 63,
             P = completeBinaryTree(N),
             W = vector<int>(N, 1),
             D = dMid(N));

        CASE(N = 99,
             P = lineBinaryTree(N),
             W = vector<int>(N, 1),
             D = dMid(N));
    }

    void TestGroup14() {
        Subtasks({4, 5, 7});

        CASE(N = 10,
             P = {1, 1, 1, 1, 3, 3, 4, 4, 8},
             W = vector<int>(N, 1),
             D = {3, 0, 2, 1, 0, 0, 0, 1, 0, 0});

        CASE(N = 11,
             P = {1, 1, 1, 1, 3, 3, 3, 3, 7, 7},
             W = vector<int>(N, 1),
             D = {2, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0});

        CASE(N = 100,
             P = heavyTree(N, 2),
             W = vector<int>(N, 1),
             D = randomD(N, false));

        CASE(N = 100,
             P = heavyTree(N, 3),
             W = vector<int>(N, 1),
             D = dMid(N));

        CASE(N = 100,
             P = heavyTree(N, 4),
             W = vector<int>(N, 1),
             D = randomMixD(N));

        CASE(N = 100,
             P = sqrtTree(N),
             W = vector<int>(N, 1),
             D = dMid(N));

        CASE(N = 100,
             P = sqrtTree(N),
             W = vector<int>(N, 1),
             D = randomD(N, false));

        CASE(N = 100,
             P = heavySqrtTree(N, 2),
             W = vector<int>(N, 1),
             D = randomD(N, false));

        CASE(N = 100,
             P = lineRandomTree(N),
             W = vector<int>(N, 1),
             D = randomD(N, false));
    }

    void TestGroup15() {
        Subtasks({5, 6, 7});

        CASE(N = 5,
             P = {1, 1, 3, 3},
             W = {1, 2, 3, 4, 5},
             D = {1, 0, 1, 0, 0});

        CASE(N = 7,
             P = {1, 2, 2, 1, 5, 5},
             W = {5, 2, 1, 4, 3, 8, 7},
             D = {1, 1, 0, 0, 1, 0, 0});

        CASE(N = 9,
             P = {1, 1, 2, 2, 3, 3, 4, 4},
             W = randomArray(N, mnW, mxW),
             D = {1, 1, 1, 1, 0, 0, 0, 0, 0}); 

        CASE(N = 15,
             P = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7},
             W = randomArray(N, mnW, mxW),
             D = {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0});

        CASE(N = 1001,
             P = binaryTree(N),
             W = randomArray(N, mnW, mxW),
             D = dMid(N));

        CASE(N = 1999,
             P = binaryTree(N),
             W = randomArray(N, mnW, mxW),
             D = dMid(N));

        CASE(N = 1023,
             P = completeBinaryTree(N),
             W = randomArray(N, mxW / 2, mxW),
             D = dMid(N));

        CASE(N = 1999,
             P = lineBinaryTree(N),
             W = randomArray(N, mxW / 2, mxW),
             D = dMid(N));
    }

    void TestGroup16() {
        Subtasks({5, 7});

        CASE(N = 2000,
             P = randomTree(N),
             W = randomArray(N, mxW / 2, mxW), 
             D = randomD(N, false));

        CASE(N = 2000,
             P = heavyTree(N, 2),
             W = randomArray(N, mxW / 2, mxW), 
             D = randomD(N, false));

        CASE(N = 2000,
             P = heavyTree(N, 3),
             W = randomArray(N, mxW / 2, mxW), 
             D = dMid(N));

        CASE(N = 2000,
             P = heavyTree(N, 4),
             W = randomArray(N, mxW / 2, mxW), 
             D = randomD(N, false));

        CASE(N = 2000,
             P = sqrtTree(N),
             W = randomArray(N, mxW / 2, mxW), 
             D = randomD(N, false));

        CASE(N = 2000,
             P = sqrtTree(N),
             W = randomArray(N, mxW / 2, mxW), 
             D = randomMixD(N));

        CASE(N = 2000,
             P = heavySqrtTree(N, 2),
             W = randomArray(N, mxW / 2, mxW),
             D = randomD(N, false));

        CASE(N = 2000,
             P = lineRandomTree(N),
             W = randomArray(N, mxW / 2, mxW),
             D = randomD(N, false));
    }

    void TestGroup17() {
        Subtasks({6, 7});

        CASE(N = rnd.nextInt(mxN / 2, mxN - 1) | 1,
             P = binaryTree(N),
             W = randomArray(N, mxW / 2, mxW),
             D = dMid(N));

        CASE(N = mxN - 1,
             P = binaryTree(N),
             W = randomArray(N, mxW / 2, mxW),
             D = dMid(N));

        CASE(N = 65535,
             P = completeBinaryTree(N),
             W = randomArray(N, mxW / 2, mxW),
             D = dMid(N));

        CASE(N = mxN - 1,
             P = lineBinaryTree(N),
             W = randomArray(N, mxW / 2, mxW),
             D = dMid(N));
    }

    void TestGroup18() {
        Subtasks({7});

        CASE(N = mxN,
             P = randomTree(N),
             W = randomArray(N, mxW / 2, mxW), 
             D = randomD(N, false));

        CASE(N = mxN,
             P = heavyTree(N, 2),
             W = randomArray(N, mxW / 2, mxW), 
             D = randomD(N, false));

        CASE(N = mxN,
             P = heavyTree(N, 3),
             W = randomArray(N, mxW / 2, mxW), 
             D = dMid(N));

        CASE(N = mxN,
             P = heavyTree(N, 4),
             W = randomArray(N, mxW / 2, mxW), 
             D = randomD(N, false));

        CASE(N = mxN,
             P = heavyTree(N, 2),
             W = randomArray(N, mxW / 2, mxW),
             D = randomMixD(N));

        CASE(N = mxN,
             P = sqrtTree(N),
             W = randomArray(N, mxW / 2, mxW), 
             D = randomD(N, false));

        CASE(N = mxN,
             P = sqrtTree(N),
             W = randomArray(N, mxW / 2, mxW), 
             D = dMid(N));

        CASE(N = mxN,
             P = heavySqrtTree(N, 2),
             W = randomArray(N, mxW / 2, mxW),
             D = randomD(N, false));

        CASE(N = mxN,
             P = heavySqrtTree(N, 2),
             W = randomArray(N, mxW / 2, mxW),
             D = randomMixD(N));

        CASE(N = mxN,
             P = lineRandomTree(N),
             W = randomArray(N, mxW / 2, mxW),
             D = randomD(N, false));
    }

private:
    void getChild() {
        child.clear();
        child.resize(N, 0);
        for (int i : P) {
            child[i - 1]++;
        }
    }

    vector<int> randomArray(int sz, int lo, int hi) {
        vector<int> res(sz);
        for (auto &i : res) {
            i = rnd.nextInt(lo, hi);
        }
        return res;
    }

    // tree generator
    vector<int> randomTree(int sz) {
        // jika kurang berkenan dengan fungsi random Tree ini, tolong beritahu cara lebih baik
        vector<int> res(sz - 1);
        for (int i = 0; i < sz - 1; i++) {
            res[i] = rnd.nextInt(1, i + 1);
        }
        return res;
    }

    vector<int> heavyTree(int sz, int heavy) {
        // tree yang memiliki heavy degree sebanyak int heavy (parameter fungsi)
        // heavy degree adalah banyak connection node yang cukup banyak
        vector<int> res(sz - 1);
        assert(heavy <= sz);
        heavy = sz / heavy;
        int par = 1;
        for (int i = 0; i < sz - 1; i++) {
            res[i] = par;
            if ((i + 2) % heavy == 0) {
                par = i + 2;
            }
        }
        return res;
    }

    vector<int> lineTree(int sz) {
        vector<int> res(sz - 1);
        iota(res.begin(), res.end(), 1);
        return res;
    }

    vector<int> binaryTree(int sz) {
        // assume sz = ganjil
        assert(sz%2 == 1);

        vector<int> res(sz - 1);

        ost<int> pbds;
        pbds.insert(1);

        for (int i = 2; i <= sz; i += 2) {
            int id = rnd.nextInt(0, (int) pbds.size() - 1); 
            int par = *pbds.find_by_order(id);
            pbds.erase(par);
            res[i - 2] = par;
            res[i - 1] = par;
            pbds.insert(i);
            pbds.insert(i + 1);
        }

        return res;
    }

    vector<int> completeBinaryTree(int sz) {
        // assume sz = 2^k - 1
        assert((sz & (sz + 1)) == 0);

        vector<int> res(sz - 1);
        for (int i = 2; i <= sz; i++) {
            res[i - 2] = i / 2;
        }
        return res;
    }

    vector<int> lineBinaryTree(int sz) {
        // binary tree: node yang punya anak selalu node ganjil
        // assume sz = ganjil
        assert(sz%2 == 1);

        vector<int> res(sz - 1);
        for (int i = 2; i <= sz; i += 2) {
            res[i - 2] = i - 1;
            res[i - 1] = i - 1;
        }
        return res;
    }

    vector<int> sqrtTree(int sz) {
        // tree yang parent nya adalah sqrt(i)
        vector<int> res(sz - 1);
        for (int i = 2; i <= sz; i++) {
            res[i - 2] = sqrt(i);
        }
        return res;
    }

    vector<int> heavySqrtTree(int sz, int heavy) {
        // campuran heavy tree dan sqrt tree

        vector<int> res(sz - 1);
        assert(heavy <= sz);
        heavy = sz / heavy;

        bool sqrTime = true;
        int par = 1;

        for (int i = 0; i < sz - 1; i++) {
            res[i] = par;
            if ((i + 2) % heavy == 0) {
                par = i + 2;
                sqrTime = false;
            }
            if (sqrTime) {
                res[i] = sqrt(i + 2);
            }
        }

        return res;
    }

    vector<int> lineRandomTree(int sz) {
        int lineNode = rnd.nextInt(4, 7);
        lineNode = sz / (lineNode + 1) * lineNode;

        vector<int> res(sz - 1);
        for (int i = 0; i < sz - 1; i++) {
            if (i <= lineNode) { // line parts
                res[i] = i + 1;
            } else { // random parts
                res[i] = rnd.nextInt(1, i + 1);
            }
        }

        return res;
    }

    // D generator
    vector<int> randomD(int sz, bool isSubtask2) {
        vector<int> res(sz);
        getChild();
        for (int i = 0; i < sz; i++) {
            if (isSubtask2) {
                res[i] = rnd.nextInt(0, 1);
                if (res[i] == 1) res[i] = child[i];
            } else {
                res[i] = rnd.nextInt(0, child[i]);
            }
        }
        if (isSubtask2) {
            // kita gak mau dia satisfies subtask 1, karena klo subtask 1 udah di generate menggunakan D = vector<int>(N, 0), jadi cari cara untuk ganti D[i] selain 0 untuk suatu nilai i
            bool isSubtask1 = true;
            for (int i = 0; i < sz; i++) {
                if (res[i] != 0) {
                    isSubtask1 = false;
                    break;
                }
            }
            if (isSubtask1) {
                for (int i = 0; i < sz; i++) {
                    if (child[i] != 0) {
                        res[i] = child[i];
                        break;
                    }
                }
            }
        } else {
            // kita gak mau dia satisfies subtask 2, jadi cari cara untuk ganti D[i] selain 0 dan deg[i] untuk suatu nilai i
            isSubtask2 = true;
            for (int i = 0; i < sz; i++) {
                if (res[i] != 0 || res[i] != child[i]) {
                    isSubtask2 = false;
                    break;
                }
            }
            if (isSubtask2) { 
                for (int i = 0; i < sz; i++) {
                    if (child[i] > 1) {
                        res[i] = child[i] / 2;
                        isSubtask2 = false;
                        break;
                    }
                }
            }
        }
        return res;
    }

    vector<int> dMax(int sz) {
        vector<int> res(sz);
        getChild();
        for (int i = 0; i < sz; i++) {
            res[i] = child[i];
        }
        return res;
    }

    vector<int> dMid(int sz) {
        vector<int> res(sz);
        getChild();
        for (int i = 0; i < sz; i++) {
            res[i] = child[i] / 2;
        }
        return res;
    }

    vector<int> randomMixD(int sz) {
        // harus ada (i, j, k)
        // res[i] = 0
        // res[j] = child[j]
        // res[k] = child[k] / 2
        // sisanya random

        assert(sz >= 3);

        vector<int> res(sz);
        getChild();

        int argmin = -1, minsofar = 1e9;
        int argmax = -1, maxsofar = -1;

        for (int i = 0; i < sz; i++) {
            if (child[i] < minsofar) { // get the first minimum
                minsofar = child[i];
                argmin = i;
            }
            if (child[i] >= maxsofar) { // get the last maximum
                maxsofar = child[i];
                argmax = i;
            }
        }

        int argmid = -1;
        for (int i = 0; i < 3; i++) {
            if (argmin == i || argmax == i) continue;
            argmid = i;
            break;
        }

        for (int i = 0; i < sz; i++) {
            if (i == argmin) {
                res[i] = 0;
            } else if (i == argmax) {
                res[i] = child[i];
            } else if (i == argmid) {
                res[i] = child[i] / 2;
            } else {
                res[i] = rnd.nextInt(0, child[i]);
            }
        }

        return res;
    }
};
