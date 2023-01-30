#include "formconfirmation.h"
#include "ui_formconfirmation.h"


Formconfirmation::Formconfirmation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formconfirmation)
{
    setWindowTitle("Подверждение операции");
    resize(330, 100);

    QLabel* plconfirmation = new QLabel ("Новый контакт добавлен");
    QPushButton *ppbconfirmation = new QPushButton ("Ок");

    QVBoxLayout* pvbxLayoutSearch = new QVBoxLayout;
    pvbxLayoutSearch->setContentsMargins(10, 10, 10, 10);
    pvbxLayoutSearch->setSpacing(20);

    pvbxLayoutSearch->addWidget(plconfirmation);
    pvbxLayoutSearch->addWidget(ppbconfirmation);

    setLayout(pvbxLayoutSearch);

    connect(ppbconfirmation,SIGNAL(clicked()), SLOT(close()));

    QFile styleF;
    styleF.setFileName(":/style/style.css");
    if (!styleF.open(QFile::ReadOnly)) qDebug() << "Ошибка при открытии файла";

    setStyleSheet(styleF.readAll());
}

Formconfirmation::~Formconfirmation()
{
    delete ui;
}

void Formconfirmation::close()
{
    QWidget::close();
}
