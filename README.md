# Estruturas de Dados: Listas e Pilhas em C

Projeto da disciplina **Algoritmos e Estruturas de Dados** com implementações em linguagem C de **Listas** (sequenciais e encadeadas) e **Pilhas** (sequenciais e encadeadas), fundamentadas no conceito de **Tipos Abstratos de Dados (TAD)**.

> **Tutor virtual:** Professor PhD Paulo Fernando Leite Filho

![Linguagem](https://img.shields.io/badge/linguagem-C-blue)
![Disciplina](https://img.shields.io/badge/disciplina-Algoritmos%20e%20Estruturas%20de%20Dados-lightgrey)

---

## Sumário

- [Objetivo](#objetivo)
- [Conteúdo abordado](#conteúdo-abordado)
- [Conceitos fundamentais](#conceitos-fundamentais)
- [Listas](#listas)
- [Pilhas](#pilhas)
- [Comparativo: sequencial × encadeada](#comparativo-sequencial--encadeada)
- [Aplicações](#aplicações)
- [Estrutura do repositório](#estrutura-do-repositório)
- [Como compilar e executar](#como-compilar-e-executar)
- [Prática de laboratório](#prática-de-laboratório)
- [Referências](#referências)
- [Autores](#autores)

---

## Objetivo

Compreender **como organizar dados na memória** e **implementar listas e pilhas em C**, partindo do conceito de dado e de TAD até a codificação das operações com alocação sequencial (vetor) e encadeada (ponteiros e alocação dinâmica).

## Conteúdo abordado

O material é cumulativo: o conceito de TAD sustenta as listas, e as listas sustentam as pilhas (que são listas com acesso restrito ao topo).

| Aula | Tema | Tópicos |
|------|------|---------|
| 1 | Introdução | Tipo de dado, estrutura de dados e TAD; estruturas lineares e não lineares; conceito de lista e formas de representação |
| 2 | Lista sequencial | Elementos em posições consecutivas (vetor); operações básicas em C; vantagens e limitações |
| 3 | Lista encadeada | Registros com ponteiro para o sucessor; `malloc`, `free` e `NULL`; operações com alocação dinâmica |
| 4 | Pilhas | Princípio LIFO; implementação sequencial e encadeada; prática com menu de opções |

---

## Conceitos fundamentais

### Tipo de dado, TAD e Estrutura de Dados

| Conceito | Definição | Exemplo |
|----------|-----------|---------|
| **Tipo de dado** | Conjunto de valores que uma variável pode assumir, mais as operações permitidas | Tipo lógico: verdadeiro ou falso |
| **Tipo Abstrato de Dado (TAD)** | Tipo de dado visto pelo que o usuário deseja fazer, "divorciado" do hardware | Lista, pilha, fila, árvore |
| **Estrutura de Dados (ED)** | Método particular de implementar um TAD, construído com tipos primitivos (`int`, `float`, `char`) ou compostos (`array`, `struct`) | Pilha em vetor ou em nós encadeados |

> **O TAD define o quê; a ED define como.** Um mesmo TAD admite várias estruturas de dados, e a interface permanece a mesma.

### O que uma declaração de variável especifica

1. **Valores:** o conjunto de valores que a variável pode assumir
2. **Operações:** o conjunto de operações que podemos efetuar
3. **Tamanho:** a quantidade de bytes reservada
4. **Interpretação:** como os bits armazenados devem ser lidos (inteiro, real…)

### Operações típicas de um TAD

`Criação` (sempre a 1ª) · `Inclusão` · `Remoção` · `Percurso` · `Busca`

### Classificação

- **Estruturas lineares:** listas ordenadas, pilhas, filas, deques
- **Estruturas não lineares:** árvores, grafos

**Foco deste projeto:** listas e pilhas (estruturas lineares).

---

## Listas

Estrutura que **preserva a relação de ordem linear** entre os dados, composta por **nós**, cada um com um dado primitivo ou composto.

```
L1 → L2 → L3 → … → L(n-1) → Ln
```

### Operações

- Criar uma lista vazia
- Verificar se está vazia
- Obter o tamanho
- Obter/modificar o elemento de uma posição
- Obter a posição de um valor dado
- Inserir após (ou antes de) uma posição
- Remover o elemento de uma posição
- Exibir os elementos
- Concatenar duas listas

### Lista sequencial (vetor)

Elementos em **posições físicas consecutivas**. O elemento `a(i)` é mapeado no índice `i`.

```c
#define MAX 100
typedef int telem;            /* tipo base */

typedef struct {
    telem v[MAX];             /* vetor da lista */
    int n;                    /* nº de elementos */
} tlista;
```

- Inserir em `a(i)`: desloca `a(i)…a(n)` para a direita
- Remover `a(i)`: desloca `a(i+1)…a(n)` para a esquerda
- Posições da lista: `1` a `n`; índices do vetor em C: `0` a `n-1`
- Convenção de retorno das funções: `1` = sucesso, `0` = erro

**Vantagens:** acesso direto indexado em tempo constante.
**Desvantagens:** movimentação de elementos ao inserir/eliminar e tamanho máximo pré-estimado.
**Quando usar:** listas pequenas, tamanho máximo bem definido, inserção/remoção no fim.

### Lista encadeada

Cada elemento é um **registro com o dado e o endereço do sucessor** (`prox`). Usa alocação dinâmica, sem tamanho máximo fixo, ao custo de **um ponteiro extra por nó**.

```c
#include <stdlib.h>
typedef int telem;

typedef struct no {
    telem dado;               /* informação */
    struct no *prox;          /* próximo nó */
} tno;

typedef tno *tlista;          /* ponteiro p/ 1º nó; lista vazia = NULL */
```

**Notação de ponteiros em C**

| Operação | Notação |
|----------|---------|
| Declarar ponteiro | `tp *P;` |
| Alocar registro | `P = (tp *) malloc(sizeof(tp));` |
| Acessar campo | `P->dado` ou `(*P).dado` |
| Endereço nulo | `P->prox = NULL;` |
| Liberar memória | `free(P); P = NULL;` |

> ⚠️ **Atenção:** `P = Q` copia o **endereço** (P passa a apontar para a lista de Q); `*P = *Q` copia o **conteúdo** do objeto apontado. Após `P = Q`, libere a lista antiga de P antes, para não perdê-la (vazamento de memória).

**Inserção após um nó `p`** (a ordem das atribuições é essencial):

```c
novo->prox = p->prox;   /* 1º: novo aponta para o sucessor */
p->prox = novo;         /* 2º: anterior aponta para o novo */
```

**Remoção:** mantém-se dois ponteiros (`a` = anterior, `p` = atual). Remover o 1º nó altera a cabeça da lista (`*L`); nos demais casos, `a->prox = p->prox` e `free(p)`.

> Observação: em C padrão, `malloc` e `free` estão em `<stdlib.h>` (a apostila de origem usa `<alloc.h>`).

### Operações implementadas

| Operação | Lista sequencial | Lista encadeada |
|----------|:----------------:|:---------------:|
| `criar` | O(1) | O(1) |
| `vazia` | O(1) | O(1) |
| `cheia` | O(1) | n/a (limitada pela memória) |
| `tamanho` | O(1) | O(n) |
| `elemento` (por posição) | O(1) | O(n) |
| `posicao` (por valor) | O(n) | O(n) |
| `inserir` | O(n) (deslocamento) | O(n) para localizar a posição; ajuste de ponteiros em O(1) |
| `remover` | O(n) (deslocamento) | O(n) para localizar a posição; ajuste de ponteiros em O(1) |

---

## Pilhas

Lista em que **inserção e remoção ocorrem em uma única extremidade: o topo**. Segue o princípio **LIFO** (*Last In, First Out*): o último a entrar é o primeiro a sair.

Para `P = (a(1), …, a(n))`: `a(1)` é a **base**, `a(n)` é o **topo** e `a(i+1)` está acima de `a(i)`.

### Operações

| # | Operação | Função |
|---|----------|--------|
| 1 | Criar uma pilha vazia | `criar` |
| 2 | Testar se está vazia | `vazia` |
| 3 | Obter o elemento do topo (sem eliminar) | `elemtopo` |
| 4 | Inserir no topo (empilhar) | `push` |
| 5 | Remover o topo (desempilhar) | `pop` |

### Pilha sequencial (vetor + índice `topo`)

```c
#define MAX 10
typedef int telem;

typedef struct {
    telem v[MAX];
    int topo;                 /* -1 = pilha vazia */
} tpilha;

int push(tpilha *p, telem valor) {
    if (p->topo == MAX-1) return 0;      /* pilha cheia */
    p->v[++(p->topo)] = valor;           /* incrementa e grava */
    return 1;
}

int pop(tpilha *p, telem *valor) {
    if (p->topo == -1) return 0;         /* pilha vazia */
    *valor = p->v[(p->topo)--];          /* lê e decrementa */
    return 1;
}
```

- `topo = -1` ⇒ pilha vazia; `topo = MAX-1` ⇒ pilha cheia
- Sem deslocamentos: todas as operações em **O(1)**

### Pilha encadeada (nós + ponteiro `topo`)

```c
typedef struct no {
    telem dado;
    struct no *prox;
} tno;

typedef tno *tpilha;          /* topo = 1º nó; vazia = NULL */

int push(tpilha *p, telem valor) {
    tpilha novo = (tpilha) malloc(sizeof(tno));
    if (novo == NULL) return 0;          /* sem memória */
    novo->dado = valor;
    novo->prox = *p;                     /* aponta p/ antigo topo */
    *p = novo;                           /* novo é o topo */
    return 1;
}

int pop(tpilha *p, telem *valor) {
    tpilha aux;
    if (*p == NULL) return 0;            /* pilha vazia */
    aux = *p;
    *valor = aux->dado;
    *p = aux->prox;                      /* topo desce */
    free(aux);
    return 1;
}
```

- `push` = inserir no início da lista; `pop` = remover o 1º nó e liberar com `free`
- Sem limite fixo de tamanho: só falha se `malloc` retornar `NULL`
- Mesmas assinaturas da versão sequencial, ou seja, **mesma interface (TAD), ED diferente**

---

## Comparativo: sequencial × encadeada

| Critério | Lista sequencial | Lista encadeada |
|----------|------------------|-----------------|
| Armazenamento | Posições consecutivas (vetor) | Nós dispersos ligados por ponteiros |
| Acesso ao i-ésimo | Direto pelo índice (tempo constante) | Percorre a lista desde o início |
| Inserir / remover | Desloca elementos | Apenas ajusta ponteiros |
| Tamanho | Máximo pré-definido | Dinâmico (limitado pela memória) |
| Memória extra | Nenhuma | Um ponteiro por nó |
| Indicada para | Listas pequenas, tamanho conhecido | Tamanho imprevisível, muitas inserções e remoções |

> Em **pilhas** não há deslocamentos (só se opera no topo), portanto a alocação **sequencial** costuma ser mais vantajosa, salvo quando o tamanho máximo não é conhecido.

---

## Aplicações

**Listas**

| Lista sequencial | Lista encadeada |
|------------------|-----------------|
| Tamanho máximo conhecido (notas de uma turma) | Volume de dados imprevisível (clientes, pedidos) |
| Buffer de amostras de sensores | Muitas inserções e remoções no meio |
| Tabelas de consulta fixas | Fila de pacotes ou de setores de disco |
| Acesso por índice e busca binária em dados ordenados | Lista de processos ou tarefas |
| Inserções e remoções no fim da lista | Base de pilhas, filas e listas de adjacência |

Exemplos clássicos: lista telefônica, clientes de uma agência bancária, setores de disco a serem acessados pelo sistema operacional e pacotes a serem transmitidos em um nó de rede.

**Pilhas**

- **Chamadas de função:** a pilha de execução guarda o retorno de cada chamada, incluindo a recursão
- **Desfazer / refazer:** editores empilham ações; `Ctrl+Z` desempilha a última
- **Histórico do navegador:** o botão "voltar" retorna à última página visitada
- **Parênteses balanceados:** compiladores empilham `(` e `{` e conferem o fechamento
- **Expressões pós-fixas:** avaliação e conversão de expressões aritméticas
- **Busca e backtracking:** busca em profundidade e retorno em labirintos

---

## Estrutura do repositório

> Sugestão de organização. Ajuste os nomes conforme os arquivos reais do projeto.

```
.
├── lista_sequencial/
│   └── lista_sequencial.c
├── lista_encadeada/
│   └── lista_encadeada.c
├── pilha_sequencial/
│   └── pilha_sequencial.c      # editor de pilha com menu
├── pilha_encadeada/
│   └── pilha_encadeada.c       # editor de pilha com menu
├── docs/
│   └── Estruturas_de_Dados_Listas_e_Pilhas.pptx
└── README.md
```

## Como compilar e executar

Pré-requisito: compilador C (ex.: `gcc`).

```bash
# Compilar (exemplo com a pilha sequencial)
gcc -Wall -Wextra -o pilha_sequencial pilha_sequencial/pilha_sequencial.c

# Executar
./pilha_sequencial          # Linux / macOS
pilha_sequencial.exe        # Windows
```

## Prática de laboratório

Programa em C com **menu de opções**, implementado primeiro com **pilha sequencial** e depois com **pilha encadeada** (mesmo menu, duas formas de alocação):

```
EDITOR DE PILHA

1 - EMPILHAR
2 - DESEMPILHAR
3 - EXIBIR ELEMENTO DO TOPO
4 - EXIBIR A PILHA
5 - ESVAZIAR A PILHA

DIGITE SUA OPÇÃO:
```

Atividade análoga é proposta para o **editor de listas**, com as duas representações.

## Síntese

1. **TAD** define o quê; a **ED** define como.
2. **Lista sequencial:** acesso direto, mas com deslocamentos e tamanho fixo.
3. **Lista encadeada:** tamanho dinâmico, ao custo de um ponteiro por nó.
4. **Pilha (LIFO):** operações só no topo, em vetor ou em nós.

## Ferramentas de visualização

- [DSA by Shadab](https://dsa-by-shadab.vercel.app/)
- [Michael Gastner – apps](https://apps.michael-gastner.com/)

## Referências

- CORMEN, Thomas H. et al. **Algoritmos: teoria e prática**. 3. ed. Rio de Janeiro: Elsevier, 2012.
- EGYPTO, Cândido. **Apostila de Estrutura de Dados**. João Pessoa: Centro Federal de Educação Tecnológica da Paraíba, Coordenação do Curso de Tecnologia em Telemática, jul. 2003.
- TENENBAUM, Aaron M.; LANGSAM, Yedidyah; AUGENSTEIN, Moshe J. **Estruturas de dados usando C**. São Paulo: Makron Books, 1995.
- ZIVIANI, Nivio. **Projeto de algoritmos: com implementações em Pascal e C**. 3. ed. São Paulo: Cengage Learning, 2011.

Figuras elaboradas pelo autor, inspiradas na representação usual desses livros-texto.

## Autores

<!-- Preencha com os integrantes do grupo -->

| Nome | GitHub |
|------|--------|
| Paulo Fernando Leite Filho | [@usuario](https://github.com/paulofernandoleitefilho/) |

**Orientação:** Professor PhD Paulo Fernando Leite Filho

---

<sub>Projeto acadêmico desenvolvido para fins educacionais.</sub>
