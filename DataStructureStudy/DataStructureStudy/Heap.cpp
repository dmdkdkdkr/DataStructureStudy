#include "Heap.h"

template<>
void Heap<LinkedGraphEdge>::Display()
{
	printf("\nDisplay heap => count: %d\n", count);

	int _lv = 0;
	for (int i = 1; i <= count; i++)
	{
		_lv = (int)(std::log2(i) + std::numeric_limits<double>::epsilon());
		for (int j = 0; j < _lv; j++) printf("\t");
		printf("[Lv:%d] => Edge => start: %d, end: %d, weight: %d\n", _lv, arr[i].start, arr[i].end, arr[i].weight);
	}

	printf("End displying heap\n");
}