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

struct Node {
	int val;
	Node* left;
	Node* right;
	Node* next;
	Node() : val(0), left(NULL), right(NULL), next(NULL) {}
	Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
	Node(int _val, Node* _left, Node* _right, Node* _next)
		: val(_val), left(_left), right(_right), next(_next) {}
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
	vector<int> twoSum(vector<int> & nums, int target) {
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
	string longestCommonPrefix(vector<string> & strs) {
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
	ListNode* mergeTwoLists(ListNode * l1, ListNode * l2) {
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
	int removeDuplicates(vector<int> & nums) {
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
	int removeElement(vector<int> & nums, int val) {
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
		unsigned int length = 0, size = 0;
		vector<char> ele;
		for (auto i : s) {
			if (find(ele.begin(), ele.end(), i) == ele.end()) {
				ele.push_back(i);
				size = ele.size();
				continue;
			}
			length = max(length, size);
			ele.erase(ele.begin(), find(ele.begin(), ele.end(), i) + 1);
			ele.push_back(i);
			size = ele.size();
		}
		return max(length, size);
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
	vector<vector<int>> threeSum(vector<int> & nums) {
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
				else if (s == 0) {
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
	void func(vector<string> & res, string str, int l, int r, int n) {
		if (l > n || r > n || r > l) return;
		if (l == n && r == n) { res.push_back(str); return; }
		func(res, str + '(', l + 1, r, n);
		func(res, str + ')', l, r + 1, n);
		return;
	}
	// 两两交换链表中的节点 普通解法
	ListNode* swapPairs(ListNode * head) {
		if (head == NULL || head->next == NULL) return head;
		ListNode * p1 = head, *p2 = p1->next;
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
	ListNode* swapPairs2(ListNode * head) {
		if (head == NULL || head->next == NULL) return head; // 终止条件
		ListNode * next = head->next; // 递归时仅考虑相邻两个节点
		head->next = swapPairs2(next->next);   // 2. 再到这里, head之后是什么是下个递归的事
		next->next = head;  // 1. 先看这里, 每次递归要做的是交换两个节点
		return next;  // next现在是head, 所以return next
	}
	// 平衡二叉树
	bool isBalanced(TreeNode * root) {
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
	int minDepth(TreeNode * root) {
		if (root == NULL) return 0;

		int left_depth = minDepth(root->left);
		int right_depth = minDepth(root->right);

		if (root->left != NULL && root->right != NULL) return min(left_depth, right_depth) + 1;
		else if (root->left != NULL) return left_depth + 1; // 否则会直接返回0
		else if (root->right != NULL) return right_depth + 1; // 同上
		return 1;
	}
	// 不同路径
	int uniquePaths(int m, int n) {
		vector<vector<int>> dp(m, vector<int>(n, 0));
		for (int x = 0; x < m; x++) {
			for (int y = 0; y < n; y++) {
				if (x == 0 || y == 0) dp[x][y] = 1;
				else dp[x][y] = dp[x - 1][y] + dp[x][y - 1];
			}
		}
		return dp[m - 1][n - 1];
	}
	// 不同路径II 带障碍物
	int uniquePathsWithObstacles(vector<vector<int>> & obstacleGrid) {
		int X = obstacleGrid[0].size(), Y = obstacleGrid.size();
		if (obstacleGrid[0][0] == 1 || obstacleGrid[Y - 1][X - 1] == 1) return 0;
		vector<vector<long>> dp(Y, vector<long>(X, 0));  // 存在中间计算值大于INT_MAX的情况, 所以要用long
		for (int y = 0; y < Y; y++) {
			for (int x = 0; x < X; x++) {
				if (obstacleGrid[y][x] == 1) continue;
				if (x == 0 && y == 0) dp[y][x] = 1;
				else if (y == 0 && dp[y][x - 1] != 0) dp[y][x] = 1;
				else if (x == 0 && dp[y - 1][x] != 0) dp[y][x] = 1;
				else dp[y][x] = dp[max(y - 1, 0)][x] + dp[y][max(x - 1, 0)];
				cout << "yx: " << y << " " << x << "  " << dp[y][x] << endl;
			}
		}
		return dp[Y - 1][X - 1];
	}
	// 最小路径和
	int minPathSum(vector<vector<int>> & grid) {
		int X = grid[0].size(), Y = grid.size();
		for (int y = 0; y < Y; y++) {
			for (int x = 0; x < X; x++) {
				if (x == 0 && y == 0) continue;
				if (x == 0) grid[y][x] += grid[y - 1][x];
				else if (y == 0) grid[y][x] += grid[y][x - 1];
				else grid[y][x] += min(grid[y - 1][x], grid[y][x - 1]);
			}
		}
		return grid[Y - 1][X - 1];
	}
	// 解码方法 递归但是把空间复杂度降低到O(1)
	int numDecodings(string s) {
		if (s[0] == '0') return 0;
		int ppre = 1, pre = 1, cur;
		for (int i = 1; i < s.length(); i++) {
			if (s[i] == '0' && s[i - 1] > '2') return 0;
			else if (s[i] == '0' && s[i - 1] > '0') cur = ppre;
			else if ((s[i - 1] == '2' && s[i] <= '6') || s[i - 1] == '1') cur = pre + ppre;
			else if (s[i] != '0') cur = pre;
			else cur = 0;
			ppre = pre;
			pre = cur;
		}
		return pre;
	}
	// 不同的二叉搜索树, 没什么思路...题解有动态规划和catalan数法
	// G(n) = G(0)*G(n-1) + G(1)*G(n-2) + ... + G(n-1)G(0)
	int numTrees(int n) {
		vector<int> dp(n + 2, 0);  // n+2是因为如果n为0的话, 会越界
		dp[0] = dp[1] = 1;
		for (int i = 2; i < n; i++) {
			int _i = i - 1;
			for (int j = 0; j < i; j++) {
				dp[i] += dp[j] * dp[_i - j];
			}
		}
		return dp[n];
	}
	// 不同的二叉搜索树II, 递归
	vector<TreeNode*> generateTrees(int n) {
		vector<TreeNode*> res;
		if (n != 0) res = generate(1, n);
		return res;

	}
	vector<TreeNode*> generate(int start, int end) {
		vector<TreeNode*> all_tree;
		if (start > end) {
			all_tree.push_back(NULL);
			return all_tree;
		}
		for (int i = start; i <= end; i++) {
			vector<TreeNode*> left_tree = generate(start, i - 1);
			vector<TreeNode*> right_tree = generate(i + 1, end);
			for (auto left : left_tree) {
				for (auto right : right_tree) {
					TreeNode* cur_tree = new TreeNode(i);
					cur_tree->left = left;
					cur_tree->right = right;
					all_tree.push_back(cur_tree);
				}
			}
		}
		return all_tree;
	}
	// 买卖股票的最佳时机, 一次遍历
	int maxProfit(vector<int> & prices) {
		int length = prices.size();
		if (length == 0 || length == 1) return 0;
		int _min = INT_MAX, _max = INT_MIN, pos, res = 0;
		for (int i = 0; i < length; i++) {
			int val = prices[i];
			if (_min > val && i != length - 1) {
				_min = val;
				pos = i;
				_max = INT_MIN;
			}
			if (_max < val && pos < i) {
				_max = val;
				int _res = _max - _min;
				if (res < _res) res = _res;
			}
		}
		return res;
	}
	// 三角形最小路径和, 原地求和, 不需要额外空间
	int minimumTotal(vector<vector<int>> & triangle) {
		int length = triangle.size();
		if (length == 0) return 0;
		else if (length == 1) return triangle[0][0];
		for (int i = 1; i < length; i++) {
			for (int j = 0; j < triangle[i].size(); j++) {
				if (j == 0) triangle[i][j] += triangle[i - 1][0];
				else if (j == triangle[i].size() - 1) triangle[i][j] += triangle[i - 1][j - 1];
				else {
					triangle[i][j] += min(triangle[i - 1][j - 1], triangle[i - 1][j]);
				}
			}
		}
		int res = INT_MAX;
		for (auto i : triangle[length - 1]) {
			if (res > i) res = i;
		}
		return res;
	}
	// 爬楼梯
	int climbStairs(int n) {
		int res = 1;
		if (n == 0) return 0;
		if (n == 1) return 1;
		int ppre = 1, pre = 2, cur;
		for (int i = 2; i < n; i++) {
			cur = ppre + pre;
			ppre = pre;
			pre = cur;
		}
		return cur;
	}
	// 单词拆分
	bool wordBreak(string s, vector<string> & wordDict) {
		if (s.size() == 0) return 0;
		vector<bool> dp(s.size() + 1, false);
		dp[0] = true;
		for (int i = 0; i < s.size(); i++) {
			for (string word : wordDict) {
				int pos = i - word.length() + 1;
				if (pos >= 0) {
					int is_word = s.compare(pos, word.length(), word) + 1;
					if (is_word == 1 && dp[pos] == 1) {
						dp[i + 1] = 1;
					}
				}
			}
		}
		return dp[s.size()];
	}
	// 乘积最大子序列, 空间压缩到O(1)
	int maxProduct(vector<int> & nums) {
		int length = nums.size(), res = INT_MIN;
		if (length == 1) return nums[0];
		for (int y = 0; y < length; y++) {
			int cur = 0;
			for (int x = y; x < length; x++) {
				if (y == x) cur = nums[x];
				else cur = cur * nums[x];
				if (res < cur) res = cur;
			}
		}
		return res;
	}
	// 打家劫舍
	int rob(vector<int> & nums) {
		int ppre = 0, pre = 0, cur = 0;
		for (auto num : nums) {
			cur = max(ppre + num, pre);
			ppre = pre;
			pre = cur;
		}
		return cur;
	}
	// 打家劫舍II, 分两种情况同步dp
	// 第一种情况: 偷第一家
	// 第二种情况: 不偷第一家
	int rob2(vector<int> & nums) {
		if (nums.size() == 0) return 0;
		else if (nums.size() == 1) return nums[0];
		else if (nums.size() == 2) return max(nums[0], nums[1]);
		int ppre0 = 0, pre0 = 0, cur0 = 0;
		int ppre1 = 0, pre1 = 0, cur1 = 0;
		for (int i = 0; i < nums.size() - 1; i++) {
			cur0 = max(ppre0 + nums[i], pre0);
			ppre0 = pre0;
			pre0 = cur0;

			cur1 = max(ppre1 + nums[i + 1], pre1);
			ppre1 = pre1;
			pre1 = cur1;
		}
		return max(cur0, cur1);
	}
	// 最大正方形
	int maximalSquare(vector<vector<char>> & matrix) {
		if (matrix.size() == 0) return 0;
		int Y = matrix.size(), X = matrix[0].size(), l = 0, max_l = 0;
		for (int y = 0; y < Y; y++) {
			for (int x = 0; x < X; x++) {
				if (matrix[y][x] != '1') continue;
				bool is_rectangle = true;
				while (is_rectangle) {
					if (x + l >= X || y + l >= Y) {
						is_rectangle = false;
						max_l = max(max_l, l);
						break;
					}
					for (int _x = x; _x < x + l + 1; _x++) {
						if (matrix[y][_x] == '0' || matrix[y + l][_x] == '0') {
							is_rectangle = false;
							break;
						}
					}
					for (int _y = y; _y < y + l; _y++) {
						if (matrix[_y][x] == '0' || matrix[_y][x + l] == '0') {
							is_rectangle = false;
							break;
						}
					}
					if (!is_rectangle) {
						max_l = max(max_l, l);
						l = 0;
						break;
					}
					else ++l;
				}
			}
		}
		return max_l * max_l;
	}
	// 丑数
	int nthUglyNumber(int n) {
		if (n == 0) return 0;
		vector<int> ugly_set = { 2, 3, 5 };
		priority_queue <long long, vector<long long>, greater<long long>> q; // 小顶堆
		q.push(1);
		long long cur = 0;
		for (int i = 0; i < n; i++) {
			if (cur == q.top()) {
				q.pop();
				--i;
				continue;
			}
			cur = q.top();
			q.pop();
			for (auto e : ugly_set) {
				long long _e = e * cur;
				q.push(_e);
			}
		}
		return cur;
	}
	// 完全平方数
	/*
	递归式f(n) = 1 + min{f(n - 1^2), f(n - 2^2), ..., f(n - i^2)}, i^2 >= n;
	例子:
	f(0) = 0, f(1) = 1,
	f(2) = 1 + min{f(1)} = 2
	f(3) = 1 + min{f(2)} = 3
	f(4) = 1 + min{f(3), f(0)} = 1
	f(5) = 1 + min{f(4), f(1)} = 2
	...
	*/
	int numSquares(int n) {
		vector<int> dp = { 0, 1 };
		for (int i = 2; i <= n; i++) {
			int _min = INT_MAX;
			for (int k = 1; pow(k, 2) <= i; k++) _min = min(_min, dp[i - pow(k, 2)]);
			dp.push_back(1 + _min);
		}
		return dp[n];
	}
	// 最长上升子序列
	int lengthOfLIS(vector<int> & nums) {
		if (nums.size() <= 1) return nums.size();
		vector<int> dp(nums.size(), 0);
		dp[0] = 1;
		int res = 1;
		for (int i = 1; i < nums.size(); i++) {
			int max_dp = 0;
			for (int j = 0; j < i; j++) {
				if (nums[j] < nums[i]) max_dp = max(max_dp, dp[j]);
			}
			dp[i] = 1 + max_dp;
			res = max(res, 1 + max_dp);
		}
		return res;
	}
	// 最佳买卖股票时机含冷冻期, 思路不是很清晰.
	// 参考了https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/solution/309-zui-jia-mai-mai-gu-piao-shi-ji-han-leng-dong-q/
	int maxProfit2(vector<int>& prices) {
		if (prices.size() == 0) return 0;
		int hold = -prices[0], sold = 0, rest = 0;  // 初始化资金为0, 从第二天开始算, hold为-prices[0]
		prices.erase(prices.begin(), prices.begin() + 1);  //去掉第一天
		for (int price : prices) {
			int pre_sold = sold;
			sold = hold + price;  // 卖掉后资金为持有资金+股票资金
			hold = max(hold, rest - price);  // 持有资金: 1. 之前持有  2. 买入后持有
			rest = max(rest, pre_sold);  // 什么都不做的资金:  1. 之前什么的不做的资金  2. 昨天卖, 进入解冻期, 所以什么都不做
		}
		return max(rest, sold);  // 最后一天, 要么什么都不做要么卖掉, 绝对不会是持有股票
	}
	// 零钱兑换
	// 状态转移方程: f(n) = 1 + min{f(n - c[0]), f(n - c[1]), ..., f(n - c[i])}
	/*
	f(11) = 1 + min{f(10), f(8), f(6)}
	f(10) = 1 + min{f(9), f(7), f(5)}
	f(9)  = 1 + min{f(8), f(6), f(4)}
	...
	f(3)  = 1 + min{f(2), f(0)} = 1
	f(2)  = 1 + min{f{1}} = 2
	f(1)  = 1 + min{f(0)} = 1
	f(0)  = 0
	*/
	int coinChange(vector<int> & coins, int amount) {
		int res = 0;
		vector<int> f(amount + 1, 0);
		for (int n = 1; n <= amount; n++) {
			int _min = amount + 1;
			for (int i : coins) {
				if (n - i < 0) continue;
				_min = min(_min, f[n - i]);
			}
			f[n] = 1 + _min;
		}
		if (f[amount] > amount) return -1;
		return f[amount];
	}
	// 比特位计数
	// 对于奇数, 1的个数一定与除以2的数加上1相等
	// 对于偶数, 1的个数一定与除以2的数相等
	// 由此得到状态转移方程
	vector<int> countBits(int num) {
		vector<int> dp(num + 1, 0);
		if (num == 0) return dp;
		dp[1] = 1;
		for (int i = 2; i <= num; i++) {
			if (i % 2 == 0) dp[i] = dp[i / 2];
			else dp[i] = dp[i / 2] + 1;
		}
		return dp;
	}
	// 整数拆分
	int integerBreak(int n) {
		vector<int> dp = { 1, 2, 4, 6, 9 };  // 索引0对应数字2
		for (int i = 7; i <= n; i++) {
			int idx = i - 2, _max = INT_MIN;
			for (int j = idx - 1; j >= 0; j--) {
				_max = max(dp[j] * (idx - j), _max);
			}
			dp.push_back(_max);
		}
		return dp[n - 2];
	}
	// 计算各个位数不同的数字个数
	// 数字一共有n位, 第1位用了数字num, 第2位数字的选择就是9-1=8, 第三位再少1, 以此类推
	// f(1) = 10, 初始
	// f(2) -> 9*9 + f(1) = 91
	// f(3) -> 9*9*8 + f(2)
	// ...
	// n > 10 后必定有重复数字, 所以恒为f(10)
	int countNumbersWithUniqueDigits(int n) {
		if (n == 0) return 1;
		int pre_f = 10, bias = 9, num = 10;
		n = min(n, 10);
		for (int i = 2; i <= n; i++) {
			bias *= --num;
			pre_f += bias;
		}
		return pre_f;
	}
	// 最大整除子集
	vector<int> largestDivisibleSubset(vector<int>& nums) {
		if (nums.size() <= 1) return nums;
		vector<int> dp(nums.size(), 0);
		vector<int> path(nums.size(), -1);
		sort(nums.begin(), nums.end());
		int _max = INT_MIN, _idx = 0;
		for (int i = 0; i < nums.size(); i++) {
			for (int j = i; j >= 0; j--) {
				if (nums[i] % nums[j] == 0 && j != i) {
					if (dp[j] + 1 > dp[i]) {
						dp[i] = dp[j] + 1;
						path[i] = j;
					}
					if (dp[i] > _max) {
						_max = dp[i];
						_idx = i;
					}
				}
				else if (i == j) dp[i] = 1;
			}
		}
		vector<int> res = {nums[_idx]};
		_idx = path[_idx];
		while (_idx >= 0) {
			res.push_back(nums[_idx]);
			_idx = path[_idx];
		}
		return res;
	}
	// 猜数字大小II, 真的又绕又难.
	// dp矩阵n x n, 只考虑y <= x的区域, 对角线为0
	// 对于dp[y][x], 具有y < x, 表示第y个数字到第x个数字的切片(dp[y: x])的极小极大
	// 特别注意填矩阵的时候要斜着填
	int getMoneyAmount2(int n) {
		vector<vector<int>> dp(n, vector<int>(n, 0)); 
		for (int len = 2; len <= n; len++) { 
			for (int y = 0; y < n - len + 1; y++) { 
				int _min = INT_MAX;
				for (int x = y; x < y + len - 1; x++) {
					cout << "y,x: " << y << "," << y + len - 1 << "->" << y << "," << x - 1 << "|" << x + 1 << "," << y + len - 1 << endl;
					_min = min(_min, x + 1 + max(dp[y][max(x - 1, 0)], dp[x + 1][y + len - 1]));
				}
				dp[y][y + len - 1] = _min;
			}
		}
		for (auto y : dp) {
			for (auto x : y) {
				cout << x << " ";
			}
			cout << endl;
		}
		return dp[0][n - 1];
	}
	// 移动零
	// 原地操作, 一次遍历
	void moveZeroes(vector<int>& nums) {
		int len = nums.size(), i = 0;
		for (int j = 0; j < len; j++) {
			if (nums[i] == 0) {
				nums.erase(nums.begin() + i, nums.begin() + i + 1);
				nums.push_back(0);
			}
			else ++i;
		}
	}
	// 合并两个有序数组
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		vector<int> res;
		int p_nums1 = 0, p_nums2 = 0;
		for (int i = 0; i < m + n; i++) {
			if (p_nums1 > m - 1 || p_nums2 > n - 1) break;
			if (nums1[p_nums1] <= nums2[p_nums2]) {
				res.push_back(nums1[p_nums1]);
				++p_nums1;
			}
			else {
				res.push_back(nums2[p_nums2]);
				++p_nums2;
			}
		}
		while (p_nums1 <= m - 1) {
			res.push_back(nums1[p_nums1]);
			++p_nums1;
		}
		while (p_nums2 <= n - 1) {
			res.push_back(nums2[p_nums2]);
			++p_nums2;
		}
		nums1 = res;
	}
	// 摆动序列
	// 去掉所有非波峰波谷点, ref: https://leetcode-cn.com/problems/wiggle-subsequence/solution/bai-dong-xu-lie-qu-diao-bo-gu-shi-yong-xie-lu-by-z/
	int wiggleMaxLength(vector<int>& nums) {
		int i = 0, j = 1, k = 2;
		while (k < nums.size()) {
			if ((nums[j] - nums[i] > 0 && nums[k] - nums[j] < 0) || (nums[j] - nums[i] < 0 && nums[k] - nums[j] > 0)) { // 波峰或波谷
				++k;
				++j;
				++i;
			}
			else nums.erase(nums.begin() + j, nums.begin() + k);
		}
		if (nums[0] == nums[1]) return nums.size() - 1;
		return nums.size();
	}
	// 组合总和IV
	// 动态规划: 假设题目是nums = [n1, n2, n3], target = n
	// 则状态转移方程: dp[n] = dp[n - n1] + dp[n - n2] + dp[n - n3], dp[0] = 1;
	int gcd(int a, int b) {
		return b ? gcd(b, a % b) : a;
	}
	int combinationSum4(vector<int>& nums, int target) {
		if (nums.size() == 0) return 0;
		int g = nums[0];
		for (int i : nums) g = gcd(g, i);
		sort(nums.begin(), nums.end());
		if ((nums[0] > target) || target % g != 0) return 0;
		vector<unsigned long long> dp(target + 2, 0);
		dp[0] = dp[1] = 1;
		for (int i = 2; i <= target; i++) {
			for (int e : nums) {
				if ((i - e == 0) || (i - e >= nums[0])) dp[i] += dp[i - e];
			}
		}
		return dp[target];
	}
	// 等差数列划分
	int numberOfArithmeticSlices(vector<int>& A) {
		if (A.size() <= 2) return 0;
		vector<int> dp(A.size(), 0);
		int res = 0;
		for (int i = 2; i < A.size(); i++) {
			if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
				dp[i] = dp[i - 1] + 1;
				res += dp[i];
			}
		}
		return res;
	}
	// 分割等和子集
	bool canPartition(vector<int>& nums) {
		if (nums.size() <= 1) return false;
		int length = 0;
		for (int i : nums) length += i;
		if (length % 2 != 0) return false;
		length /= 2;
		vector<vector<bool>> dp(nums.size(), vector<bool>(length + 1, false));
		for (int y = 0; y < nums.size(); y++) {
			for (int x = 1; x <= length; x++) {
				if (y == 0 && nums[y] == x) {
					dp[y][x] = true;
					break;
				}
				else if ((y >= 1) && (dp[y - 1][x] || (x > nums[y] && dp[y - 1][x - nums[y]]))) dp[y][x] = true;
			}
		}
		return dp[nums.size() - 1][length];
	}
	// 反转链表
	ListNode* reverseList(ListNode* head) {
		ListNode* p1 = head, * p2 = head, * p3 = head;
		if (p1 == NULL || p1->next == NULL) return p1;
		p2 = p1->next;
		if (p2->next == NULL) {
			int temp = p1->val;
			p1->val = p2->val;
			p2->val = temp;
			return p1;
		}
		p3 = p2->next;
		p1->next = NULL;
		while (p3 != NULL) {
			p2->next = p1;
			p1 = p2;
			p2 = p3;
			p3 = p3->next;
		}
		p2->next = p1;
		p1 = p2;
		return p1;
	}
	// 最后一个单词的长度
	int lengthOfLastWord(string s) {
		int res = 0;
		bool is_word = false;
		for (int i = s.length() - 1; i >= 0; i--) {
			if (s[i] == ' ' && !is_word) continue;
			if (s[i] != ' ') {
				is_word = true;
				++res;
			}
			else if (is_word) return res;
		}
		return res;
	}
	// 反转字符串
	void reverseString(vector<char>& s) {
		if (s.size() >= 2) {
			int i = 0, j = s.size() - 1;
			char temp;
			while (i < j) {
				temp = s[i];
				s[i] = s[j];
				s[j] = temp;
				++i;
				--j;
			}
		}
	}
	// 只出现一次的数字, 空间复杂度O(1)
	int singleNumber(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		for (int i = 1; i < nums.size() - 1; i++) {
			if (i == 1 && nums[i - 1] < nums[i]) return nums[0];
			else if (i == nums.size() - 2 && nums[i] < nums[i + 1]) return nums[i + 1];
			if (nums[i - 1] < nums[i] && nums[i] < nums[i + 1]) return nums[i];
		}
		return 0;
	}
	// 盛水最多的容器
	int maxArea(vector<int>& height) {
		int left = 0, right = height.size() - 1, area = 0;
		while (left < right) {
			area = max(min(height[left], height[right]) * (right - left), area);
			if (height[left] < height[right]) ++left;
			else --right;
		}
		return area;
	}
	// 简化路径
	string simplifyPath(string path) {
		path += "/";
		string dir;
		stack<string> st;
		for (auto i : path) {
			if (i == '/' && dir.length() == 0) {
				continue;
			}
			else if (i != '/'){
				dir += i;
			}
			else if (i == '/' && dir.length() != 0){
				if (dir == ".." && !st.empty()) {
					st.pop();
					dir.clear();
				}
				if ((dir == ".." && st.empty()) || dir == ".") {
					dir.clear();
				}
				else if (dir != ""){
					st.push(dir);
					dir.clear();
				}
			}
		}
		string res;
		while (!st.empty()) {
			res = "/" + st.top() + res;
			st.pop();
		}
		if (res == "") res = "/";
		return res;
	}
	// 相同的树
	bool isSameTree(TreeNode* p, TreeNode* q) {
		if ((p == NULL && q != NULL) || (p != NULL && q == NULL)) return false;
		else if (p != NULL && q != NULL && p->val != q->val) return false;
		if (p == NULL && q == NULL) return true;

		return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
	}
	// 对称二叉树
	// 跟相同树差不多, 只是一个优先走左, 一个优先走右
	bool isSymmetric(TreeNode* root) {
		TreeNode* l = root, * r = root;
		return func(l, r);
	}
	bool func(TreeNode* l, TreeNode* r) {
		if ((l == NULL && r != NULL) || (l != NULL && r == NULL)) return false;
		else if (l != NULL && r != NULL && l->val != r->val) return false;
		if (l == NULL && r == NULL) return true;

		return func(l->left, r->right) && func(l->right, r->left);
	}
	// 从前序和中序遍历序列构造二叉树
	// 多写一个递归函数可以节省很多时空, 思路是一样的
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		if (preorder.size() == 0 || inorder.size() == 0) return NULL;
		else if (preorder.size() == 1 || inorder.size() == 1) return new TreeNode(preorder[0]);

		TreeNode* root = new TreeNode(preorder[0]);
		int root_pos = 0;
		for (; root_pos < inorder.size(); root_pos++) {
			if (inorder[root_pos] == preorder[0]) break;
		}

		vector<int> left_in(inorder.begin(), inorder.begin() + root_pos);
		vector<int> left_pre(preorder.begin() + 1, preorder.begin() + left_in.size() + 1);
		root->left = buildTree(left_pre, left_in);

		vector<int> right_in(inorder.begin() + root_pos + 1, inorder.end());
		vector<int> right_pre(preorder.end() - right_in.size(), preorder.end());
		root->right = buildTree(right_pre, right_in);

		return root;
	}
	// 将有序数组转换为二叉搜索树
	// 二叉搜索树的中序遍历为有序数组, 利用这一点递归, 每次root为中位数
	TreeNode* sortedArrayToBST(vector<int>& nums) {
		return sortedArrayToBST_func(nums, 0, nums.size() - 1);
	}
	TreeNode* sortedArrayToBST_func(vector<int>& nums, int left, int right) {
		if (left > right) return NULL;

		int root_idx = (left + right) / 2;
		TreeNode* res = new TreeNode(nums[root_idx]);

		res->left = sortedArrayToBST_func(nums, left, root_idx - 1);
		res->right = sortedArrayToBST_func(nums, root_idx + 1, right);
		return res;
	}
	// 有序链表转换二叉搜索树
	TreeNode* sortedListToBST(ListNode* head) {
		vector<int> nums;
		ListNode* p = head;
		while (p != NULL) {
			nums.push_back(p->val);
			p = p->next;
		}
		return sortedListToBST_func(nums, 0, nums.size() - 1);
	}
	TreeNode* sortedListToBST_func(vector<int>& nums, int left, int right) {
		if (left > right) return NULL;

		int root_idx = (left + right) / 2;
		TreeNode * res = new TreeNode(nums[root_idx]);

		res->left = sortedArrayToBST_func(nums, left, root_idx - 1);
		res->right = sortedArrayToBST_func(nums, root_idx + 1, right);
		return res;
	}
	// 验证二叉搜索树
	// 二叉搜索树性质: 中序遍历为升序数组
	bool isValidBST(TreeNode* root) {
		string nums = isValidBST_func(root);
		string num;
		long cur_num = LONG_MIN;
		for (char i : nums) {
			if (i == ' ' && num.length() != 0) {
				if (cur_num < atoi(num.c_str())) cur_num = atoi(num.c_str());
				else return false;
				num.clear();
			}
			else if (i != ' ') num += i;
		}
		return true;
	}
	string isValidBST_func(TreeNode* root) {
		if (root == NULL) return " ";
		return isValidBST_func(root->left) + " " + to_string(root->val) + " " + isValidBST_func(root->right);
	}
	// 二叉树的中序遍历
	// 同上, 小修小改即可
	// 另外, 利用栈的方法: https://leetcode-cn.com/problems/binary-tree-inorder-traversal/solution/die-dai-fa-by-jason-2/
	// 非常值得学习
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> res;
		string nums = inorderTraversal_func(root);
		string num;
		for (char i : nums) {
			if (i == ' ' && num.length() != 0) {
				res.push_back(atoi(num.c_str()));
				num.clear();
			}
			else if (i != ' ') num += i;
		}
		return res;
	}
	string inorderTraversal_func(TreeNode * root) {
		if (root == NULL) return " ";
		return inorderTraversal_func(root->left) + " " + to_string(root->val) + " " + inorderTraversal_func(root->right);
	}
	// 路径总和
	// 典型的DFS
	bool hasPathSum(TreeNode* root, int sum) {
		if (root == NULL) return false;
		return hasPathSum_func(root, sum);
	}
	bool hasPathSum_func(TreeNode * root, int sum) {
		if (root == NULL) return false;
		if (root != NULL) sum -= root->val;
		if (root->left == NULL && root->right == NULL && sum == 0) return true;
		if (root->left == NULL && root->right == NULL && sum != 0) return false;

		return hasPathSum_func(root->left, sum) || hasPathSum_func(root->right, sum);
	}
	// 路径总和II
	// DFS+条件筛选
	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		vector<vector<int>> res;
		vector<int> path;
		pathSum_func(root, res, path, sum);
		return res;
	}
	void pathSum_func(TreeNode * root, vector<vector<int>>& res, vector<int> path, const int sum) {
		if (root != NULL && root->left == NULL && root->right == NULL) {
			path.push_back(root->val);
			int s = 0;
			for (int i : path) s += i;
			if (s == sum) res.push_back(path);
		}
		else if (root != NULL) {
			path.push_back(root->val);
			pathSum_func(root->left, res, path, sum);
			pathSum_func(root->right, res, path, sum);
		}
	}
	// 二叉树展开为链表
	// 原地操作, 非递归
	void flatten(TreeNode* root) {
		if (root == NULL) return;
		TreeNode* p, * p_right, * _root = root;
		while (_root != NULL) {
			p = _root;
			p_right = NULL;
			if (p->left == NULL) {
				_root = _root->right;
				continue;
			}
			p = p->left;
			while (p->right != NULL) p = p->right;
			if (_root->right != NULL) p_right = _root->right;
			_root->right = _root->left;
			_root->left = NULL;
			p->right = p_right;
			_root = _root->right;
		}
	}
	// 判断子序列
	bool isSubsequence(string s, string t) {
		int len_s = s.length(), len_t = t.length();
		if (s == "") return true;
		else if (len_s > len_t || len_t == 0) return false;
		stack<char> _stack;
		for (auto i : s) _stack.push(i);
		for (int i = len_t - 1; i >= 0; i--) {
			if (_stack.top() == t[i]) _stack.pop();
			if (_stack.empty()) return true;
		}
		return false;
	}
	// Pow(x, n)
	// 快速幂, 否则超时
	double myPow(double x, int n) {
		bool is_neg = false;
		if (n < 0) {
			n = (long)n * -1;
			is_neg = true;
		}
		else n = (long)n;
		double res = myPow_func(x, n);
		if (is_neg) return 1 / res;
		else return res;
	}
	double myPow_func(double x, long n) {
		if (1 / x == 0) return 0;
		if (n == 0 || x == 1) return 1;
		if (n == 1) return x;
		double _x = x;
		x *= x;
		return myPow(x, n / 2) * myPow(_x, n % 2);
	}
	// 两数相除
	// 麻烦的地方在边界判断
	int divide(int dividend, int divisor) {
		int is_neg = 1;
		if ((dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0)) is_neg = -1;

		if (dividend > 0) dividend *= -1;
		if (divisor > 0) divisor *= -1;

		if (dividend == 0) return 0;
		long factor = 1;
		while (dividend < (divisor * factor)) factor += factor;
		if (-1 * factor == INT_MIN && is_neg == 1) return INT_MAX;
		long left_factor = factor / 2;
		long res = left_factor + divide_func(0, factor - left_factor, dividend, divisor, left_factor) - 1;
		return is_neg * res;
	}
	long divide_func(long left, long right, int target, int divisor, long left_factor) {
		if (left > right) return left;
		int center = (left + right) / 2;

		if (target > (divisor * (left_factor + center))) {
			return divide_func(left, center - 1, target, divisor, left_factor);
		}
		else {
			return divide_func(center + 1, right, target, divisor, left_factor);
		}
	}
	// 在排序数组中查找元素的第一个和最后一个位置
	// 二分查找搜索左右边界
	vector<int> searchRange(vector<int>& nums, int target) {
		vector<int> res(2, -1);
		int length = nums.size();
		int left = 0, right = length - 1;
		if (length == 0) return res;
		// 找左
		while (left < right) {
			int center = (left + right) / 2;
			if (nums[center] >= target) right = center;
			else if (nums[center] < target) left = center + 1;
		}
		if (nums[left] != target) return res;
		res[0] = left;
		// 找右
		left = 0, right = length;
		while (left < right) {
			int center = (left + right) / 2;
			if (nums[center] <= target) left = center + 1;
			else if (nums[center] > target) right = center;
		}
		res[1] = left - 1;
		return res;
	}
	// 填充每个节点的下一个右侧节点指针
	// root->left->next = root->right; root->right->next = root->next->left;
	Node* connect(Node* root) {
		if (root == NULL) return NULL;
		return connect_func(root);
	}
	Node* connect_func(Node* root) {
		if (root->left == NULL) return root;

		root->left->next = root->right;
		if (root->next != NULL) root->right->next = root->next->left;

		root->left = connect_func(root->left);
		root->right = connect_func(root->right);

		return root;
	}
	// 二叉树的层次遍历
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> res;
		levelOrder_func(root, res, 0);
		return res;
	}
	void levelOrder_func(TreeNode* root, vector<vector<int>>& res, int layer) {
		if (root != NULL && res.size() == layer) res.push_back({ root->val });
		else if (root != NULL && res.size() > layer) res[layer].push_back(root->val);
		if (root == NULL) return;
		++layer;

		levelOrder_func(root->left, res, layer);
		levelOrder_func(root->right, res, layer);
	}
	// 二叉树的锯齿形层次遍历
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		vector<vector<int>> res;
		zigzagLevelOrder_func(root, res, 0);  // 奇数从右向左, 偶数从左向右
		return res;
	}
	void zigzagLevelOrder_func(TreeNode* root, vector<vector<int>>& res, int layer) {
		if (root == NULL) return;
		if (res.size() == layer) res.push_back({});
		if (layer % 2 == 0) res[layer].push_back(root->val);
		else res[layer].insert(res[layer].begin(), root->val);
		++layer;
		zigzagLevelOrder_func(root->left, res, layer);
		zigzagLevelOrder_func(root->right, res, layer);
	}
};
// 区域和检索 - 数组不可变
class NumArray {
public:
	vector<int> _nums;
	NumArray(vector<int>& nums) {
		_nums = nums;
	}
	int sumRange(int i, int j) {
		int res = 0;
		for (int idx = i; idx <= j; idx++) res += _nums[idx];
		return res;
	}
};
// 二维区域和检索 - 矩阵不可变
class NumMatrix {
public:
	vector<vector<int>> _matrix;
	int length;
	NumMatrix(vector<vector<int>>& matrix) {
		length = matrix.size();
		_matrix = matrix;
		if (length != 0) {
			for (int y = 0; y < length; y++) {
				for (int x = 1; x < _matrix[0].size(); x++) {
					_matrix[y][x] += _matrix[y][x - 1];
				}
			}
		}
	}
	int sumRegion(int row1, int col1, int row2, int col2) {
		if (length == 0) return 0;
		int res = 0;
		for (int y = row1; y <= row2; y++) {
			int ele = 0;
			if (col1 - 1 >= 0) ele = _matrix[y][col1 - 1];
			res += _matrix[y][col2] - ele;
		}
		return res;
	}
};


int main()
{
	Solution solve;

	vector<int> a = { 1 };
	vector<int> b = solve.searchRange(a, 1);
	cout << b[0] << " " << b[1];
}