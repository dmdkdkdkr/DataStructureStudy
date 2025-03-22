#include "Etc.h"
#include "LinkedStack.h"
#include <stdio.h>
#include <tuple>

void Etc::HanoiRecursively(int h, int from, int mid, int to)
{
	if (h < 0)
	{
		printf("유효하지 않은 h값입니다.\n");
		return;
	}

	if (h == 1)
	{
		PrintHanoiResult(h, from, to);
	}
	else
	{
		HanoiRecursively(h - 1, from, to, mid);
		PrintHanoiResult(h, from, to);
		HanoiRecursively(h - 1, mid, from, to);
	}
}

void Etc::Hanoi(int h, int from, int mid, int to)
{
	typedef std::tuple<int, int, int, int> HanoiData;
	
	auto _pStack = new LinkedStack<HanoiData>();
	_pStack->Push(std::make_tuple(h, from, mid, to));

	bool _flag = true;
	while (_pStack->Count() > 0)
	{
		auto _data = _pStack->Pop();
		int _h = std::get<0>(_data);
		int _from = std::get<1>(_data);
		int _mid = std::get<2>(_data);
		int _to = std::get<3>(_data);

		if (_h == 1)
		{
			PrintHanoiResult(_h, _from, _to);
			_flag = false;
		}
		else if (_flag)
		{
			_pStack->Push(std::make_tuple(_h, _from, _mid, _to));
			_pStack->Push(std::make_tuple(_h - 1, _from, _to, _mid));
		}
		else
		{
			PrintHanoiResult(_h, _from, _to);
			_pStack->Push(std::make_tuple(_h - 1, _mid, _from, _to));
			_flag = true;
		}
	}

	delete _pStack;
}

void Etc::PrintHanoiResult(int h, int from, int to)
{
	printf("h:%d => %d에서 %d로 옮겼습니다.\n", h, from, to);
}
