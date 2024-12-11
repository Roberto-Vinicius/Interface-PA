#include "incluirdvd.h"
#include "ui_incluirdvd.h"
#include <QMessageBox>  // Para usar o QMessageBox

IncluirDVD::IncluirDVD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirDVD)
{
    ui->setupUi(this);
}

IncluirDVD::~IncluirDVD()
{
    delete ui;
}

void IncluirDVD::on_buttonBox_accepted()
{
    QString nome = ui->lineEditNome->text();
    QString preco = ui->lineEditPreco->text();
    QString duracao = ui->lineEditDuracao->text();

    if (nome.isEmpty() || preco.isEmpty() || duracao.isEmpty()) {
        QMessageBox::warning(this, tr("Campos vazios"), tr("Por favor, preencha todos os campos."));
        return;
    }

    emit signIncluirDVD(nome, preco, duracao);

    accept();
}

void IncluirDVD::clear() {
    ui->lineEditNome->clear();  // Limpa o campo de nome
    ui->lineEditPreco->clear();  // Limpa o campo de preço
    ui->lineEditDuracao->clear();  // Limpa o campo de duração
}
