// Aggregate Method
#include <stdio.h>
#include <math.h>
void main()
{
    float tot = 0;
    int arr[4] = {0};
    printf("Enter value between 0 to %f\n", pow(2, 4));
    float n;
    scanf("%f", &n);
    printf("Counter:0, Cost:0 \n");
    for (int j = 0; j < n; j++)
    {
        int i = 0;
        while (arr[i] == 1 && i < 4)
        {
            arr[i] = 0;
            tot++;
            i++;
        }
        if (i < 4)
        {
            tot++;
            arr[i] = 1;
        }
        printf("Counter:%d, Cost:%f \n", j + 1, tot);
    }
    float avgcost = tot / n;
    printf("Avg Cost:%f \n", avgcost);
}
// Accounting method
#include <stdio.h>
#include <math.h>
void main()
{
    int size[10];
    printf("\n");
    float tot[10];
    int credit[11] = {0};
    int arr[4] = {0};
    for (int j = 0; j < 10; j++)
    {
        int total = 0;
        int i = 0;
        while (arr[i] == 1 && i < 4)
        {
            arr[i] = 0;
            total++;
            i++;
        }
        if (i < 4)
        {
            total++;
            arr[i] = 1;
        }
        credit[j + 1] = 2 - total + credit[j];
        printf("Counter:%d, ", j + 1);
        printf("Cost:%d \n", credit[j]);
    }
}

// Potential Method:
#include <stdio.h>
#include <math.h>
void main()
{
    float tot = 0;
    int arr[4] = {0};
    printf("Enter value between 0 to %f\n", pow(2, 4));
    float n;
    scanf("%f", &n);
    float prev_potential = 0;
    printf("Counter:0, Cost:0\n");
    float prevones = 0;
    for (int j = 0; j < n; j++)
    {
        float currentones = 0;
        float potential = 0;
        int i = 0;
        while (arr[i] == 1 && i < 4)
        {
            arr[i] = 0;
            tot++;
            i++;
        }
        if (i < 4)
        {
            tot++;
            arr[i] = 1;
        }
        for (int k = 0; k < 4; k++)
            if (arr[k] == 1)
                currentones++;
        float current_cost = tot;
        potential = current_cost + potential - prev_potential;
        prev_potential = current_cost;
        float amort = potential + (currentones - prevones);
        prevones = currentones;
        printf("Counter:%d, Cost:%f, Current Cost:%f, amort Cost:%f\n", j + 1, current_cost, potential, amort);
    }
    float avg_cost = tot / n;
    printf("Avg Cost:%f\n", avg_cost);
}
