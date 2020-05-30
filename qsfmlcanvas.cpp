
#include "qsfmlcanvas.h"
#include<QResizeEvent>
#ifdef Q_WS_X11
    #include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif
QSFML_Canvas::QSFML_Canvas(QWidget* parent, const QPoint& position, const QSize& size, unsigned int FrameTime) : QWidget(parent), myInitialized(false)
{

    QWidget::setWindowState(Qt::WindowFullScreen);
    QWidget::setAttribute(Qt::WA_PaintOnScreen);
    QWidget::setAttribute(Qt::WA_OpaquePaintEvent);
    QWidget::setAttribute(Qt::WA_NoSystemBackground);

    QWidget::setFocusPolicy(Qt::StrongFocus);

   // QWidget::move(position);
    QWidget::resize(size);
     myTimer.setInterval(FrameTime);
     setVerticalSyncEnabled(true);
}
QSFML_Canvas::~QSFML_Canvas(){}

QPaintEngine* QSFML_Canvas::paintEngine() const
{
    return nullptr;
}
void QSFML_Canvas::resizeEvent(QResizeEvent*)
{
    sf::RenderWindow::setSize(sf::Vector2u(QWidget::width(), QWidget::height()));
}

void QSFML_Canvas::showEvent(QShowEvent*)
{
  //  Under X11, we need to flush the commands sent to the server to ensure that
            // SFML will get an updated view of the windows
            #ifdef Q_WS_X11
                XFlush(QX11Info::display());
            #endif

            // Create the SFML window with the widget handle
            sf::RenderWindow::create((sf::WindowHandle)QWidget::winId());

            // Let the derived class do its specific stuff
            this->onInit();

            // Setup the timer to trigger a refresh at specified framerate
            connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
            myTimer.start();

            myInitialized = true;
}

void QSFML_Canvas::paintEvent(QPaintEvent*)
{
    // Let the derived class do its specific stuff
       this->onUpdate();

       // Display on screen
       sf::RenderWindow::display();
}
