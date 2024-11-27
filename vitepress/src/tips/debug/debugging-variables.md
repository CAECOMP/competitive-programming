# Debuggando variáveis

## Introdução

Nem tudo são flores, e nem sempre seu código irá funcionar.
E pior ainda, nem sempre você terá noção sobre o que está causando o problema.

Uma forma comum e eficiente para debuggar é mostrar os dados contidos nas variáveis
do programa. Geralmente, isso é feito da seguinte forma:

```c++
int a = 10;
string b = "b";
bool c = false;
std::cout << "A = " << a << ", b = " << b << "c = " << c << endl;
```

Porém, debuggar dessa forma tem várias desvantagens:

1. Ter que especificar o nome de cada variável manualmente é verboso e repetitivo.
2. O `std::cout`, por si só, não é capaz de apresentar o valor de estruturas como
vetores ou sets.
3. Para desativar, é necessário manualmente remover todas as linhas com `std::cout`.
4. Pode ficar bem confuso, principalmente se o código de debug for repetido
em várias linhas.

## Parte 1: Macros para o resgate! {#macros}

Macros podem solucionar uma boa parte desses problemas. Como são expandidos
em tempo de compilação, podem gerar código com informações essenciais.

Por exemplo, o macro a seguir:

```c++:no-line-numbers
#define debug(x) cout << #x << " = " << x << endl
```

Mostrará o nome e o valor da expressão x:

```c++
int numero = 900;
debug(numero);      // saída: numero = 900
debug(numero / 2);  // saída: numero / 2 = 450
debug(20 & 1);      // saída: 20 & 1 = 0

string str = "explodiu"
debug(str);         // saída: str = explodiu
debug("não " + str) // saída: "não " + str = não explodiu
```

Macros também podem obter o nome da função e número da linha em que foram usados.

Por exemplo:

```c++:line-numbers=5
#define debug(x)                            \
    cout << "Linha " << __LINE__            \
    << ", função " << __FUNCTION__ << ": "  \
    << #x << " = " << x << endl

void func(string x) { debug(x); }

int main() {
    func("teste");
    debug(33 + 36);
}
```

Tem como saída:

```bash:no-line-numbers
Linha 10, função func: x = teste
Linha 14, função main: 33 + 36 = 69
```

Porém, como visto em todos esses exemplos, apenas uma variável está sendo debuggada
por vez. Podemos melhorar?

## Parte 2: Templates também ajudam! {#templates}

Templates em C++ são ferramentas complexas e poderosas capazes de fazer uma função
poder receber vários tipos de dados diferentes, o que será fundamental pros códigos
a seguir.

Exemplo simples:

```c++
void printer() { cout << endl; }
template <typename H, typename... T> void printer(H val, T... args) {
    cout << val << ", ";
    printer(args...);
}

int main() {
    printer("a", "b", true, false, 10, 0.5);
    return 0;
}
```

Terá `a, b, 1, 0, 10, 0.5,` como saída.

Agora podemos debuggar várias variáveis de uma vez só.... Mas e os nomes das
variáveis, que apareciam nos macros? E o número da linha?

## Parte 3: Macros + Templates, união sinistra {#templates-e-macros}

Juntando o ~~in~~útil ao ~~des~~agradável, podemos criar um macro capaz de receber
infinitas expressões, e usá-lo junto do template anterior:

```c++
#define debug(...) ({                       \
    cout << "Linha " <<__LINE__ << ": ";    \
    printer(__VA_ARGS__);                   \
})
```

E assim obtemos de volta a informação sobre a linha onde isso foi executado!

..... Mas e os nomes das variáveis?

É ligeiramente mais complicado, mas nada demais. Considerando que
`#define nome(x) #x` retorna a expressão `x` como uma string, também podemos aplicar
essa idéia á macros com infinitos argumentos:

```c++
#define nomes(...) #__VA_ARGS__
int x = 10;
string str = "sim";
string dados = nomes(x, str, true, 30 >> 1);
```

Nesse trecho de código, a variável `dados` assumirá o valor `"x, str, true, 30 >> 1"`.
Ou seja, só precisamos printar a string antes de cada vírgula,
e depois mostrar o valor real.

Implementação:

```c++
void print_name(string &s) {
    // Printa caractere a caractere, até achar uma vírgula
    do {
        cout << s[0];
        s = s.substr(1);
    } while (s.size() && s[0] != ',');
    cout << " = ";
}

void printer(string s) { cout << endl; }
template <typename V, typename... A> void printer(string s, V val, A... args) {
    print_name(s);          // Mostra o nome da variável
    cout << val;            // Mostra o valor da variável
    printer(s, args...);    // Segue recursivamente
}

#define debug(...) ({                       \
    cout << "Linha " << __LINE__ << ": ";   \
    printer(#__VA_ARGS__, __VA_ARGS__);     \
})
```

Agora sim, você terá a linha de execução e o nome das variáveis!

Porém, ainda existem limitações: Esse código não é capaz de debuggar estruturas
como vetores, sets, maps, e etc.
Suportar essas estruturas aumentam bastante a complexidade, e para algo realmente
completo, recomendamos ler [este post no Codeforces](https://codeforces.com/blog/entry/125435)
 ou os arquivos do [repositório disponibilizado no post](https://github.com/Anshul-Johri-1/Debug-Template/).

De toda forma, para adicionar o suporte a vetores de forma simples no código anterior,
é só adicionar essa função logo acima da função `printer` anterior:

```c++
template <typename H, typename... A>
void printer(string s, vector<H> &vec, A... args) {
    print_name(s);
    cout << "{";
    for (int len = vec.size(), i = 0; i < len; ++i) {
        cout << " " << vec[i];
        if (i + 1 != len)
            cout << ",";
    }
    cout << " }";
    printer(s, args...);
}
```

## Desativando o debug {#desativando}

Novamente, macros te ajudarão. Você pode escrever algo do tipo:

```c++
#define DEBUG // [!code highlight]
#ifdef DEBUG
#define debug(...) printer(#__VA_ARGS__, __VA_ARGS__);
#else
#define debug(...) 0
#endif
```

Assim, para desativar o debug no código INTEIRO, é só comentar a linha destacada.
