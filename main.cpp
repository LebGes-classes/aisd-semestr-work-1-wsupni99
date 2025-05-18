#include <iostream>
#include "SegmentTree.h"

int main() {
	std::vector<int> data = { 5, 3, 8, 6, 1 };
	SegmentTree st(data);

	std::cout << "Sum [1, 3] = " << st.querySum(1, 3) << std::endl;
	std::cout << "Max [1, 3] = " << st.queryMax(1, 3) << std::endl;

	st.update(2, 10); // обновим data[2] = 10

	std::cout << "After update: Sum [1, 3] = " << st.querySum(1, 3) << std::endl;
	std::cout << "After update: Max [1, 3] = " << st.queryMax(1, 3) << std::endl;

	return 0;
}
