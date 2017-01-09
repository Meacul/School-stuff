#include <QString>
#include <QtTest>

#include "tilasto.hh"


class YksikkoTesti : public QObject
{
    Q_OBJECT

public:
    YksikkoTesti();
    Tilasto* t;

private Q_SLOTS:
    void testitapaus1();
    void testitapaus2();
    void testitapaus3();
    void latausTesti();
};

YksikkoTesti::YksikkoTesti()
{

}

void YksikkoTesti::testitapaus1()
{
    Tilasto* t1 = new Tilasto;
    for (unsigned int i = 0; i < 10000; i++){

        QCOMPARE(t1->anna_matkustajien_maara(), i);
        t1->lisaaMatkustajia(1);

    }
    QVERIFY2(true, "Failure");
}

void YksikkoTesti::testitapaus2(){
    Tilasto* t2 = new Tilasto;
    for (int i = 0; i < 10000; i++){
        int j = i * 100;
        QCOMPARE(t2->annaPisteet(), j);
        t2->uusiNysse();
        t2->nysseTuhoutui();
    }
}

void YksikkoTesti::testitapaus3(){
    Tilasto* t3 = new Tilasto;
    for (int i = 0; i < 10000; i++){
        int j = i * 100 + i;
        QCOMPARE(t3->annaPisteet(), j);
        t3->uusiNysse();
        t3->matkustajiaKuoli(1);
        t3->nysseTuhoutui();
    }
}


void YksikkoTesti::latausTesti(){
    Tilasto* t4 = new Tilasto;
    for (int i = 0; i < 15; i++){
        if(t4->annaPisteet() >= 10){
            QCOMPARE(t4->lataa(), true);
        }
        else {
            QCOMPARE(t4->lataa(), false);
        }
        t4->lisaaMatkustajia(i);
        t4->matkustajiaKuoli(i);
    }

}

QTEST_APPLESS_MAIN(YksikkoTesti)

#include "tst_yksikkotesti.moc"
