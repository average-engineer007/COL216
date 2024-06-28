.data
array1: .space 40   
array2: .space 40   
.text

.global main

main:
#input number of characters and store in t4
	li a7,5
	ecall
	mv t4,a0
#addi sp,sp,-64




la a1, array1
li t1, 0
addi t0,t4,0
input_loop1:
	addi t1,t1,1
	li a7,12
	ecall
	mv s0,a0
	sw s0,0(a1)
	addi a1,a1,1
	
	bne t1, t0, input_loop1
	
	
initialise:
la a2, array2
li t1, 0
addi t0,t4,0
	
input_loop2:
	addi t1,t1,1
	li a7,12
	ecall
	mv s0,a0
	sw s0,0(a2)
	addi a2,a2,1
	
	bne t1, t0, input_loop2
	
	
	
inti_again:
	li t1,0
	addi t0,t4,0
	la a1, array1
	la a2, array2
	li s0,0
	li s1,0
	li a6,10
	
sum:	
	addi t1,t1,1
	lw t3,0(a1)
	lw t4,0(a2)
	addi a1,a1,1
	addi a2,a2,1
	add s0,t3,t4
	add s0,s0,s1
	li s1,0
	bge s0,a6,carry
	carry: 
		addi s0,s0,-10
		li s1,1
	li a7,11
	mv a0,s0
	ecall
	bne t1, t0, sum

success:
	li a0, 0 
	li a7, 93
	ecall
