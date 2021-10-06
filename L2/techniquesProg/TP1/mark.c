#include <stdio.h>

int main()
{
    int note = -1;
    char str[2] = "aa";

    while(!(note >= 0 && note <= 20))
    {
        printf("mark: ");
        scanf("%2s", str);      
        //printf("%c %c\n", str[0], str[1]);
        
        if(str[0] >= '0' && str[0] <= '9')
        {
            if(str[1] >= '0' && str[1] <= '9' && (str[0] == '1' || str[0] == '2')) 
            {
                note = ((str[0] - '0')*10) + (str[1] - '0');        
            }
            else
            {
                note = str[0] - '0';
            }
        }
        //printf("%d\n", note);
    }

    if(note >= 0 && note < 10)
    {
        printf("failing\n");
    }
    else if(note >= 10 && note < 12)
    {
        printf("satisfactory\n");
    }
    else if(note >= 12 && note < 16)
    {
        printf("good\n");
    }
    else if(note >= 16 && note <= 20)
    {
        printf("excellent\n");
    }

    return 0; 
}