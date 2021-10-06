#include <stdio.h>

int main()
{
    int note;

    do
    {
        printf("mark: ");
        scanf("%d", &note);
        while(getchar() != '\n');
    }while(!(note >= 0 && note <= 20));

    if(note >= 0 && note < 10)
    {
        printf("failing\n");
    }
    if(note >= 10 && note < 12)
    {
        printf("satisfactory\n");
    }
    if(note >= 12 && note < 16)
    {
        printf("good\n");
    }
    if(note >= 16 && note <= 20)
    {
        printf("excellent\n");
    }

    return 0;
}