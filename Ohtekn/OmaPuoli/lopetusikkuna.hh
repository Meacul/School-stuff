#ifndef LOPETUSIKKUNA_HH
#define LOPETUSIKKUNA_HH

#include <QDialog>
#include "tilasto.hh"

using namespace std;

/// Lopetusikkuna avataan pelin paatyttya ja siina esitetaan pelaajan pisteet

namespace Ui {
class Lopetusikkuna;
}

class Lopetusikkuna : public QDialog
{
    Q_OBJECT

public:
    explicit Lopetusikkuna(QWidget *parent = 0);
    void nayta_pisteet(double pisteet, double bussit, double tarkkuus);
    ~Lopetusikkuna();

private slots:
    void on_exitButton_clicked();

private:
    Ui::Lopetusikkuna *ui;
};

#endif // LOPETUSIKKUNA_HH
