#include <algorithm>
#include <iostream>
#include <memory>
#include <numeric>
#include <vector>

using namespace std;

// * Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        if (!l1 || !l2) {
            return nullptr;
        }
        std::string str1, str2;
        str1 += *l1->val;
        str2 += *l2->val;
        while (*l1->next) {
            str1 += l1->val;
        }
        while (*l2->next) {
            str1 += l2->val;
        }
        std::stoi(str1);
        std::stoi(str2);
        int res = str1 + str2;
        std::to_string(res);
        ListNode res;
        for (const char chr : res) {
            ListNode res(chr, nullptr);
            
        }
    }
}

int
main() {
    ListNode node;
    auto l1 = {2, 4, 3};
    auto l2 = {5, 6, 4};
    for (auto i : l1) {
    }
    node(, ptr)
            std::cout
        << '\n';
}
