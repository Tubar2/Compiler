mod_b: begin
val: extern
l1: extern
public y
public mod_b

section .data
y: space

section .text
    output y
    output val
    output y
    jmp l1

end