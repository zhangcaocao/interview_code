/*
 * https://ce39906.github.io/2018/07/20/Trie-C-%E5%AE%9E%E7%8E%B0%E4%B8%8E%E8%A7%A3%E6%9E%90/
 * https://blog.csdn.net/lisonglisonglisong/article/details/45584721
*/

#include <assert.h>
#include "TrieNode.h"



TrieNode::TrieNode()
{
	root = new TrieNodeStruct('0');
    minHeap = new MinHeap();

}

TrieNode::~TrieNode()
{
	ReleaseTrieNode(root);
	delete minHeap;
}

// A utility function to swap two min heap nodes. This function 
// is needed in minHeapify 

void TrieNode::swapMinHeapNodes (TrieNode::MinHeapNodeStruct* a, TrieNode::MinHeapNodeStruct* b)
{
	MinHeapNodeStruct temp = *a;
	*a = *b;
	*b = temp;
}

// This is the standard minHeapify function. It does one thing extra. 
// It updates the minHapIndex in Trie when two nodes are swapped in 
// in min heap 

void TrieNode::minHeapify (MinHeap* minHeap, int idx)
{
	unsigned int left, right, smallest;

	left = 2 * idx + 1;
	right = 2 * idx + 2;
	smallest = idx;
	if (left < minHeap->count &&
		minHeap->array[left]->frequency <
		minHeap->array[smallest]->frequency
		)
		smallest = left;

	if (right < minHeap->count &&
		minHeap->array[right]->frequency <
		minHeap->array[smallest]->frequency
		)
		smallest = right;

	if (smallest != idx)
	{
		// Update the corresponding index in Trie node. 
		minHeap->array[smallest]->root->indexMinHeap = idx;
		minHeap->array[idx]->root->indexMinHeap = smallest;

		// Swap nodes in min heap 
		swapMinHeapNodes(minHeap->array[smallest], minHeap->array[idx]);

		minHeapify(minHeap, smallest);
	}
}

// A standard function to build a heap 
void TrieNode::buildMinHeap(MinHeap* minHeap)
{
	int n, i;
	n = minHeap->count - 1;
	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}



// Inserts a word to heap, the function handles the 3 cases explained above 
void TrieNode::insertInMinHeap(MinHeap* minHeap, TrieNodeStruct* root, const std::string& word)
{
	// Case 1: the word is already present in minHeap 
	if (root->indexMinHeap != -1)
	{
		++(minHeap->array[root->indexMinHeap]->frequency);

		// percolate down 
		minHeapify(minHeap, root->indexMinHeap);
	}

	// Case 2: Word is not present and heap is not full 
	else if (minHeap->count < 10)
	{
		int count = minHeap->count;
		/*std::cout << root->c <<std::endl;*/
		if (minHeap->array[count] == nullptr)
		{
			minHeap->array[count] = new(std::nothrow) MinHeapNodeStruct();
			//std::cout << "null" << std::endl;
		}
		unsigned int c = root->c;
		minHeap->array[count]->frequency = c; 
		minHeap->array[count]->word = word;  

		minHeap->array[count]->root = root;
		root->indexMinHeap = minHeap->count;

		++(minHeap->count);
		buildMinHeap(minHeap);
	}

	// Case 3: Word is not present and heap is full. And frequency of word 
	// is more than root. The root is the least frequent word in heap, 
	// replace root with new word 
	else if (root->c > minHeap->array[0]->frequency)
	{

		minHeap->array[0]->root->indexMinHeap = -1;
		minHeap->array[0]->root = root;
		minHeap->array[0]->root->indexMinHeap = 0;
		minHeap->array[0]->frequency = root->c;

		// delete previously allocated memoory and 
		minHeap->array[0]->word.clear();
		minHeap->array[0]->word = word; 
		//new char[strlen(word) + 1];
		//strcpy(minHeap->array[0]->word, word);

		minHeapify(minHeap, 0);
	}
}


void TrieNode::Init(const std::vector<std::string>& dict)
{
	for (const std::string& word : dict)
	{
		_Insert(word);
		
	}
}


void TrieNode::_Insert(const std::string& word)
{
	if (word.empty())
		return;
	TrieNodeStruct* cur = root;
	for (const unsigned char i : word)
	{
		//如果不存在，建新结点
		if (!cur->childrens[i])
		{
			cur->childrens[i] = new(std::nothrow) TrieNodeStruct(i);
			if (cur->childrens[i] == nullptr) {
				std::cout << "Allocation returned nullptr\n" << std::endl;
			}
		}
		cur = cur->childrens[i]; 
	}
	

	cur->is_end = true;
	cur->c += 1;

	insertInMinHeap(minHeap, cur, word);
}

int TrieNode::_Search(const TrieNodeStruct* parent, const std::string& word, const size_t idx) const
{
	if (word.empty())
	{
		return 0;
	}
	const std::vector<TrieNodeStruct*>& childrens = parent->childrens;
	const unsigned char c = word[idx];
	TrieNodeStruct* cur = childrens[c];
	if (!cur)
	{
		return 0;
	}
	if (idx == word.size() - 1)
	{
		return cur->c;
	}
	return _Search(cur, word, idx + 1);
}


int TrieNode::Lookup(const std::string& word) const
{
	return _Search(root, word, 0);
}




void TrieNode::ReleaseTrieNode(const TrieNodeStruct* root)
{
	if (!root) return;
	//bool 
	const std::vector<TrieNodeStruct*>& childrens = root->childrens;
	for (const TrieNodeStruct* children : childrens)
	{
		if (children)
		{
			ReleaseTrieNode(children);
		}
	}
	
	delete root;
}



