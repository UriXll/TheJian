typedef struct arcnode{
    int serial_number;
    struct arcnode* nextArc;
} ArcNode;

typedef struct vnode{
    int serial_number;
    ArcNode* firstArc;
} VNode;

typedef struct {
    VNode* Adjlist;
    int Vertice;
    int Edge;
} AdjGraph;

AdjGraph* CreateAdj();