// incluirdvd.h
#ifndef INCLUINDVD_H
#define INCLUINDVD_H

#include <QDialog>

namespace Ui {
class IncluirDVD;
}

class IncluirDVD : public QDialog
{
    Q_OBJECT

public:
    explicit IncluirDVD(QWidget *parent = nullptr);
    ~IncluirDVD();

    void clear();  // Adicione a declaração do método clear()

private:
    Ui::IncluirDVD *ui;

signals:
    void signIncluirDVD(QString nomeIn, QString precoIn, QString duracaoIn);

private slots:
    void on_buttonBox_accepted();
};

#endif // INCLUINDVD_H
