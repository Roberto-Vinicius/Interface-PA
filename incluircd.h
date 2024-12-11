#ifndef INCLUIRCD_H
#define INCLUIRCD_H

#include <QDialog>
#include "ui_incluircd.h"  // Certifique-se de que está incluindo o arquivo gerado pelo Qt

namespace Ui {
class IncluirCD;
}

class IncluirCD : public QDialog
{
    Q_OBJECT

public:
    explicit IncluirCD(QWidget *parent = nullptr);
    ~IncluirCD();

    void clear();  // Método para limpar os campos de entrada

private:
    Ui::IncluirCD *ui;  // Aqui a definição completa da classe Ui::IncluirCD é necessária

signals:
    // Sinal emitido quando um CD é adicionado
    void signIncluirCD(QString nomeIn, QString precoIn, QString numfaixasIn);

private slots:
    // Slot chamado quando o botão "OK" é pressionado no QDialog (buttonBox)
    void on_buttonBox_accepted();
};

#endif // INCLUIRCD_H
