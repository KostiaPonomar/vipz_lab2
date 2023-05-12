#include "prog.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

//--------------------------------------------------------------------------------
void ReadFromConsole(SStudent *&p, SStudent *&head, int &size) {
    bool condition = true;
    while(condition)
    {
        std::string temp;
        bool break_conditioon;
        do {
            break_conditioon = true;
            std::cout<<"Enter Surname\n";
            std::cin>> temp;
            if(temp.length()>50)
            {
                std::cout<<"Too many characters, enter up to 50. Try again\n";
            }
            else {
                strcpy(p->m_cSecondName, temp.c_str());
                temp.clear();
                break_conditioon = false;
            }
        } while (break_conditioon);//цикл для задання прізвища, поки користувач не введе прізвище коротше за 50 символів
        do {
            break_conditioon = true;
            std::cout<<"Enter Name\n";
            std::cin>> temp;
            if(temp.length()>50)
            {
                std::cout<<"Too many characters, enter up to 50. Try again\n";
            }
            else {
                strcpy(p->m_cName, temp.c_str());
                temp.clear();
                break_conditioon = false;
            }
        } while (break_conditioon);//цикл для задання імені, поки користувач не введе ім'я коротше за 50 символів
        do {
            break_conditioon = true;
            std::cout<<"Enter date of birth in format xx.xx.xxxx\n";
            std::cin>> temp;
            std::regex pattern("\\d{2}\\.\\d{2}\\.\\d{4}");
            if(std::regex_match(temp, pattern))
            {
                int day = std::stoi(temp.substr(0, 2));
                int month = std::stoi(temp.substr(3, 2));
                int year = std::stoi(temp.substr(6, 4));
                if (year <= 2023 && month >= 1 && month <= 12) {
                    bool is_leap_year = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
                    int max_days = (month == 2 ? (is_leap_year ? 29 : 28) :
                            (month == 4 || month == 6 || month == 9 || month == 11 ? 30 : 31));
                    if (day >= 1 && day <= max_days) {
                        strcpy(p->m_cdob, temp.c_str());
                        temp.clear();
                        break_conditioon = false;
                    } else {
                        std::cout << "Count day in month " << month << " can't be bigger then " << max_days << "\n";
                    }
                } else {
                    std::cout << "The year must be no more than 2023 and the month must be between 1 and 12\n";
                }
            } else {
                std::cout << "Eror: date " << p->m_cdob << " enter doesn't correctly\n";
            }
        } while (break_conditioon);//цикл для задання дати, поки користувач не введе коректний формат дати
        std::cout<<"Enter marks\n";
        for(int i = 0;i<6;i++)
        {
            bool condition_b;
            do {
                condition_b = true;
                int marks;
                std::cout<<"Mark"<<i+1<<"\n";
                std::cin>>marks;
                if(marks>0&&marks<6)
                {
                    p->mark[i] = marks;
                    p->m_davg += p->mark[i];
                    condition_b = false;
                }
                else
                    std::cout<<"Not correct mark";
            }while(condition_b);//цикл для задання оцінки, поки користувач не введе оцінку в діапазоні від 1 до 5
        }//цикл для створення масиву оцінок
        p->m_davg/=6;//знаходження середнього арифметичного
        if(!head)//якщо список пустий то перший елемент іменуймо головою
            head = p;
        SStudent* pp = new SStudent;
        p->pnext = pp;
        p = pp;//створення та задання нового елементу списку
        size++;
        std::cout<<"Add one more student?\n1.Yes\n2.No\n";
        int choice;
        std::cin>>choice;
        bool condition_switch = true;
        while (condition_switch)
        {
            switch (choice) {
                case 1:
                    condition = true;
                    condition_switch = false;
                    break;
                case 2:
                    condition = false;
                    condition_switch = false;
                    break;
                default:
                    std::cout<<"Wrong choice\n";
            }
        }//цикл для того щоб знати чи хоче користувач додати ще одного студента до списку
    }
}
//--------------------------------------------------------------------------------
void ReadFromFile(SStudent *&p, SStudent *&head, int &size) {
    std::ifstream fin;
    fin.open("/Users/kostaponomar/CLionProjects/untitled1/students");
    if(!fin.is_open())
    {
        std::cout<<"WRONG\n";
    }
    else
    {
        char temp[200];
        char* buff;
        do
        {
            fin.getline(temp,200);
            buff = strtok(temp, "|");
            strcpy(p->m_cSecondName, buff);
            buff = strtok(NULL, "|");
            strcpy(p->m_cName, buff);
            buff = strtok(NULL, "|");
            strcpy(p->m_cdob, buff);
            for(int i = 0; i < 6;i++)
            {
                p->mark[i] = atoi(strtok(NULL,"|,"));
                p->m_davg+=p->mark[i];
            }
            p->m_davg/=6;
            if(!head)
                head = p;
            SStudent* pp = new SStudent;
            p->pnext = pp;
            p = pp;
            size++;
        }while(!fin.eof());
        p->pnext = NULL;
        fin.close();
    }
}
//--------------------------------------------------------------------------------
void Display(SStudent *p, SStudent *head) {
    p=head;
    while(p->pnext != NULL)
    {
        printf("**********************************\n");
        printf("SURNAME\t\t\t||%s\n", p->m_cSecondName);
        printf("NAME\t\t\t||%s\n", p->m_cName);
        printf("DATA OF BIRTH\t||%s\n", p->m_cdob);
        printf("KDM\t\t\t\t||%d\n", p->mark[0]);
        printf("MAT\t\t\t\t||%d\n", p->mark[1]);
        printf("LAG\t\t\t\t||%d\n", p->mark[2]);
        printf("OP\t\t\t\t||%d\n", p->mark[3]);
        printf("HIS\t\t\t\t||%d\n", p->mark[4]);
        printf("ENG\t\t\t\t||%d\n", p->mark[5]);
        printf("AVG\t\t\t\t||%lf\n", p->m_davg);
        p=p->pnext;
    }
    printf("**********************************\n");

}
//--------------------------------------------------------------------------------
void RecordingToFile(SStudent *&p, SStudent *&head) {
    char file_name[50];
    std::cout<<"Enter file name:";
    std::cin>>file_name;
    std::ofstream fout;
    fout.open(file_name);
    p = head;
    if(!fout.is_open())
    {
        std::cout<<"WRONG\n";
        return;
    }
    while(p->pnext != NULL)
    {
        fout << p->m_cSecondName << "|" << p->m_cName << "|" << p->m_cdob << "|"
            <<p->mark[0]<<","<<p->mark[1]<<","<<p->mark[2]<<","<<p->mark[3]<<","<<p->mark[4]<<","<<p->mark[5]<<"|\n";
        p = p->pnext;
    }//цикл для запису даних елементів списку у файл
    fout.close();
    std::cout<<"Data recorded to file succesful\n";
}
//--------------------------------------------------------------------------------
SStudent* Swap(SStudent* ptr1, SStudent* ptr2) {//допоміжна функція для переставки елементів для сортування
    SStudent* tmp = ptr2->pnext;
    ptr2->pnext = ptr1;
    ptr1->pnext = tmp;
    return ptr2;
}
//--------------------------------------------------------------------------------
void SortList(SStudent **head, int size) {
    SStudent** h;
    int i, j, swapped;
    for (i = 0; i <= size; i++) {
        h = head; swapped = 0;
        for (j = 0; j < size - i - 1; j++) {
            SStudent* p1 = *h;
            SStudent* p2 = p1->pnext;
            if (p1->m_davg < p2->m_davg)
            {
                *h = Swap(p1, p2);
                swapped = 1;
            }
            h = &(*h)->pnext;
        }
        if (swapped == 0)
            break;
    }
}
//--------------------------------------------------------------------------------
void DisplayAllExcept5(SStudent *p, SStudent *head) {
    p=head;
    while(p->pnext != NULL)
    {
        if(p->mark[0]!=5&&p->mark[1]!=5&&p->mark[2]!=5&&p->mark[3]!=5&&p->mark[4]!=5&&p->mark[5]!=5)
        {
            printf("**********************************\n");
            printf("SURNAME\t\t\t||%s\n", p->m_cSecondName);
            printf("NAME\t\t\t||%s\n", p->m_cName);
            printf("DATA OF BIRTH\t||%s\n", p->m_cdob);
            printf("KDM\t\t\t\t||%d\n", p->mark[0]);
            printf("MAT\t\t\t\t||%d\n", p->mark[1]);
            printf("LAG\t\t\t\t||%d\n", p->mark[2]);
            printf("OP\t\t\t\t||%d\n", p->mark[3]);
            printf("HIS\t\t\t\t||%d\n", p->mark[4]);
            printf("ENG\t\t\t\t||%d\n", p->mark[5]);
            printf("AVG\t\t\t\t||%lf\n", p->m_davg);
        }
        p=p->pnext;
    }
    printf("**********************************\n");
}
//--------------------------------------------------------------------------------
SStudent* SearchAndDel(SStudent *head, int* size) {
    if (head == NULL) {
        return NULL;
    }
    if (head->mark[0] == 3&&head->mark[2]==3)
    {
        SStudent* temp = head;
        head = head->pnext;
        delete temp;
        size--;
        return head;
    }
    SStudent* current = head;
    while (current->pnext != NULL) {
        if (current->pnext->mark[0] == 3 && current->pnext->mark[2] == 3)
        {
            SStudent* temp = current->pnext;
            current->pnext = current->pnext->pnext;
            delete temp;
            size--;
            return head;
        }
        current = current->pnext;
    }
    return NULL;
}
//--------------------------------------------------------------------------------
void OldestStudent(SStudent **head) {
    SStudent*p = (*head);
    SStudent*Old;
    std::vector<std::string> dates;
    while(p->pnext != NULL)
    {
        std::string tmp = p->m_cdob;
        dates.push_back(tmp);
        p=p->pnext;
    }
    std::sort(dates.begin(), dates.end());
    p = *head;
    while(p->pnext != NULL)
    {
        std::string tmp = p->m_cdob;
        if(tmp==dates[0])
        {
            Old = p;
        }
        p=p->pnext;
    }
    std::cout<<"The Oldest student:\n";
    printf("**********************************\n");
    printf("SURNAME\t\t\t||%s\n", Old->m_cSecondName);
    printf("NAME\t\t\t||%s\n", Old->m_cName);
    printf("DATA OF BIRTH\t||%s\n", Old->m_cdob);
    printf("KDM\t\t\t\t||%d\n", Old->mark[0]);
    printf("MAT\t\t\t\t||%d\n", Old->mark[1]);
    printf("LAG\t\t\t\t||%d\n", Old->mark[2]);
    printf("OP\t\t\t\t||%d\n", Old->mark[3]);
    printf("HIS\t\t\t\t||%d\n", Old->mark[4]);
    printf("ENG\t\t\t\t||%d\n", Old->mark[5]);
    printf("AVG\t\t\t\t||%lf\n", Old->m_davg);
    printf("**********************************\n");
}
//--------------------------------------------------------------------------------
void YoungestStudent(SStudent **head) {
    SStudent*p = (*head);
    SStudent*Young;
    std::vector<std::string> dates;
    while(p->pnext != NULL)
    {
        std::string tmp = p->m_cdob;
        dates.push_back(tmp);
        p=p->pnext;
    }
    std::sort(dates.begin(), dates.end());
    p = *head;
    int i = dates.size()-1;
    while(p->pnext != NULL)
    {
        std::string tmp = p->m_cdob;
        if(tmp == dates[i])
        {
            Young = p;
        }
        p=p->pnext;
    }
    std::cout<<"The Youngest student:\n";
    printf("**********************************\n");
    printf("SURNAME\t\t\t||%s\n", Young->m_cSecondName);
    printf("NAME\t\t\t||%s\n", Young->m_cName);
    printf("DATA OF BIRTH\t||%s\n", Young->m_cdob);
    printf("KDM\t\t\t\t||%d\n", Young->mark[0]);
    printf("MAT\t\t\t\t||%d\n", Young->mark[1]);
    printf("LAG\t\t\t\t||%d\n", Young->mark[2]);
    printf("OP\t\t\t\t||%d\n", Young->mark[3]);
    printf("HIS\t\t\t\t||%d\n", Young->mark[4]);
    printf("ENG\t\t\t\t||%d\n", Young->mark[5]);
    printf("AVG\t\t\t\t||%lf\n", Young->m_davg);
    printf("**********************************\n");
}
//--------------------------------------------------------------------------------
void InsertNewStudent(
        SStudent* p,
        SStudent** head,
        int& size) {
    std::cout << "Enter position: ";
    int pos;
    std::cin >> pos;
    p = (*head);
    if(pos==1)
    {
        SStudent* new_node = new SStudent;
        std::cout<<"Enter surname: ";
        std::cin>>new_node->m_cSecondName;
        std::cout<<"Enter name: ";
        std::cin>>new_node->m_cName;
        std::cout<<"Enter date of birht: ";
        std::cin>>new_node->m_cdob;
        std::cout<<"Enter marks: \n";
        for(int i = 0; i < 6;i++)
        {
            std::cin>>new_node->mark[i];
            new_node->m_davg+=new_node->mark[i];
        }
        new_node->m_davg/=6;
        new_node->pnext = (*head);
        (*head) = new_node;
    }
    else if(pos>1&&pos<=size)
    {
        if (p == NULL) {
            std::cout<<"The given previous node cannot be NULL";
            return;
        }
        else {
            for (int i = 0; i < pos-2; i++) {
                p = p->pnext;
            }
            SStudent *new_node = new SStudent;
            std::cout<<"Enter surname: ";
            std::cin>>new_node->m_cSecondName;
            std::cout<<"Enter name: ";
            std::cin>>new_node->m_cName;
            std::cout<<"Enter date of birht: ";
            std::cin>>new_node->m_cdob;
            std::cout<<"Enter marks: \n";
            for(int i = 0; i < 6;i++)
            {
                std::cin>>new_node->mark[i];
                new_node->m_davg+=new_node->mark[i];
            }
            new_node->m_davg/=6;
            new_node->pnext = p->pnext;
            p->pnext = new_node;
        }
    }
    else if(pos>size)
    {
        SStudent* new_node = new SStudent;
        SStudent* currNode = (*head);
        std::cout<<"Enter surname: ";
        std::cin>>new_node->m_cSecondName;
        std::cout<<"Enter name: ";
        std::cin>>new_node->m_cName;
        std::cout<<"Enter date of birht: ";
        std::cin>>new_node->m_cdob;
        std::cout<<"Enter marks: \n";
        for(int i = 0; i < 6;i++)
        {
            std::cin>>new_node->mark[i];
            new_node->m_davg+=new_node->mark[i];
        }
        new_node->m_davg/=6;
        new_node->pnext = NULL;
        if (*head == NULL)
        {
            *head = new_node;
            size++;
            return;
        }
        while (currNode->pnext->pnext != NULL) {
            currNode = currNode->pnext;
        }
        currNode->pnext = new_node;
        SStudent* pp = new SStudent;
        pp->pnext=NULL;
        currNode->pnext->pnext=pp;
    }
    size++;
}
//--------------------------------------------------------------------------------
void DeleteFromPosition(SStudent **head, int& size) {
    std::cout << "Enter position: ";
    int pos;
    std::cin >> pos;
    if (*head == NULL)
        return;
    if(pos>size) {
        std::cout<<"Out the size of list\n";
        return;
    }
    SStudent* temp = *head;
    if (pos == 1) {
        *head = temp->pnext;
        delete temp;
        size--;
        return;
    }
    for (int i = 0; temp != NULL && i < pos-2; i++)
        temp = temp->pnext;
    if (temp == NULL || temp->pnext == NULL)
        return;
    SStudent* next = temp->pnext->pnext;
    delete temp->pnext;
    size--;
    temp->pnext = next;
}
