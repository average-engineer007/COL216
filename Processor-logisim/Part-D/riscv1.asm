.text
start: addi t0 zero 10
addi t1 zero 10
sw t1 3(zero)
beq t1 t1 start
