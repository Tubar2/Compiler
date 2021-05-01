mod_A: begin
y: extern
mod_b: extern
public val
public l1

section .text
    input y
    load val
    add y
    store y
    jmp mod_b
l1: stop

section .data
val: const 5
end