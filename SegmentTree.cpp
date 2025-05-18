#include "SegmentTree.h"
#include <algorithm>

SegmentTree::SegmentTree(const std::vector<int>& data) {
	size = data.size();
	treeSum.resize(size * 4);
	treeMax.resize(size * 4);
	build(data, 1, 0, size - 1);
}

void SegmentTree::build(const std::vector<int>& data, int node, int l, int r) {
	if (l == r) {
		treeSum[node] = data[l];
		treeMax[node] = data[l];
	}
	else {
		int mid = (l + r) / 2;
		build(data, node * 2, l, mid);
		build(data, node * 2 + 1, mid + 1, r);
		treeSum[node] = treeSum[node * 2] + treeSum[node * 2 + 1];
		treeMax[node] = std::max(treeMax[node * 2], treeMax[node * 2 + 1]);
	}
}

int SegmentTree::querySum(int node, int l, int r, int ql, int qr) {
	if (ql > r || qr < l) return 0;
	if (ql <= l && r <= qr) return treeSum[node];
	int mid = (l + r) / 2;
	return querySum(node * 2, l, mid, ql, qr) + querySum(node * 2 + 1, mid + 1, r, ql, qr);
}

int SegmentTree::queryMax(int node, int l, int r, int ql, int qr) {
	if (ql > r || qr < l) return INT_MIN;
	if (ql <= l && r <= qr) return treeMax[node];
	int mid = (l + r) / 2;
	return std::max(
		queryMax(node * 2, l, mid, ql, qr),
		queryMax(node * 2 + 1, mid + 1, r, ql, qr)
	);
}

int SegmentTree::querySum(int l, int r) {
	return querySum(1, 0, size - 1, l, r);
}

int SegmentTree::queryMax(int l, int r) {
	return queryMax(1, 0, size - 1, l, r);
}

void SegmentTree::update(int node, int l, int r, int pos, int value) {
	if (l == r) {
		treeSum[node] = value;
		treeMax[node] = value;
	}
	else {
		int mid = (l + r) / 2;
		if (pos <= mid)
			update(node * 2, l, mid, pos, value);
		else
			update(node * 2 + 1, mid + 1, r, pos, value);
		treeSum[node] = treeSum[node * 2] + treeSum[node * 2 + 1];
		treeMax[node] = std::max(treeMax[node * 2], treeMax[node * 2 + 1]);
	}
}

void SegmentTree::update(int pos, int value) {
	update(1, 0, size - 1, pos, value);
}
