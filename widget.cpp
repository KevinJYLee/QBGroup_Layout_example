#include "widget.h"

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QButtonGroup>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
//  is declared as a member variable in the header
    const int Width = 4;
    isFirst = true;

    //탑레벨 Parent 위젯 소속의 라벨 하나 선언
    label = new QLabel("0",this);
    //수평 우측 & 수직 가운데 정렬 해줍시다. 포지션정렬은 이따 레이아웃에서 할것.
    label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    //???외각 프레임 설정
    label->setFrameShape(QFrame::Box);
    label->setMaximumHeight(30);


    //오늘의 버튼배치에 사용할 레이아웃들..
    VBox = new QVBoxLayout();
    Grid = new QGridLayout();


    //Why [16][2] => it's an array of strings look like {c,'\n'}
    const char ButtonChar[16][2] = {
        "7","8","9","/",
        "4","5","6","x",
        "1","2","3","-",
        "0","C","=","+",};


    //배치한번 해 봅시다..

    //소속 버튼들 만들어 봅시다.
    //이번엔 버튼그룹으로!
    buttonGroup = new (QButtonGroup)(this);

    for(int y = 0;y<Width;y++){
        for(int x=0;x<Width;x++){
            int idx = x+y*Width;

            QPushButton* nButton = new QPushButton(ButtonChar[idx],this);
            //buttons.append(,this));
            buttonGroup->addButton(nButton,idx);
            //buttons.at(idx)->setGeometry(5+60*x,50+60*y,60,60);
            Grid->addWidget(nButton,idx/Width,idx%Width);
        }
    }

    //To do : VBox 에 버튼그룹을 넣어야 할 셈으로 보입니다만...


    //한번에!
    connect(buttonGroup,SIGNAL(idClicked(int)),this,SLOT(methods(int)));

    VBox->setContentsMargins(6,6,6,6);
    VBox->addWidget(label);
    VBox->addLayout(Grid);
    setLayout(VBox);

    //안해도 동일하다 ?
    //resize(VBox->sizeHint());
}

void Widget::methods(int id){

    //connection 을 버튼그룹 가지고 했으니, sender 가 받아온 친구도 버튼그룹이겠죠?
    QButtonGroup* buttonGroup = static_cast<QButtonGroup*>(sender());

    //눌러진 버튼을 찾기 위해, 우리는 우리가 취한 버튼그룹(=sender) 으로부터 button(id) 메소드를 한번더 불러야,
    //버튼그룹에 속한 해당 id 의 버튼을 찾을 수가 있습니다.
    //connect 의 두번째 argument 로 들어간 idClicked 가 해당 버튼의 id 를 건네준 덕분에 우린 그걸 그대로 버튼을 되찾는데 쓸 수 있어요.
    //요점은 connect 함수 한번 & 되찾을때 건네받은 id 사용 한번으로, 16번의 connect 함수 연결을 스킵할 수 있었다는 것이겠죠.
    QPushButton* button = static_cast<QPushButton*>(buttonGroup->button(id));
    QString bStr;

    if(button!=nullptr) bStr  = button->text();

    //테스트 코드 : 누른 버튼 잘 취해졌는지 확인
    //이제 조건분기 하면서, setNum & setOp & doCalc 에 알맞게 동작하도록 해야 한다.
    if(label!=nullptr) label->setText(QString(bStr));

}



/*
 1. Receives the button input
 2. Takes button string : 즉 버튼 위에 써진 수=>bStr
ㄴ> button->text() 메소드로 받아온다.

 3. 
 */
void Widget::setNum(){
    //sender() returns the object that called this SLOT.
    //...which is a first argument in connect();
    //dynamic_cast : if there is no Inheritance to TYPE, return nullptr
    //else cast to TYPE
    QPushButton *button = dynamic_cast<QPushButton*>(sender());
    
    //button string!
    QString bStr;

    //if its a valid button
    if(button!=nullptr) bStr = button->text();

    //if there is a valid label
    if(label!=nullptr){
    if(label->text()=="0"||isFirst==true) label->setText(bStr);
    else label->setText(label->text()+bStr);
	isFirst = false;
    }

}

//Set op & clear label
void Widget::setOp(){

    //always take the sender first when writing a SLOT
    QPushButton *button = dynamic_cast<QPushButton*>(sender());
    

    
    if(button!=nullptr) op = button->text();

    //number that has been shown in label should be saved at this point before Calc.
    if(label!=nullptr){
    num1 = label->text();
    label->setText("0");
	isFirst = true;
    }
}

//계산은 구현 해야함..기본적으로 등호가 눌렸을 때, 계산하고 


Widget::~Widget()
{
    //delete childern
    delete label;

    //hmmm.....
    buttons.clear();
}
