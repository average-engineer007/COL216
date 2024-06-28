.data
prompt1: .asciz "Enter the value of n: "
prompt2: .asciz "Enter the value of acc: "
prompt3: .asciz "\nans: "
prompt4: .asciz "\ncycles: "
nl: .asciz "\n"
.text
.global main

main:
	li a7,4
	la a0,prompt1
	ecall 
	li a7,5
	ecall
	mv s1,a0
	
	li a7,4
	la a0,prompt2
	ecall 
	li a7,5
	ecall
	mv s2,a0
	# s1 has n and s2 has acc
	
	mv a0,s2
	mv a1,s1
	rdcycle s8
	jal sum_tail
	rdcycle s9
	mv s6,a0
	sub s9,s9,s8
	li a7,4
	la a0,prompt3
	ecall 
	mv a0,s6
	li a7,1
	ecall
	li a7,4
	la a0,prompt4
	ecall 
	mv a0,s9
	li a7,1
	ecall
	
	
	mv a0,s2
	mv a1,s1
	rdcycle s8
	jal sum_rec
	rdcycle s9
	mv s6,a0
	sub s9,s9,s8
	li a7,4
	la a0,prompt3
	ecall 
	mv a0,s6
	li a7,1
	ecall
	li a7,4
	la a0,prompt4
	ecall 
	mv a0,s9
	li a7,1
	ecall
	
	
	mv a0,s2
	mv a1,s1
	rdcycle s8
	jal sum_iter
	rdcycle s9
	mv s6,a0
	sub s9,s9,s8
	li a7,4
	la a0,prompt3
	ecall 
	mv a0,s6
	li a7,1
	ecall
	li a7,4
	la a0,prompt4
	ecall 
	mv a0,s9
	li a7,1
	ecall
	
	
	
	
	
	
	
	

	

	
success:
	li a7,93
	li a0,0
	ecall
	
sum_tail:
	bne a1,zero,rec_tail
	jr ra
rec_tail:
	add a0,a0,a1
	addi a1,a1,-1
	j sum_tail
	
	
	
	
sum_rec:
	addi sp,sp,-16
	sd ra,0(sp)
	sd a1,8(sp)
	#addi a1,a1,-1
	bne a1,zero,rec
	addi sp,sp,16
	jr ra
rec:
	addi a1,a1,-1
	jal sum_rec
	ld t0,8(sp)
	ld ra,0(sp)
	add a0,a0,t0
	addi sp,sp,16
	jr ra
		
sum_iter:	#acc will be in a0 and n will be in a1
	li t0,0
	j loop
loop:
	addi t0,t0,1
	add a0,a0,t0
	bne t0,a1,loop
	jr ra

