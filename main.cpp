#include <string>
#include "prog.h"
#include <iostream>

int main()
{
    //створення пустого списку
    SStudent* p = new SStudent;
    SStudent* head = NULL;
    int size = 0;//кількість елементів списку
    bool exit = true;//умова виходу з консольного меню програми
    //вміст меню програми
    std::string menu = "Choose variant:\n1.Read data from file\n2.Read data from console\n3.Record data to file\n4.Sort List\n5.Display List and youngest and oldest student\n"
                       "6.Diplay the list of students who did not receive a single grade 5 in the exams\n"
                       "7.Delete Students, who have 3 on First and Third exams\n8.Add new student in position\n9.Delete student from position\n0.Exit\n";
    //реалізація меню програми
    do
    {
        std::cout<<menu;
        int switcher_funtion;
        std::cin>>switcher_funtion;
        switch (switcher_funtion) {
            case 1:
                if(head)
                    std::cout<<"You already have a list\n";
                else
                    ReadFromFile(p,head,size);Display(p, head);
                break;
            case 2:
                if(head)
                    std::cout<<"You already have a list\n";
                else
                    ReadFromConsole(p,head,size);Display(p, head);
                break;
            case 3:
                if(!head)
                    std::cout<<"First need to read the data from the file or console\n";
                else
                    Display(p, head);RecordingToFile(p,head);
                break;
            case 4:
                if(!head)
                    std::cout<<"First need to read the data from the file or console\n";
                else
                    SortList(&head,size);Display(p, head);
                break;
            case 5:
                if(!head)
                    std::cout<<"First need to read the data from the file or console\n";
                else {
                    OldestStudent(&head);
                    YoungestStudent(&head);
                }
                break;
            case 6:
                if(!head)
                    std::cout<<"First need to read the data from the file or console\n";
                else
                    DisplayAllExcept5(p,head);
                break;
            case 7:
                if(!head)
                    std::cout<<"First need to read the data from the file or console\n";
                else {
                    for (int i = 0; i < size; i++) {
                        SearchAndDel(head, &size);
                    }
                    menu.erase(166, 55);
                    Display(p, head);
                }
                break;
            case 8:
                if(!head)
                    std::cout<<"First need to read the data from the file or console\n";
                else {
                    Display(p, head);
                    InsertNewStudent(p, &head, size);
                    Display(p, head);
                }
                break;
            case 9:
                if(!head)
                    std::cout<<"First need to read the data from the file or console\n";
                else {
                    Display(p, head);
                    DeleteFromPosition(&head, size);
                    Display(p, head);
                }
                break;
            case 0:
                exit = false;
                break;
            default:
                std::cout<<"Wrong choice\n";
        }
    }while(exit);
    delete p;
    delete head;
}
