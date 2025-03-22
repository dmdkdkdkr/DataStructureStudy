#include "LinkedGraph.h"
#include "LinkedStack.h"
#include "LinkedQueue.h"
#include "Heap.h"
#include "ArrayList.h"
#include <malloc.h>

LinkedGraphEdge::LinkedGraphEdge() {}

LinkedGraphEdge::LinkedGraphEdge(int _start, int _end, int _weight) : start(_start), end(_end), weight(_weight) {}

LinkedGraph::LinkedGraph(GraphType::Type _type, int _maxVertexCount) : type(_type), maxVertexCount(_maxVertexCount)
{
    if (_maxVertexCount < 1)
    {
        printf("_maxVertexCount is less than 1. Adjust value to 1\n");
        maxVertexCount = 1;
    }

    vertexCount = 0;
    edgeCount = 0;
    pVertices = new bool[_maxVertexCount] {false, };
    ppEdges = new LinkedList<LinkedGraphEdge>*[_maxVertexCount]();
    for (int i = 0; i < _maxVertexCount; i++)
        ppEdges[i] = new LinkedList<LinkedGraphEdge>();
}

LinkedGraph::~LinkedGraph()
{
    printf("LinkedGraph is called");
    delete[] pVertices;
    for (int i = 0; i < maxVertexCount; i++)
        delete ppEdges[i];
    delete[] ppEdges;
}

bool LinkedGraph::AddVertex(int n)
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

bool LinkedGraph::DeleteVertex(int n)
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
        printf("Can't find the same vertex\n");
        return false;
    }

    pVertices[n] = false;
    vertexCount--;

    for (int i = 0; i < maxVertexCount; i++)
    {
        int start = i;
        auto pList = ppEdges[i];
        for (int j = 0; j < pList->Count(); j++)
        {
            auto edge = pList->Get(j);
            if (start == n || edge.end == n)
            {
                pList->Remove(j);
                edgeCount--;
                j--;
            }
        }
    }

    return true;
}

bool LinkedGraph::AddEdge(int start, int end, int weight)
{
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

    auto pList = ppEdges[start];
    for (int i = 0; i < pList->Count(); i++)
    {
        auto edge = ppEdges[start]->Get(i);
        if (edge.end == end)
        {
            printf("Same edge is already adeed\n");
            return false;
        }
    }

    ppEdges[start]->AddToLast(LinkedGraphEdge(start, end, weight));
    edgeCount++;

    if (type == GraphType::NON_DIRECTIONAL)
    {
        ppEdges[end]->AddToLast(LinkedGraphEdge(end, start, weight));
        edgeCount++;
    }

    return true;
}

bool LinkedGraph::DeleteEdge(int start, int end)
{
    if (edgeCount == 0)
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

    bool canRemove = false;
    auto pList = ppEdges[start];
    for (int i = 0; i < pList->Count(); i++)
    {
        auto edge = pList->Get(i);
        if (edge.end == end)
        {
            pList->Remove(i);
            edgeCount--;
            canRemove = true;
            break;
        }
    }

    if (!canRemove)
    {
        printf("Can't find the same edge\n");
        return false;
    }

    if (type == GraphType::NON_DIRECTIONAL)
    {
        pList = ppEdges[end];
        for (int i = 0; i < pList->Count(); i++)
        {
            auto edge = pList->Get(i);
            if (edge.end == start)
            {
                pList->Remove(i);
                edgeCount--;
                break;
            }
        }
    }

    return false;
}

void LinkedGraph::Clear()
{
    if (IsEmpty()) return;

    for (int i = 0; i < maxVertexCount; i++)
    {
        pVertices[i] = false;
        ppEdges[i]->Clear();
    }

    vertexCount = 0;
    edgeCount = 0;
}

void LinkedGraph::Display() const
{
    printf("\nDisplaying linked graph => type: %d, vertexCount: %d, edgeCount: %d\n", type, vertexCount, edgeCount);

    printf("[Vertexs]\n");
    if (vertexCount > 0)
    {
        int displayCnt = 0;
        for (int i = 0; i < maxVertexCount; i++)
        {
            if (i == 0) printf("\t");

            if (pVertices[i])
            {
                printf("(%d)", i);
                if (displayCnt < vertexCount - 1)
                    printf(", ");
                displayCnt++;
            }

            if (i == maxVertexCount - 1) printf("\n");
        }
    }

    printf("[Edges]\n");
    if (edgeCount > 0)
    {
        for (int i = 0; i < maxVertexCount; i++)
        {
            auto pList = ppEdges[i];
            int start = i;
            for (int j = 0; j < pList->Count(); j++)
            {
                auto edge = pList->Get(j);
                printf("\t(%d, %d) => Weight: %d\n", start, edge.end, edge.weight);
            }
        }
    }

    printf("End displaying linked graph\n");
}

void LinkedGraph::TraversalDFS(int startVertexID) const
{
    printf("\nTraverse graph by DFS\n");

    if (!IsVertexValid(startVertexID))
    {
        printf("Start vertex ID isn't valid\n");
        return;
    }

    auto vertex = startVertexID;
    auto pVisited = new bool[_msize(pVertices) / sizeof(bool)] {false, };
    auto pStack = new LinkedStack<int>();
    pStack->Push(vertex);
    pVisited[vertex] = true;

    while (!pStack->IsEmpty())
    {
        int vertex = pStack->Pop();
        printf("(%d) ", vertex);

        auto edgeList = ppEdges[vertex];
        for (int i = 0; i < edgeList->Count(); i++)
        {
            auto edge = edgeList->Get(i);
            if (!pVisited[edge.end])
            {
                pStack->Push(edge.end);
                pVisited[edge.end] = true;
            }
        }
    }
    printf("\n");

    delete[] pVisited;
    delete pStack;

    printf("End traversing graph\n");
}

void LinkedGraph::TraversalBFS(int startVertexID) const
{
    printf("\nTraverse graph by BFS\n");

    if (!IsVertexValid(startVertexID))
    {
        printf("Start vertex ID isn't valid\n");
        return;
    }

    auto vertex = startVertexID;
    auto pVisited = new bool[_msize(pVertices) / sizeof(bool)] {false, };
    auto pQueue = new LinkedQueue<int>();
    pQueue->Enqueue(vertex);
    pVisited[vertex] = true;

    while (!pQueue->IsEmpty())
    {
        int vertex = pQueue->Dequeue();
        printf("(%d) ", vertex);

        auto edgeList = ppEdges[vertex];
        for (int i = 0; i < edgeList->Count(); i++)
        {
            auto edge = edgeList->Get(i);
            if (!pVisited[edge.end])
            {
                pQueue->Enqueue(edge.end);
                pVisited[edge.end] = true;
            }
        }
    }
    printf("\n");

    delete[] pVisited;
    delete pQueue;

    printf("End traversing graph\n");
}

LinkedGraph* LinkedGraph::MinimumSpanningTreeKruskal() const
{
    // 최소 신장 트리를 초기화 한다.
    auto pMst = new LinkedGraph(type, maxVertexCount);
    for (int i = 0; i < vertexCount; i++) pMst->AddVertex(i);

    // 그래프의 모든 간선을 가중치 별로 정렬한 힙을 만든다.
    auto pEdgeHeap = new Heap<LinkedGraphEdge>(edgeCount, false);
    for (int i = 0; i < maxVertexCount; i++)
    {
        for (int j = 0; j < ppEdges[i]->Count(); j++)
            pEdgeHeap->Insert(ppEdges[i]->Get(j));
    }

    // 힙을 순회하며 그래프의 모든 정점을 잇는다.
    int maxEdgeCount = (type == GraphType::DIRECTIONAL) ? vertexCount - 1 : 2 * (vertexCount - 1);
    while (pMst->EdgeCount() < maxEdgeCount)
    {
        auto edge = pEdgeHeap->Peek();
        pMst->AddEdge(edge.start, edge.end, edge.weight);
        if (pMst->IsCycle(edge.start)) pMst->DeleteEdge(edge.start, edge.end);

        pEdgeHeap->Remove(edge);
        if (type == GraphType::NON_DIRECTIONAL)
        {
            auto pEdgeList = ppEdges[edge.end];
            for (int i = 0; i < pEdgeList->Count(); i++)
            {
                auto otherEdge = pEdgeList->Get(i);
                if (otherEdge.end == edge.start)
                {
                    pEdgeHeap->Remove(otherEdge);
                    break;
                }
            }
        }
    }

    delete pEdgeHeap;
    return pMst;
}

LinkedGraph* LinkedGraph::MinimumSpanningTreePrim() const
{
    // 최소 신장 트리를 초기화 한다.
    LinkedGraph* pMst = new LinkedGraph(type, maxVertexCount);

    // 첫번째로 방문할 정점을 찾아 신장 트리에 넣는다.
    int vertex = 0;
    for (int i = 0; i < maxVertexCount; i++)
    {
        if (pVertices[i])
        {
            vertex = i;
            break;
        }
    }
    pMst->AddVertex(vertex);

    // 신장 트리에 모든 정점이 추가될때까지 반복한다.
    auto pVisited = new bool[maxVertexCount] {false, };
    auto pEdgeHeap = new Heap<LinkedGraphEdge>(edgeCount, false);
    while (pMst->vertexCount < vertexCount)
    {
        // 노드를 방문처리 한다.
        pVisited[vertex] = true;

        // 정점과 연결된 모든 간선을 힙에 넣는다. 단, 방문 이력이 있는 노드로 이어지는 간선은 제외.
        auto pEdgeList = ppEdges[vertex];
        for (int i = 0; i < pEdgeList->Count(); i++)
        {
            auto edge = pEdgeList->Get(i);
            if (pVisited[edge.end]) continue;
            pEdgeHeap->Insert(edge);
        }

        // 힙에서 최소 비용의 간선을 꺼내 사이클이 발생하는지 체크한다. 발생하지 않는다면 해당 간선을 따라 이동한다.
        LinkedGraphEdge* pCheapest = NULL;
        while (pCheapest == NULL)
        {
            auto edge = pEdgeHeap->Peek();

            if (!pVisited[edge.end]) pMst->AddVertex(edge.end);
            pMst->AddEdge(edge.start, edge.end, edge.weight);
            if (pMst->IsCycle(edge.start))
            {
                if (!pVisited[edge.end])
                    pMst->DeleteVertex(edge.end);
                else
                    pMst->DeleteEdge(edge.start, edge.end);
            }
            else
            {
                vertex = edge.end;
                pCheapest = &edge;
            }
            pEdgeHeap->Remove(edge);
        }
    }

    delete[] pVisited;
    delete pEdgeHeap;

    return pMst;
}

void LinkedGraph::DisplayShortestPathByDijkstra(int start, int end) const
{
    if (!IsVertexValid(start))
    {
        printf("시작 노드가 유효하지 않습니다. => start: %d\n", start);
        return;
    }

    if (!IsVertexValid(end))
    {
        printf("도착 노드가 유효하지 않습니다. => end: %d\n", end);
        return;
    }

    int* pDistanceArr = new int[maxVertexCount] {};
    std::fill(pDistanceArr, pDistanceArr + maxVertexCount, std::numeric_limits<int>::max());
    pDistanceArr[start] = 0;

    int* pPrevVisitArr = new int[maxVertexCount] {};
    std::fill(pPrevVisitArr, pPrevVisitArr + maxVertexCount, -1);

    auto* pList = new ArrayList<int>(vertexCount - 1);
    for (int i = 0; i < maxVertexCount; i++)
    {
        if (IsVertexValid(i) && i != start)
            pList->AddToLast(i);
    }

    int node = start;
    while (pList->Count() > 0)
    {
        auto edges = ppEdges[node];
        for (int i = 0; i < edges->Count(); i++)
        {
            auto edge = edges->Get(i);
            int to = edge.end;
            int weight = pDistanceArr[node] + edge.weight;
            if (weight < pDistanceArr[to])
            {
                pDistanceArr[to] = weight;
                pPrevVisitArr[to] = node;
            }
        }

        int iNext = -1;
        int minWeight = std::numeric_limits<int>::max();
        for (int i = 0; i < pList->Count(); i++)
        {
            node = (*pList)[i];
            if (pDistanceArr[node] < minWeight)
            {
                iNext = i;
                minWeight = pDistanceArr[node];
            }
        }
        node = (*pList)[iNext];
        pList->Remove(iNext);
    }

    LinkedStack<int>* pStack = new LinkedStack<int>();
    node = end;
    while (node != -1)
    {
        pStack->Push(node);
        node = pPrevVisitArr[node];
    }

    printf("Shortest Path (%d -> %d)\n", start, end);
    while (!pStack->IsEmpty())
    {
        int node = pStack->Pop();
        if (pStack->Count() > 0)
            printf("%d -> ", node);
        else
            printf("%d\n", node);
    }

    delete pStack;
    delete pList;
    delete[] pPrevVisitArr;
    delete[] pDistanceArr;
}

void LinkedGraph::DisplayShortestPathByFloyd() const
{
    int** ppDistanceArr = new int* [maxVertexCount] {};
    for (int i = 0; i < maxVertexCount; i++)
    {
        ppDistanceArr[i] = new int[maxVertexCount] {};
        std::fill(ppDistanceArr[i], ppDistanceArr[i] + maxVertexCount, std::numeric_limits<int>::max() / 3);
    }

    for (int i = 0; i < maxVertexCount; i++)
    {
        if (!IsVertexValid(i)) continue;

        ppDistanceArr[i][i] = 0;
        auto edges = ppEdges[i];
        for (int j = 0; j < edges->Count(); j++)
        {
            auto edge = edges->Get(j);
            ppDistanceArr[i][edge.end] = edge.weight;
        }
    }

    for (int v = 0; v < maxVertexCount; v++)
    {
        for (int r = 0; r < maxVertexCount; r++)
        {
            for (int s = 0; s < maxVertexCount; s++)
            {
                if (ppDistanceArr[r][v] + ppDistanceArr[v][s] < ppDistanceArr[r][s])
                    ppDistanceArr[r][s] = ppDistanceArr[r][v] + ppDistanceArr[v][s];
            }
        }
    }

    printf("Show shortest weight by Floyd. (Row = Start, Column = End)\n");
    PrintMatrix2rd(ppDistanceArr);

    for (int i = 0; i < maxVertexCount; i++)
        delete[] ppDistanceArr[i];
    delete[] ppDistanceArr;
}

void LinkedGraph::DisplayReachability() const
{
    int** ppReachable = new int* [maxVertexCount];
    for (int i = 0; i < maxVertexCount; i++)
    {
        ppReachable[i] = new int[maxVertexCount];
        std::fill(ppReachable[i], ppReachable[i] + maxVertexCount, 0);
    }

    for (int i = 0; i < maxVertexCount; i++)
    {
        if (!IsVertexValid(i)) continue;
        ppReachable[i][i] = 1;
        auto edges = ppEdges[i];
        for (int j = 0; j < edges->Count(); j++)
        {
            auto edge = edges->Get(j);
            ppReachable[i][edge.end] = 1;
        }
    }

    for (int v = 0; v < maxVertexCount; v++)
    {
        for (int r = 0; r < maxVertexCount; r++)
        {
            if (ppReachable[r][v] <= 0) continue;
            for (int s = 0; s < maxVertexCount; s++)
            {
                if (ppReachable[v][s] <= 0) continue;
                ppReachable[r][s] = 1;
            }
        }
    }

    printf("Show reachability. (Row = Start, Column = End)\n");
    PrintMatrix2rd(ppReachable);

    for (int i = 0; i < maxVertexCount; i++)
        delete[] ppReachable[i];
    delete[] ppReachable;
}

bool inline LinkedGraph::IsEmpty() const { return vertexCount == 0; }

bool inline LinkedGraph::IsFull() const { return vertexCount == maxVertexCount; }

int inline LinkedGraph::VertexCount() const { return vertexCount; }

int inline LinkedGraph::MaxVertexCount() const { return maxVertexCount; }

int inline LinkedGraph::EdgeCount() const { return edgeCount; }

bool inline LinkedGraph::IsVertexValid(int n) const { return n < maxVertexCount && pVertices[n]; }

bool LinkedGraph::IsCycle(int start) const
{
    bool IsCycle = false;

    auto pVisited = new bool[maxVertexCount] {false, };
    auto pPrevVisited = new int[maxVertexCount] {-1, };

    auto pStack = new LinkedStack<int>();
    pStack->Push(start);
    pVisited[start] = true;
    while (pStack->Count() > 0)
    {
        int vertex = pStack->Pop();
        auto pEdges = ppEdges[vertex];
        for (int i = 0; i < pEdges->Count(); i++)
        {
            auto edge = pEdges->Get(i);
            if (pPrevVisited[vertex] == edge.end) continue;

            if (pVisited[edge.end])
            {
                IsCycle = true;
                break;
            }
            else
            {
                pVisited[edge.end] = true;
                pPrevVisited[edge.end] = vertex;
                pStack->Push(edge.end);
            }
        }
    }

    delete[] pVisited;
    delete[] pPrevVisited;
    delete pStack;

    return IsCycle;
}

void LinkedGraph::PrintMatrix2rd(int** ppMatrix) const
{
    for (int i = 0; i < maxVertexCount; i++)
    {
        if (i == 0) printf("\t|");
        if (!IsVertexValid(i)) continue;
        printf("%d\t|", i);
    }
    printf("\n");

    for (int i = 0; i < maxVertexCount; i++)
    {
        if (!IsVertexValid(i)) continue;
        printf("%d\t|", i);
        for (int j = 0; j < maxVertexCount; j++)
        {
            if (!IsVertexValid(j)) continue;
            printf("%d\t|", ppMatrix[i][j]);
        }
        printf("\n");
    }
}
