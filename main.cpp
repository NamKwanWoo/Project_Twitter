#include "User.h"


int main(void)
{
    InitUser();
    GetTheUserNum();
    GetFriendShipNum();
    GetTweetsNum();

    printf("%d %d %d\n\n", Total_Tweets, Total_User, Total_Friendship_Records);

    PrintInterface();    // Show Interface

    //while (Process()) {}
    
    CloseFile();
    
    return 0;
}