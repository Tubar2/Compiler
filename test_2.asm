; Arquivo sem erros

SECTION DATA
N1: const 2
N2: space

SECTION TEXT
rot:
jmp rot
rot: jmp n1
stop
