#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Jobs
{
    char name[30];
    int size, id, rt;
};
typedef struct Jobs jobs;
int Cin()
{
    int n;
    char ch;
    while (1)
    {
        if (scanf("%d", &n) != 1)
        {
            printf("Enter Integer Value greater than Zero\n");
            do
            {
                ch = getchar();
            } while (ch != '\n');
        }
        else if (n <= 0)
        {
            printf("Enter a Value Greater than Zero\n");
        }
        else
            break;
    }
    return n;
}
void getString(char name[])
{
    int i = 0;
    char c = getchar();
    while (c != '\n')
    {
        name[i++] = c;
        c = getchar();
    }
    name[i] = '\0';
}
void merge(jobs *Job, int lo, int mid, int hi, int *a)
{
    int s1 = mid - lo + 1;
    int s2 = hi - mid;
    int *t1 = (int *)malloc(s1 * sizeof(int));
    int *t2 = (int *)malloc(s2 * sizeof(int));

    for (int i = 0; i < s1; i++)
    {
        t1[i] = a[lo + i];
    }
    for (int i = 0; i < s2; i++)
    {
        t2[i] = a[mid + 1 + i];
    }
    int i = 0, j = 0, k = lo;
    while (i < s1 && j < s2)
    {
        if ((Job + t1[i] - 1)->size <= (Job + t2[j] - 1)->size)
        {
            a[k] = t1[i++];
        }
        else
        {
            a[k] = t2[j++];
        }
        ++k;
    }
    while (i < s1)
    {
        a[k++] = t1[i++];
    }
    while (j < s2)
    {
        a[k++] = t2[j++];
    }
    free(t1), free(t2);
}
void merge_sort(jobs *Job, int lo, int hi, int *a)
{
    if (lo < hi)
    {
        int mi = (lo + hi) / 2;
        merge_sort(Job, lo, mi, a);
        merge_sort(Job, mi + 1, hi, a);
        merge(Job, lo, mi, hi, a);
    }
}
int main()
{
    int ch, total_tapes, total_jobs;
    jobs *Job = NULL;
    int *aa = NULL;
    while (1)
    {
        printf("\t\t-----OST-----\n");
        printf("\n\tEnter Choice\n1.Take Input\n2.Find Average Retreival Time\n3.Exit\n\n");
        printf("Choice ::\t");
        ch = Cin();
        switch (ch)
        {
        case 1:
            free(Job), free(aa);
            Job = NULL;
            aa = NULL;
            printf("\nEnter the Number of Jobs::\t");
            total_jobs = Cin();
            Job = (jobs *)malloc(total_jobs * sizeof(jobs));
            aa = (int *)malloc(total_jobs * sizeof(int));
            for (int i = 0; i < total_jobs; i++)
            {
                printf("\nEnter the Name of Job::\t");
                fflush(stdin);
                getString((Job + i)->name);
                printf("\nEnter the Size of Job::\t");
                (Job + i)->size = Cin();
                (Job + i)->id = i + 1;
                aa[i] = (Job + i)->id;
            }
            printf("\nEnter the Number of Tapes::\t");
            total_tapes = Cin();
            //total_tapes = total_jobs > total_tapes ? total_tapes : total_jobs;
            break;
        case 2:
            if (!Job)
            {
                printf("\nPlease Enter the Job Details First\n");
                break;
            }
            float avg_time = 0.0;
            if (total_tapes >= total_jobs)
            {
                for (int i = 0; i < total_jobs; i++)
                {
                    (Job + i)->rt = (Job + i)->size;
                    avg_time += (Job + i)->size;
                }
            }
            else
            {
                merge_sort(Job, 0, total_jobs - 1, aa);
                for (int i = 0; i < total_tapes; i++)
                {
                    int j = i;
                    printf("Tape %d:=> ", i + 1);
                    while (j < total_jobs)
                    {
                        printf("%d ", aa[j]);
                        j += total_tapes;
                    }
                    printf("\n");
                }
                int *a = (int *)calloc(total_tapes, sizeof(int));
                for (int i = 0; i < total_jobs; i++)
                {
                    a[i % total_tapes] += (Job + aa[i] - 1)->size;
                    (Job + aa[i] - 1)->rt = a[i % total_tapes];
                    avg_time += a[i % total_tapes];
                }
                free(a);
            }
            printf("\n\nId\tName\tSize\tRetreival Time\n");
            for (int i = 0; i < total_jobs; i++)
            {
                printf("%d\t%s\t%d\t%d\n", (Job + i)->id, (Job + i)->name, (Job + i)->size, (Job + i)->rt);
            }
            printf("\n\n");
            printf("\nAverage Retreival Time is :: %0.2f\n\n", avg_time / total_jobs);
            break;
        case 3:
            printf("\nThank You!!\n");
            free(Job), free(aa);
            return 0;
        default:
            printf("\nWrong Choice!!!\n");
        }
    }
}