#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <wchar.h>

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
    listaEncadeada.inicio = NULL;
}

template<typename Tipo>
bool adicionarInicio(ListaEncadeada<Tipo> &listaEncadeada, Tipo item) {
    auto *novoItem = new Item<Tipo>;
    novoItem->dado = item;
    novoItem->proximo = listaEncadeada.inicio == NULL ? NULL : listaEncadeada.inicio;
    listaEncadeada.inicio = novoItem;
    return true;
}

template<typename TIPO>
TIPO itemNaPosicao(ListaEncadeada<TIPO> &listaEncadeada, const unsigned int posicao) {
    if (listaEncadeada != NULL) {
        auto nav = listaEncadeada.inicio;

        int i = 0;

        while (nav != NULL && i < posicao) {
            nav = nav->proximo;
            i++;
        }

        if (nav != NULL) {
            return nav->dado;
        }
    }
}

#endif
