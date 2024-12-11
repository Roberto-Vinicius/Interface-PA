#ifndef INCLUIRLIVRO_H
#define INCLUIRLIVRO_H

#include <QDialog>
#include "ui_incluirlivro.h"

namespace Ui {
class IncluirLivro;
}

class IncluirLivro : public QDialog
{
    Q_OBJECT

public:
    explicit IncluirLivro(QWidget *parent = nullptr);
    ~IncluirLivro();

    void clear();  // Função de limpeza dos campos

private:
    Ui::IncluirLivro *ui;

signals:
    void signIncluirLivro(QString nomeIn, QString precoIn, QString autorIn);

private slots:
    void on_buttonBox_accepted();  // Declaração do método

};

#endif // INCLUIRLIVRO_H
