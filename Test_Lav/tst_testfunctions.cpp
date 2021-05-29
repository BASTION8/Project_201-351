#include <QtTest>
#include"D:\Project_201-351-main\serverQt\functions.h"
//#include"D:\Project_201-351-main\serverQt\functions.cpp"



// add necessary includes here

class Testfunctions : public QObject
{
    Q_OBJECT

public:
    Testfunctions();
    ~Testfunctions();

private slots:
    void test_authorize();

};

Testfunctions::Testfunctions()
{

}

Testfunctions::~Testfunctions()
{

}

void Testfunctions::test_authorize()
{

    //add
       std::string str = "qwerty";
       std::string fswitch = "pass";
       QString result = authorize(str, fswitch);

       //assert
       QVERIFY2(result == "authorization error", "checkText failed");
}

QTEST_APPLESS_MAIN(Testfunctions)

#include "tst_testfunctions.moc"
