#include <stdio.h>
#include <math.h>
#include <cs50.c>

int find_digit_num(long long number);
int find_first_two_digit(long long number,int digit_num);
void initialize_array(int digits[],long long number,int digit_num);
short check_validation(long long number,int digit_num,int digits[]);

int main(void)
{
    long long number=0;
    do
     number= get_long_long("Number: ");
    while(number <= 0);

    int digit_num = find_digit_num(number);
    int digits[digit_num];
    initialize_array(digits,number,digit_num);
    int first_two_digit= find_first_two_digit(number,digit_num);
    short flag = check_validation(number,digit_num,digits);
    if(flag==0)
        printf("INVALID\n");
    else if(flag==1 && (first_two_digit==37 || first_two_digit==34) && digit_num==15)
        printf("AMEX\n");
    else if(flag==1 && first_two_digit>39 && first_two_digit<50 && (digit_num== 13 || digit_num== 16) )
        printf("VISA\n");
    else if(flag==1 && first_two_digit>50 && first_two_digit<56 && digit_num==16)
        printf("MASTERCARD\n");
    else
        printf("INVALID\n");
    return 0;
}
int find_digit_num(long long number)
{
    int digit_num=0;
    long long i;
    for(i=number;i>0;i=i/10)
    		digit_num++;

    return digit_num;
}
int find_first_two_digit(long long number, int digit_num)
{
    int first_two_digit = (int)(number / (long long)pow(10,digit_num-2));
    return first_two_digit;
}
void initialize_array(int digits[],long long number,int digit_num)
{
    int index;
    for(index=0;index < digit_num;index++)
    {
        digits[digit_num-index-1]= number % 10;
        number = number/10;
    }
}
short check_validation(long long number,int digit_num,int digits[])
{
    int index,result,first_sum=0, second_sum=0, third_sum=0;
    if(digit_num % 2 == 0)
    {
        for(index=digit_num-2;index >= 0 ;index= index-2)
        {
            result = 2 * digits[index];
            if(result >= 10)
            {
                int i;
                for(i=result;i>0;i=i/10)
                    first_sum = first_sum + i%10;
            }
            else
                first_sum = first_sum + result;
        }
        for(index= digit_num-1;index > 0; index= index-2)
            second_sum = second_sum + digits[index];
        third_sum = first_sum + second_sum;
        if(third_sum % 10 == 0)
            return 1;
        else
            return 0;
    }
    else
    {
        for(index=digit_num-2; index > 0 ; index = index-2)
        {
             result = 2 * digits[index];
            if(result > 9)
            {
                int i;
                for(i=result;i>0;i=i/10)
                    first_sum = first_sum + i%10;
            }
            else
                first_sum = first_sum + result;
        }
        for(index= digit_num-1;index >= 0; index= index-2)
            second_sum = second_sum + digits[index];
        third_sum = first_sum + second_sum;
        if(third_sum % 10 == 0)
            return 1;
        else
            return 0;
    }
}

