#include <stdio.h>
#include <math.h>
#include <string.h>


int main(void) 
{
char a[] = "100,2123,3213";
char *pEnd;


printf("%s\n",a);
int b = sizeof(a);
printf("%i\n",b);

for (int i = 0 ; i<sizeof(a)-1; i++) 
{ 
    if (a[i] == 44) {
        a[i] = 32;
    }

}

float para1 = strtof(a, &pEnd);
float para2 = strtof(pEnd, &pEnd);
float para3 = strtof(pEnd, &pEnd);

printf("%f\n",para1);
printf("%f\n",para2);
printf("%f\n",para3);

    return 0;
}
