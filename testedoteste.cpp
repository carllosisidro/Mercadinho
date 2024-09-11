#include <locale.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

// Estrutura para representar um produto
struct Produto {
    string nome;
    int quantidade;
    float valorVenda;
};

// Função para carregar produtos do arquivo
vector<Produto> carregarProdutos(const string& nomeArquivo) {
    vector<Produto> produtos;
    ifstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        string nome, quantidadeStr, valorVendaStr;
        while (getline(arquivo, nome, ';')) {
            getline(arquivo, quantidadeStr, ';');
            getline(arquivo, valorVendaStr, '\n');

            Produto produto;
            produto.nome = nome;
            produto.quantidade = stoi(quantidadeStr);
            produto.valorVenda = stof(valorVendaStr);

            produtos.push_back(produto);
        }
        arquivo.close();
    }

    return produtos;
}

// Função para salvar produtos no arquivo
void salvarProdutos(const string& nomeArquivo, const vector<Produto>& produtos) {
    ofstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        for (const Produto& produto : produtos) {
            arquivo << produto.nome << ";" << produto.quantidade << ";" << produto.valorVenda << endl;
        }
        arquivo.close();
    }
}

// Função para cadastrar um produto
void cadastrarProduto(vector<Produto>& produtos) {
    string nome;
    int quantidade;
    float valorVenda;

    cout << "Nome do produto: ";
    cin.ignore(); // Limpa o buffer de entrada
    getline(cin, nome);

    cout << "Quantidade: ";
    cin >> quantidade;

    cout << "Valor de venda: ";
    cin >> valorVenda;

    // Verifica se o produto já existe
    bool produtoExistente = false;
    for (Produto& produto : produtos) {
        if (produto.nome == nome) {
            produto.quantidade += quantidade;
            produto.valorVenda = valorVenda;
            produtoExistente = true;
            cout << "Produto atualizado com sucesso!" << endl;
            break;
        }
    }

    // Se o produto não existe, adiciona-o à lista
    if (!produtoExistente) {
        Produto novoProduto;
        novoProduto.nome = nome;
        novoProduto.quantidade = quantidade;
        novoProduto.valorVenda = valorVenda;
        produtos.push_back(novoProduto);
        cout << "Produto cadastrado com sucesso!" << endl;
    }
}

// Função para adicionar produtos à cesta
void adicionarCesta(const vector<Produto>& produtos) {
    string nome;
    float quantidade;
    vector<pair<string, float>> cesta;

    while (true) {
        cout << "Nome do produto (ou digite 'A' para finalizar): ";
        cin.ignore();
        getline(cin, nome);

        if (nome =="A") {
            break;
        }

        bool produtoEncontrado = false;
        for (const Produto& produto : produtos) {
            if (produto.nome == nome) {
                cout << "Quantidade: ";
                cin >> quantidade;
                cesta.push_back(make_pair(nome, quantidade));
                produtoEncontrado = true;
                break;
            }
        }

        if (!produtoEncontrado) {
            cout << "Produto não encontrado!" << endl;
        }
    }

    // Calcula o valor total da cesta
    float valorTotal = 0.0;
    for (const auto& item : cesta) {
        for (const Produto& produto : produtos) {
            if (produto.nome == item.first) {
                valorTotal += produto.valorVenda * item.second;
                break;
            }
        }
    }

    cout << "\nValor total da cesta: R$ " << fixed << setprecision(2) << valorTotal << endl;
    
    // Processa o pagamento
    int opcaoPagamento;
    cout << "Opções de pagamento:\n";
    cout << "1) À vista (5% de desconto)\n";
    cout << "2) Em até 3 vezes sem juros\n";
    cout << "3) Em até 12 vezes com 10% de juros\n";
    cout << "Digite a opção desejada: ";
    cin >> opcaoPagamento;

    // Calcula o valor final e exibe as informações de pagamento
    switch (opcaoPagamento) {
        case 1: {
            valorTotal *= 0.95;
            cout << "\nValor total com desconto: R$ " << fixed << setprecision(2) << valorTotal << endl;
            cout << "Pagamento à vista realizado com sucesso!" << endl;
            break;
        }
        case 2: {
            cout << "\nValor total: R$ " << fixed << setprecision(2) << valorTotal << endl;
            cout << "Pagamento em 3 parcelas de R$ " << fixed << setprecision(2) << (valorTotal / 3) << endl;
            break;
        }
        case 3: {
            valorTotal *= 1.10;
            cout << "\nValor total com juros: R$ " << fixed << setprecision(2) << valorTotal << endl;
            cout << "Pagamento em 12 parcelas de R$ " << fixed << setprecision(2) << (valorTotal / 12) << endl;
            break;
        }
        default:
            cout << "Opção inválida!" << endl;
    }

    // Exibe as datas de cada pagamento (opcional)
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int ano = 1900 + ltm->tm_year;
    int mes = 1 + ltm->tm_mon;
    int dia = ltm->tm_mday;

    if (opcaoPagamento == 2) {
        cout << "\nDatas dos pagamentos:\n";
        cout << "1ª parcela: " << dia << "/" << mes << "/" << ano << endl;
        cout << "2ª parcela: " << dia << "/" << (mes + 1) % 12 << "/" << (mes + 1 == 13 ? ano + 1 : ano) << endl;
        cout << "3ª parcela: " << dia << "/" << (mes + 2) % 12 << "/" << (mes + 2 == 13 ? ano + 1 : ano) << endl;
    } else if (opcaoPagamento == 3) {
        cout << "\nDatas dos pagamentos:\n";
        for (int i = 0; i < 12; i++) {
            cout << (i + 1) << "ª parcela: " << dia << "/" << (mes + i) % 12 << "/" << (mes + i == 13 ? ano + 1 : ano) << endl;
        }
    }
}

// Função para exibir o menu principal
int menu() {
    int opcao;

    cout << "----------MENU-----------" << endl;
    cout << "1) Cadastrar produtos" << endl;
    cout << "2) Adicionar à cesta" << endl;
    cout << "3) Sair" << endl;

    cout << "Digite a opção desejada: ";
    cin >> opcao;
    return opcao;
}

int main() {
    

    string nomeArquivo = "produtos.txt";
    vector<Produto> produtos = carregarProdutos(nomeArquivo);

    while (true) {
        int opcao = menu();

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos);
                salvarProdutos(nomeArquivo, produtos);
                break;
            case 2:
                adicionarCesta(produtos);
                break;
            case 3:
                cout << "Saindo do programa..." << endl;
                return 0;
            default:
                cout << "Opção inválida!" << endl;
        }
    }
}