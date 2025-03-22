#pragma once
#include "LinkedList.h"
#include "GraphType.h"

class LinkedGraphEdge
{
public:
	int start;
	int end;
	int weight;

	LinkedGraphEdge();
	LinkedGraphEdge(int _start, int _end, int _weight);

	bool operator<(const LinkedGraphEdge other) { return weight < other.weight; }
	bool operator<=(const LinkedGraphEdge other) { return weight <= other.weight; }
	bool operator==(const LinkedGraphEdge other) { return (weight == other.weight) && (start == other.start) && (end == other.end); }
	bool operator>(const LinkedGraphEdge other) { return weight > other.weight; }
	bool operator>=(const LinkedGraphEdge other) { return weight >= other.weight; }
};

class LinkedGraph
{
private:
	GraphType::Type type;
	int vertexCount;
	int maxVertexCount;
	int edgeCount;
	bool* pVertices;
	LinkedList<LinkedGraphEdge>** ppEdges;

public:
	LinkedGraph(GraphType::Type _type, int _maxVertexCount);
	~LinkedGraph();

	bool AddVertex(int n);
	bool DeleteVertex(int n);
	bool AddEdge(int start, int end, int weight = 1);
	bool DeleteEdge(int start, int end);
	void Clear();
	void Display() const;
	void TraversalDFS(int startVertexID) const;
	void TraversalBFS(int startVertexID) const;
	LinkedGraph* MinimumSpanningTreeKruskal() const;
	LinkedGraph* MinimumSpanningTreePrim() const;
	void DisplayShortestPathByDijkstra(int start, int end) const;
	void DisplayShortestPathByFloyd() const;
	void DisplayReachability() const;

	bool IsEmpty() const;
	bool IsFull() const;
	int VertexCount() const;
	int MaxVertexCount() const;
	int EdgeCount() const;

private:
	bool IsVertexValid(int n) const;
	bool IsCycle(int start) const;
	void PrintMatrix2rd(int** ppMatrix) const;
};

