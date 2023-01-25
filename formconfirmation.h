#ifndef FORMCONFIRMATION_H
#define FORMCONFIRMATION_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>
#include <QDebug>
#include <QString>

namespace Ui {
class Formconfirmation;
}

class Formconfirmation : public QWidget
{
    Q_OBJECT

public:
    explicit Formconfirmation(QWidget *parent = nullptr);
    ~Formconfirmation();

private:
    Ui::Formconfirmation *ui;

    QLabel* plconfirmation;
    QPushButton *ppbconfirmation;

public slots:
    void slot();
    void close();
};

#endif // FORMCONFIRMATION_H
