#include <stdio.h>

int main()
{
    int note = -1;
        char un, deux;
        scanf("%c", un);        
        scanf("%c", deux);

        printf("%c %c\n", un, deux);
    while(!(note >= 0 && note <= 20))
    {
        /*
            Usar note y ch como vienen y restarles el valor despues para poder
            hacer una comparacion directa y no tener que hacer las conversiones 
            scanf dos chars, puede llegar a dar error, pero es una opcion
        */
        /*
        int ch;
        printf("mark: ");
        note = getchar() - '0';
        ch = getchar() - '0';
        if(note >= 0 && note <= 9)
        {
            Deux digits 
            if(ch >= 0 && ch <= 9) 
            {
                note = (note * 10) + ch;
            }
        }    
        printf("%d\n", note);
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
        */
    }

    return 0; 
}