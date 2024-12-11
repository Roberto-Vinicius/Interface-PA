#include "mainloja.h"
#include "ui_incluircd.h"
#include "ui_incluirdvd.h"
#include "ui_incluirlivro.h"
#include "ui_mainloja.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

MainLoja::MainLoja(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainLoja)
    , X()
    , inclLivro(new IncluirLivro(this))
    , inclCD(new IncluirCD(this))
    , inclDVD(new IncluirDVD(this))
    , total_itens(new QLabel(this))
{
    ui->setupUi(this);

    // Centralizando
    ui->labelLivros->setAlignment(Qt::AlignCenter);
    ui->labelCds->setAlignment(Qt::AlignCenter);
    ui->labelDvds->setAlignment(Qt::AlignCenter);
    // Cor de fundo
    ui->labelLivros->setStyleSheet("background: #94b0b7;");
    ui->labelCds->setStyleSheet("background: #94b0b7;");
    ui->labelDvds->setStyleSheet("background: #94b0b7;");

    // Barra de status
    statusBar()->insertWidget(0, new QLabel(tr("Total de itens: ")));
    statusBar()->insertWidget(1, total_itens);

    // Configuração das colunas
    QStringList nomesColunasLivros = {tr("NOME"), tr("PRECO"), tr("AUTOR")};
    QStringList nomesColunasCds = {tr("NOME"), tr("PRECO"), tr("N FAIXAS")};
    QStringList nomesColunasDvds = {tr("NOME"), tr("PRECO"), tr("DURACAO")};

    ui->tabelaLivros->setHorizontalHeaderLabels(nomesColunasLivros);
    ui->tabelaCds->setHorizontalHeaderLabels(nomesColunasCds);
    ui->tabelaDvds->setHorizontalHeaderLabels(nomesColunasDvds);

    for (int i = 0; i < 3; ++i) {
        QHeaderView::ResizeMode mode = (i == 0) ? QHeaderView::Stretch : QHeaderView::ResizeToContents;
        ui->tabelaLivros->horizontalHeader()->setSectionResizeMode(i, mode);
        ui->tabelaCds->horizontalHeader()->setSectionResizeMode(i, mode);
        ui->tabelaDvds->horizontalHeader()->setSectionResizeMode(i, mode);
    }

    // Estilizando os cabeçalhos
    const QString headerStyle = "QHeaderView::section { text-align:center; background-color:#94b0b7; color: black; font-weight: bold }";
    ui->tabelaLivros->horizontalHeader()->setStyleSheet(headerStyle);
    ui->tabelaCds->horizontalHeader()->setStyleSheet(headerStyle);
    ui->tabelaDvds->horizontalHeader()->setStyleSheet(headerStyle);

    // Conectando sinais e slots
    connect(inclLivro, &IncluirLivro::signIncluirLivro, this, &MainLoja::slotIncluirLivro);
    connect(inclCD, &IncluirCD::signIncluirCD, this, &MainLoja::slotIncluirCD);
    connect(inclDVD, &IncluirDVD::signIncluirDVD, this, &MainLoja::slotIncluirDVD);
}

MainLoja::~MainLoja()
{
    delete inclLivro;
    delete inclCD;
    delete inclDVD;
    delete total_itens;
    delete ui;
}

void MainLoja::mudarStatus() {
    total_itens->setNum(X.getNumLivro() + X.getNumCD() + X.getNumDVD());
}

void MainLoja::exibirLivros() {
    ui->tabelaLivros->clearContents();
    ui->tabelaLivros->setRowCount(X.getNumLivro());

    for (int i = 0; i < X.getNumLivro(); ++i) {
        Livro L = X.getLivro(i);
        ui->tabelaLivros->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(L.getNome())));
        ui->tabelaLivros->setItem(i, 1, new QTableWidgetItem(QString::number(L.getPreco(), 'f', 2)));
        ui->tabelaLivros->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(L.getAutor())));
    }
    mudarStatus();
}

void MainLoja::exibirCDs() {
    ui->tabelaCds->clearContents();
    ui->tabelaCds->setRowCount(X.getNumCD());

    for (int i = 0; i < X.getNumCD(); ++i) {
        CD c = X.getCD(i);
        ui->tabelaCds->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(c.getNome())));
        ui->tabelaCds->setItem(i, 1, new QTableWidgetItem(QString::number(c.getPreco(), 'f', 2)));
        ui->tabelaCds->setItem(i, 2, new QTableWidgetItem(QString::number(c.getNumFaixas())));
    }
    mudarStatus();
}

void MainLoja::exibirDVDs() {
    ui->tabelaDvds->clearContents();
    ui->tabelaDvds->setRowCount(X.getNumDVD());

    for (int i = 0; i < X.getNumDVD(); ++i) {
        DVD d = X.getDVD(i);
        ui->tabelaDvds->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(d.getNome())));
        ui->tabelaDvds->setItem(i, 1, new QTableWidgetItem(QString::number(d.getPreco(), 'f', 2)));
        ui->tabelaDvds->setItem(i, 2, new QTableWidgetItem(QString::number(d.getDuracao())));
    }
    mudarStatus();
}

void MainLoja::on_tabelaLivros_cellDoubleClicked(int row, int) {
    if (X.excluirLivro(row)) {
        exibirLivros();
    }
}

void MainLoja::on_tabelaCds_cellDoubleClicked(int row, int) {
    if (X.excluirCD(row)) {
        exibirCDs();
    }
}

void MainLoja::on_tabelaDvds_cellDoubleClicked(int row, int) {
    if (X.excluirDVD(row)) {
        exibirDVDs();
    }
}

void MainLoja::slotIncluirLivro(const QString &nome, const QString &preco, const QString &autor) {
    if (nome.isEmpty() || preco.toFloat() <= 0.0 || autor.isEmpty()) {
        QMessageBox::critical(this, tr("Livro inválido"),
                              tr("Não foi possível incluir o livro: \nNome: %1\nPreço: %2\nAutor: %3")
                                  .arg(nome).arg(preco).arg(autor));
        return;
    }
    X.incluirLivro(Livro(nome.toStdString(), preco.toFloat(), autor.toStdString()));
    exibirLivros();
    QMessageBox::information(this, tr("Sucesso"), tr("Livro incluído com sucesso!"));
}

void MainLoja::slotIncluirCD(const QString &nome, const QString &preco, const QString &numfaixas) {
    if (nome.isEmpty() || preco.toFloat() <= 0.0 || numfaixas.toInt() <= 0) {
        QMessageBox::critical(this, tr("CD inválido"),
                              tr("Não foi possível incluir o CD: \nNome: %1\nPreço: %2\nNúmero de Faixas: %3")
                                  .arg(nome).arg(preco).arg(numfaixas));
        return;
    }
    X.incluirCD(CD(nome.toStdString(), preco.toFloat(), numfaixas.toInt()));
    exibirCDs();
    QMessageBox::information(this, tr("Sucesso"), tr("CD incluído com sucesso!"));
}

void MainLoja::slotIncluirDVD(const QString &nome, const QString &preco, const QString &duracao) {
    if (nome.isEmpty() || preco.toFloat() <= 0.0 || duracao.toInt() <= 0) {
        QMessageBox::critical(this, tr("DVD inválido"),
                              tr("Não foi possível incluir o DVD: \nNome: %1\nPreço: %2\nDuração: %3")
                                  .arg(nome).arg(preco).arg(duracao));
        return;
    }
    X.incluirDVD(DVD(nome.toStdString(), preco.toFloat(), duracao.toInt()));
    exibirDVDs();
    QMessageBox::information(this, tr("Sucesso"), tr("DVD incluído com sucesso!"));
}

void MainLoja::on_actionLer_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ler estoque"), QString(), tr("Estoques (*.txt)"));
    if (!fileName.isEmpty()) {
        if (!X.ler(fileName.toStdString())) {
            QMessageBox::critical(this, tr("Erro"), tr("Não foi possível ler o arquivo."));
        }
        exibirLivros();
        exibirCDs();
        exibirDVDs();
    }
}

void MainLoja::on_actionSalvar_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Salvar estoque"), QString(), tr("Estoques (*.txt)"));
    if (!fileName.isEmpty()) {
        if (!X.salvar(fileName.toStdString())) {
            QMessageBox::critical(this, tr("Erro"), tr("Não foi possível salvar o arquivo."));
        } else {
            QMessageBox::information(this, tr("Sucesso"), tr("Estoque salvo com sucesso!"));
        }
    }
}

void MainLoja::on_actionSair_triggered() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Sair"), tr("Tem certeza de que deseja sair?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QCoreApplication::quit();
    }
}

void MainLoja::on_actionIncluir_Livro_triggered() {
    if (inclLivro) {
        inclLivro->clear();
        inclLivro->show();
    }
}

void MainLoja::on_actionIncluir_CD_triggered() {
    if (inclCD) {
        inclCD->clear();
        inclCD->show();
    }
}

void MainLoja::on_actionIncluir_DVD_triggered() {
    if (inclDVD) {
        inclDVD->clear();
        inclDVD->show();
    }
}
