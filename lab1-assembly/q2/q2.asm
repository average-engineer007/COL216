.global main
.data
array: .space 40   
prompt1 : .asciz "Name : Mohit Dua\n "
newline : .asciz"\n"

.text
main:
	la a1, array 
	li t0, 10
	li t1, 0
input_loop:
	addi t1,t1,1
	li a7,5
	ecall
	mv s0,a0
	sw s0,0(a1)
	addi a1,a1,4
	
	bne t1, t0, input_loop
initialise:
	la a1, array 
	li t0, 10
	li t1, 0
	li s1,0
loop2:
	addi t1,t1,1
	lw t3,0(a1)
	add s1,s1,t3
	addi a1,a1,4
	bne t1, t0, loop2
	beq t1, t0, success
	
success:
	li a7,1
	addi a0,s1,0
	ecall
	li a0, 0 
	li a7, 93
	ecall

	
