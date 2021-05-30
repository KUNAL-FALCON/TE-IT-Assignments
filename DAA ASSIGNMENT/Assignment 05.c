#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int place (int R , int C , int X[])
{
    for(int i = 0 ; i < R ; i++ ) {
        if(X[i] == C || abs(X[i] - C) == abs(i - R)) 
            return 0;
    }
    return 1;
}
void Display(int N , int X[])
{
    
    printf("\n");
    for(int i = 0 ; i < N ; i++ ) 
        printf("----");
    printf("-\n");
    for(int i = 0 ; i < N ; i++ ) {
        printf("|");
        for(int j = 0 ; j < N ; j++ ) {
            if(X[i] == j) 
                printf(" Q |");
            else 
                printf("   |");
        }
        printf("\n");
        for(int A = 0 ; A < N ; A++ ) 
            printf("----");
        printf("-\n");
    }
    printf("\n**************************************************************************\n");
    char ch; 
    // scanf("%c",&ch); 
    fflush(stdin);
    do
    {
        scanf("%c",&ch);
    } while (ch != '\n');
    
}
void nQueen_Recursive(int k , int N , int *flag, int X[], int *cnt)
{
    if (*flag == 0) 
        return;
    for(int i = 0 ; i < N ; i++ ) {
        if(place(k , i , X))
        {
            X[k] = i;
            if(k + 1 == N && *flag != 0) {
                *cnt += 1;
                printf("Solution Number : %d", *cnt);
                Display(N , X);
                if(*flag == 1)
                    *flag = 0;
            }
            else
                nQueen_Recursive(k + 1 , N , flag , X , cnt);
        }
    }   
}
void nQueen_Iterative(int N , int flag , int X[] , int *cnt)
{
    int k = 0;
    while(k != -1)
    {
        if(X[k] < N)
        {
            if(place(k , X[k] , X))
            {
                if(k + 1 == N) 
                {
                    X[k] += 1;
                    *cnt += 1;
                    printf("Solution Number : %d", *cnt);
                    Display(N , X);
                    if(flag == 1)
                        return;
                }
                else 
                    k += 1;
            }
            else 
                X[k] += 1;
        } 
        else {
            X[k] = 0;
            k -= 1;
            X[k] += 1;
        }
    }
}
int Cin(int flag)
{
    int temp;
    char ch;
    while(1) {
        if(scanf("%d",&temp) != 1) {
            do
            {
                ch = getchar();
            } while (ch != '\n');
            printf("\nEnter Correct Value\n");
        }
        else if(temp < 0) 
            printf(" --> Enter A Value Greater than 0\n");
        else if(flag == 2 && temp <= 3) 
            printf(" --> Value Should be Greater than 3 for a Solution\n");
        else if(flag == 3 && (temp > 2 || temp <= 0)) 
            printf(" --> Wrong Value\n");
        else 
            break;
    }
    return temp;
}
int main()
{
    int choice , N = -1;
    while(1) {
        printf("\t***MENU***\n");
        printf("1.Input\n2.Solution\n3.Exit\nChoice :: ");
        choice = Cin(1);

        switch(choice)
        {
            case 1 :printf("\nEnter The Value of N :: ");
                    N = Cin(2);
                    break;
            case 2 :if(N == -1)
                    {
                        printf("\nEnter the Value of N\n");
                        break;
                    }
                    int ch1 , ch2;
                    printf("\nWhich Method You want to find the solution with\n\t1.Recursive\n\t2.Iterative\n");
                    ch1 = Cin(3);
                    printf("\nDo You want \n\t1.One Solution\n\t2.All Solution\n");
                    ch2 = Cin(3);

                    int *X = (int *)calloc(N , sizeof(int));
                    int cnt = 0;
                    if(ch1 == 1){   
                        nQueen_Recursive(0 , N , &ch2 , X , &cnt);
                        if(ch2 != 0)
                            printf("\nTotal Solutions are :: %d\n", cnt);
                    }
                    else {
                        nQueen_Iterative(N , ch2 , X , &cnt);
                        if(ch2 == 2)
                            printf("\nTotal Solutions are :: %d\n", cnt);
                    }
                    free(X);
                    break;
            case 3 :printf("\nThank You!\n");
                    return 0;
            default:printf("\nWrong Choice\n");
        }
    }
}