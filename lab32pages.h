#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab32pages.h"
#include <qgridlayout.h>
#include <qpushbutton.h>
#include "Sequance.h"
#include "Dictionary.h"
#include <fstream>
#include "qtextedit.h"

class lab32pages : public QWidget
{
    Q_OBJECT

public:
    lab32pages(QWidget *parent = Q_NULLPTR);

private:
    Ui::lab32pagesClass* ui;
};


class String
{
private:
    char* symbols;
    int n;
public:
    String(); // from file
    String(int n);
    void Output(); // in file
    int GetLength();
    char Get(int i);
    void Set(char chr, int pos);
};

class Grid : public QGridLayout
{
    Q_OBJECT
public:
    Grid(QWidget* parent);
    void SeparateWords();
    void PutOnPages();
    QTextEdit** text;
    QTextEdit* onGrid; 
    QTextEdit* numOfPage;
    int current = 0;
public slots:
    void GoPrev();
    void GoNext();
private:
    
    
    String* str;
    int size;
    int pages;
    ArrayVector<String*>* words;
    Dictionary<String*, int>* dict;
    
};