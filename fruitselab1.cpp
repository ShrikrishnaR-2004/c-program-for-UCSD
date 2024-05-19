#include<bits/stdc++.h>
#include<vector>
using namespace std;

int Minweightloss(int n, int target, const vector<int>&weights){
    // vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
    // dp[0][0] = 0;
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 0; j <= target; j++) {
    //         dp[i][j] = dp[i - 1][j];
    //         if (weights[i - 1] <= j) {
    //             int loss = j - weights[i - 1];
    //             dp[i][j] = max(dp[i][j], dp[i - 1][j - weights[i - 1]] + loss);
    //         }
    //     }
    // }
    // return target - dp[n][target];
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));

    // Initializing the dp table
    for (int i = 1; i <= target; ++i)
        dp[0][i] = INT_MAX;

    // Filling the dp table
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= target; ++j) {
            if (weights[i - 1] <= j) {
                if (dp[i - 1][j - weights[i - 1]] != INT_MAX)
                    dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - weights[i - 1]] + weights[i - 1]);
                else
                    dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    int loss = dp[n][target] - target;
    return loss;
}

int main()
{
    int T,n,target,weight;
    cin>>T;
    for(int i=0;i<T;i++)
    {
        cin>>n>>target;
        vector<int>weight;
        for (int i=0;i<n;i++)
        {
            int W;
            cin>>W;
            weight.push_back(W);
        }
        cout<<Minweightloss(n,target,weight)<<endl;
    }
    return 0;
}



/*
#include <iostream>
using namespace std;
int money(int s1, int r1, int s2, int r2)
{
    if (s1>s2 && r1>r2){
        return 0;
    }
    else if (s1<s2 && r1<r2){
        return 0;
    }
    if (r1==r2)
    {
        return 0;}
    if (((s2-s1)%(r1-r2)==0)||((s2-s1)%(r2-r1)==0)){
            return 1;
        }
    
    else{
        return 0;
    }
}
int main()
{
    int s1, r1, s2, r2;
    cin>>s1>>r1>>s2>>r2;
    int monkey=money(s1,r1,s2,r2);
    if (monkey==0){
        cout<<"NO"<<endl;
    }
    else{e{
        cout<<"YES"<<endl;
    }
	return 0;
}*/