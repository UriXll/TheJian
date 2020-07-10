#include "general.h"


int main()
{
    AdjGraph* G = CreateAdj();
    int path[MaxSize];
    int d = -1;
    Find_All_Path(G, path, d, 1, 4);
    return 0;
}
