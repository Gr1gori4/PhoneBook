#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <QMainWindow>
#include <QWidget>
#include <QFile>
#include <QDebug>
#include <QVector>
#include <QLineEdit>
#include <QTextEdit>
#include <QRadioButton>
#include <QGroupBox>
#include <QString>
#include <QTextStream>
#include "formconfirmation.h"

namespace Ui {
class PhoneBook;
}

class PhoneBook : public QWidget
{
    Q_OBJECT

public:
    explicit PhoneBook(QWidget *parent = nullptr);
    ~PhoneBook();

    QLineEdit* plename;
    QLineEdit* plesurname;
    QLineEdit* plepatronymic;
    QLineEdit* plenumber;
    QLineEdit* pleadress;
    QLineEdit* pledescription;
    QLineEdit* plenameSearch;
    QLineEdit* plesurnameSearch;
    QLineEdit* plenumberSearch;

    QTextEdit* plinfmessageSearch;
    QTextEdit* plinfmessageSort;

    QRadioButton *prbname;
    QRadioButton *prbsurname;

    struct PhoneRecord
        {
            QVector<QString> *pvphonerecord = new QVector<QString>;
            PhoneRecord(){ }
        };

    QVector<PhoneRecord> *pvphonebook;

    void readFile();
    void writeFile();
    void printMessageSort();
    void printMessageSearch(int);
    bool searchRecord(int);


private:
    Ui::PhoneBook *ui;

    Formconfirmation *form;

private slots:
    void add_number();
    void search();
    void sortname();
    void sortsurname();
    void deletephonerecord();
};

#endif // PHONEBOOK_H
