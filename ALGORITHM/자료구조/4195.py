import sys

input = sys.stdin.readline


class Set:
    def __init__(self, N):
        self.S = [-1 for _ in range(N)]
        self.C = [1 for _ in range(N)]
        Set.size = N

    def find(self, u):
        to_change = []

        def up_ward(i):
            set_num = self.S[i]
            if set_num < 0:
                return i
            else:
                to_change.append(i)
                return up_ward(set_num)

        res = up_ward(u)
        for i in to_change:
            self.S[i] = res
        return res

    def count(self, u):
        u = self.find(u)
        return self.C[u]

    def union(self, u, v):
        u = self.find(u)
        v = self.find(v)

        if u != v:
            if self.S[u] < self.S[v]:
                self.S[v] = u
                self.C[u] += self.C[v]
            elif self.S[u] > self.S[v]:
                self.S[u] = v
                self.C[v] += self.C[u]
            else:
                self.S[u] -= 1
                self.S[v] = u
                self.C[u] += self.C[v]
            Set.size -= 1


test_case_n: int = int(input())

for _ in range(test_case_n):
    F: int = int(input())
    name_dic = {}
    counter = 1
    network = Set(F * 2 + 1)
    for _ in range(F):
        [p, q] = input().strip().split(" ")
        idx_p = name_dic.get(p)
        if idx_p is None:
            idx_p = name_dic[p] = counter
            counter += 1
        idx_q = name_dic.get(q)
        if idx_q is None:
            idx_q = name_dic[q] = counter
            counter += 1
        network.union(idx_p, idx_q)

        print(network.count(idx_p))
