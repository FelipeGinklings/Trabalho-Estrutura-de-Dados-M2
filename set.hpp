#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED

template<typename Tipo>
struct Item {
    Tipo dado;
    Item<Tipo> *proximo, *anterior;
};

template<typename Tipo>
struct SetEncadeado {
    Item<Tipo> *inicio;
    Item<Tipo> *fim;
};

template<typename Tipo>
void inicializarSet(SetEncadeado<Tipo> &setEncadeadado) {
    setEncadeadado.inicio = NULL;
    setEncadeadado.fim = NULL;
}

template<typename Tipo>
bool adicionarNoSet(SetEncadeado<Tipo> &setEncadeado, Tipo item) {
    auto *novoItem = new Item<Tipo>;
    novoItem->dado = item;

    if (setEncadeado.fim == NULL || setEncadeado.inicio == NULL) {
        novoItem->anterior = novoItem;
        novoItem->proximo = novoItem;
        setEncadeado.inicio = novoItem;
        setEncadeado.fim = novoItem;
        return true;
    }

    novoItem->proximo = setEncadeado.inicio;  // Aponta para o antigo inicio
    novoItem->anterior = setEncadeado.fim;  // O anterior aponta para o fim
    setEncadeado.inicio->anterior = novoItem;  // O início aponta para o novo ‘item’
    setEncadeado.fim->proximo = novoItem;  // O próximo do fim aponta para o início
    setEncadeado.inicio = novoItem;  // Atualiza o inicio
    return true;
}

template<typename Tipo>
bool atualizarSet(SetEncadeado<Tipo> &setEncadeado) {
    if (setEncadeado.inicio == NULL || setEncadeado.fim == NULL ||
        setEncadeado.fim->proximo != setEncadeado.inicio ||
        setEncadeado.inicio->anterior != setEncadeado.fim) {
        return false;
    }

    const Tipo dadoAntigoInicio = setEncadeado.inicio->dado;
    const Tipo dadoInicioProximo = setEncadeado.inicio->proximo->dado;

    if (dadoInicioProximo >= dadoAntigoInicio) return true;

    Item<Tipo> *antigoInicio = setEncadeado.inicio;
    antigoInicio->dado = dadoAntigoInicio;

    setEncadeado.inicio = antigoInicio->proximo;
    setEncadeado.inicio->anterior = setEncadeado.fim;
    setEncadeado.fim->proximo = setEncadeado.inicio;

    const Tipo dadoFim = setEncadeado.fim->dado;

    if (dadoAntigoInicio >= dadoFim) {
        setEncadeado.inicio->anterior = antigoInicio;
        setEncadeado.fim->proximo = antigoInicio;
        antigoInicio->proximo = setEncadeado.inicio;
        setEncadeado.fim = antigoInicio;
        return true;
    }

    Item<Tipo> *auxiliar = setEncadeado.fim;
    Tipo dadoAuxiliar = auxiliar->dado;

    while (dadoAuxiliar > dadoAntigoInicio) {
        auxiliar = auxiliar->anterior;
        dadoAuxiliar = auxiliar->dado;
    }

    Item<Tipo> *proximoDoAuxiliar = auxiliar->proximo;

    antigoInicio->proximo = auxiliar->proximo;
    antigoInicio->anterior = auxiliar;
    auxiliar->proximo = antigoInicio;
    proximoDoAuxiliar->anterior = antigoInicio;


    return true;
}

#endif
