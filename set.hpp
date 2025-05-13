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
    if (setEncadeado.inicio == NULL || setEncadeado.fim == NULL || setEncadeado.fim->proximo != setEncadeado.inicio ||
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

template<typename Tipo>
bool atualizarSet(SetEncadeado<Tipo> &setEncadeado, Item<Tipo> *item) {
    bool naoCircular = setEncadeado.inicio == NULL || setEncadeado.fim == NULL || setEncadeado.fim->proximo != setEncadeado.inicio ||
                       setEncadeado.inicio->anterior != setEncadeado.fim;
    bool itemInvalido = item == NULL || item->anterior == NULL || item->proximo == NULL;
    if (naoCircular || itemInvalido) return false;

    bool umItem = setEncadeado.inicio == setEncadeado.fim;
    bool posicaoCorreta1 = item->proximo->dado == item->dado || item->anterior->dado == item->dado;
    bool posicaoCorreta2 = item->proximo->dado > item->dado && item->anterior->dado < item->dado;

    if (umItem || posicaoCorreta1 || posicaoCorreta2) return true;

    bool doisItens = setEncadeado.inicio->proximo == setEncadeado.fim && setEncadeado.fim->anterior == setEncadeado.inicio;

    if (doisItens) {
        Tipo dadoInicio = setEncadeado.inicio->dado;
        Tipo dadoFim = setEncadeado.fim->dado;
        if (dadoInicio < dadoFim) return true;
        setEncadeado.inicio->dado = dadoFim;
        setEncadeado.fim->dado = dadoInicio;
        return true;
    }


    auto aux = item->dado < item->anterior->dado ? item->anterior : item->proximo;

    // Desconecta o item
    item->anterior->proximo = item->proximo;
    item->proximo->anterior = item->anterior;
    if (item == setEncadeado.inicio) {
        setEncadeado.inicio = item->proximo;
        setEncadeado.fim->proximo = setEncadeado.inicio;
    }
    if (item == setEncadeado.fim) {
        setEncadeado.fim = item->anterior;
        setEncadeado.inicio->anterior = setEncadeado.fim;
    }

    if (aux->dado > item->dado) {
        while (aux->dado > item->dado && aux != setEncadeado.inicio) {
            aux = aux->anterior;
        }
        if (aux == setEncadeado.inicio && aux->dado > item->dado) {
            item->proximo = aux;
            item->anterior = setEncadeado.fim;
            setEncadeado.inicio = item;
            setEncadeado.fim->proximo = setEncadeado.inicio;
            aux->anterior = setEncadeado.inicio;
            return true;
        }
        item->proximo = aux->proximo;
        item->anterior = aux;
        aux->proximo->anterior = item;
        aux->proximo = item;
        return true;
    }
    while (aux->dado < item->dado && aux != setEncadeado.fim) {
        aux = aux->proximo;
    }
    if (aux == setEncadeado.fim && aux->dado < item->dado) {
        item->anterior = aux;
        item->proximo = setEncadeado.inicio;

        setEncadeado.fim = item;
        setEncadeado.inicio->anterior = setEncadeado.fim;
        aux->proximo = setEncadeado.fim;
        return true;
    }
    item->proximo = aux;
    item->anterior = aux->anterior;
    aux->anterior->proximo = item;
    aux->anterior = item;
    return true;
}

#endif
