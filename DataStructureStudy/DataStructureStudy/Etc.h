#pragma once
class Etc
{
public:
	static void HanoiRecursively(int h, int from, int mid, int to);
	static void Hanoi(int h, int from, int mid, int to);

private:
	static void PrintHanoiResult(int h, int from, int to);
};

