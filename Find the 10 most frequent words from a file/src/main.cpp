#include "TrieNode.h"

#include<chrono>
#include <fstream>
#include <cstdlib>


void ReadFile2Vector(const std::string& file, std::vector<std::string>& vec);

void ReadFile2Vector(const std::string& file, std::vector<std::string>& vec)
{
	std::fstream infile(file, std::ios_base::in);
    if ( !infile )
    {
        std::cout<<"please Choose the correct file !!"<<std::endl;
        return;
    }

	std::string line;
	while (getline(infile, line, '\n'))
	{
		vec.emplace_back(line);
	}
}


int main(int argc, char* argv[])
{
	TrieNode Trie;
	if (argc != 2)
	{
		 std::cout<<"usage: main dataset.txt"<<std::endl;
		 return 0;
	}
	const std::string data_file = argv[1];


    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	//std::cout << data_file << std::endl;
	std::vector<std::string> dict;
	ReadFile2Vector(data_file, dict);
	//std::cout << dict[0] << std::endl;
	Trie.Init(dict);
	//std::cout << Trie.Lookup("beiji") << std::endl;
	//std::cout << "hello world" << std::endl;
	int i;
	// print top K word with frequency 
	for(auto i : Trie.minHeap->array)
	{
		std::cout << i->word << " : "   << i->frequency << std::endl;
	}
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

	std::cout << "time cost: " << double ((t2-t1).count()) << 's' << std::endl;


	return 0;
}

