#include "general.h"

AdjGraph* CreateAdj()
{
    int origin;
    int destination;
    int Vertice = 0;
    int Edge = 0;
    int Visited[MaxSize] = { 0 };
    AdjGraph* G = (AdjGraph*)malloc(sizeof(AdjGraph));
    G->Adjlist = (VNode*)malloc(sizeof(VNode) * MaxSize);
    for (int i = 0; i < MaxSize; i++) {
        G->Adjlist[i].serial_number = i;
        G->Adjlist[i].firstArc = NULL;
    }
    ArcNode* temp;
    while (scanf("%d%d", &origin, &destination) != EOF) {
        if (Visited[origin] == 0) {
            Vertice++;
            Visited[origin] = 1;
        }
        if (Visited[destination] == 0) {
            Vertice++;
            Visited[destination] = 1;
        }
        temp = (ArcNode*)malloc(sizeof(ArcNode));
        temp->serial_number = destination;
        temp->nextArc = G->Adjlist[origin].firstArc;
        G->Adjlist[origin].firstArc = temp;
        Edge++;
    }
    G->Vertice = Vertice;
    G->Edge = Edge;
    return G;
}
