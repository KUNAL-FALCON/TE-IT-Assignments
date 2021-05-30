#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define maxN (1 << 16) - 1

typedef struct G
{
    int u, v, w;
} Graph;

int Cin(int flag)
{
    int n;
    char ch;

    while (1)
    {
        if (scanf("%d", &n) != 1)
        {
            do
            {
                ch = getchar();
            } while (ch != '\n');
            printf("\nEnter Correct Value\n");
        }
        else if (flag == 1 && n <= 0)
            printf("\nEnter a Value Greater than Zero\n");
        else if (flag == 2 && n < 0)
            printf("\nEnter a Postive Number\n");
        else
            break;
    }
    return n;
}
int solve(int s, int ne, int nv, int *dis, int *fr, Graph *G)
{
    int itr = 0, upd;
    dis[s] = 0;
    while (1)
    {
        itr++, upd = 0;
        if (itr > nv)
        {
            return 0;
        }
        for (int i = 0; i < ne; i++)
        {
            if (dis[G[i].u - 1] != maxN)
            {
                if (dis[G[i].u - 1] + G[i].w < dis[G[i].v - 1])
                {
                    dis[G[i].v - 1] = dis[G[i].u - 1] + G[i].w;
                    upd++;
                    fr[G[i].v - 1] = G[i].u - 1;
                }
            }
        }

        if (upd == 0)
            break;
    }
    return itr;
}
void printPath(int src, int *from, int idx)
{
    if (from[idx] == src)
    {
        printf("%d->", src + 1);
        return;
    }
    printPath(src, from, from[idx]);
    printf("%d->", from[idx] + 1);
}
int main()
{
    int ch, ne, nv;
    Graph *G = NULL;
    while (1)
    {
        printf("\n* * * Menu * * *\n");
        printf("\nEnter Choice\n\t1.Take Input\n\t2.Display\n\t3.Exit\n");
        printf("Choice :: ");
        ch = Cin(1);
        switch (ch)
        {
        case 1:
            free(G);
            printf("\nEnter the Number of Vertices :: ");
            nv = Cin(1);

            printf("\nEnter the Number of Edges :: ");
            while (1)
            {
                ne = Cin(1);
                if (ne <= nv * (nv - 1) / 2)
                    break;
                else
                    printf("\nMaximum Limit for Number of Edges is : %d\nPlease Enter it Again!!\n", nv * (nv - 1) / 2);
            }

            G = (Graph *)malloc(ne * sizeof(Graph));
            printf("\nEnter the Details for the Graph\n");
            for (int i = 0; i < ne; i++)
            {
                printf("Edge : %d\n", i + 1);
                printf("Source Vertex :: ");
                G[i].u = Cin(2);
                printf("Destination Vertex :: ");
                G[i].v = Cin(2);
                if (G[i].u == G[i].v || G[i].u > nv || G[i].v > nv)
                {
                    printf("\nWrong Information .. Please Enter Again\n");
                    i--;
                }
                else
                {
                    int j;
                    for (j = 0; j < i; j++)
                    {
                        if (G[j].u == G[i].u && G[j].v == G[i].v)
                        {
                            printf("The Edge Set is Already Present in The Graph\nDo you Want to Change the Weight? (1 - Yes / Other - No) :");
                            ch = Cin(1);
                            if (ch)
                            {
                                G[j].w = Cin(0);
                            }
                            break;
                        }
                    }
                    if (j == i)
                    {
                        printf("Weight of the Edge :: ");
                        G[i].w = Cin(0);
                    }
                    else 
                        i--;
                }
            }
            break;
        case 2:
            if (!G)
            {
                printf("\n The Graph is Empty\n");
                break;
            }
            int src;
            printf("\nEnter the Source Vertex\n");
            src = Cin(2);
            int *dist = (int *)malloc(nv * sizeof(int));
            int *from = (int *)malloc(nv * sizeof(int));
            for (int i = 0; i < nv; i++)
                dist[i] = maxN;
            int chk = solve(src - 1, ne, nv, dist, from, G);
            if (chk == 0)
            {
                printf("\nNegative Cycle is Present in the Graph\n");
                break;
            }
            printf("\nThe Number of Iteration are :: %d\n", chk);
            printf("\nVertex\tDistance From Source\tPath\n");
            for (int i = 0; i < nv; i++)
            {
                printf("%d\t\t%d\t\t", i + 1, dist[i]);
                if (dist[i] == maxN)
                {
                    printf("No Path Present\n"); 
                }
                else if (i + 1 == src)
                {
                    printf("Source Vertex\n");
                }
                else {
                    printPath(src - 1, from, i);
                    printf("%d\n", i + 1);
                }
            }
            free(dist), free(from);
            break;
        case 3:
            printf("\nThank You !!");
            free(G);
            return 0;
        default:
            printf("\nWroong Choice\n");
        }
    }
}