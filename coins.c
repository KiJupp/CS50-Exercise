#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)

//getting user input
{
    float cash;
    do
    {
        cash = get_float("Change owed: ");
    }    
    while (cash < 0);
    
    //making dollars to cents for easier math
    int cents = round(cash * 100);
    
    //giving everything a name
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;
    int q = 0;
    int d = 0;
    int n = 0;
    int p = 0;
    int i = 0;
    
    //starting the loop and counting process for how many specific coins are used and how many coins in total
    while (cents >= quarter)
    {
        cents = cents - quarter;
        q++;
    }
    while (cents >= dime)
    {
        cents = cents - dime;
        d++;
    }
    while (cents >= nickel)
    {
        cents = cents - nickel;
        n++;
    }
    while (cents >= penny)
    {
        cents = cents - penny;
        p++;
    }
    //printing results
    printf("Quarter: %i\n", q);
    printf("Dime: %i\n", d);
    printf("Nickel: %i\n", n);
    printf("Pennies: %i\n", p);
    printf("Total Coins: %i\n", (q + d + n + p));
}
