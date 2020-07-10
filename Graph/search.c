#include "general.h"
int Visited[MaxSize] = { 0 };
int pathnum = 1;

void DFS(AdjGraph* G, int v)
{
    Visited[v] = 1;
    int temp;
    ArcNode* p;
    printf("%2d", v);
    p = G->Adjlist[v].firstArc;
    while (p != NULL) {
        temp = p->serial_number;
        if (Visited[temp] == 0) {
            DFS(G, temp);
        }
        p = p->nextArc;
    }
}

void Find_Path(AdjGraph* G, int path[], int d, int start, int target)
{
    d++;
    path[d] = start;
    Visited[start] = 1;
    if (start == target) {
        for (int i = 0; i <= d; i++) {
            if (i == d) {
                printf("%d\n", path[i]);
                break;
            }
            printf("%d->", path[i]);
        }
        return;
    }
    ArcNode* p = G->Adjlist[start].firstArc;
    while (p != NULL) {
        start = p->serial_number;
        if (Visited[start] == 0) {
            Find_Path(G, path, d, start, target);
        }
        p = p->nextArc;
    }
}

void Find_All_Path(AdjGraph* G, int path[], int d, int start, int target)
{
    d++;
    path[d] = start;
    Visited[start] = 1;
    if (start == target) {
        printf("Path %d: ", pathnum++);
        for (int i = 0; i <= d; i++) {
            if (i == d) {
                printf("%d\n\n", path[i]);
                break;
            }
            printf("%d->", path[i]);
        }
    }
    ArcNode* p = G->Adjlist[start].firstArc;
    while (p != NULL) {
        start = p->serial_number;
        if (Visited[start] == 0) {
            Find_All_Path(G, path, d, start, target);
            Visited[start] = 0;
        }
        p = p->nextArc;
    }
}