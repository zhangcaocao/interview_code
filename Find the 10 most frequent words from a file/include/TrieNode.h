#include <iostream>
#include <string>
#include <vector>

class TrieNode
{
public:

	static constexpr size_t AsciiCount = 256;

	struct TrieNodeStruct
	{
		TrieNodeStruct(const char value)
			: value(value), is_end(false), childrens(AsciiCount, nullptr), c(0), indexMinHeap(-1)
		{

		}
		char value;
		bool is_end;
		unsigned int c;
		unsigned int indexMinHeap;
		std::vector<TrieNodeStruct*> childrens;
	};

	struct MinHeapNodeStruct
	{
		MinHeapNodeStruct()
			: frequency(0), word("0")
		{
			//root = new TrieNodeStruct('0');
		}
		TrieNodeStruct* root;
		unsigned int frequency;
		std::string word;
	};

	struct MinHeap
	{
		
		MinHeap()
			: count(0) , array(10, nullptr)
		{
			for (auto i : array)
			{
				i = new MinHeapNodeStruct();
			}
		}
		int count;
		std::vector<MinHeapNodeStruct*> array;
	};

	TrieNodeStruct* root;
	MinHeap* minHeap;
	
	void Init(const std::vector<std::string>& dict);
	void ReleaseTrieNode(const TrieNodeStruct* root);
	int Lookup(const std::string& word) const;

	void swapMinHeapNodes(MinHeapNodeStruct* a, MinHeapNodeStruct* b);
	void minHeapify(MinHeap* minHeap, int idx);

	void buildMinHeap(MinHeap* minHeap);

	void insertInMinHeap(MinHeap* minHeap, TrieNodeStruct* root, const std::string& word);

	TrieNode();
	~TrieNode();
	

private:

	void _Insert(const std::string& word);
	int _Search(const TrieNodeStruct* parent, const std::string& word, const size_t idx) const;

};

