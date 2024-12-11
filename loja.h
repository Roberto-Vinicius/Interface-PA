#ifndef _LOJA_H_
#define _LOJA_H_

#include <iostream>
#include <string>
#include <vector>

class Produto
{
private:
  std::string nome;
  double preco;
public:
  /// Construtor default
  Produto(const std::string& N, double P): nome(N), preco(P) {}

  /// Funcoes de consulta
  const std::string& getNome() const
  {
    return nome;
  }
  double getPreco() const
  {
    return preco;
  }

  /// Metodos de entrada/saida
  void digitar();
  void imprimir() const;

  bool ler(std::istream& I);
  void salvar(std::ostream& O) const;
};

/// Operator >> e <<
std::istream& operator>>(std::istream& I, Produto& P);
std::ostream& operator<<(std::ostream& O, const Produto& P);

class Livro: public Produto
{
private:
  std::string autor;
public:
  /// Construtor
  Livro(const std::string& N="", double P=0.0, const std::string& A=""):
    Produto(N,P), autor(A) {}

  /// Funcoes de consulta
  const std::string& getAutor() const
  {
    return autor;
  }

  /// Funcoes de entrada/saida
  void digitar();
  void imprimir() const;

  bool ler(std::istream& I);
  void salvar(std::ostream& O) const;
};

std::istream& operator>>(std::istream& I, Livro& L);
std::ostream& operator<<(std::ostream& O, const Livro& L);

class CD: public Produto
{
private:
  int nfaixas;
public:
  /// Construtor
  CD(const std::string& N="", double P=0.0, int NF=0):
    Produto(N,P), nfaixas(NF) {}

  /// Funcoes de consulta
  int getNumFaixas() const
  {
    return nfaixas;
  }

  /// Funcoes de entrada/saida
  void digitar();
  void imprimir() const;

  bool ler(std::istream& I);
  void salvar(std::ostream& O) const;
};

std::istream& operator>>(std::istream& I, CD& C);
std::ostream& operator<<(std::ostream& O, const CD& C);

class DVD: public Produto
{
private:
  int duracao;
public:
  /// Construtor
  DVD(const std::string& N="", double P=0.0, int D=0):
    Produto(N,P), duracao(D) {}

  /// Funcoes de consulta
  int getDuracao() const
  {
    return duracao;
  }

  /// Funcoes de entrada/saida
  void digitar();
  void imprimir() const;

  bool ler(std::istream& I);
  void salvar(std::ostream& O) const;
};

std::istream& operator>>(std::istream& I, DVD& D);
std::ostream& operator<<(std::ostream& O, const DVD& D);

class Loja
{
private:
  std::vector<Livro> LL;
  std::vector<CD>    LC;
  std::vector<DVD>   LD;
public:
  /// Construtor
  Loja(): LL(), LC(), LD() {}

  /// Funcoes de consulta
  int getNumLivro() const
  {
    return LL.size();
  }

  int getNumCD() const
  {
    return LC.size();
  }

  int getNumDVD() const
  {
    return LD.size();
  }
  Livro getLivro(int id) const;
  CD getCD(int id) const;
  DVD getDVD(int id) const;

  /// Funcoes de manipulacao (inclusao/exclusao) de itens do estoque
  void incluirLivro(const Livro& X)
  {
    LL.push_back(X);
  }
  bool excluirLivro(int id);
  void incluirCD(const CD& X)
  {
    LC.push_back(X);
  }
  bool excluirCD(int id);
  void incluirDVD(const DVD& X)
  {
    LD.push_back(X);
  }
  bool excluirDVD(int id);

  /// Funcoes de entrada/saida
  bool ler(const std::string& arq);
  bool salvar(const std::string& arq) const;
  void imprimir() const;
};
#endif // _LOJA_H_
