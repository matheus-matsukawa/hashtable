#include "hashtable.h"

unsigned int hash(const char *key)
{
    unsigned long int value = 0;

    unsigned int key_len = strlen(key);

    // um loop arbitrário para "traduzir" a string em valor numérico
    // um número primo é utilizado para tentar reduzir as colisões
    for (unsigned int i = 0; i < key_len; ++i)
    {
        value = value * 37 + key[i];
    }

    // garante que 0 <= value < TABLE_SIZE
    value = value % TABLE_SIZE;

    return value;
}

unsigned int nextSlot(unsigned int slot)
{
    if (slot >= TABLE_SIZE - 1)
    {
        return 0;
    }
    return slot + 1;
}

entry_t *ht_pair(const char *key, const char *value)
{
    // aloca a entrada
    entry_t *entry = malloc(sizeof(entry_t) * 1);
    entry->key = malloc(strlen(key) + 1);
    entry->value = malloc(strlen(value) + 1);

    // copia a chave e o valor para a entrada
    strcpy(entry->key, key);
    strcpy(entry->value, value);

    return entry;
}

ht_t *ht_create(void)
{
    // aloca a tabela
    ht_t *hashtable = malloc(sizeof(ht_t) * 1);

    // aloca as entradas
    hashtable->entries = malloc(sizeof(entry_t *) * TABLE_SIZE);

    // inicializa com NULL
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        hashtable->entries[i] = NULL;
    }

    return hashtable;
}

void ht_set(ht_t *hashtable, const char *key, const char *value)
{
    unsigned int slot = hash(key);

    // acessa o index nas entradas da tabela
    entry_t *entry = hashtable->entries[slot];

    // se não há entradas, insira
    if (entry == NULL)
    {
        hashtable->entries[slot] = ht_pair(key, value);
        return;
    }

    entry_t *prev = entry;

    // anda pela tabela até encontrar a chave ou uma posição vazia para inserir
    do
    {
        if (strcmp(entry->key, key) == 0)
        {
            // chave encontrada, atualiza o valor
            free(entry->value);
            entry->value = malloc(strlen(value) + 1);
            strcpy(entry->value, value);
            return;
        }
        slot = nextSlot(slot);
        entry = hashtable->entries[slot];

    } while (entry != NULL && entry != prev);
    // insere na posição vazia
    if (entry == NULL)
    {
        hashtable->entries[slot] = ht_pair(key, value);
        return;
    }

    printf("Tabela cheia!!!\n");
}

char *ht_get(ht_t *hashtable, const char *key)
{
    unsigned int slot = hash(key);

    entry_t *entry = hashtable->entries[slot];

    // se NULL, não está na tabela
    if (entry == NULL)
    {
        return NULL;
    }

    entry_t *prev = entry;

    do
    {
        // verifica a chave e retorna a entrada caso encontrada
        if (strcmp(entry->key, key) == 0)
        {
            return entry->value;
        }
        // anda para o próximo índice
        slot = nextSlot(slot);
        entry = hashtable->entries[slot];

    } while (entry != NULL && entry != prev);

    // Entrada não está na tabela
    return NULL;
}

void ht_del(ht_t *hashtable, const char *key)
{
    unsigned int slot = hash(key);

    entry_t *entry = hashtable->entries[slot];

    // se NULL não há o que deletar
    if (entry == NULL)
    {
        return;
    }

    entry_t *prev = entry;

    // walk through each entry until either the end is reached or a matching key is found
    do
    {

        // verifica a chave
        if (strcmp(entry->key, key) == 0)
        {
            hashtable->entries[slot] = NULL;

            // libera a entrada
            free(entry->key);
            free(entry->value);
            free(entry);

            return;
        }
        // tenta o proximo indice
        slot = nextSlot(slot);
        entry = hashtable->entries[slot];
    } while (entry != NULL && entry != prev);
}

void ht_dump(ht_t *hashtable) // printa a tabela
{
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        entry_t *entry = hashtable->entries[i];

        if (entry == NULL)
        {
            continue;
        }

        printf("slot[%4d]: ", i);
        printf("%s=%s ", entry->key, entry->value);
        printf("\n");
    }
}
