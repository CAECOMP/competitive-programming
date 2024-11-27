# Debuggando crashes e situações absurdas

## Introdução

Alguns tipos de erros de programação podem causar uma parada inesperada do programa
ou funcionamento completamente caótico.

Em boa parte das linguagens de programação modernas, como Java, Python e JavaScript,
esse tipo de situação dispara uma exceção que irá:

1. Relatar o tipo de erro que ocorreu (ex: acessar um item inexistente, divisão
por 0)
2. Mostrar a pilha de execução até o momento em que o erro aconteceu (stacktrace)
3. Terminar a execução do programa, caso a exceção não seja tratada.

Em C, tal mecanismo não existe nativamente, e em C++ comum, isso raramente é usado.
Portanto, muitas vezes, o programa seguirá executando com valores errados, ou
simplesmente irá parar de executar sem relatar nada sobre o problema ocorrido,
o que dificulta o debug.

Exemplos:

::: tabs
==Divisão por zero

```c++
int main() {
    int a = 1, b = 0;
    return a / b;
}
```

```bash
$ ./main
Tarefa 1, './main' encerrada pelo sinal
SIGFPE (Exceção de ponto flutuante)
```

==Falha de segmentação

```c++
int main() {
    int *a = nullptr;
    return *a;
}
```

```bash
$ ./main
Tarefa 1, './main' encerrada pelo sinal
SIGSEGV (Erro de fronteira de endereço (Falha de segmentação))
```

:::

## Usando opções do compilador

Versões recentes de compiladores modernos (ex, GCC 12+, Clang 16+) possuem
diversas opções que podem facilitar essa tarefa de encontrar coisas que podem
causar crashes em tempo de compilação, ou mostrar a causa do crash durante a runtime.

Por exemplo, se você tentar compilar os snippets acima usando a opção `-fanalyzer`
no GCC:
::: tabs
== Divisão por zero

```bash
$ g++ -fanalyzer main.cpp
main.cpp: In function ‘int main()’:
main.cpp:2:23: warning: infinite loop [CWE-835] [-Wanalyzer-infinite-loop]
    2 |     for (int i = 2; i >= 0; --i)
      |                     ~~^~~~
  ‘int main()’: events 1-5
    |
    |    2 |     for (int i = 2; i >= 0; --i)
    |      |     ~~~             ~~^~~~
    |      |     |                 |
    |      |     |                 (1) infinite loop here
    |      |     |                 (2) when ‘i >= 0’: always following ‘true’ branch...
    |      |     |                 (5) ...to here
    |      |     (4) looping back...
    |    3 |         i /= i;
    |      |         ~~~~~~         
    |      |           |
    |      |           (3) ...to here
    |

```

== Falha de segmentação

```bash
$ g++ -fanalyzer main.cpp
main.cpp: In function ‘int main()’:
main:3:13: warning: dereference of NULL ‘a’ [CWE-476] [-Wanalyzer-null-dereference]
    3 |     return *a;
      |             ^
  ‘int main()’: events 1-2
    |
    |    2 |     int *a = nullptr;
    |      |          ^
    |      |          |
    |      |          (1) ‘a’ is NULL
    |    3 |     return *a;
    |      |             ~
    |      |             |
    |      |             (2) dereference of NULL ‘a’
    |

```

:::

Porém, análise estática de código (em tempo de compilação) não é capaz de
detectar todos os bugs, e nem ajuda a explicar os crashes.

## Debuggando bizonhices em tempo de execução - com opções do compilador

:::warning AVISO
Algumas dessas opções podem não estar presentes no seu compilador, principalmente
no Windows.

A solução é instalar um sistema que preste (ex: [CachyOS Linux](https://cachyos.org/),
[Pop!OS Linux](https://pop.system76.com/), etc).
:::

Leia o código a seguir:

```c++
#include <iostream>

using namespace std;

void f(int tamanho, int index) {
    int arr[tamanho];
    arr[index] = index + tamanho;
    cout << arr[index] << " " << arr[index + 1] << endl;
}

int main() {
    f(3, 4);
    return 0;
}
```

Nesse trecho de código, é fácil ver que a função `f` irá acessar um
índice maior que o tamanho da array, mas isso NÃO crashará o programa, o que abre
um mundo de possibilidades para bugs bizonhos aparecerem.

Em códigos bem mais complexos, não é tão fácil ver um erro desses de cara.
Nesses casos, você pode compilar o programa usando a opção `-fsanitize=undefined`:

```bash
$ g++ -fsanitize=undefined main.cpp -o main
$ ./main
main.cpp:7:14: runtime error: index 3 out of bounds for type 'int [*]'
    #0 0x556d628ca28b in f(int, int) (/tmp/main+0x128b) (BuildId: 0f08dc3fbd7e58985de984fd951d8608c071a6bb)
    #1 0x556d628ca741 in main (/tmp/main+0x1741) (BuildId: 0f08dc3fbd7e58985de984fd951d8608c071a6bb)
    #2 0x7efcdd633d67 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #3 0x7efcdd633e24 in __libc_start_main_impl ../csu/libc-start.c:360
    #4 0x556d628ca100 in _start (/tmp/main+0x1100) (BuildId: 0f08dc3fbd7e58985de984fd951d8608c071a6bb)
.............

6 1600677166
```

Note que você pode tornar essa saída um **pouco** mais legível caso adicione a
opção `-g`, que mantém dados importantes para debuggar no binário, como a linha
dos itens na pilha de chamada:

```bash
$ g++ -fsanitize=undefined -g main.cpp -o main
$ ./main
main.cpp:7:14: runtime error: index 3 out of bounds for type 'int [*]'
    #0 0x5650df40628b in f(int, int) /tmp/main.cpp:7
    #1 0x5650df406741 in main /tmp/main.cpp:12
    #2 0x7f9764833d67 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #3 0x7f9764833e24 in __libc_start_main_impl ../csu/libc-start.c:360
    #4 0x5650df406100 in _start (/tmp/main+0x1100) (BuildId: 75c7c990a14b29566e6674bf62b7b892048ccd58)

6 1600677166

```
