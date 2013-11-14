/*******************************************************
 *Problem: find the longest palindrome sub string of a string
 *idea: Dynamic Programming
 **********************************************************/
#include<iostream>
#include<string>
using namespace std;

// Transform S into T.
// For example, S = "abba", T = "^#a#b#b#a#$".
// ^ and $ signs are sentinels appended to each end to avoid bounds checking
string preProcess(string s) 
{
	int n = s.length();
	if (n == 0) return "^$";
	string ret = "^";
	for (int i = 0; i < n; i++)
	    ret += "#" + s.substr(i, 1);    //在每个字符之间加#字符
 
	ret += "#$";
	return ret;
}
 
string longestPalindrome(string s) 
{
	string T = preProcess(s);
	int n = T.length();
	int *P = new int[n];    //开辟一个数组，存储回文子串的长度
	int C = 0, R = 0;    //C是字符串当前的i所在的位置，R的当前以C为中心的回文子串的最右边界位置
	for (int i = 1; i < n-1; i++) //s[0]='^',s[n-1]='$', they are not a part of the string s. So, i from index=1, end to index=n-2
	{
		int i_mirror = 2*C-i; // equals to i' = C - (i-C)
    
		P[i] = (R > i) ? min(R-i, P[i_mirror]) : 0;
    
		// Attempt to expand palindrome centered at i
		while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
			P[i]++;
 
		// If palindrome centered at i expand past R,
		// adjust center based on expanded palindrome.
		if (i + P[i] > R) 
		{
			C = i;
			R = i + P[i];
		}
	}
 
	// Find the maximum element in P.
	int maxLen = 0;
	int centerIndex = 0;
	for (int i = 1; i < n-1; i++) 
	{
		if (P[i] > maxLen) 
		{
			maxLen = P[i];
			centerIndex = i;
		}
	}
	delete[] P;
  
	return s.substr((centerIndex - 1 - maxLen)/2, maxLen);
}

int main()
{
	string s;
	cin>>s;
	string res;
	res=longestPalindrome(s);
	cout<<res;

	return 0;
}
