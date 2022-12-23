#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct DoubleLinkedList{
    int user;
    int points;
    int win;
    int loss;
    struct DoubleLinkedList* next;
    struct DoubleLinkedList* prev;
}DLL;

DLL* adduser(DLL* headofthelist, int user)
{
    DLL* newuser = (DLL*) malloc(sizeof(DLL));

    if(NULL == newuser)
    {
        printf("Cannot allocate memory!\n");
        exit(EXIT_FAILURE);
    }

    newuser->user=user;
    newuser->points=0;
    newuser->win=0;
    newuser->loss=0;
    newuser->next=NULL;
    newuser->prev=NULL;

    if(NULL==headofthelist)
        return(newuser);

    DLL* temp = headofthelist;
    while(NULL!=temp->next)
        temp=temp->next;

    temp->next=newuser;
    newuser->prev=temp;

    return headofthelist;
}

int random_number()
{
    srand(time(0));
    int number = 1+rand()%10;
    return(number);
}

void clear()
{
    system("cls");
}

int win_key(int points)
{
    int x;
    x=21-points;
    return x;
}

void show_stats(int house_points,DLL* headofthelist)
{
    clear();
    printf("Users    |    Points    |    Win     |    Loss\n");
    printf("-----------------------------------------------\n");
    printf("House    |      %d       |            |          \n",house_points);
    while(headofthelist!=NULL)
    {
        printf("User-%d   |      %d       |     %d      |     %d  \n",headofthelist->user,headofthelist->points,headofthelist->win,headofthelist->loss);
        headofthelist=headofthelist->next;
    }

}


int main()
{
    DLL* headofthelist1 = NULL;
    int i=1;
    int house_points=0;
    int choice1;
    int selection;
    int added_points;

    printf("Welcome to blakcjack\n\n");
    headofthelist1=adduser(headofthelist1,i);
    i++;
    printf("1 player has been created, would you like to add another one? \n1-yes\n2-no\n\n");
    scanf("%d",&choice1);
    if(choice1==2)
        goto contnue;
    add_another:
    if(choice1==1)
    {
        headofthelist1 = adduser(headofthelist1,i);
        i++;
        printf("Added 1 player.\n");
    }
    printf("\nWould you like to add another player? \n1-yes\n2-no\n\n");
    scanf("%d",&choice1);

    if(choice1==1)
        goto add_another;
    contnue:
    restart:
    printf("The game is begining...");
    sleep(1);

    DLL* temporary = headofthelist1;

    //Hand over first cards
    srand(time(0));
    house_points=random_number();
    DLL* temp1 = headofthelist1;
    while(temp1!=NULL)
    {
        int m = 1+rand()%10;
        temp1->points=m;
        temp1=temp1->next;
    }
    temp1=headofthelist1;

    while(temp1!=NULL)
    {
        show_stats(house_points,headofthelist1);
        printf("\nPlaying -> user-%d\n\n",temporary->user);
        retry:
        printf("Select your next move\n\n1-Hit\n2-Stay\n\n");
        printf("Your selection -> ");
        scanf("%d",&selection);
        if(selection != 1 && selection != 2 && selection!=3)
            goto retry;
        if(selection==3)
        {
            temporary->points=temporary->points+win_key(temporary->points);
            temporary=temporary->next;
        }

        if(selection==1)
        {
            added_points=random_number();
            temporary->points=temporary->points+added_points;
            if(temporary->points>=21)
            {
               temporary=temporary->next;
            }

        }
        if(temporary==NULL || (selection==2 &&temporary->next==NULL ))
                break;

        if(selection==2 && temporary->next!=NULL)
            temporary=temporary->next;
    }
    show_stats(house_points,headofthelist1);
    printf("House hitting.\n");
    sleep(2);

    while(house_points<17)
    {
        house_points=house_points+random_number();
        show_stats(house_points,headofthelist1);
        printf("House hitting...\n\n");
        sleep(2);
    }
    printf("\n\n");
    temporary=headofthelist1;
    while(temporary!=NULL)
    {
        if(house_points==21)
        {
            if(temporary->points==21)
            {
                printf("User-%d's round is draw.\n\n",temporary->user);
            }
            else
            {
                printf("User-%d has lost.\n\n",temporary->user);
                temporary->loss++;
            }
        }
        else if(house_points>21)
        {
            if(temporary->points<=21)
            {
                printf("User-%d has won.\n\n",temporary->user);
                temporary->win++;
            }
            else
            {
                printf("User-%d's round is draw.\n\n",temporary->user);
            }
        }
        else if(house_points>temporary->points)
        {
            temporary->loss++;
            printf("User-%d has lost.\n\n",temporary->user);
        }
        else
        {
            printf("User-%d has won.\n\n",temporary->user);
            temporary->win++;
        }
        temporary=temporary->next;
    }

    sleep(2);
    show_stats(house_points,headofthelist1);

    int selection2;

    printf("\n\nEnter 1 to replay 2 to exit -> ");
    scanf("%d",&selection2);

    if(selection2==1)
        goto restart;

    return 0;
}









