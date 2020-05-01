#ifndef QSFML_MASSONSPRING_H
#define QSFML_MASSONSPRING_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QVBoxLayout>
#include <cmath>
#include "qsfmlcanvas.h"
#include <iostream>
namespace massonspring{
enum DiffEqSolver{EULER,RK4};
class OscillationData : public QWidget
{
    Q_OBJECT
public:
    OscillationData(QWidget *parent = nullptr,const int labelsize = 0):QWidget(parent)
    {
        mainLayout_ = new QVBoxLayout(this);
        labels.resize(labelsize);
        for(int i = 0;i<labels.size();i++)
        {
            labels[i] = new QLabel(this);
            mainLayout_->addWidget(labels[i]);
        }
        setLayout(mainLayout_);
    }
    ~OscillationData(){}
    void setLabelText(const int label_num,const QString& str){labels[label_num]->setText(str);}
private:
    QVector<QLabel*> labels;
    QVBoxLayout* mainLayout_;
};
class Solver{
public:
    Solver(sf::RenderWindow* window,const float mass = 500,const float elastic_constant = 500,const int label_num = 3):
    window_(window),
    mass_(mass),
    elastic_constant_(elastic_constant),
    data_(new OscillationData(nullptr,label_num))
    {
        body_.setRadius(50);
        body_.setOrigin(body_.getRadius(),body_.getRadius());
        body_.setFillColor(sf::Color(128,0,0));
        body_.setPosition(window_->getSize().x/2.0,window_->getSize().y/2.0);
        l_= window_->getSize().x / 2.0;
        data_->show();
    }
    virtual ~Solver()
    {
        data_->close();
        if(data_ != nullptr) delete data_;
    }
    virtual void draw() = 0;
    void setSystemValue(const float mass, const float elastic_constant){mass_ = mass; elastic_constant_ = elastic_constant;}
    virtual void restartSimulation(const sf::Event& event) = 0;
    virtual DiffEqSolver getSolverType() const = 0;

    protected:
    sf::RenderWindow* window_;
    float mass_;
    float elastic_constant_;
    float l_;
    sf::CircleShape body_;
    sf::Time told_;
    sf::Clock clock_;
    OscillationData* data_;
    const float g = 9.81f;
    float ThetaAcc(const float x,const float vel,const float theta,const float theta_vel)
    {
        return (-g * sin(theta) - 2.0f * vel * theta_vel) / (l_ + x);
    }


    float XAcc(const float x,const float theta,const float theta_vel)
    {
        return (l_ + x) * theta_vel * theta_vel + g * cos(theta) - (elastic_constant_/mass_) * x;
    }

};

class EulerSolver:public Solver
{
public:
    EulerSolver(sf::RenderWindow* window,const float mass = 5000,const float elastic_constant = 50,const int label_num = 3):Solver(window,mass,elastic_constant,label_num){}
    ~EulerSolver(){}
    void restartSimulation(const sf::Event &event) override
    {
        l_= window_->getSize().y / 2.0;
        thetaold_ = atan2(event.mouseButton.x - window_->getSize().x / 2.0,event.mouseButton.y);
        thetavelold_ = 0.0;
        xold_ = sqrt(event.mouseButton.y * event.mouseButton.y + (event.mouseButton.x - window_->getSize().x / 2.0) * (event.mouseButton.x - window_->getSize().x / 2.0)) - l_;
        vold_ = 0.0;
        aold_ = XAcc(xold_,thetaold_,thetavelold_);
        std::cout<< thetaold_ <<std::endl;
        thetaaccold_ = ThetaAcc(xold_,vold_,thetaold_,thetavelold_);
        told_ = sf::seconds(0.0);
        clock_.restart();
    }

    void draw() override
    {
        sf::Time time_now = clock_.getElapsedTime();
        float dt = (time_now - told_).asSeconds();
        int times = int(dt / h);
        for(int i= 0; i< times ;i++)
        {
            a_ = aold_ + h * XAcc(xold_,thetaold_,thetavelold_);
            v_ = vold_ + h * aold_;
            x_ = xold_ + h* vold_;

            thetaacc_ = thetaaccold_ + h * ThetaAcc(xold_,vold_,thetaold_,thetavelold_);
            thetavel_ = thetavelold_ + h * thetaaccold_;
            theta_ = thetaold_ + h * thetavelold_;


            aold_ = a_;
            vold_ = v_;
            xold_ = x_;

            thetaaccold_ = thetaacc_;
            thetavelold_ = thetavel_;
            thetaold_ = theta_;
        }
        //vold_ = v_;
        //xold_ = x_;
        //thetavelold_ = thetavel_;
        //thetaold_ = theta_;
        std::cout<< " x= " << theta_ <<std::endl;
        body_.setPosition(window_->getSize().x / 2.0 + (l_ + x_) * sin(theta_),(l_ + x_)  * cos(theta_));
        window_->draw(body_);
        told_ = time_now;
      std::cout << "EULER" << std::endl;
    }

    DiffEqSolver getSolverType() const override {return EULER;};

private:
    float xold_;
    float x_;
    float vold_;
    float v_;
    float aold_;
    float a_;
    float thetaold_;
    float theta_;
    float thetavelold_;
    float thetavel_;
    float thetaaccold_;
    float thetaacc_;
    const float h = 0.00001;
};

class RK4_Solver:public Solver
{
public:
    RK4_Solver(sf::RenderWindow* window,const float mass = 5000,const float elastic_constant = 50,const int label_num = 3):Solver(window,mass,elastic_constant,label_num){}
    ~RK4_Solver(){}
    void restartSimulation(const sf::Event &event) override
    {
        l_= window_->getSize().y / 2.0;
        thetaold_ = atan2(event.mouseButton.x - window_->getSize().x / 2.0,event.mouseButton.y);
        thetavelold_ = 0.0;
        xold_ = sqrt(event.mouseButton.y * event.mouseButton.y + (event.mouseButton.x - window_->getSize().x / 2.0) * (event.mouseButton.x - window_->getSize().x / 2.0)) - l_;
        vold_ = 0.0;
        aold_ = XAcc(xold_,thetaold_,thetavelold_);
        std::cout<< thetaold_ <<std::endl;
        thetaaccold_ = ThetaAcc(xold_,vold_,thetaold_,thetavelold_);
                told_ = sf::seconds(0.0);
        clock_.restart();
    }

    void draw() override
    {
        sf::Time time_now = clock_.getElapsedTime();
        float dt = (time_now - told_).asSeconds();
        int times = int(dt / h);
        for(int i= 0; i< times ;i++)
        {
            float k1_x = XAcc(xold_,thetaold_,thetavelold_);
            float k1_theta = ThetaAcc(xold_,vold_,thetaold_,thetavelold_);

            thetavel_ = thetavelold_ + h * thetaaccold_ / 2.0;
            theta_ = thetaold_ + h * thetavelold_ / 2.0;
            x_ = xold_ +  h * vold_ / 2.0;
            v_ = vold_ + h * aold_ / 2.0;

            std::cout<< " x = " << x_ <<std::endl;

            float k2_x = XAcc(x_,theta_,thetavel_);
            float k2_theta = ThetaAcc(x_,v_,theta_,thetavelold_+ h * k1_theta / 2.0);


            float k3_x = k2_x;
            float k3_theta = ThetaAcc(x_,v_,theta_,thetavelold_+  h * k2_theta / 2.0);

            thetavel_ = thetavelold_ + h * thetaaccold_;
            theta_ = thetaold_ + h * thetavelold_;
            x_ = xold_ + h * vold_;
            v_ = vold_ + h * aold_;

            float k4_theta = ThetaAcc(x_,v_,theta_,thetavelold_ +  h * k3_theta);


            float k4_x = XAcc(x_,theta_,thetavel_);

            aold_ += (h * (k1_x + 2.0 * k2_x + 2.0 * k3_x + k4_x)/6.0f);
            thetaaccold_ += (h * (k1_theta + 2.0 * k2_theta + 2.0 * k3_theta + k4_theta)/6.0f);

            vold_ = v_;
            xold_ = x_;
            thetavelold_ = thetavel_;
            thetaold_ = theta_;


        }
        //vold_ = v_;
        //xold_ = x_;
        //thetavelold_ = thetavel_;
        //thetaold_ = theta_;
        std::cout<< " x= " << theta_ <<std::endl;
        body_.setPosition(window_->getSize().x / 2.0 + (l_) * sin(theta_),/*(l_ + x_)  * cos(theta_)*/window_->getSize().y/2.0 );
        window_->draw(body_);
        told_ = time_now;
      // std::cout<<"new = " <<body_.getPosition().x << " " << body_.getPosition().y << " " << aold_ << std::endl;
    }

    DiffEqSolver getSolverType() const override {return RK4;};

private:
    float xold_;
    float x_;
    float vold_;
    float v_;
    float aold_;
    float thetaold_;
    float theta_;
    float thetavelold_;
    float thetavel_;
    float thetaaccold_;
    const float h = 0.00001;
};


class QSFML_MassOnSpring:public QSFML_Canvas
{
    Q_OBJECT
public:
    QSFML_MassOnSpring(QWidget* parent, const QPoint& position, const QSize& size);
    void setSystemValues(const float mass, const float elastic_constant){solver_->setSystemValue(mass,elastic_constant);}
    void setDiffEqSolver(const DiffEqSolver diff){diff_ = diff;}

 signals:
    void simulationRestarted();

 private:
     void onInit() override;
     void onUpdate() override;
     Solver* solver_;
     DiffEqSolver diff_;
};
}
#endif // QSFML_MASSONSPRING_H
