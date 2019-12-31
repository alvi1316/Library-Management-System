#include<stdio.h>
#include<string.h>
char globalname[20];
struct Book
{
    int id,piece;
    char name[20],author[20];
    double price;
};


//This function returns this book details if it exists
struct Book bookDetails(char name[])
{
    struct Book b;
    int flag=0;
    FILE *fp;
    fp = fopen("book.txt","r");
    while(fscanf(fp,"%d %s %s %lf %d",&b.id,b.name,b.author,&b.price,&b.piece)!=EOF)
    {
        if(strcmp(b.name,name)==0)
        {
            flag = 1;
            break;
        }
    }
    fclose(fp);
    if(flag==1)
    {
        return b;
    }
    else if(flag==0)
    {
        b.piece=0;
        return b;
    }
}


//This function writes book details
void writeBookDetails(struct Book b)
{
    FILE *fp;
    fp = fopen("book.txt","a");
    fprintf(fp,"%d %s %s %lf %d\n",b.id,b.name,b.author,b.price,b.piece);
    fclose(fp);
}


//This function issues a book from book.txt
void issueBook(char name[],char username[])
{
    int i,count=0,index=0;
    FILE *fp;

    //This part is to count number of books and index of the book
    struct Book b;
    fp = fopen("book.txt","r");
    while(fscanf(fp,"%d %s %s %lf %d",&b.id,b.name,b.author,&b.price,&b.piece)!=EOF)
    {
        count++;
        if(strcmp(name,b.name))
        {
            index=count-1;
        }
    }
    fclose(fp);

    //This part is for reading the details from the text file and decrease the piece number in the proper index
    fp = fopen("book.txt","r");
    struct Book b1[count];
    int flag=0;
    for(i=0;i<count;i++)
    {
        fscanf(fp,"%d %s %s %lf %d",&b1[i].id,b1[i].name,b1[i].author,&b1[i].price,&b1[i].piece);
        if(i==index && b1[index].piece>0)
        {
            b1[i].piece=b1[i].piece-1;
            flag=1;
        }
    }
    fclose(fp);

    //This part is for overwriting the text file
    fp = fopen("book.txt","w");
    for(i=0;i<count;i++)
    {
        fprintf(fp,"%d %s %s %lf %d\n",b1[i].id,b1[i].name,b1[i].author,b1[i].price,b1[i].piece);
    }
    fclose(fp);

    //This part is for writing issue data
    if(flag==1)
    {
        fp = fopen("issue.txt","a");
        fprintf(fp,"%s %s\n",username,b1[index].name);
        fclose(fp);
    }
}


//This function saves suggested books
void suggestBook(char username[],char name[])
{
    FILE *fp;
    fp = fopen("suggest.txt","a");
    fprintf(fp,"%s %s\n",username,name);
    fclose(fp);
}


//This function shows all the book data
void showAllBook()
{
    FILE *fp;
    fp = fopen("book.txt","r");
    struct Book b;
    while(fscanf(fp,"%d %s %s %lf %d",&b.id,b.name,b.author,&b.price,&b.piece)!=EOF)
    {
        printf("Book Id : %d Book Name : %s Book Author : %s Book Price : %lf Books Left : %d\n",b.id,b.name,b.author,b.price,b.piece);
    }
    fclose(fp);
}


//This function shows all the book suggestion
void showAllSuggestion()
{
    char username[20],name[20];
    FILE *fp;
    fp = fopen("suggest.txt","r");
    while(fscanf(fp,"%s %s",username,name)!=EOF)
    {
        printf("Username : %s, Book Name : %s\n",username,name);
    }
    fclose(fp);
}


//This function shows all the book suggestion
void showAllIssues()
{
    char username[20],name[20];
    FILE *fp;
    fp = fopen("issue.txt","r");
    while(fscanf(fp,"%s %s",username,name)!=EOF)
    {
        printf("Username : %s, Book Name : %s\n",username,name);
    }
    fclose(fp);
}


//This function saves username and password
void saveUser(char username[],char password[])
{
    FILE *fp;
    fp=fopen("users.txt","a");
    fprintf(fp,"%s %s\n",username,password);
    fclose(fp);
    printf("Registration successful\n");
}


//This function checks successful login
int readUser(char username[],char password[])
{
    int flag=0;
    char username1[20],password1[20];
    FILE *fp;
    fp=fopen("users.txt","r");
    while(fscanf(fp,"%s %s",username1,password1)!=EOF)
    {
        if(strcmp(username1,username)==0 && strcmp(password1,password)==0)
        {
            flag=1;
            break;
        }
    }
    return flag;
}


//This function checks successful login on admin
int readAdmin(char username[],char password[])
{
    int flag=0;
    char username1[20],password1[20];
    FILE *fp;
    fp=fopen("admin.txt","r");
    while(fscanf(fp,"%s %s",username1,password1)!=EOF)
    {
        if(strcmp(username1,username)==0 && strcmp(password1,password)==0)
        {
            flag=1;
            break;
        }
    }
    return flag;
}



int main()
{
    char choice; //Variable for user choice for main menu
    while(1)
    {
        printf("Welcome to Library Management System!\n\n");
        printf("Press 1 if you are a student\n");
        printf("Press 2 if you are an Admin\n");
        printf("Press 3 to exit\n");
        scanf("%ch",&choice);
        fflush(stdin);
        system("cls");
        if(choice=='1')
        {
            while(1)
            {
                printf("Welcome to student portal\n\n");
                printf("Press 1 to register student account\n");
                printf("Press 2 to login\n");
                printf("Press 3 to search books\n");
                printf("Press 4 to suggest book name\n");
                printf("Press 5 to view library rules\n");
                printf("Press 6 to return to main menu\n");
                scanf("%ch",&choice);
                fflush(stdin);
                system("cls");
                if(choice=='1')
                {
                    char username[20],password[20];
                    printf("Enter new username\n");
                    scanf("%s",&username);
                    fflush(stdin);
                    printf("Enter new password\n");
                    scanf("%s",&password);
                    fflush(stdin);
                    saveUser(username,password);
                    printf("Press enter to continue");
                    scanf("%ch",&choice);
                    fflush(stdin);
                    system("cls");

                }
                else if(choice=='2')
                {
                    char username[20],password[20];
                    printf("Enter your username\n");
                    scanf("%s",&username);
                    fflush(stdin);
                    printf("Enter your password\n");
                    scanf("%s",&password);
                    fflush(stdin);
                    int isLogin = readUser(username,password);
                    system("cls");
                    if(isLogin==1)
                    {
                        strcpy(globalname,username);
                        while(1)
                        {
                            printf("Press 1 to issue a book\n");
                            printf("Press 2 to exit\n");
                            scanf("%ch",&choice);
                            fflush(stdin);
                            system("cls");
                            if(choice=='1')
                            {
                                printf("Search the book by name : ");
                                char name[20];
                                scanf("%s",name);
                                fflush(stdin);
                                system("cls");
                                struct Book b = bookDetails(name);
                                if(b.piece==0)
                                {
                                    printf("This book does not exist\n");
                                    printf("Press enter to continue\n");
                                    scanf("%ch",&choice);
                                    fflush(stdin);
                                    system("cls");
                                }
                                else
                                {
                                    printf("The book details are....\n");
                                    printf("Book Id : %d Book Name : %s Book Author : %s Book Price : %lf Books Left : %d\n",b.id,b.name,b.author,b.price,b.piece);
                                    printf("Do you want to issue this book? y/n \n");
                                    scanf("%ch",&choice);
                                    fflush(stdin);
                                    system("cls");
                                    if(choice=='y')
                                    {
                                        issueBook(b.name,globalname);
                                        printf("Issue successful!\n");
                                        printf("Press enter to continue\n");
                                        scanf("%ch",&choice);
                                        fflush(stdin);
                                        system("cls");
                                    }
                                }
                            }
                            else if(choice=='2')
                            {
                                break;
                            }
                            else
                            {
                                printf("Wrong input press enter to continue\n");
                                scanf("%ch",&choice);
                                fflush(stdin);
                                system("cls");
                            }
                        }
                    }
                    else
                    {
                        printf("Wrong username or password\n");
                        printf("press enter to continue\n");
                        scanf("&ch",choice);
                        fflush(stdin);
                        system("cls");
                    }

                }
                else if(choice=='3')
                {
                    printf("Search the book by name : ");
                    char name[20];
                    scanf("%s",name);
                    fflush(stdin);
                    system("cls");
                    struct Book b = bookDetails(name);
                    if(b.piece==0)
                    {
                        printf("This book does not exist\n");
                        printf("Press enter to continue\n");
                        scanf("%ch",&choice);
                        fflush(stdin);
                        system("cls");
                    }
                    else
                    {
                        printf("The book details are....\n");
                        printf("Book Id : %d Book Name : %s Book Author : %s Book Price : %lf Books Left : %d\n",b.id,b.name,b.author,b.price,b.piece);
                        printf("Press enter to continue\n");
                        scanf("%ch",&choice);
                        fflush(stdin);
                        system("cls");
                    }

                }
                else if(choice=='4')
                {
                    char name[20];
                    printf("Give the name of suggested book : ");
                    scanf("%s",name);
                    fflush(stdin);
                    suggestBook(globalname,name);
                    printf("Suggestion successful!\n");
                    printf("Press enter to continue\n");
                    scanf("%ch",&choice);
                    fflush(stdin);
                    system("cls");
                }
                else if(choice=='5')
                {
                    printf("rules\n");
                    printf("Press enter to continue\n");
                    scanf("%ch",&choice);
                    fflush(stdin);
                    system("cls");
                }
                else if(choice=='6')
                {
                    break;
                }
                else
                {
                    printf("Wrong input please press enter to try again\n");
                    scanf("%ch",&choice);
                    fflush(stdin);
                    system("cls");
                }
            }

        }
        else if(choice=='2')
        {
            char username[20],password[20];
            printf("Enter your username\n");
            scanf("%s",&username);
            fflush(stdin);
            printf("Enter your password\n");
            scanf("%s",&password);
            fflush(stdin);
            int isLogin = readAdmin(username,password);
            system("cls");
            if(isLogin==1){
                while(1)
                {
                    printf("Press 1 to view all books\n");
                    printf("Press 2 to add new book\n");
                    printf("Press 3 to view issues\n");
                    printf("Press 4 to view suggestions\n");
                    printf("Press 5 to return to main menu\n");
                    scanf("%ch",&choice);
                    fflush(stdin);
                    system("cls");
                    if(choice=='1')
                    {
                        showAllBook();
                        printf("Press enter to continue\n");
                        scanf("%ch",&choice);
                        fflush(stdin);
                        system("cls");
                    }
                    else if(choice=='2')
                    {
                        struct Book b;
                        printf("Enter book ID : \n");
                        scanf("%d",&b.id);
                        printf("Enter book Name : \n");
                        scanf("%s",b.name);
                        printf("Enter book Author : \n");
                        scanf("%s",b.author);
                        printf("Enter book Price : \n");
                        scanf("%lf",&b.price);
                        printf("Enter book pieces : \n");
                        scanf("%d",&b.piece);
                        writeBookDetails(b);
                        system("cls");
                        printf("New Book Added!\n");
                        printf("Press enter to continue\n");
                        scanf("%ch",&choice);
                        fflush(stdin);
                        system("cls");
                    }
                    else if(choice=='3')
                    {
                        showAllIssues();
                        printf("Press enter to continue\n");
                        scanf("%ch",&choice);
                        fflush(stdin);
                        system("cls");
                    }
                    else if(choice=='4')
                    {
                        showAllSuggestion();
                        printf("Press enter to continue\n");
                        scanf("%ch",&choice);
                        fflush(stdin);
                        system("cls");
                    }
                    else if(choice=='5')
                    {
                        break;
                    }
                    else
                    {
                        printf("Wrong input please press enter to try again\n");
                        scanf("%ch",&choice);
                        fflush(stdin);
                        system("cls");
                    }
                }
            }
            else
            {
                printf("Wrong username or password\n");
                printf("press enter to continue\n");
                scanf("&ch",choice);
                fflush(stdin);
                system("cls");
            }
        }
        else if(choice=='3')
        {
            break;
        }
        else
        {
            printf("Wrong input please press enter to try again\n");
            scanf("%ch",&choice);
            fflush(stdin);
            system("cls");
        }
    }
    return 0;
}
