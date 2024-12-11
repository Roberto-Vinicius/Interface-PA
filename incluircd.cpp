#include "incluircd.h"
#include "ui_incluircd.h"
#include <QMessageBox>

IncluirCD::IncluirCD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirCD)
{
    ui->setupUi(this);
}

IncluirCD::~IncluirCD()
{
    delete ui;
}

void IncluirCD::clear()
{
    ui->lineEditNome->clear();         // Limpa o campo de nome
    ui->lineEditPreco->clear();        // Limpa o campo de preço
    ui->lineEditNumFaixas->clear();   // Limpa o campo de número de faixas
}

void IncluirCD::on_buttonBox_accepted()
{
    QString nome = ui->lineEditNome->text();         // Nome do CD
    QString preco = ui->lineEditPreco->text();       // Preço do CD
    QString numFaixas = ui->lineEditNumFaixas->text();  // Número de faixas do CD

    if (nome.isEmpty() || preco.isEmpty() || numFaixas.isEmpty()) {
        QMessageBox::warning(this, tr("Campos vazios"), tr("Por favor, preencha todos os campos."));
        return;  // Não prosseguir se houver campos vazios
    }

    emit signIncluirCD(nome, preco, numFaixas);  // Emitir o sinal com os dados
    accept();  // Fecha o QDialog após a ação
}
