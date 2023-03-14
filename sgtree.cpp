#include <bits/stdc++.h>
using namespace std;
class sgtree{
 public:
    vector<int>st;
    sgtree (int n){
        st.resize(4*n + 1);
    }
     void Build(int ind,int low,int high,int arr[],int orr)
     {
          if (low==high)
          {
               st[ind] = arr[low];
               return;
          }
          int mid=(low+high)/2;
          Build(2*ind +1 ,low,mid,arr,!orr);
          Build(ind* 2 + 2, mid+1, high,arr,!orr);
          if(orr)
          st[ind]=st[2*ind + 1] | st[2*ind + 2];
          else
          st[ind]=st[2*ind + 1] ^ st[2*ind + 2];
     }
       
       int query(int ind,int low,int high,int i,int j,int orr){
 
		if(i<low || j>high) return 0;
 
		if(low>=i && high<=j) return st[ind];
 
		int mid=(low+high)/2;
 
		int left=query(2*ind+1,low,mid,i,j,!orr);
		int right=query(2*ind+2,mid+1,high,i,j,!orr);
		if(orr)
		  return left|right;
		  else
		  return left^right;
	}
     void Update(int ind ,int low,int high,int i,int val,int orr)
     {
          if (low==high)
          {
               st[ind] =val;
               return;
          }
          int mid=(low + high)/2;
          if (i<= mid)
               Update(ind * 2 + 1, low , mid,i, val,!orr);
          else
               Update(2*ind + 2 , mid + 1, high, i, val,!orr);
          if(orr)
          st[ind]=st[2*ind + 1] | st[2*ind + 2];
          else
          st[ind]=st[2*ind + 1 ] ^ st[2*ind + 2];
     }
};

void solve()
{
  int n,q;
  cin>>n>>q;
  int sz=pow(2,n);
  int arr[sz]={0};
  for(int i=0;i<sz;i++)
  cin>>arr[i];
  sgtree st1(sz);
  if(n%2==0)
  st1.Build(0,0,sz-1,arr,0);
  else
   st1.Build(0,0,sz-1,arr,1);
   while(q--)
   {
       int i,val;
       cin>>i>>val;
       i--;
       if(n%2==0)
      st1.Update(0,0,sz-1,i,val,0);
       else
      st1.Update(0,0,sz-1,i,val,1);
       cout<<st1.st[0]<<endl;
   }
   
}
int main()
{
    solve();
}