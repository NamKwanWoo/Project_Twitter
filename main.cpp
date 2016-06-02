#include <stdio.h>
#include <stdlib.h>

void Interface();

int main(void)
{
    FILE *user = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/user.utf8", "r");
    FILE *fren = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/friend.utf8", "r");
    FILE *word = fopen("/Users/namnamnam/Desktop/KOREAUNIV_DS_03/word.utf8", "r");
    
    int sKey;   // select number
    if(user == NULL || fren == NULL || word == NULL)
    {
        puts("File does not exits!");       // error
        exit(-1);                           // exit
    }
    
    Interface();    // Show Interface
    
    
    
    return 0;
}

void Interface()
{
    puts("0. Read data files");
    puts("1. display statistics");
    puts("2. Top 5 most tweeted words");
    puts("3. Top 5 most tweeted users");
    puts("4. Find users who tweeted a word (e.g., ’연세대’)");
    puts("5. Find all people who are friends of the above users");
    puts("6. Delete users who mentioned a word");
    puts("7. Delete all users who mentioned a word");
    puts("8. Find strongly connected components");
    puts("9. Find shortest path from a given user");
    puts("99. Quit");
    printf("Select Menu:");
}