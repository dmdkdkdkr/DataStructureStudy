#include "ArrayGraph.h"
#include <stdio.h>

ArrayGraph::ArrayGraph(GraphType::Type _type, int _maxVertexCount)
	: type(_type), vertexCount(0), maxVertexCount(_maxVertexCount), edgeCount(0)
{
	pVertices = new bool[_maxVertexCount] {false, };
	ppEdges = new int* [_maxVertexCount] {NULL};
	for (int i = 0; i < _maxVertexCount; i++)
		ppEdges[i] = new int[_maxVertexCount] {0, };
}

ArrayGraph::~ArrayGraph()
{
	printf("~ArrayGraph\n");
	delete[] pVertices;
	for (int i = 0; i < maxVertexCount; i++)
		delete[] ppEdges[i];
	delete ppEdges;
}

bool ArrayGraph::AddVertex(int n)
{
	if (IsFull())
	{
		printf("Graph is full\n");
		return false;
	}

	if (n >= maxVertexCount)
	{
		printf("Index is in out of range\n");
		return false;
	}

	if (pVertices[n])
	{
		printf("Same vertex is already added\n");
		return false;
	}

	pVertices[n] = true;
	vertexCount++;

	return true;
}

bool ArrayGraph::DeleteVertex(int n)
{
	if (IsEmpty())
	{
		printf("Graph is empty\n");
		return false;
	}

	if (n >= maxVertexCount)
	{
		printf("Index is in out of range\n");
		return false;
	}

	if (!pVertices[n])
	{
		printf("Can't find vertex\n");
		return false;
	}

	pVertices[n] = false;
	vertexCount--;

	// 정점 n과 연결되어 있는 간선을 모두 삭제
	for (int i = 0; i < maxVertexCount; i++)
	{
		if (ppEdges[n][i] > 0)
		{
			ppEdges[n][i] = 0;
			edgeCount--;
		}

		if (ppEdges[i][n] > 0)
		{
			ppEdges[i][n] = 0;
			edgeCount--;
		}
	}

	return true;
}

bool ArrayGraph::AddEdge(int start, int end, int weight)
{
	// 이미 추가되었을 경우 false 반환
	if (ppEdges[start][end] > 0)
	{
		printf("Same edge is already added\n");
		return false;
	}

	if (!IsVertexValid(start))
	{
		printf("Start vertex isn't valid\n");
		return false;
	}

	if (!IsVertexValid(end))
	{
		printf("End vertex isn't valid\n");
		return false;
	}

	// 간선 추가
	ppEdges[start][end] = weight;
	edgeCount++;

	// 타입 검사후 무방향이면 대칭 간선 추가
	if (type == GraphType::NON_DIRECTIONAL)
	{
		ppEdges[end][start] = weight;
		edgeCount++;
	}

	return true;
}

bool ArrayGraph::DeleteEdge(int start, int end)
{
	// 간선이 없으면 바로 리턴
	if (EdgeCount() == 0)
	{
		printf("There's no edge in graph\n");
		return false;
	}

	if (!IsVertexValid(start))
	{
		printf("Start vertex isn't valid\n");
		return false;
	}

	if (!IsVertexValid(end))
	{
		printf("End vertex isn't valid\n");
		return false;
	}

	// 간선 삭제
	ppEdges[start][end] = 0;
	edgeCount--;

	// 타입 검사후 무방향 그래프면 대칭 간선도 삭제
	if (type == GraphType::NON_DIRECTIONAL)
	{
		ppEdges[end][start] = 0;
		edgeCount--;
	}

	return true;
}

void ArrayGraph::Clear()
{
	for (int i = 0; i < maxVertexCount; i++) pVertices[i] = false;
	for (int i = 0; i < maxVertexCount; i++)
	{
		for (int j = 0; j < maxVertexCount; j++)
			ppEdges[i][j] = 0;
	}

	vertexCount = 0;
	edgeCount = 0;
}

void ArrayGraph::Display()
{
	printf("\nDisplay array graph => type: %d vertexCount: %d, edgeCount: %d\n", type, vertexCount, edgeCount);
	printf("[Vertices]\n");
	int displayedCnt = 0;
	for (int i = 0; i < maxVertexCount; i++)
	{
		bool bIsAdded = pVertices[i];
		if (bIsAdded)
		{
			if (i == 0) printf("\t");
			printf("(%d)", i);
			if (displayedCnt < vertexCount - 1) printf(", ");

			displayedCnt++;
			if (displayedCnt == vertexCount)
			{
				printf("\n");
				break;
			}
		}
	}

	printf("[Edges]\n");
	for (int i = 0; i < maxVertexCount; i++)
	{
		for (int j = 0; j < maxVertexCount; j++)
		{
			bool bIsAdded = ppEdges[i][j] > 0;
			if (bIsAdded) printf("\t(%d, %d) => weight: %d\n", i, j, ppEdges[i][j]);
		}
	}

	printf("End displaying array graph\n");
}

int inline ArrayGraph::VertexCount() { return vertexCount; }

int inline ArrayGraph::EdgeCount() { return edgeCount; }

int inline ArrayGraph::MaxVertexCount() { return maxVertexCount; }

bool inline ArrayGraph::IsEmpty() { return vertexCount == 0; }

bool inline ArrayGraph::IsFull() { return vertexCount == maxVertexCount; }

bool inline ArrayGraph::IsVertexValid(int n) const { return n < maxVertexCount && pVertices[n]; }
