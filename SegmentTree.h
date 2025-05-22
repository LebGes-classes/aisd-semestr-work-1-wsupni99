#pragma once
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>

class SegmentTree {
private:
	std::vector<int> tree;
	std::vector<int> lazy;
	std::vector<int> arr;
	int size;

	// Внутренние методы
	void build_tree(int node, int start, int end);

	// Методы для запросов
	int get_sum(int node, int start, int end, int l, int r);
	int get_min(int node, int start, int end, int l, int r);
	int get_max(int node, int start, int end, int l, int r);

	// Обновления
	void update_point(int node, int start, int end, int idx, int val);
	void update_range(int node, int start, int end, int l, int r, int val);

	// Распространение отложенных обновлений 
	void push_lazy(int node, int start, int end); // propogate

public:
	SegmentTree(const std::vector<int>& input_array);

	// Запросы на отрезке
	int sumQuery(int l, int r);
	int minQuery(int l, int r);
	int maxQuery(int l, int r);

	// Обновления
	void update(int idx, int new_val);
	void updateRange(int l, int r, int delta);

	// Отладка
	void print();
};
