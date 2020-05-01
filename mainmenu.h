#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QGridLayout>

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void simulationCalled();
    void widgetClosed();

private:
    QVector<QPushButton*> simulations_;
    QGridLayout* gridLayout_ ;


};

#endif // MAINMENU_H
