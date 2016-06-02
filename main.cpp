#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *user = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/user.utf8", "r");
    FILE *fren = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/friend.utf8", "r");
    FILE *word = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/word.utf8", "r");
    
    if(user == NULL || fren == NULL || word == NULL)
    {
        puts("File does not exits!");       // error
        exit(-1);                           // exit
    }
    
    char *str = (char*)malloc(sizeof(char) * 1000);
    int i;
    
    while(fgets(str, 1000, user) && i<1000)
        printf("%s", str);

    while(fgets(str, 1000, fren) && i<1000)
        printf("%s", str);

    while(fgets(str, 1000, word) && i<1000)
        printf("%s", str);
    
    
    return 0;
}