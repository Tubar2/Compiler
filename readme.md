# Aluno
Ricardo Santos - 18/0027263

# Formato da .asm
O programa espera que o código assembly esteja no seginte formato
primeiro: headers \
depois: .sections, onde: \
Headers:
```
mod: BEGIN
bar: extern
public foo
```
.sections (qualquer ordem):
```
section .data
labl_1: space
labl_2: const 5

section .text
    add labl_1
    end
```

# Compilando
Basta rodar `make` no terminal e ambos os executáveis (montador e simulador)
serão gerados

É utilizada a versão `C++ 11` para compilar os arquivos

O comando `make clean` deve remover todos os arquivos .o, .out e .obj,
assim como os executáveis compilados pelo make

# Execução
A execução segue então por
1. `./montador <nome-do-arquivo>.asm`    (a extensão ".asm" é opcional)
2. `./simulador <nome-do-arquivo>.obj`   (a extensão ".obj" é opcional)

# Saídas
### Terminal
A saída no terminal representa os valores contidos em `ACC` e `PC` após a
execução de cada linha de instrução.

Também são impressos os valores
gerados por `output`


### Arquivo
O programa gera um arquivo de texto com nome `<nome-do-arquivo>.out` onde
são armazenados saídas geradas pela instrução `output`
