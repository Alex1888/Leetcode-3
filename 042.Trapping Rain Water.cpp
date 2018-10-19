elevation 海拔
题意：
在不同海拔高度的地方下雨，因为高度差会有积水，求积水量。
方法1:stack
思路：
1.通过分析题意得到如果stack为空或者后面的海拔高度低于等于前一位，没有高度差，无法积水，入栈。
2.如果高于前一位，出栈，如果栈为空也要扔掉，因为没有差距没有坑。
3.当高度和宽度都有差距的时候，取两者高度较小的一个减去坑的高度*两者的宽度差就是水的多少。
注意：
1.所谓的高度差都是当前元素与其前一位置的元素，即栈顶元素比较。
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int>st;
        int ret = 0;
        int i = 0;
        while(i < height.size()){
            if(st.empty()||height[i]<=height[st.top()]){
                st.push(i);
                ++i;
            }else{
                int j = st.top();
                st.pop();
                if(st.empty()) continue;
                ret += (min(height[i],height[st.top()])-height[j])*(i-st.top()-1);
            }
        }
        return ret;
    }
};
方法二：dp两次遍历数组
思路：
1.针对每一个坐标而言，因为一点是否有积水是其左右海拔决定的，因此找到其最大的左坐标，再找到其最大的右坐标，两者取其小就是当前下雨后的位置
2.再用下雨后的位置减去下雨前的位置，就是积水量
class Solution {
public:
    int trap(vector<int>& height) {
        vector<int>dp(height.size(),0);
        int m = 0;
        int ret = 0;
        for(int i = 0; i< height.size();++i){
            dp[i] = m;
            m = max(m,height[i]);
        }
        m = 0;
        for(int i = height.size()-1;i> 0; --i){
            dp[i]= min(m,dp[i]);
            m = max(m,height[i]);
            if(dp[i] > height[i]) ret += dp[i]-height[i];
        }
        return ret;
    }
};
方法三：两个指针一次性扫描数组
思路：
1.可以从图中直观的看到，如果设置两个指针从头尾中较小值开始扫描，哪边小移动哪边，如果更小的值，将差值加到ret中，如果遇到更大的值，那么重新确定左右窗口
2.直到左右指针相遇后返回结果
class Solution {
public:
    int trap(vector<int>& height) {
        int l = 0; 
        int r = height.size()-1;
        int ret = 0;
        while(l < r){
            int m = min(height[l],height[r]);
            if(m == height[l]){
                ++l;
                while(l < r && height[l]< m){
                    ret += m-height[l];
                    ++l;
                }
            }else{
                --r;
                while(l < r && height[r]< m){
                    ret += m-height[r];
                    --r;
                }
            }
        }
        return ret;
    }
};