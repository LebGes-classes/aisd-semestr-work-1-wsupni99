#include "SegmentTree.h"

SegmentTree::SegmentTree(const std::vector<int>& input_array) {
	arr = input_array;
	size = arr.size();
	tree.resize(4 * size, 0); // в 4 раза больше памяти
	lazy.resize(4 * size, 0);
	build_tree(1, 0, size - 1);
}

void SegmentTree::build_tree(int node, int start, int end) {
	if (start == end) {
		tree[node] = arr[start];
		return;
	}

	// Разбиваем отрезок пополам
	int mid = (start + end) / 2;

	// Строим левое и правое поддерево
	build_tree(2 * node, start, mid);
	build_tree(2 * node + 1, mid + 1, end);
	tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void SegmentTree::push_lazy(int node, int start, int end) {
	if (lazy[node] != 0) {
		tree[node] += (end - start + 1) * lazy[node];
		// Если это не лист, передаем изменения вниз
		if (start != end) {
			lazy[2 * node] += lazy[node];
			lazy[2 * node + 1] += lazy[node];
		}
		lazy[node] = 0;
	}
}

int SegmentTree::get_sum(int node, int start, int end, int l, int r) {
	push_lazy(node, start, end);

	// Случай 1: отрезок [start, end] не пересекается с [l, r]
	if (r < start || end < l) return 0;

	// Случай 2: отрезок [start, end] полностью внутри [l, r]
	if (l <= start && end <= r) return tree[node];

	// Случай 3: частичное пересечение
	int mid = (start + end) / 2;
	return get_sum(2 * node, start, mid, l, r) + get_sum(2 * node + 1, mid + 1, end, l, r);
}

int SegmentTree::get_min(int node, int start, int end, int l, int r) {
	push_lazy(node, start, end);
	if (r < start || end < l) return INT_MAX;
	if (l <= start && end <= r) return tree[node];
	int mid = (start + end) / 2;
	return std::min(get_min(2 * node, start, mid, l, r), get_min(2 * node + 1, mid + 1, end, l, r));
}

int SegmentTree::get_max(int node, int start, int end, int l, int r) {
	push_lazy(node, start, end);
	if (r < start || end < l) return INT_MIN;
	if (l <= start && end <= r) return tree[node];
	int mid = (start + end) / 2;
	return std::max(get_max(2 * node, start, mid, l, r), get_max(2 * node + 1, mid + 1, end, l, r));
}

void SegmentTree::update_point(int node, int start, int end, int idx, int val) {
	if (start == end) {
		arr[idx] = val;
		tree[node] = val;
		return;
	}
	int mid = (start + end) / 2;
	if (idx <= mid) update_point(2 * node, start, mid, idx, val);
	else update_point(2 * node + 1, mid + 1, end, idx, val);
	tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void SegmentTree::update_range(int node, int start, int end, int l, int r, int val) {
	push_lazy(node, start, end);
	if (start > r || end < l) return;
	if (start >= l && end <= r) {
		tree[node] += (end - start + 1) * val;
		if (start != end) {
			lazy[2 * node] += val;
			lazy[2 * node + 1] += val;
		}
		return;
	}
	int mid = (start + end) / 2;
	update_range(2 * node, start, mid, l, r, val);
	update_range(2 * node + 1, mid + 1, end, l, r, val);
	tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int SegmentTree::sumQuery(int l, int r) {
	if (l < 0 || r >= size || l > r) {
		std::cout << "Invalid query range [" << l << ", " << r << "]\n";
		return -1; // или бросить исключение
	}
	return get_sum(1, 0, size - 1, l, r);
}

int SegmentTree::minQuery(int l, int r) {
	if (l < 0 || r >= size || l > r) {
		std::cout << "Invalid query range [" << l << ", " << r << "]\n";
		return INT_MAX;
	}
	return get_min(1, 0, size - 1, l, r);
}

int SegmentTree::maxQuery(int l, int r) {
	if (l < 0 || r >= size || l > r) {
		std::cout << "Invalid query range [" << l << ", " << r << "]\n";
		return INT_MIN;
	}
	return get_max(1, 0, size - 1, l, r);
}

void SegmentTree::update(int idx, int new_val) {
	if (idx < 0 || idx >= size) {
		std::cout << "Index " << idx << " is out of bounds\n";
		return;
	}
	update_point(1, 0, size - 1, idx, new_val);
}

void SegmentTree::updateRange(int l, int r, int delta) {
	if (l < 0 || r >= size || l > r) {
		std::cout << "Invalid update range [" << l << ", " << r << "]\n";
		return;
	}
	update_range(1, 0, size - 1, l, r, delta);
}

void SegmentTree::print() {
	std::cout <<"\n" ;
	std::cout << "Segment Tree nodes:\n";
	for (int i = 1; i < (int)tree.size(); ++i) {
		if (tree[i] != 0) {
			std::cout << "node[" << i << "] = " << tree[i] << "\n";
		}
	}
	std::cout << "Lazy array:\n";
	for (int i = 1; i < (int)lazy.size(); ++i) {
		if (lazy[i] != 0) {
			std::cout << "lazy[" << i << "] = " << lazy[i] << "\n";
		}
	}
}
