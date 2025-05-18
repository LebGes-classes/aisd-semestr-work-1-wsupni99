#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H

#include <vector>

class SegmentTree {
private:
	std::vector<int> treeSum;
	std::vector<int> treeMax;
	int size;

	void build(const std::vector<int>& data, int node, int l, int r);
	int querySum(int node, int l, int r, int ql, int qr);
	int queryMax(int node, int l, int r, int ql, int qr);
	void update(int node, int l, int r, int pos, int value);

public:
	SegmentTree(const std::vector<int>& data);
	int querySum(int l, int r);  // сумма на [l, r]
	int queryMax(int l, int r);  // максимум на [l, r]
	void update(int pos, int value); // обновить значение
};

#endif
