#include "lab32pages.h"
#include "Dictionary.h"
#include "Sequance.h"
#include <fstream>
#include "Dictionary.cpp"
#include "Sequance.cpp"
#include "DynamicArray.cpp"
#include "qinputdialog.h"
#include "qtextedit.h"
#include "qpushbutton.h"
#include <qgridlayout.h>


lab32pages::lab32pages(QWidget *parent)
    : QWidget(parent), ui(new Ui::lab32pagesClass)
{
    //ui.setupUi(this);

    Grid* grid = new Grid(this);

    grid->numOfPage = new QTextEdit();
    grid->numOfPage->setFixedSize(25, 25);
    QString* s = new QString();
    s->setNum(grid->current + 1);
    grid->numOfPage->setText(*s);

    QPushButton* next = new QPushButton();
    next->setText("next");
    next->setFixedSize(50, 20);
    QPushButton* prev = new QPushButton();
    prev->setText("prev");
    prev->setFixedSize(50, 20);
    
    grid->onGrid = grid->text[0];
    grid->addWidget(grid->onGrid,0,0,1,3);
   
    connect(prev, SIGNAL(clicked()), grid, SLOT(GoPrev()));
    connect(next, SIGNAL(clicked()), grid, SLOT(GoNext()));
    grid->addWidget(next, 1, 2);
    grid->addWidget(grid->numOfPage, 1, 1);
    grid->addWidget(prev, 1, 0);

    
    setLayout(grid);
}

String::String()
{
    std::ifstream inf("Input.txt");
   // std::ofstream outf("Output.txt");
    int cnt = 0;
    char chr = ' ';
    while (!inf.eof())
    {
        inf >> std::noskipws >> chr;
        cnt++;
    }
    n = cnt - 1;
    symbols = new char[n];

    inf.close();
    inf.open("Input.txt");
    for (int i = 0; i < n; i++)
    {
        inf >> std::noskipws >> symbols[i];
        //i++;
    }
    inf.close();
}

String::String(int n_)
{
    n = n_;
    symbols = new char[n];
}

void String::Output()
{
    std::ofstream outf("Output.txt", std::ios::app);
    for (int i = 0; i < n; i++)
    {
        outf << symbols[i];
    }
}

int String::GetLength()
{
    return n;
}

char String::Get(int i)
{
    return symbols[i];
}

void String::Set(char chr, int pos)
{
    //if (pos >= n) return;
    symbols[pos] = chr;
}

Grid::Grid(QWidget* parent)
    :QGridLayout(parent)
{
    std::ofstream outf("Output.txt");
    str = new String();
    words = new ArrayVector<String*>();
    dict = new Dictionary<String*, int>();
    onGrid = nullptr;
    size = QInputDialog::getInt(0, "Input", "Size of page:", QLineEdit::Normal); 
    SeparateWords();
    PutOnPages();
   
    int* count = new int[pages+1];
    for (int i = 0; i <= pages; i++)
    {
        count[i] = 0;
    }
    for (int i = 0; i < words->GetLength(); i++)
    {
        count[dict->Get(words->Get(i))] += words->Get(i)->GetLength();
        //outf << words->Get(i)->GetLength() << " ";
    }

    text = new QTextEdit* [pages+1];
    QString** qs = new QString* [pages+1];
    for (int i = 0; i <= pages; i++)
    {
        qs[i] = new QString[count[i]];
        text[i] = new QTextEdit[count[i]];
    }
      
    for (int i = 0; i < words->GetLength(); i++) 
    { 
        for (int j = 0; j < words->Get(i)->GetLength(); j++)
        {
            qs[dict->Get(words->Get(i))]->append(words->Get(i)->Get(j)); 
        }
        qs[dict->Get(words->Get(i))]->append(" ");
       
    }
    
    for (int i = 0; i <= pages; i++)
    {
        text[i]->setText(*qs[i]);
    }
    
}


void Grid::SeparateWords()
{
    int save = 0;
    int flag = 0;
    int space = 0;
    int i = 0;
    int j = 0;
    while (i < str->GetLength())
    {
        i = save;
        if (i == str->GetLength()) return;
        while (str->Get(i) != ' ')  
        {
            if (i >= str->GetLength() )
            {
                space = str->GetLength() ;
                flag = 1;
                break;
            }
             i++; 
             space = i ;
        }
        String* string = new String(space - save);
        for (int j = 0; j < space - save; j++)
        {
            string->Set(str->Get(save + j), j);
        }
       // string->Output();//==================================================output====================================================
        words->Append(string);
        string = nullptr;
        save = space + 1;
        space = 0;
        if (flag == 1)return;
    }
    return;
}

void Grid::PutOnPages()
{
    int cnt = 0;
    int page = 0;
    for (int i = 0; i < words->GetLength(); i++)
    {
        int sz = size;
        if (page == 0) sz = size / 2;
        else if (page % 9 == 0) sz = size * 3 / 4;
        cnt += words->Get(i)->GetLength();

        if (cnt <= sz)
        {
            dict->Add(words->Get(i), page);
            cnt++;
        } else
        if (cnt > sz)
        {
            page++;
            dict->Add(words->Get(i), page);
            cnt = words->Get(i)->GetLength() + 1;
        }
    }
    pages = page;
}

void Grid::GoNext()
{
    QWidget* widget = this->itemAtPosition(0, 0)->widget();
    widget->hide();
    this->removeWidget(widget);
    
    widget = this->itemAtPosition(1, 1)->widget();
    widget->hide();
    this->removeWidget(widget);

    current++;
    if (current > pages) current = pages;
    onGrid = text[current];

    QString* s = new QString();
    s->setNum(current + 1);
    numOfPage->setText(*s);
    delete s;

    this->addWidget(numOfPage, 1,1);
    widget = this->itemAtPosition(1, 1)->widget();
    widget->show();

    this->addWidget(onGrid,0,0,1,3);
    widget = this->itemAtPosition(0, 0)->widget();
    widget->show();
}

void Grid::GoPrev()
{
    QWidget* widget = this->itemAtPosition(0, 0)->widget();
    widget->hide();
    this->removeWidget(widget);
  
    widget = this->itemAtPosition(1, 1)->widget();
    widget->hide();
    this->removeWidget(widget);

    current--;
    if (current < 0) current = 0;
    onGrid = text[current];

    QString* s = new QString();
    s->setNum(current + 1);
    numOfPage->setText(*s);
    delete s;

    this->addWidget(numOfPage, 1, 1);
    widget = this->itemAtPosition(1, 1)->widget();
    widget->show();
    
    this->addWidget(onGrid,0,0,1,3);
    widget = this->itemAtPosition(0, 0)->widget();
    widget->show();
}


