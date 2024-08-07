#include "widget.h"
#include <QApplication>
#include <QPushButton>

//계산기 클래스를 일단 맹글어 볼..까?



int main(int argc, char *argv[])
{
    //이건 무조건 있어야 한다.
    QApplication a(argc, argv);


    Widget w;



    w.show();

    return a.exec();


}

