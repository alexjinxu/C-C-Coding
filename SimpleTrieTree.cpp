//============================================================================
// Name        : Temp.cpp
// Author      : ax
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include<stdlib.h>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<algorithm>
#include<string>
#include<iostream>
using namespace std;

class Trie {
public:

	typedef struct Node
	{

		char Letter = 0xFF;
		bool isROOT = false;
		bool isCompleted = false;
		struct Node * ChildNode[26];

	} TrieTreeNode;



	TrieTreeNode * ROOT = NULL;

    /** Initialize your data structure here. */
    Trie() {

    	ROOT = new TrieTreeNode;
    	ROOT->isROOT =true;
    	for (int i = 0 ; i < 26 ; i ++)
    	{
    		ROOT->ChildNode[i] = NULL;
    	}

    }

    TrieTreeNode* CreateTrieTreeNode( )
    {

    	TrieTreeNode* res = new TrieTreeNode;

    	for (int i = 0 ; i < 26 ; i ++)
    	{
    		res->ChildNode[i] = NULL;
    	}

    	return res;

    }


    /** Inserts a word into the trie. */
    void insert(string word) {

    	TrieTreeNode * TreeNodeP , * ChildTreeNodeP;

    	if( !word.empty() )
    	{
    		    TreeNodeP = ROOT;

    			for (int i =0; i < word.size() ; i++)
    			{
    				int index = word[i]-'a';

    				if(TreeNodeP->isROOT == true )
    				{

    					if (TreeNodeP->ChildNode[index] == NULL)
    					{
    						TreeNodeP=CreateTrieTreeNode();
    						TreeNodeP->Letter = word[i];
    						ROOT->ChildNode[index] = TreeNodeP;
    					}
    					else
    					{
    						TreeNodeP=ROOT->ChildNode[index];
    						continue;
    					}
    				}
    				else
    				{
    					if (TreeNodeP->ChildNode[index] == NULL)
    					{
    						ChildTreeNodeP=CreateTrieTreeNode();
    						ChildTreeNodeP->Letter = word[i];
     						TreeNodeP->ChildNode[index] = ChildTreeNodeP;
    						TreeNodeP = ChildTreeNodeP;
    					}
    					else
    					{
    						TreeNodeP=TreeNodeP->ChildNode[index];
    					}
    				}
    			}
    			TreeNodeP->isCompleted =true;
    	}

    }

    /** Returns if the word is in the trie. */
    bool search(string word) {

    	TrieTreeNode * TreeNodeP , * ChildTreeNodeP;

    	if( !word.empty() )
    	{
    		TreeNodeP = ROOT;

    		for (int i =0; i < word.size(); i ++)
    		{
    			int index = word[i]-'a';

    			if (TreeNodeP->isROOT ==  true)
    			{
    				if (ROOT->ChildNode[index] != NULL)
    				{
    					TreeNodeP=ROOT->ChildNode[index];
    					continue;
    				}
    				else
    				{
    					return false;
    				}
    			}
    			else
    			{
    				if (TreeNodeP->ChildNode[index] != NULL)
    				{
    					TreeNodeP=TreeNodeP->ChildNode[index];
    				}
    				else
    				{
    					return false;
    				}
    			}
    		}

    	}
    	if(TreeNodeP->isCompleted == true)
    	{
    		return true;
    	}
    	else
    	{
    		return false;
    	}



    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {

    	TrieTreeNode * TreeNodeP , * ChildTreeNodeP;

    	if (! prefix.empty())
    	{
    		TreeNodeP=ROOT;


    		for (int i = 0; i < prefix.size(); i ++)
    		{
    			int index = prefix[i]-'a';

    			if (TreeNodeP->isROOT == true)
    			{
    				if (TreeNodeP->ChildNode[index] == NULL)
    				{
    					return false;
    				}
    				else
    				{
    					TreeNodeP = TreeNodeP->ChildNode[index];
    				}
    			}
    			else
    			{
    				if (TreeNodeP->ChildNode[index] == NULL)
    				{
    					return false;
    				}
    				else
    				{
    					TreeNodeP = TreeNodeP->ChildNode[index];
    				}
    			}
    		}
    	}

    	return true;

    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */

int main() {

	Trie Tree;
	Tree.insert("ab");
	cout << Tree.search("a") <<endl;
	cout << Tree.startsWith("a") << endl;

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
