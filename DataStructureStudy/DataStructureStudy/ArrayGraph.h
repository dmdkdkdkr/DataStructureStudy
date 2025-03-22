#pragma once
#include "GraphType.h"

class ArrayGraph
{
private:
	GraphType::Type type;
	int vertexCount;
	int maxVertexCount;
	int edgeCount;
	bool* pVertices;
	int** ppEdges;

public:
	ArrayGraph(GraphType::Type _type, int _maxVertexCount);
	~ArrayGraph();

	bool AddVertex(int n);
	bool DeleteVertex(int n);
	bool AddEdge(int start, int end, int weight = 1);
	bool DeleteEdge(int start, int end);
	void Clear();
	void Display();
	int VertexCount();
	int EdgeCount();
	int MaxVertexCount();
	bool IsEmpty();
	bool IsFull();

private:
	bool IsVertexValid(int n) const;
};