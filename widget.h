#ifndef WIDGET_H
#define WIDGET_H

//Template 을 가져다가 객체를 생성해야 하는지라, QVector 까지는 헤더에 필수요소다.
#include <QWidget>
#include <QVector>


//하지만,포인터 형태로만 존재하는 아래 두 친구는 전방참조를 사용해 컴파일 시간 절약한다.:
class QLabel;
class QPushButton;
class QVBoxLayout;
class QGridLayout;
class QButtonGroup;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private:
    QLabel *label;

    //Differet than the basic example : buttons saved in QSTL vector class.
    QVector<QPushButton*> buttons;
    QButtonGroup* buttonGroup;

    //num2 will take place in the label.
    QString num1,op;

    bool isFirst;

    //const integer. 아마도 명시적 사이즈 지정의 의미가 큰 듯해?
    const qint32 Width = 4;

    //레이아웃 두점..
    QVBoxLayout* VBox;
    QGridLayout* Grid;


//Slots that will be connected with Signals
public slots:
    void setNum();
    void setOp();
    void methods(int);

};
#endif // WIDGET_H
