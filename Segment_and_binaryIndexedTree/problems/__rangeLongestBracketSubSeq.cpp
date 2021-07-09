// { Driver Code Starts
// Initial template for C++

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int pairs;
    int open;   // unused
    int closed; // unused

    Node() { pairs = open = closed = 0; }
};

int getMid(int s, int e) {
    return s + (e - s) / 2;
}

Node merge(Node leftChild, Node rightChild) {
    Node parentNode;
    int minMatched = min(leftChild.open, rightChild.closed);
    parentNode.pairs = leftChild.pairs + rightChild.pairs + minMatched;
    parentNode.open = leftChild.open + rightChild.open - minMatched;
    parentNode.closed = leftChild.closed + rightChild.closed - minMatched;
    return parentNode;
}

void constructSTUtil(string str, int ss, int se, Node* st, int si) {
    if (ss == se) {
        st[si].pairs = 0;
        if (str[ss] == '(')
            st[si].open = 1;
        else
            st[si].closed = 1;

        return;
    }

    int mid = getMid(ss, se);
    constructSTUtil(str, ss, mid, st, si * 2 + 1);
    constructSTUtil(str, mid + 1, se, st, si * 2 + 2);

    st[si] = merge(st[si * 2 + 1], st[si * 2 + 2]);
}

Node* constructST(string str, int n) {
    int x = (int)(ceil(log2(n)));

    int max_size = 2 * (int)pow(2, x) - 1;
    Node* st = new Node[max_size];

    constructSTUtil(str, 0, n - 1, st, 0);
    return st;
}


 // } Driver Code Ends
// User function template for C++

class Solution
{
    public:
    //recursive function to get the desired Longest Sequence.
    Node getLongestSequenceUtil(Node* st,int ss,int se,int qs,int qe,int si) 
    {
        //if segment of this node is outside given range, we return null node.
        if (ss > qe || se < qs) {
            Node nullNode;
            return nullNode;
        }
    
        //if segment of this node is part of given range then we return st[si].
        if (ss >= qs && se <= qe) {
            return st[si];
        }
        
        //if a part of this segment overlaps with the given range, we call
        //the function recursively for the children nodes.
        int mid = getMid(ss, se);
        Node left = getLongestSequenceUtil(st, ss, mid, qs, qe, si * 2 + 1);
        Node right = getLongestSequenceUtil(st, mid + 1, se, qs, qe, si * 2 + 2);
    
        //merging left and right subtree query results.
        Node res = merge(left, right);
        return res;
    }
    
    //Function to returns the maximum length of correct bracket subsequence
    //between starting and ending indexes.
    int getLongestSequence(Node* st, string str, int qs, int qe, int n)
    {
        Node res = getLongestSequenceUtil(st, 0, n - 1, qs, qe, 0);
        
        //since we are storing numbers pairs and have to return maximum 
        //length hence we multiply no of pairs with 2.
        return 2 * res.pairs;
    }
};

// { Driver Code Starts.

// Driver Code
int main() {
    int t;
    cin >> t;
    while (t--) {
        int query;
        string str;

        cin >> str >> query;
        int n = str.length();

        Node* st = constructST(str, n);

        int startIndex, endIndex;
        while (query--) {
            cin >> startIndex >> endIndex;
            Solution obj;
            cout << obj.getLongestSequence(st, str, startIndex, endIndex, n)
                 << endl;
        }
    }

    return 0;
}
  // } Driver Code Ends