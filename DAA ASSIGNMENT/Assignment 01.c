#include<stdio.h>
#include<malloc.h>
#include<string.h>

/*
    Function to find Minimum and Maximum in a Array using Divide and Conquere Technique
*/

void min_max(int *arr , int low , int high , int *min , int *max , int *no_comp)
{
    if (low == high)
    {
        *min = arr[low];
        *max = arr[high];
        return;
    }
    if (high - low == 1)
    {
        if (arr[low] < arr[high])
        {
            *min = arr[low];
            *max = arr[high];
        }
        else
        {
            *min = arr[high];
            *max = arr[low];
        }
        *no_comp = *no_comp + 1;
        return;
    }
    int min_temp, max_temp;
    int mid = low + (high - low) / 2;
    min_max(arr, low, mid, min, max, no_comp);
    min_max(arr, mid + 1, high, &min_temp, &max_temp, no_comp);
    if(min_temp < *min)
    {
        *min = min_temp;
    }
    if(max_temp > *max)
    {
        *max = max_temp;
    }
    *no_comp += 2;
}
int Cin()
{
    int n;
    char c;
    while(1)
    {
        if(scanf("%d",&n) != 1)
        {
            do
            {
               c = getchar();
            }while(c != '\n');
            printf("\nEnter a Valid Number :: \t");
        }
        else{
            break;
        }
    }
    return n;
}
int main() {
   int ch , n ;
   int *a = NULL;
   while(1) {
       printf("\n\t***MENU***\n1.Enter The Elements\n2.Print Tht Array\n3.Find the Min and Max\n4.Exit\n");
       ch = Cin();
       switch(ch)
       {
            case 1  :   printf("\nEnter the size of array:\t");
                        n = Cin();
                        if(n > 0) {
                            printf("\nPlease Enter the Elements\n");
                            free(a);
                            a = (int*)malloc(n * sizeof(int));
                            for(int i = 0 ; i < n ; i++ ) {
                                printf("Enter the Element %d\t" , i + 1);
                                a[i] = Cin();
                            }
                            printf("\nAll Elements Entered\n");
                        }
                        else {
                            printf("\n\nPlease enter the Correct size of Array\n");
                        }
                        break;
            case 2  :   if(!a) {
                            printf("The Array is Empty. Fill the Array\n");
                            break;
                        }
                        printf("\nThe Size of the Array %d\t\n" , n);
                        printf("The Entered Elements are :: \t");
                        for(int i = 0 ; i < n ; i++ ) {
                            printf("%d ", a[i]);
                        }
                        break;
            case 3  :   if(!a)
                            printf("\n\nThe Array is Empty.\nPlease Fill the Array\n");
                        else
                        {
                            int mn , mx , comp = 0;
                            min_max(a , 0 , n - 1 , &mx , &mn , &comp);
                            printf("\n\nThe Minimum in the Array :\t%d\n" , mx);
                            printf("\n\nThe Maximum in the Array :\t%d\n" , mn);
                            printf("\n\nTotal Number of Comparison:\t%d\n" , comp);
                        }
                        break;     
            case 4  :   printf("Thank You !Visit Again\n");
                        return 0;
            default : printf("Wrong Choice !!!!\n\n");
       }
   }
}