### 找到给出的文件中 top 10 frequent words。


##### 几种方案：

* HashMap + quick sort

使用HashMap存frequent,然后使用一个List 存word，之后进行quick sort。
且不论算法的cost，HashMap面对大量数据时容易产生冲突是我们不能接受的，因此所有关于HashMap的方法都排除掉。

* Trie + MinHeap

![](https://pic3.zhimg.com/v2-6d34a6ecc3022dec787b6ba9458a3199_1200x500.jpg)

Trie树能够对word进行有效的储存，如上图所示。Trie的核心思想是空间换时间，利用字符串的公共前缀来降低查询时间的开销以达到提高效率的目的。在进行word的insert时候能够进行计数，之后利用最小堆维护一个计数值top10的word堆。

使用最小堆实际是一种边insert边sort的操作，一开始我想的是将Trie统计的word frequent储存起来然后进行quick sort，不过显而易见的浪费时间与空间让我没法下手。然后google了一下，找到了Trie + MinHeap的方法。


##### 算法大致流程：

首先调用初始化函数：

```c++
TrieNode::Init（）
```
一方面初始化 'MinHeap'与'TrieNodeStruct'。然后开始'_insert'word到trie数与minheap。
在insert word 到 minheap 的时候 注意有三种情况：

case 1: the word is already present in minHeap 

直接调用 `minHeapify`函数即可。

case 2: Word is not present and heap is not full 

这种情况需要新new一个`MinHeapNodeStruct`空间进行初始化，之后将word添加到minheap中。

case 3: Word is not present and heap is full

这个时候就需要比较当前的要插入的word的frequent是否比`minHeap->array[0]`的frequent大，比他大的话就替换，否则不进行insert。最后输出minheap的内容即可。

##### 如何运行：

* 环境

ubuntu 1604 + C/C++

* 编译

```
cd build/
cmake ..
make -j4
```
* 运行

```
../bin/main ../words.txt
```

* output:

```
AAU : 13
aasvogels : 13
Aaru : 13
A'asia : 13
aasvogel : 13
aarrgh : 13
aarrghh : 13
AAA : 18
18-point : 21
AAS : 13
time cost: 2.38102e+09s
```