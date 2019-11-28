// sum of two numbers.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack> 
#include <queue>
#include <array>
#include <algorithm>
using namespace std;


struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
	// 二叉树最大深度
	int maxDepth(TreeNode* root) {
		if (root == NULL) return 0;
		int left_depth = maxDepth(root->left);
		int right_depth = maxDepth(root->right);
		return max(left_depth, right_depth) + 1;
	}

	// 两数相加
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> mymap;
		vector<int> res(2, 0);
		for (int i = 0; i < nums.size(); i++) {
			int sub = target - nums[i];
			if (mymap.find(sub) != mymap.end()) { 
				res[0] = mymap[sub];
				res[1] = i;

				return res;
			}
			mymap[nums[i]] = i;
		}
		return vector<int>(nums[0], nums[1]);
	}

	// 整数反转
	int reverse(int x) {
		if (x <= INT_MIN) {
			return 0;
		}

		int f = 1;
		if (x < 0) {
			f = -1;
		}
		x = abs(x);
		string str_x = to_string(x);
		int length = str_x.length();
		int j = length - 1;
		long long long_x;
		for (int i = 0; i < length; i++) {
			if (i >= j) {
				long_x = stoll(str_x);
				// long_x *= f;

				if (long_x > INT_MAX) {
					return 0;
				}
				else {
					return (int)long_x* f;
				}
			}

			swap(str_x[i], str_x[j]);
			j--;
		}
		return 0;
	}

	// 回文数
	bool isPalindrome(int x) {
		if (x < 0) {
			return false;
		}

		string str_x = to_string(x);
		int length = str_x.length();

		int j = length - 1;
		for (int i = 0; i < length; i++) {
			if (i >= j) {
				return true;
			}
			if (str_x[i] != str_x[j]) {
				return false;
			}
			j--;
		}
	}

	// 罗马数字转整数
	int romanToInt(string s) {
		int num = 0;
		unordered_map<char, int> mymap = {
			{'I', 1},
			{'V', 5},
			{'X', 10},
			{'L', 50},
			{'C', 100},
			{'D', 500},
			{'M', 1000}
		};

		if (s.length() == 1) {
			return mymap[s[0]];
		}

		for (int i = 0; i < s.length(); i++) {
			int num1 = mymap[s[i]];
			int num2 = mymap[s[i + 1]];

			if (num1 < num2) {
				num += num2 - num1;
				i++;
			}
			else {
				num += num1;
			}
		}

		return num;
	}

	// 最长公共字符串
	string longestCommonPrefix(vector<string>& strs) {
		vector<string> s;
		int min_length = INT_MAX, cur_length;
		char cur_char;

		if (strs.size() == 0) {
			return "";
		}
		else if (strs[0].length() == 0) {
			return "";
		}
		else if (strs.size() == 1) {
			return strs[0];
		}

		for (int i = 0; i < strs.size(); i++) {
			cur_length = strs[i].length();
			if (min_length > cur_length) {
				min_length = cur_length;
			}
		}

		for (int i = 0; i < min_length; i++) {
			cur_char = strs[0][i];
			for (int j = 1; j < strs.size(); j++) {
				if (strs[j][i] != cur_char) {
					return strs[0].substr(0, i);
				}
			}
		}
		return strs[0].substr(0, min_length);
	}

	// 有效的括号
	bool isValid(string s) {
		stack<char> _stack;
		char need;
		unordered_map<char, char> _map{
			{'(', ')'},
			{'[', ']'},
			{'{', '}'}
		};

		if (s.length() == 0) {
			return true;
		}
		if ((s.length() == 1) || (_map.find(s[0]) == _map.end())) {
			return false;
		}

		for (auto i : s) {
			if (_map.find(i) == _map.end()) {
				if (_stack.empty()) {
					return false;
				}
				if (_map[_stack.top()] != i) {
					return false;
				}
				else {
					_stack.pop();
				}
			}
			else {
				_stack.push(i);
			}
		}
		if (!_stack.empty()) {
			return false;
		}
		return true;
	}

	// 合并有序链表
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode* new_l = NULL;
		ListNode* p = new_l, * p1 = l1, * p2 = l2;
		int val0, val1, val2;
		if ((p1 == NULL) && (p2 != NULL)) {
			return l2;
		}
		else if ((p1 != NULL) && (p2 == NULL)) {
			return l1;
		}
		else if ((p1 == NULL) && (p2 == NULL)) {
			return l1;
		}
		while ((p1 != NULL) && (p2 != NULL)) {
			val1 = p1->val;
			val2 = p2->val;
			if (val1 < val2) {
				val0 = val1;
				p1 = p1->next;
			}
			else {
				val0 = val2;
				p2 = p2->next;
			}
			if (new_l == NULL) {
				new_l = new ListNode(val0);
				p = new_l;
			}
			else {
				p->next = new ListNode(val0);
				p = p->next;
			}
		}
		while ((p1 == NULL) && (p2 != NULL)) {
			p->next = new ListNode(p2->val);
			p = p->next;
			p2 = p2->next;
		}
		while ((p1 != NULL) && (p2 == NULL)) {
			p->next = new ListNode(p1->val);
			p = p->next;
			p1 = p1->next;
		}
		return new_l;
	}
	// 删除有序数组的重复项
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() == 0) {
			return 0;
		}
		int i = 0;
		for (int j = 0; j < nums.size(); j++) {
			if (nums[i] != nums[j]) {
				swap(nums[++i], nums[j]);
			}
		}
		return i + 1;
	}
	// 移除元素
	int removeElement(vector<int>& nums, int val) {
		if (nums.size() == 1) {
			if (nums[0] == val) return 0;
			else return 1;
		}
		else if (nums.size() == 0) return 0;
		int length = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] != val) {
				length = i + 1;
				continue;
			}
			for (int j = i; j < nums.size(); j++) {
				if (nums[i] != nums[j]) {
					swap(nums[i], nums[j]);
					length = i + 1;
					break;
				}
			}
		}
		return length;
	}

	// strStr()
	int strStr(string haystack, string needle) {
		if (needle.size() == 0) {
			return 0;
		}
		else if (haystack.size() < needle.size()) {
			return -1;
		}
		int needle_length = needle.size();
		string win_str;
		for (int i = 0; i < haystack.size() - needle_length + 1; i++) {
			win_str = haystack.substr(i, needle_length);
			// cout << "i: " << i << "   win_str: " << win_str << endl;
			if (win_str == needle) {
				return i;
			}
		}
		return -1;
	}
	// 搜索插入位置
	int searchInsert(vector<int> & nums, int target) {
		int pos1 = 0, pos2 = nums.size() - 1, center;
		if (nums[pos1] > target) {
			return 0;
		}
		else if (nums[pos2] < target) {
			return nums.size();
		}
		while (pos1 != pos2) {
			// cout << "pos1: " << pos1 << "    pos2: " << pos2 << endl;
			center = (pos1 + pos2) / 2;
			if (nums[center] == target) {
				return center;
			}
			else if (nums[center] < target) {
				if (pos1 != center) pos1 = center;
				else {
					return pos1 + 1;
				}
			}
			else if (nums[center] > target) {
				if (pos2 != center) pos2 = center;
				else {
					return pos2 - 1;
				}
			}
		}
		return pos1;
	}
	// 报数
	string countAndSay(int n) {
		string res = "1", new_res;
		int length;
		char val = NULL;
		if (n == 1) {
			return res;
		}
		for (int i = 1; i < n; i++) {
			new_res = "";
			length = 0;
			val = res[0];
			for (auto _i : res) {
				if (val == _i) {
					length++;
				}
				else {
					new_res = new_res + to_string(length) + val;
					val = _i;
					length = 1;
				}
			}
			res = new_res + to_string(length) + val;
			// cout << res << endl;
		}
		return res;
	}
	// 最大子序列和(动态规划
	int maxSubArray(vector<int> & nums) {
		int max_sum = nums[0];
		vector<int> dp(nums.size());
		dp[0] = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			dp[i] = max(dp[i - 1] + nums[i], nums[i]);
			max_sum = max(dp[i], max_sum);
		}
		return max_sum;
	}
	// 两数相加
	ListNode* addTwoNumbers(ListNode * l1, ListNode * l2) {
		int length1 = 0, length2 = 0;
		ListNode* p1 = l1, * p2 = l2;
		while (p1->next != NULL) {
			length1++;
			p1 = p1->next;
		}
		while (p2->next != NULL) {
			length2++;
			p2 = p2->next;
		}
		length1++;
		length2++;
		int sub_length = abs(length1 - length2);
		ListNode * l_zero = NULL, *p_zero = NULL;
		for (int i = 0; i < sub_length; i++) {
			if (i == 0) {
				l_zero = new ListNode(0);
				p_zero = l_zero;
				continue;
			}
			p_zero->next = new ListNode(0);
			p_zero = p_zero->next;
		}
		if (length1 > length2) {
			p2->next = l_zero;
		}
		else if (length1 < length2) {
			p1->next = l_zero;
		}
		p1 = l1;
		p2 = l2;
		int node_sum = 0, flag = 0;
		ListNode* new_l = NULL, * new_p = NULL;

		for (int i = 0; i < max(length1, length2); i++) {
			node_sum = p1->val + p2->val;
			if (i == 0) {
				new_l = new ListNode(node_sum % 10);
				new_p = new_l;
			}
			else {
				new_p->next = new ListNode((node_sum + flag) % 10);
				new_p = new_p->next;
			}
			p1 = p1->next;
			p2 = p2->next;
			if (node_sum + flag >= 10) flag = 1;
			else flag = 0;
		}
		if (flag == 1) {
			new_p->next = new ListNode(1);
		}
		return new_l;
	}
	// 无重复串长度
	int lengthOfLongestSubstring(string s) {
		unsigned int length = 0;
		vector<char> ele;
		for (auto i : s) {
			if (find(ele.begin(), ele.end(), i) == ele.end()) {
				ele.push_back(i);
				continue;
			}
			length = max(length, ele.size());
			ele.erase(ele.begin(), find(ele.begin(), ele.end(), i) + 1);
			ele.push_back(i);
		}
		return max(length, ele.size());
	}
	// atoi(有点麻烦的题, 要考虑各种case
	int myAtoi(string str) {
		int res = 0;
		int i = 0;
		int flag = 1;
		// 1. 检查空格
		while (str[i] == ' ') { i++; }
		// 2. 检查符号
		if (str[i] == '-') { flag = -1; }
		if (str[i] == '+' || str[i] == '-') { i++; }
		// 3. 计算数字
		while (i < str.size() && isdigit(str[i])) {
			int r = str[i] - '0';
			// ------ 4. 处理溢出，这是关键步骤 ------
			if (res > INT_MAX / 10 || (res == INT_MAX / 10 && r > 7)) {
				return flag > 0 ? INT_MAX : INT_MIN;
			}
			// ------------------------------------
			res = res * 10 + r;
			i++;
		}
		return flag > 0 ? res : -res;
	}
	// 删除链表的倒数第N个节点
    // 两次遍历
	ListNode* removeNthFromEnd(ListNode * head, int n) {
		ListNode* p = head;
		int length = 0;
		while (p != NULL) {
			p = p->next;
			length++;
		}
		if (length == 1) return NULL;
		p = head;
		int del_position = length - n;
		if (del_position == 0) {
			p = p->next;
			delete head;
			return p;
		}
		for (; del_position > 1; del_position--) {
			p = p->next;
		}
		p->next = p->next->next;
		return head;
	}
    // 双指针一次遍历
	ListNode* removeNthFromEnd2(ListNode * head, int n) {
		ListNode* pre_p = head, * p = head;
		for (int i = 0; i < n; i++) p = p->next;
		if (p == NULL) {
			pre_p = pre_p->next;
			delete head;
			return pre_p;
		}
		while (p->next != NULL) {
			p = p->next;
			pre_p = pre_p->next;
		}
		pre_p->next = pre_p->next->next;
		return head;
	}
	// 最长回文子串(动态规划, 有点难...
	void longestPalindrome(string s) {
		// 思路: dp[i][j]代表第i个元素到第j个元素是否为回文子串
		//       要满足dp[i][j]为回文子串, 那么dp[i+1][j-1]必定是回文子串
		//       因此dp[i][j]为回文子串的条件为 dp[i+1][j-1] && s[i] == s[j];
		int length = s.size(), pos1, pos2;
		vector<vector<bool>> dp(length, vector<bool>(length, false));
		// 长度为1和2的情况单独考虑
		for (int len = 1; len <= length; len++) {
			for (int i = 0; i < length; i++) {
				int j = i + len - 1;
				if (j >= length) break;
				cout << s.substr(i, len) << "    i, j: " << i << ", " << j << endl;
				if (len == 2) dp[i][j] = s[i] == s[j];
				else  dp[i][j] = (len == 1 || (dp[i + 1][j - 1] && (s[i] == s[j])));
				if (dp[i][j]) {
					pos1 = i;
					pos2 = j;
				}
			}
		}
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j++) {
				cout << dp[i][j] << " ";
			}
			cout << endl;
		}
		cout << s.substr(pos1, pos2 - pos1 + 1) << endl;

	}
	// 电话号码字母组合
    // BFS
	vector<string> letterCombinations(string digits) {
		unordered_map<int, string> _map = {
			{'2', "abc"},
			{'3', "def"},
			{'4', "ghi"},
			{'5', "jkl"},
			{'6', "mno"},
			{'7', "pqrs"},
			{'8', "tuv"},
			{'9', "wxyz"}
		};
		vector<string> res;
		queue<string> q;
		// 第一层
		for (auto i : _map[digits[0]]) {
			string temp;
			temp.push_back(i);
			q.push(temp);
		}
		// 其它层
		string _res;
		int q_len = q.size();
		for (int i = 1; i < digits.length(); i++) {
			while (q_len--) {
				_res = q.front();
				for (auto e : _map[digits[i]]) {
					_res.push_back(e);
					q.push(_res);
					_res = q.front();
				}
				q.pop();
			}
			q_len = q.size();
		}
		while (!q.empty()) {
			cout << q.front() << endl;
			res.push_back(q.front());
			q.pop();
		}
		return res;
	}
	// 三数之和(总是超时...好好总结一下
		vector<vector<int>> threeSum(vector<int>& nums) {
			sort(nums.begin(), nums.end());
			vector<vector<int>> res;
			int center, right, s;
			for (int left = 0; left < nums.size(); left++) {
				if (left > 0 && (nums[left] == nums[left - 1])) continue; // 相同元素说明是重复
				if (nums[left] > 0) break; // 最小的数大于0, 则和不可能为0
				center = left + 1;
				right = nums.size() - 1;
				while (center < right) {
					s = nums[left] + nums[center] + nums[right];
					if (s > 0) --right;
					else if (s < 0) ++center;
					else if (s == 0){
						res.push_back({ nums[left], nums[center], nums[right] });
						++center;
						--right; // ++center后会变大, 所以相应的, right要变小也可能和为0
						// 继续检查重复元素
						while (center < right && (nums[center] == nums[center - 1])) ++center;
						while (center < right && (nums[right] == nums[right + 1])) --right;
					}
				}
			}
			return res;
		}
	// Z字形变换(注意去掉'\0', DEBUG半天才发现
		string convert(string s, int numRows) {
			if (s.length() <= 1 || numRows == 1) return s;
			string res = "", r = "";
			vector<string> temp;
			int col = 0, d = numRows - 1;  // 列数, 满列索引
			for (int i = 0; i < s.length(); i++) {
				char e = s[i];
				if (col % d == 0) {
					r += e;
					if (r.length() == numRows || i == s.length() - 1) {
						// for (int _ = 0; _ < numRows - r.length(); _++) r += " ";
						temp.push_back(r);
						r = "";
						++col;
					}
				}
				else {
					for (int _ = 0; _ < numRows; _++) r += " ";
					r[col % d] = e;
					std::reverse(r.begin(), r.end());
					temp.push_back(r);
					++col;
					r = "";
				}
			}
			for (int i = 0; i < numRows; i++) {
				for (int j = 0; j < temp.size(); j++) {
					// cout << temp[j].size() << endl;
					if (temp[j].size() < i) break;
					if (temp[j][i] == ' ' || temp[j][i] == '\0') continue;
					res += temp[j][i];
				}
			}
			return res;
		}
		// 括号生成  全排列数字法
		vector<string> generateParenthesis(int n) { // -1 -> (, 1 -> )
			vector<string> res, cur_s;
			string str;
			for (int i = 0; i < 2 * n; i++) {
				if (i >= n) cur_s.push_back("-1");
				else cur_s.push_back("1");
			}
			next_permutation(cur_s.begin(), cur_s.end()); // 全排列, 找和为0的排列
			while (next_permutation(cur_s.begin(), cur_s.end())) {
				int s = 0;
				str = "";
				for (auto i : cur_s) {
					int _i;
					if (i[1] == '1') {
						_i = 1;
						str += ")";
					}
					else {
						_i = -1;
						str += "(";
					}
					s += _i;
					if (s > 0) break; // 如果>0, 说明加入了单独的反括号
				}
				if (s != 0) continue;
				cout << str << endl;
				res.push_back(str);
			}
			return res;
		}
		// 括号生成  DFS + 少量剪枝
		vector<string> generateParenthesis2(int n) {
			vector<string> res;
			func(res, "", 0, 0, n);
			return res;
		}
		void func(vector<string>& res, string str, int l, int r, int n) {
			if (l > n || r > n || r > l) return;
			if (l == n && r == n) { res.push_back(str); return; }
			func(res, str + '(', l + 1, r, n);
			func(res, str + ')', l, r + 1, n);
			return;
		}
		// 两两交换链表中的节点 普通解法
		ListNode* swapPairs(ListNode* head) {
			if (head == NULL || head->next == NULL) return head;
			ListNode* p1 = head, * p2 = p1->next;
			p1->next = p2->next;
			p2->next = p1;
			head = p2;
			p2 = p1->next;
			while (p1 != NULL && p2 != NULL) {
				if (p2->next == NULL) break;
				p1->next = p2->next;
				p1 = p1->next;
				p2->next = p1->next;
				p1->next = p2;
				p1 = p2;
				p2 = p2->next;
			}
			return head;
		}
		// 两两交换链表中的节点 递归
		ListNode* swapPairs2(ListNode* head) {
			if (head == NULL || head->next == NULL) return head; // 终止条件
			ListNode* next = head->next; // 递归时仅考虑相邻两个节点
			head->next = swapPairs2(next->next);   // 2. 再到这里, head之后是什么是下个递归的事
			next->next = head;  // 1. 先看这里, 每次递归要做的是交换两个节点
			return next;  // next现在是head, 所以return next
		}

		void a(ListNode* head) {
			head->val = 999;
		}
		// 平衡二叉树
		bool isBalanced(TreeNode* root) {
			if (root == NULL) return true;
			int _ = depth(root);
			return root->val <= 1;
		}
		int depth(TreeNode * root) {
			if (root == NULL) return 0;

			int left_depth = depth(root->left);
			int right_depth = depth(root->right);
			// root->val放的是子树和自身最大高度差
			root->val = abs(left_depth - right_depth);
			if (root->right != NULL) root->val = max(root->val, root->right->val);
			if (root->left != NULL) root->val = max(root->val, root->left->val);
			return max(left_depth, right_depth) + 1;
		}
		// 二叉树最小深度(类似求最大深度
		int minDepth(TreeNode* root) {
			if (root == NULL) return 0;

			int left_depth = minDepth(root->left);
			int right_depth = minDepth(root->right);

			if (root->left != NULL && root->right != NULL) return min(left_depth, right_depth) + 1;
			else if (root->left != NULL) return left_depth + 1; // 否则会直接返回0
			else if (root->right != NULL) return right_depth + 1; // 同上
			return 1;
		}
};



int main()
{
	Solution solve;

	ListNode* head = &ListNode(1), *p = head;
	p->next = &ListNode(5);
	solve.a(head);
	cout << head->val;

	return 0;
}
