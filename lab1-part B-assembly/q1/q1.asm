
.data
prompt1: .asciz "Enter the value of n: "
prompt2: .asciz "Enter the value of r: "
.global main
.text
main:
	li a7,4
	la a0,prompt1
	ecall
	li a7,5
	ecall
	mv s1,a0
	#s1 has n
	
	li a7,4
	la a0,prompt2
	ecall
	li a7,5
	ecall
	mv s2,a0
	#s2 has r
	
	mv a0,s1
	jal fact
	mv s5,a0
	#s5 has n!

	mv a0,s2
	jal fact
	mv s6,a0
	#s6 has r!
	
	sub a0,s1,s2
	jal fact
	mv s7,a0
	#s7 has n-r!
	div s5,s5,s6
	div s5,s5,s7
	mv a0,s5
	li a7,1
	ecall
	
success:
	li a7,93
	li a0,0
	ecall
fact:
	addi sp,sp,-16
	sd ra,0(sp)
	sd a0,8(sp)
	addi a0,a0,-1
	bge a0,zero,next
	li a0,1
	addi sp,sp,16
	jr ra
next:
	jal fact
	ld t0,8(sp)
	ld ra,0(sp)
	mul a0,a0,t0
	addi sp,sp,16
	jr ra
	
