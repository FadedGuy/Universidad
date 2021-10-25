#include <stdio.h>
#include "message.h"

int main()
{
    message msg = creer();
    printf("%s\n", msg->msg);
    msg = editer(msg, "Hi there yall");
    printf("%s\n", msg->msg);
    return 0;
}