#ifndef MAINLOJA_H
#define MAINLOJA_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include "loja.h"
#include "incluirlivro.h"
#include "incluircd.h"
#include "incluirdvd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainLoja; }
QT_END_NAMESPACE

class MainLoja : public QMainWindow
{
    Q_OBJECT

public:
    MainLoja(QWidget *parent = nullptr);
    ~MainLoja();

private:
    Ui::MainLoja *ui;
    Loja X;                        // Variável da classe Loja com o nome definido como X
    IncluirLivro *inclLivro;
    IncluirCD *inclCD;
    IncluirDVD *inclDVD;
    QLabel *total_itens;           // QLabel para exibir o total de itens no status bar

    // Métodos auxiliares
    void configurarTabela(QTableWidget *tabela);  // Configura propriedades das tabelas
    void atualizarTabelaLivros();                 // Atualiza dados da tabela de livros
    void atualizarTabelaCDs();                    // Atualiza dados da tabela de CDs
    void atualizarTabelaDVDs();                   // Atualiza dados da tabela de DVDs
    void adicionarItemTabela(QTableWidget *tabela, int linha, int coluna, const QString &texto); // Adiciona item a uma tabela
    void atualizarTotalItens();                   // Atualiza o total de itens no status bar

private slots:
    // Slots de interação com tabelas
    void on_tabelaLivros_cellDoubleClicked(int row, int column);
    void on_tabelaCds_cellDoubleClicked(int row, int column);
    void on_tabelaDvds_cellDoubleClicked(int row, int column);

    // Slots para inclusão de itens
    void slotIncluirLivro(const QString &nome, const QString &preco, const QString &autor);
    void slotIncluirCD(const QString &nome, const QString &preco, const QString &numfaixas);
    void slotIncluirDVD(const QString &nome, const QString &preco, const QString &duracao);

    // Slots para ações do menu
    void on_actionLer_triggered();
    void on_actionSalvar_triggered();
    void on_actionSair_triggered();

    // Slots para ações de inclusão (menu)
    void on_actionIncluir_Livro_triggered();
    void on_actionIncluir_CD_triggered();
    void on_actionIncluir_DVD_triggered();

    // Métodos adicionais de exibição e status
    void exibirLivros();           // Exibe dados dos livros na tabela
    void exibirCDs();              // Exibe dados dos CDs na tabela
    void exibirDVDs();             // Exibe dados dos DVDs na tabela
    void mudarStatus();            // Altera status bar
};

#endif // MAINLOJA_H
