#include <QtTest>

// add necessary includes here
#include "D:\QtProject\Project_201-351\serverQt\functions.h"


class Testfunctions : public QObject
{
    Q_OBJECT

public:
    Testfunctions();
    ~Testfunctions();

private slots:
    void test_start();

};

Testfunctions::Testfunctions()
{

}

Testfunctions::~Testfunctions()
{

}

void Testfunctions::test_start()
{

    //add
       int arr[200];
       std::string str = "";
       start(arr);
       for(int i=0; i<200; i++) {
           if (arr[i] != 0) {
               str = "failed";
               break;
           }
           else
               str = "true";

       }
       //assert
       QVERIFY2(str == "true", "checkText true");
}

QTEST_APPLESS_MAIN(Testfunctions)

#include "tst_testfunctions.moc"
