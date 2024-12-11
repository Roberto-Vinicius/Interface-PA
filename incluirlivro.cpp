#include "incluirlivro.h"
#include "ui_incluirlivro.h"
#include <QMessageBox>  // Não esqueça de incluir o QMessageBox

IncluirLivro::IncluirLivro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirLivro)
{
    ui->setupUi(this);
}

IncluirLivro::~IncluirLivro()
{
    delete ui;
}

void IncluirLivro::on_buttonBox_accepted()
{
    QString nome = ui->lineEditNome->text();
    QString preco = ui->lineEditPreco->text();
    QString autor = ui->lineEditAutor->text();

    if (nome.isEmpty() || preco.isEmpty() || autor.isEmpty()) {
        QMessageBox::warning(this, tr("Campos vazios"), tr("Por favor, preencha todos os campos."));
        return;
    }

    emit signIncluirLivro(nome, preco, autor);
    accept();  // Fecha o diálogo
}

void IncluirLivro::clear()
{
    ui->lineEditNome->clear();
    ui->lineEditPreco->clear();
    ui->lineEditAutor->clear();
}
