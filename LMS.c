#include<stdio.h>
#include<stdlib.h>
int add_book();
int search_book();
int remove_book();
int display_books();
int update_book();

int main()
{
    int choice;
    char ch='y';
    while(ch=='Y' || ch=='y')
    {
    
    printf("******Library Management System******\n");
    printf("Select Your Option Below:\n");
    printf("1. Add Book\n2. Search Book\n3. Remove Book\n4. Display Books\n5. Update Book\n");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        add_book();
        break;
    case 2:
        search_book();
        break;
    case 3:
        remove_book();
        break;
    case 4:
        display_books();
        break;
    case 5:
        update_book();
        break;
    default:
        printf("Invalid Choice...");
        break;
    }
    printf("\nEnter (Y / y)to do more:");
    scanf(" %c", &ch);
    system("CLS");
    }
    return 0;
}

int add_book()
{
    FILE *fp;
    int id;
    char name[50],author[60],level[20];
    fp=fopen("Record.txt","a");
    if(fp==NULL)
    {
        printf("File couldn't open.");
        exit(0);
    }
    printf("Enter Details of book:\n");
    printf("Id:\n");
    scanf("%d",&id);

    printf("Book Name:\n");
    scanf(" %[^\n]",name);

    printf("Author Name:\n");
    scanf(" %[^\n]",author);

    printf("Level:\n");
    scanf(" %[^\n]",level);

    fprintf(fp,"ID:%d\n",id);
    fprintf(fp,"Book Name: %s\n",name);
    fprintf(fp,"Author Name: %s\n",author);
    fprintf(fp,"Level: %s\n",level);

    fclose(fp);
    printf("Book record added successfully.");
    return 0;
}

int search_book() {

    FILE *fp;
    int search_id, id, found = 0;
    char name[50], author[60], level[20];

    fp = fopen("Record.txt", "r");

    if(fp == NULL) {
        printf("File can't open.");
        exit(0);
    }

    printf("Enter id to search: ");
    scanf("%d", &search_id);

    while(fscanf(fp,"ID:%d\nBook Name: %[^\n]\nAuthor Name: %[^\n]\nLevel: %[^\n]\n",&id, name, author, level) !=EOF)
    {
        if(search_id == id) {
            found = 1;

            printf("\n---Book Found---\n");
            printf("ID: %d\n", id);
            printf("Book Name: %s\n", name);
            printf("Author Name: %s\n", author);
            printf("Level: %s\n", level);

            break;
        }
    }

    if(found == 0) {
        printf("Book Id Not found.\n");
    }

    fclose(fp);
    return 0;
}

int remove_book()
{
    FILE *fp,*temp;
    int s_id,id,found=0;
    char name[50],author[60],level[20];
    fp=fopen("Record.txt","r");
    if(fp==NULL)
    {
        printf("File not found.\n");
        exit(0);
    }
    temp=fopen("temp.txt","w");
    if(temp==NULL)
    {
        printf("File not found.\n");
        fclose(fp);
        exit(0);
    }
    printf("Enter id to remove:");
    scanf("%d",&s_id);
    while(fscanf(fp,"ID:%d\nBook Name: %[^\n]\nAuthor Name: %[^\n]\nLevel: %[^\n]\n",&id, name, author, level) !=EOF)
    {
        if(s_id == id)
        {
            found = 1;
        }
        else
        {
            fprintf(temp,"ID: %d\n", id);
            fprintf(temp,"Book Name: %s\n", name);
            fprintf(temp,"Author Name: %s\n", author);
            fprintf(temp,"Level: %s\n", level);
        }  
    }
    fclose(fp);
    fclose(temp);
    if(found==1)
    {
        remove("Record.txt");
        rename("temp.txt","Record.txt");
        printf("Record removed successfully.\n");
    }
    else
    {
        remove("temp.txt");
        printf("Book ID not found.\n");
    }
    return 0;
}

int display_books()
{
    FILE *fp;
    int id;
    char name[50],author[60],level[20];
    fp=fopen("Record.txt","r");
    if(fp==NULL)
    {
        printf("File not open.");
        exit(0);
    }
    while(fscanf(fp,"ID:%d\nBook Name: %[^\n]\nAuthor Name: %[^\n]\nLevel: %[^\n]\n",&id, name, author, level)!=EOF)
    {
        printf("ID: %d\n", id);
        printf("Book Name: %s\n", name);
        printf("Author Name: %s\n", author);
        printf("Level: %s\n", level);   
    }
    fclose(fp);
    return 0;
}

int update_book()
{
    FILE *fp,*temp;
    int s_id,id,found=0,choice;
    char name[50],author[60],level[20];
    fp=fopen("Record.txt","r");
    if(fp==NULL)
    {
        printf("File not open.\n");
        exit(0);
    }
    temp=fopen("temp.txt","w");
        if(temp==NULL)
        {
            printf("File not open.");
            fclose(fp);
            exit(0);
        }
    printf("Search ID to update: ");
    scanf("%d",&s_id);
    while(fscanf(fp,"ID:%d\nBook Name: %[^\n]\nAuthor Name: %[^\n]\nLevel: %[^\n]\n",&id, name, author, level)!=EOF)
    {
        if(s_id==id)
        {
            found=1;
            printf("What you want to update?\n");
            printf("1. Book Name\n2. Author Name\n3. Level\n");
            scanf("%d",&choice);
                if(choice == 1)
                {
                    printf("Enter new Book Name: ");
                    scanf(" %[^\n]", name);
                }
                else if(choice == 2)
                {
                    printf("Enter new Author Name: ");
                    scanf(" %[^\n]", author);
                }
                else if(choice == 3)
                {
                    printf("Enter new Level: ");
                    scanf(" %[^\n]", level);
                }
                else
                    printf("Invalid Choice...\n");
        }
            fprintf(temp,"ID:%d\n", id);
            fprintf(temp,"Book Name: %s\n", name);
            fprintf(temp,"Author Name: %s\n", author);
            fprintf(temp,"Level: %s\n", level);
    }
    
    fclose(fp);
    fclose(temp);
    if(found==1)
    {
    remove("Record.txt");
    rename("temp.txt","Record.txt");
    printf("Record Updated Successfully.\n");
    }
    else
    {
        printf("Book ID not found.\n");
    }
    return 0;    
}