#include <stdio.h>
#include <cs50.h>
int main(void)
{
string name;
name = get_string("Please, type your name here: ");
printf("hello, %s\n", name);
return 0;
}