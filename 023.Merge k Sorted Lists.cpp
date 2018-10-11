题意：
汇合多路已经排序好的链表
--------------------------------------------------
法一：二分法
应用二路合并的方法，两两合并链表，直到合并成一个链表
k表示平均一个链表的长度, n表示一共有几个链表
T(n) = n/2 * 2k + n/4 * 4k +...+ n/2^n + 2^nk
     = logn * nk
     = O(nklogn)
思路：
1.用二分法分别求出第一个链表和最后一个链表合并后的链表，作为新的lists[0],同时向内部移动
2.直到只剩下一个链表，即end元素为0的时候返回lists[0]
3.两个链表汇合的方法同021题，注意新建dummy结点便于操作头结点
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size() == 0) return NULL;
        int end = lists.size() -1;
        while(end > 0){
            int begin = 0;
            while(begin < end){
                lists[begin] = mergeList(lists[begin],lists[end]);
                ++begin;
                --end;
            }
        }
        return lists[0];
    }
    ListNode* mergeList(ListNode*p, ListNode*q){
        ListNode *dummy = new ListNode(-1);
        ListNode *pre = dummy;
        while(p && q){
            if(p -> val <= q -> val){
                pre -> next = p;
                p = p -> next;
            }
            else{
                pre -> next = q;
                q = q -> next;
            }
            pre = pre -> next;
        }
        if(p){
            pre -> next = p;
        }else{
            pre -> next = q;
        }
        return dummy -> next;
    }
};
--------------------------------------------------
法2:最小堆min heap
priority queue的大小为始终为k，而每次插入的复杂度是log k，一共插入过nk个节点
T(n) = O(nklogn)
S(n) = O(k);
思路：
1.创建一个队列，每次push进去每个链表的第一个元素，队列中的元素会按照由小到大的顺序排放
2.建立一个dummy头结点和一个指针，每次读取queue中的第一个元素，只要这个元素后面还有元素，那么再push进来
即每从queue中取出一个节点，则将该节点在其list中的下一个节点插入，以此类推直到全部节点都经过priority queue
3.最后返回dummy -> next;
补充：
1.priority_queue是c++ STL里面的模版
2.priority_queue<Type, Container, Functional>
Type为数据类型， Container为保存数据的容器，Functional为元素比较方式。
如果不写后两个参数，那么容器默认用的是vector，比较方式默认用operator<，也就是优先队列是大顶堆，队头元素最大。
3.STL里面定义了一个仿函数 greater<>，对于基本类型可以用这个仿函数声明小顶堆
priority_queue<int, vector<int>, greater<int> >q；
只有在int类型的时候可以用greater<int>
4.如果是其他类型声明小顶堆，需要重新构造，自己重载 operator< 或者自己写仿函数，制造小顶堆
struct cmp{
    bool operator()(ListNode *a ,ListNode *b){
        return a -> val > b -> val;
    }
};
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct cmp{
    bool operator()(ListNode *a ,ListNode *b){
        return a -> val > b -> val;
    }
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>,cmp>q;
        for(int i = 0; i < lists.size(); ++i){
            if(lists[i]) q.push(lists[i]);
        }
        
        ListNode *dummy = new ListNode(-1);
        ListNode *temp = dummy;
        while(!q.empty()){
            temp -> next = q.top();
            q.pop();
            temp = temp -> next;
            if(temp -> next) q.push(temp -> next);
        }
        
        return dummy -> next;
    }
};