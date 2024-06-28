main: addi t0 zero -12
addi t1 zero 20
sw t0 4(t1)
lw t2 4(t1)
sub a0 t1 t2
addi s0 zero -1
slli s1 s0 2
and s0 s1 t0
ori s0 zero -32
sltiu s0 t2 10
beq t1 t1 main