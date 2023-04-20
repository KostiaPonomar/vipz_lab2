#pragma once
#include <string>

class CStudent
{
public:
    char m_cName[50];
    char m_cSecondName[50];
    char m_cdob[12];
    int mark[6];
    double m_davg;
    CStudent* pnext;
};
CStudent* SearchAndDel(CStudent *p, int* size);
void ReadFromFile(CStudent*& p, CStudent*& head, int& size);
void ReadFromConsole(CStudent*& p, CStudent*& head, int& size);
void RecordingToFile(CStudent*& p, CStudent*& head);
void Display(CStudent* p, CStudent* head);
void DisplayAllExcept5(CStudent* p, CStudent* head);
void SortList(CStudent** head, int size);
void OldestStudent(CStudent**head);
void YoungestStudent(CStudent **head);
void InsertNewStudent(CStudent* prev_node, CStudent** head, int& size);
void DeleteFromPosition(CStudent** head, int& size);
