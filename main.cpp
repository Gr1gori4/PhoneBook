#include "phonebook.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PhoneBook phonebook;
    phonebook.setWindowTitle("Phone Book");
    phonebook.resize(1250, 600);
    phonebook.show();
    return app.exec();
}
