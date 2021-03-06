题意：
反转字符串，但是是反转字符串中所有的字母，不是字母的话跳过。
例子：
Input: "ab-cd"
Output: "dc-ba"
Input: "a-bC-dEf-ghIj"
Output: "j-Ih-gfE-dCba"
Input: "Test1ng-Leet=code-Q!"
Output: "Qedo1ct-eeLg=ntse-T!"
思路：
1.设置一头一尾两个指针循环string
2.当头指针小于尾指针的时候，用isalpha()方法判断当前元素是否是字母，如果是，头指针++，尾指针--
3.直到找到第一位字母元素，交换，头指针++，尾指针--
注意：
1.有可能string中没有字母，那么p会一直递增，因此在判断p是否是字母的时候需要判断如果p大于原字符串的长度，那么直接返回原字符串
2.还有一种情况是，p找到了不是字母元素之后，其位置已经大于等于q,这种情况也应该直接输出
e.g. tNh95p+tv
class Solution {
public:
    string reverseOnlyLetters(string S) {
        int p = 0;
        int q = S.size()-1;
        char temp;
        while(p + 1 <= q){
            while(!isalpha(S[p])) {
                ++p;
                if(p >= S.size()-1 || p == q)
                    return S;
            }
            while(!isalpha(S[q])){
                --q;
            }
            temp = S[p];
            S[p] = S[q];
            S[q] = temp;
            ++p;
            --q;
        }
        return S;
    }
};
Weekly Contest 105总结:
1.只做出来了一道easy题，WA了三次才AC，30分钟49秒，corner cases考虑不周。
在平时做题的时候需要着重培养，尽可能想到每一种情况再动手写，写完之后要想反复测试所有情况再提交，重点在于这个思考过程。
2.看了第二题，是让找环形数组中最大的数组之和。
可笑的是读懂了题意之后想到了与第53题（找最大数组之和，连题号都能记得）有异曲同工之处，想了3秒没有认真思考就开始翻之前的笔记。
这种做法下次应该避免，见到问题思考解决问题的方法，而不是答案。
我想这和我平时做题的习惯有关，一旦遇到没有思路的题目就开始看详解和discussion，无论如何自己思考的10分钟这个过程是必须要有。同时还需要大量刷题，有思路的题目不会出现这种情况。
3.看了53题的笔记，发现仍然没有完全掌握，我想就算是给53题原题也不能AC。
刷题时理解不透彻，当时会写了其实思路的源头并没有完全掌握，复习不及时。
每次刷题切忌背代码，一定要自己理解了再写，同时把复习写过的题目放到刷题计划里。
另外，看了之前记的笔记，也不是清晰易懂，仍然需要反复读来理解，说明一当时理解的不透彻，二记笔记的方法有问题。
提高方法：
*首先题目必须完全理解再总结思路，并总结为什么X题要用到X算法或数据结构，根本上解决了什么问题。
*每个步骤的思路都需要按点列出，注意条理。
*重点关注在每道题目卡顿的地方，这次卡顿的点一定也会是下一次卡顿的地方，只有把这些点突破才能有所进步。
