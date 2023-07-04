#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void Sort();
void printArray();
int *Winning_Number();
int megaplier_num();
int *moreThan400();
void printWinners();

// Generating input to store in a file
struct input
{
    int num;
    int arr[5];
    int gold;
    int binary;
};

// Counting the number of winners who win below or equal to 400
typedef struct {
    int count400;
    int count200;
    int count50;
    int count40;
    int count30;
    int count20;
    int count16;
    int count12;
    int count10;
    int count8;
    int count6;
    int count4;
    int count2;
    int total_count;
    int total_saleAbove400;
} Count;


Count counts1={0,0,0,0};
Count counts2={0,0,0,0,0,0,0,0,0,0,0};
Count Total={0,0};


Count money();
Count Multiplier();


int main(void)
{
    struct input S1;
    Count counts1;
    Count counts2;
    Count total;

    printf("\n\n\t\t  Welcome To Mega Million Lottery");
    printf("\n\t\t***********************************\n\n");
    
    // Asking the user to enter number of tickets to be generated
    while (1)
    {
        printf(" Enter how many tickets to be generated : ");
        scanf("%d", &S1.num);
        if (S1.num > 0)
        {
            break;
        }
        else
        {
            printf("\n Sorry. Please enter a valid number\n\n");
        }
    }
    
    printf("\n");

    // Opening a file to input the tickets
    FILE *cPtr;

    cPtr = fopen("Text.txt", "w");

    // Generating 5 white balls in sorting order 
    int i = 0;
    int k, l, m;
    srand(time(0));
    while (i < S1.num)
    {
        fprintf(cPtr, "%d, ", i + 1);
        for (int j = 0; j < 5; j++)
        {
            k = rand() % 70 + 1;
            for (int l=0;l<j;l++)
            {
                while (k == S1.arr[l])
                {
                    k = rand() % 70 + 1;
                }
            }
            S1.arr[j] = k;
        }

        Sort(S1.arr);
        printArray(cPtr,S1.arr);

        // Generating the gold ball
        S1.gold = rand() % 25 + 1;
        fprintf(cPtr, "%d, ", S1.gold);

        // Generating the binary megaplier number (0/1)
        S1.binary = rand() % 2;
        fprintf(cPtr, "%d\n", S1.binary);

        i++;
        
    }

    fclose(cPtr);


    int Winners=0,Sales=0,Payout1=0,Payout2=0,Payout=0,Average=0,Profit=0;
    int *result = Winning_Number(S1);
    
    // Printing the megaplier number
    int megaplier=megaplier_num();
    printf("\n\n The Multiplier number is %d\n\n\n\n",megaplier);
  


    // Reopening the file for reading as well as for selecting the winning tickets
    cPtr = fopen("Text.txt", "r");

    if (cPtr == NULL) 
    {
        printf("Failed to open file\n");
        return 1;
    }
    else
    {
        while (fscanf(cPtr, "%d, %d, %d, %d, %d, %d, %d, %d",&S1.num, &S1.arr[0], &S1.arr[1], &S1.arr[2], &S1.arr[3], &S1.arr[4], &S1.gold,&S1.binary) == 8)
        {   
            // Calculating the number of sales depending on megaplier binary option
            if(S1.binary == 0)
            {
                Sales+=2;
            }
            else
            {
                Sales+=3;
            }

            int count1 = 0, count2 = 0;

            for (int i = 0; i < 5; i++) 
            {
                for (int j = 0; j < 5; j++)
                {
                    if (S1.arr[i] == result[j]) 
                    {
                        count1++;
                    }
                }
            }

            if (result[5] == S1.gold) 
            {
                count2++;
            }
        
            // Calling out the necessary functions to print the winners
            moreThan400(S1.num,count1,count2,S1.binary,megaplier,S1.arr,S1.gold);

            counts1=money(S1.num, count1, count2, S1.binary);

            counts2=Multiplier(S1.num, count1, count2, S1.binary,megaplier);

            Payout1 = (counts1.count2 * 2) + (counts1.count4 * 4) + (counts1.count10 * 10) + (counts1.count200 * 200);
            Payout2 = (counts2.count4 *4) + (counts2.count6 *6) + (counts2.count8 *8) + (counts2.count10 *10)+ (counts2.count12 *12)+ (counts2.count16 * 16)+ (counts2.count20 *20) + (counts2.count30 * 30) + (counts2.count40 * 40)+ (counts2.count50 * 50) + (counts2.count200 *200);

        }

        // Printing out the number of tickets winning below or equal to 400 
        int Total1 = 0;
        int a[4] = {counts1.count2, counts1.count4, counts1.count10, counts1.count200};

        for (int i = 0; i < 4; i++)
        {
            if (a[i] != 0)
            {
                printf("\n Without a Megapiler\n");
            }
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            if (a[i] != 0)
            {
                if (i < 2)
                {
                    printf( " %d won $%d\n", a[i], 2*i+2);
                    Total1 += a[i];
                }
                else
                {
                    printf(" %d won $%d\n", a[i],(190 * (i - 2) + 10));
                    Total1 += a[i] ;
                }
            }
        }


        int Total2 = 0;
        int b[11] = {counts2.count4, counts2.count6, counts2.count8, counts2.count10, counts2.count12, counts2.count16, counts2.count20, counts2.count30, counts2.count40, counts2.count50, counts2.count200};
        for (int i = 0; i < 11; i++)
        {
            if (b[i] != 0)
            {
                printf("\n With a Megapiler\n");
            }
            break;
        }
        for (int i = 0; i < 11; i++)
        {
            if (b[i] != 0)
            {
                if (i < 5) 
                {
                    printf(" %d won $%d\n", b[i], 2*(i+2));
                    Total2 += b[i];
                }
                else if(i == 5)
                {
                    printf(" %d won $16\n", b[5]);
                    Total2 += b[5];
                }
                else if(i<10)
                {
                    printf(" %d won $%d\n", b[i], 10*(i-4) );
                    Total2 += b[i];
                }
                else
                {
                    printf(" %d won $400\n", b[i]);
                    Total2 += b[i];
                }
            }
        }
 
        // Calculating the details like number of winners, payout, profit
        Winners=Total1+Total2+Total.total_count;
        Payout=Payout1+Payout2+Total.total_saleAbove400;
        if (Winners == 0)
        {
            Average=0;
        }
        else
        {
            Average = Payout/Winners;
        }
        Profit= Sales - Payout;
    }
    fclose(cPtr);

    // Printing the details like number of winners, payout, profit
    if (Winners > 0)
    {
        printf("\n There were total %d Winners.", Winners);
    }
    else
    {
        printf("\n There were no winners.");
    }
    printf("\n The total sales were $%d.", Sales);
    printf("\n The total payout was $%d.", Payout);
    if (Winners > 0)
    {
        Average = Payout / Winners;
        printf("\n The average amount won was $%d.", Average);
    }
    else
    {
        printf("\n The average amount won was $0.");
    }
    printf("\n The total profit was $%d.\n", Profit);

    printf("\n\n If the jackpot is won:\n\n");
    printf(" \t      Cash option : $100000000\n\n");
    printf("\t\t\tOR\n\n");
    printf(" \t\t  Annuity option\n" );
    printf(" \t\t ----------------\n") ;
    printf("\n\t  Initital Payment   : 1500000.00 ");
    float payment=1500000;
    
    for(int i=2;i<30;i++)
    {
        if (i<10)
        { 
            printf("\n\t Payment of year  %d  : ",i);
        }
        else
        {
             printf("\n\t Payment of year %d  : ",i);
        }
       
        payment = payment + (0.05 * payment);
        
        printf("%.2f",payment);
        
    }

    printf("\n\n\n\n\t\t Thank You\n");
    printf("\t\t***********\n\n\n");
    
    return 0;
    }


// Function to sort white balls
void Sort(int arr[])
{
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5 - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }    
    }
}

// Function to print white balls after sorting
void printArray(FILE *cPtr, int arr[])
{
    int i;
    for (i = 0; i < 5; i++)
        fprintf(cPtr, "%d, ", arr[i]);
   
}

// Function to genearte the winning numbers (5 white and 1 gold ball)
int* Winning_Number(struct input S1)
{
    int j,k,*a;
    a = malloc(sizeof(int) * 6); // allocate memory for the array of integers
    for (int j = 0; j < 5; j++)
    {
        k = rand() % 70 + 1;
        for (int l=0;l<j;l++)
            {
                while (k == S1.arr[l])
                {
                    k = rand() % 70 + 1;
                }
            }
        S1.arr[j] = k;
        ; // assign the value of S1.arr[j] to a[j]
    }
    Sort(S1.arr);
    printf(" Winning Numbers : ");
    for (int j = 0; j < 5; j++)
    {
        a[j] = S1.arr[j];
        printf(" %d ", S1.arr[j]);
    }
    printf("|");
    S1.gold = rand() % 25 + 1;
    a[5] = S1.gold; // assign the value of S1.gold to a[5]
    printf(" %d ", S1.gold);
    return a; // return the pointer to the array of integers
}

// Generating the megaplier number if the winner has chosen a megaplier option
int megaplier_num()
{
    int a[]={2,2,2,2,2,3,3,3,3,3,3.4,4,4,5};
    int k= rand()%15 +1;
    return a[k];
}

// Printing out the winners winning more than 400 and taking into acccount the megaplier option and counting their occurences
int *moreThan400(int num,int white,int gold,int multiplier, int megaplier,int arr[5],int special)
{
    int total,k;
    if (white == 5 && gold == 1)
    {
        printf("\n Congratulations\n");
        printf(" %d won Jackpot\n",num);
        printWinners(arr,special);
        printf(" Won : 100000000\n\n\n");
        Total.total_count++;
    } 
    else if(white == 5 )
    {
        if(multiplier == 0)
        {
            k=1;
        }
        else
        {
            k=megaplier;
        }
        total= 1000000 * k;
        printf(" Ticket Number : %d \n",num);
        printWinners(arr,special);
        printf(" Won : %d\n\n",total);
        Total.total_count++;
        Total.total_saleAbove400+=total;
    }
    else if(white == 4 && gold == 1 )
    {
        if(multiplier == 0)
        {
            k=1;
        }
        else
        {
            k=megaplier;
        }
        total= 10000 * k;
        printf(" Ticket Number : %d \n",num);
        printWinners(arr,special);
        printf(" Won : %d\n\n",total);
        Total.total_count++;    
        Total.total_saleAbove400+=total;
    }
    else if(white == 4)
    {
        if(multiplier == 0)
        {
            k=1;
        }
        else
        {
            k=megaplier;
        }
        total= 500 * k;
        printf(" Ticket Number : %d \n",num);
        printWinners(arr,special);
        printf(" Won : %d\n\n",total);
        Total.total_count++;
        Total.total_saleAbove400+=total;
    }
    else if(white == 3 && gold == 1)
    {
        if(multiplier == 0)
        {
            k=1;
        }
        else
        {
            k=megaplier;
            total=200 * k;
            if ((total) > 400 )
            {
                printf(" Ticket Number : %d \n",num);
                printWinners(arr,special);
                printf(" Won : %d\n\n",total);
                Total.total_count++;
                Total.total_saleAbove400+=total;
            }

        }
    }
    else
    {
       return 0;
    }
    

}

// Printing out the winners who won less than or equal to 400 but does not have opted for megaplier option
Count money(int num, int white, int gold, int multiplier)
{ 
    if (white == 3 && gold == 1 && multiplier == 0) 
    {
        counts1.count200++;
    }
    else if (white == 3 && multiplier == 0) 
    {
        counts1.count10++;
    }
    else if (white == 2 && gold == 1 && multiplier == 0) 
    {
        counts1.count10++;
    }
    else if (white == 1 && gold == 1 && multiplier == 0) 
    {
        counts1.count4++;
    }
    else if (gold == 1 && multiplier == 0) 
    {
        counts1.count2++;
    }

    return counts1;
}

// Function to print out the winners who won 400 or below and have opted for megaplier option
Count Multiplier(int num,int white,int gold,int multiplier,int megaplier)
{   
    int k,total;
    if (white == 3 && gold == 1 && multiplier == 1) {
        total=200 * megaplier;
        if (total == 400)
        {
            counts2.count400++;
        } 
    }
    else if ((white == 3 && multiplier == 1) || (white == 2 && gold == 1 && multiplier == 1)) {
        
        total=10 * megaplier;
        if(total == 50)
        {
            counts2.count50++;
        }
        else if(total == 40)
        {
            counts2.count40++;
        }
        else if(total == 30)
        {
            counts2.count30++;
        }
        else
        {
            counts2.count20++;
        }
        
    }
    else if (white == 1 && gold == 1 && multiplier == 1) {
      
        total=4 * megaplier;
        if(total == 20)
        {
            counts2.count20++;
        }
        else if(total == 16)
        {
            counts2.count16++;
        }
        else if(total == 12)
        {
            counts2.count12++;
        }
        else
        {
            counts2.count8++;
        }
    }
    else if (gold == 1 && multiplier == 1) {
   
        total=2 * megaplier;
        if(total == 10)
        {
            counts2.count10++;
        }
        else if(total == 8)
        {
            counts2.count8++;
        }
        else if(total == 6)
        {
            counts2.count6++;
        }
        else
        {
            counts2.count4++;
        }
    }

    return counts2;
}

// Function for printing out the white and gold ball if the winner is winning above 400 
void printWinners(int arr[5],int special)
{ 
    int a;
    for (int j = 0; j < 5; j++)
    {
        printf(" %d ", arr[j]);
    }
    printf("|");
    printf(" %d \n", special);
}
