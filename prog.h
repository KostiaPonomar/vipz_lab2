#pragma once
#include <string>

struct SStudent
{
public:
    char m_cName[50];//поле для задання імені студента
    char m_cSecondName[50];//поле для задання прізвище студента
    char m_cdob[12];//поле для задання
    int mark[6];//масив оцінок
    double m_davg;//середнє арифметичне
    SStudent* pnext;//вказівник на наступний елемент зв'язного списку
};
SStudent* SearchAndDel(SStudent *p, int* size);//видалення за умовою
void ReadFromFile(SStudent*& p, SStudent*& head, int& size);//зчитування з файлу
void ReadFromConsole(SStudent*& p, SStudent*& head, int& size);//зчитування з консолі
void RecordingToFile(SStudent*& p, SStudent*& head);//запис зв'язного списку у файл
void Display(SStudent* p, SStudent* head);//вивід зв'язного списку
void DisplayAllExcept5(SStudent* p, SStudent* head);//вивід студентів котрі не мають оцінки ні однієї оцінки 5
void SortList(SStudent** head, int size);//сортування списку студентів
void OldestStudent(SStudent**head);//вивід найстоаршого
void YoungestStudent(SStudent **head);//вивід наймолодшого
void InsertNewStudent(SStudent* prev_node, SStudent** head, int& size);//додавання нового студента у задану позицію списку
void DeleteFromPosition(SStudent** head, int& size);//видалення студента з заданної позиції списку
