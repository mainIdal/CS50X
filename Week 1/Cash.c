#include <stdio.h>
#include <cs50.h>
#include <math.h>
#define quarter 25
#define dime 10
#define nickel 5
#define penny 1
int main(void)
{
float cash;
do{
cash= get_float("Change owed: ");
}while(cash <= 0);
int money= round (cash*100);
int counter=0;
while(money != 0)
{
if(money >= quarter)
{
money= money-quarter;
counter++;
}
else if(money >= dime)
{
money= money-dime;
counter++;
}
else if(money >= nickel)
{
money= money-nickel;
counter++;
}
else
{
money = money-penny;
counter++;
}
}
printf("%d\n", counter);
return 0;
}