#include "phonebook.h"
#include "ui_phonebook.h"

const int numberrows=6;

PhoneBook::PhoneBook(QWidget *parent)
    :QWidget(parent),
    ui(new Ui::PhoneBook)
{

    QGroupBox *groupBoxAdd  = new QGroupBox(tr("Добавить контакт"));
    QGroupBox *groupBoxSearch  = new QGroupBox(tr("Поиск контакта"));
    QGroupBox *groupBoxSort  = new QGroupBox(tr("Отсортировать контакты"));
    QHBoxLayout* phbxLayout = new QHBoxLayout;

    phbxLayout->setContentsMargins(10, 10, 10, 10);
    phbxLayout->setSpacing(20);
    phbxLayout->addWidget(groupBoxAdd);
    phbxLayout->addWidget(groupBoxSearch);
    phbxLayout->addWidget(groupBoxSort);

    //groupBoxAdd
    QLabel* plsurname = new QLabel("Фамилия:");
    QLabel* plname = new QLabel ("Имя:");
    QLabel* plpatronymic = new QLabel ("Отчество:") ;
    QLabel* plnumber = new QLabel ("Номер телефона:");
    QLabel* pladress = new QLabel ("Адрес:");
    QLabel* pldescription = new QLabel ("Описание:");

    plename = new QLineEdit ();
    plesurname = new QLineEdit ();
    plepatronymic = new QLineEdit ();
    plenumber = new QLineEdit ();
    pleadress = new QLineEdit ();
    pledescription = new QLineEdit ();

    plesurname->setPlaceholderText("Введите фамилию");
    plename->setPlaceholderText("Введите имя");
    plepatronymic->setPlaceholderText("Введите отчество");
    plenumber->setPlaceholderText("Введите номер телефона");
    pleadress->setPlaceholderText("Введите адрес");
    pledescription->setPlaceholderText("Введите описание");

    QPushButton *ppbinput = new QPushButton ("Ввод");

    QGridLayout* pgrdLayout = new QGridLayout;
    pgrdLayout->setContentsMargins(5, 5, 5, 5);
    pgrdLayout->setSpacing(15);

    pgrdLayout->addWidget(plsurname, 0, 0);
    pgrdLayout->addWidget(plesurname, 0, 1) ;
    pgrdLayout->addWidget(plname, 1, 0);
    pgrdLayout->addWidget(plename, 1, 1);
    pgrdLayout->addWidget(plpatronymic, 2, 0);
    pgrdLayout->addWidget(plepatronymic, 2, 1);
    pgrdLayout->addWidget(plnumber, 3, 0);
    pgrdLayout->addWidget(plenumber, 3, 1) ;
    pgrdLayout->addWidget(pladress, 4, 0);
    pgrdLayout->addWidget(pleadress, 4, 1);
    pgrdLayout->addWidget(pldescription, 5, 0);
    pgrdLayout->addWidget(pledescription, 5, 1) ;
    pgrdLayout->addWidget(ppbinput, 6, 1) ;

    groupBoxAdd->setLayout(pgrdLayout);

    //groupBoxSearch
    QVBoxLayout* pvbxLayoutSearch = new QVBoxLayout;
    pvbxLayoutSearch->setContentsMargins(10, 10, 10, 10);
    pvbxLayoutSearch->setSpacing(20);

    QGridLayout* pgrdLayoutSearch = new QGridLayout;
    pgrdLayoutSearch->setContentsMargins(5, 5, 5, 5);
    pgrdLayoutSearch->setSpacing(15);

    QLabel* plsurnameSearch = new QLabel("Фамилия:");
    QLabel* plnameSearch = new QLabel ("Имя:");
    QLabel* plnumberSearch = new QLabel ("Номер телефона:");

    plenameSearch = new QLineEdit ();
    plesurnameSearch = new QLineEdit ();
    plenumberSearch = new QLineEdit ();

    plesurnameSearch->setPlaceholderText("Введите фамилию");
    plenameSearch->setPlaceholderText("Введите имя");
    plenumberSearch->setPlaceholderText("Введите номер телефона");

    QPushButton *ppbinputSearch = new QPushButton ("Поиск");
    QPushButton *ppbdelete = new QPushButton ("Удалить");

    pgrdLayoutSearch->addWidget(plsurnameSearch, 0, 0);
    pgrdLayoutSearch->addWidget(plesurnameSearch, 0, 1) ;
    pgrdLayoutSearch->addWidget(plnameSearch, 1, 0);
    pgrdLayoutSearch->addWidget(plenameSearch, 1, 1);
    pgrdLayoutSearch->addWidget(plnumberSearch, 2, 0);
    pgrdLayoutSearch->addWidget(plenumberSearch, 2, 1) ;
    pgrdLayoutSearch->addWidget(ppbdelete, 3, 0) ;
    pgrdLayoutSearch->addWidget(ppbinputSearch, 3, 1) ;

    plinfmessageSearch = new QTextEdit ();
    plinfmessageSearch->setPlaceholderText("Информационное сообщение");
    plinfmessageSearch->setReadOnly('ro');

    pvbxLayoutSearch->addLayout(pgrdLayoutSearch);
    pvbxLayoutSearch->addWidget(plinfmessageSearch);

    groupBoxSearch->setLayout(pvbxLayoutSearch);

    //groupBoxSort
    QHBoxLayout* phbxLayoutSort = new QHBoxLayout;
    phbxLayoutSort->setContentsMargins(10, 10, 10, 10);
    phbxLayoutSort->setSpacing(20);

    QVBoxLayout* pvbxLayoutSort = new QVBoxLayout;
    pvbxLayoutSort->setContentsMargins(10, 10, 10, 10);
    pvbxLayoutSort->setSpacing(20);

    prbname = new QRadioButton ("По имени");
    prbsurname = new QRadioButton ("По фамилии");

    pvbxLayoutSort->addWidget(prbname);
    pvbxLayoutSort->addWidget(prbsurname);

    plinfmessageSort = new QTextEdit ();
    plinfmessageSort->setPlaceholderText("Информационное сообщение");
    plinfmessageSort->setReadOnly('ro');

    phbxLayoutSort->addLayout(pvbxLayoutSort);
    phbxLayoutSort->addWidget(plinfmessageSort);

    groupBoxSort->setLayout(phbxLayoutSort);

    setLayout(phbxLayout);

    pvphonebook = new QVector<PhoneRecord>;

    connect(ppbinput,SIGNAL(clicked()), SLOT(add_number()));
    connect(ppbinputSearch,SIGNAL(clicked()),SLOT(search()));
    connect(ppbdelete,SIGNAL(clicked()),SLOT(deletephonerecord()));
    connect(prbname,SIGNAL(clicked()),SLOT(sortname()));
    connect(prbsurname,SIGNAL(clicked()),SLOT(sortsurname()));

    QFile styleF;
    styleF.setFileName(":/style/style.css");
    if (!styleF.open(QFile::ReadOnly)) qDebug() << "Ошибка при открытии файла чтения CSS";
    setStyleSheet(styleF.readAll());

    readFile();
}

void PhoneBook :: add_number()
{
    PhoneRecord *phonerecord = new PhoneRecord;
    phonerecord->pvphonerecord->push_back(plesurname->text());
    phonerecord->pvphonerecord->push_back(plename->text());
    phonerecord->pvphonerecord->push_back(plepatronymic->text());
    phonerecord->pvphonerecord->push_back(plenumber->text());
    phonerecord->pvphonerecord->push_back(pleadress->text());
    phonerecord->pvphonerecord->push_back(pledescription->text());

    pvphonebook->push_back(*phonerecord);

    form = new Formconfirmation;
    form->show();

    plename->clear();
    plesurname->clear();
    plepatronymic->clear();
    plenumber->clear();
    pleadress->clear();
    pledescription->clear();

    writeFile();
}

void PhoneBook :: search()
{
    plinfmessageSearch->clear();
    for(int i=0;i<pvphonebook->size();i++)
        if(searchRecord(i))
            printMessageSearch(i);

    if(plinfmessageSearch->toPlainText()=="")
        plinfmessageSearch->append("В телефонной книге нет записи с введёнными данными");

    plesurnameSearch->clear();
    plenameSearch->clear();
    plenumberSearch->clear();
}

void PhoneBook::sortname()
{
    plinfmessageSort->clear();
    std::sort(pvphonebook->begin(), pvphonebook->end(), [] (PhoneRecord lh, PhoneRecord rh)
        {return lh.pvphonerecord->at(1) < rh.pvphonerecord->at(1);});

    printMessageSort();
}

void PhoneBook::sortsurname()
{
    plinfmessageSort->clear();
    std::sort(pvphonebook->begin(), pvphonebook->end(), [] (PhoneRecord lh, PhoneRecord rh)
        {return lh.pvphonerecord->at(0) < rh.pvphonerecord->at(0);});

    printMessageSort();
}

void PhoneBook::deletephonerecord()
{
    plinfmessageSearch->clear();
    int size=pvphonebook->size();

    for(int i=0;i<pvphonebook->size();i++)
        if(searchRecord(i))
            pvphonebook->remove(i);

    if(size==pvphonebook->size())
        plinfmessageSearch->append("В телефонной книге нет записи с введёнными данными");
    else
    {
        plinfmessageSearch->append("Телефонная запись удалена");
        plinfmessageSort->clear();
    }

    plesurnameSearch->clear();
    plenameSearch->clear();
    plenumberSearch->clear();

    writeFile();

}

void PhoneBook::readFile()
{
    QFile inputfile("C:/Users/d.andronychev/study/Qt/PhoneBook/file.txt");
    if (!inputfile.open(QIODevice::ReadOnly))
        qDebug() << "Ошибка при открытии файла чтения";

    QTextStream stream(&inputfile);

    QString line = stream.readLine().toUtf8();
    while(!line.isNull())
        {
           PhoneRecord *phonerecord = new PhoneRecord;
           for(int i=0;i<numberrows && !line.isNull();i++)
           {
               phonerecord->pvphonerecord->push_back(line);
               line= stream.readLine().toUtf8();
           }
           pvphonebook->push_back(*phonerecord);

        }
    inputfile.close();
}

void PhoneBook::writeFile()
{
    QFile outputfile("C:/Users/d.andronychev/study/Qt/PhoneBook/file.txt");
    if (!outputfile.open(QIODevice::WriteOnly ))
        qDebug() << "Ошибка при открытии файла записи";

    QTextStream writeStream(&outputfile);

    for(int i=0;i<pvphonebook->size();i++)
        for(int j=0;j<pvphonebook->at(i).pvphonerecord->size();j++)
            writeStream <<pvphonebook->at(i).pvphonerecord->at(j)<<"\n";

    outputfile.close();
}

void PhoneBook::printMessageSort()
{
    for(int i=0;i<pvphonebook->size();i++)
    {
        for(int j=0;j<pvphonebook->at(i).pvphonerecord->size();j++)
            plinfmessageSort->append(pvphonebook->at(i).pvphonerecord->at(j));
        plinfmessageSort->append("");
    }
}

void PhoneBook::printMessageSearch(int i)
{
    for(int j=0;j<pvphonebook->at(i).pvphonerecord->size();j++)
        plinfmessageSearch->append(pvphonebook->at(i).pvphonerecord->at(j));
    plinfmessageSearch->append("");
}

bool PhoneBook::searchRecord(int i)
{
    bool flag=false;
    if(pvphonebook->at(i).pvphonerecord->at(0)==plesurnameSearch->text() && plesurnameSearch->text().size()!=0 && pvphonebook->at(i).pvphonerecord->at(1)==plenameSearch->text() && plenameSearch->text().size()!=0)
        flag=true;

    else if(pvphonebook->at(i).pvphonerecord->at(0)==plesurnameSearch->text() && plesurnameSearch->text().size()!=0 && plenameSearch->text().size()==0)
        flag=true;

    else if(pvphonebook->at(i).pvphonerecord->at(1)==plenameSearch->text() && plenameSearch->text().size()!=0 && plesurnameSearch->text().size()==0)
        flag=true;

    else if (pvphonebook->at(i).pvphonerecord->at(3)==plenumberSearch->text() && plenumberSearch->text().size()!=0)
        flag=true;

    return flag;
}

PhoneBook::~PhoneBook()
{
    delete ui;
}
