#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

template<typename Tipo>
struct Item {
    Tipo dado;
    Item<Tipo> *proximo;
};

template<typename Tipo>
struct ListaEncadeada {
    Item<Tipo> *inicio;
};

template<typename Tipo>
void inicializarLista(ListaEncadeada<Tipo> &listaEncadeada) {
    listaEncadeada.inicio = nullptr;
}

template<typename Tipo>
bool adicionarInicio(ListaEncadeada<Tipo> &listaEncadeada, Tipo item) {
    Item<TIPO> *novoItem = new Item<Tipo>;
    novoItem->dado = item;
    novoItem->proximo = listaEncadeada.inicio ? listaEncadeada.inicio->proximo : NULL;
    listaEncadeada.inicio = novoItem;
    return true;
}

#endif
