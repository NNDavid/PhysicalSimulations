#ifndef QSFML_HARMONICOSCILLATOR_H
#define QSFML_HARMONICOSCILLATOR_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTimer>
#include <SFML/Graphics.hpp>

class QSFML_Canvas : public QWidget,public sf::RenderWindow
{
    Q_OBJECT
public:
    explicit QSFML_Canvas(QWidget* parent, const QPoint& position, const QSize& size, unsigned int FrameTime = 0);
    virtual ~QSFML_Canvas();
    void pause();
    void unpause();

protected:
    virtual void onInit() = 0;

    virtual void onUpdate() = 0;

    virtual QPaintEngine* paintEngine() const;

    virtual void showEvent(QShowEvent*);

    virtual void paintEvent(QPaintEvent*);

    virtual void resizeEvent(QResizeEvent*);

    QTimer myTimer;
    bool   myInitialized;

};

#endif // QSFML_HARMONICOSCILLATOR_H
