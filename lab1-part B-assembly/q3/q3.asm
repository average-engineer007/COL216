.data
prompt1 : .asciz "Enter number 1: "
prompt2 : .asciz "Enter number 2: "
prompt3 : .asciz "Enter operation to be performed: "   
nl : .asciz "\n"
.text

.global main

main:
	li s0,10
	li s1,43
	li s2,45 #-
	
	li a7,4
	la a0,prompt1
	ecall
	li a7,8
	li a1,20
	ecall
	li t3,1
	jal ra, strlen    # call the strlen function
	mv s4,a0
	
	
	
	li a7,4
	la a0,prompt2
	ecall
	li a7,8
	li a1,20
	ecall
	li t3,1
	jal ra, strlen    # call the strlen function
	mv s5,a0
	
	li a7,4
	la a0,prompt3
	ecall
	li a7,12
	#li a1,20
	ecall
	mv t1,a0
	li a7,4
	la a0,nl
	ecall

	li t2,42
	beq t1,t2,multiply
	li t2,47
	beq t1,t2,divide
	beq t1,s2,subtract
	beq t1,s1,add_
	
	
multiply:
	mul t6,s4,s5
	addi a0,t6,0
	li a7,1
	ecall
	li a0, 0 
	li a7, 93
	ecall
add_:
	add t6,s4,s5
	addi a0,t6,0
	li a7,1
	ecall
	li a0, 0 
	li a7, 93
	ecall
subtract:
	sub t6,s4,s5
	addi a0,t6,0
	li a7,1
	ecall
	li a0, 0 
	li a7, 93
	ecall
divide:
	div t6,s4,s5
	addi a0,t6,0
	li a7,1
	ecall
	li a0, 0 
	li a7, 93
	ecall
	
	#li a7,1
	#ecall

	
	

	
	

strlen:
    li a1, 0      # initialize counter to zero

strlen_loop:
    lb a2, 0(a0)       # load the byte at the current address
    beq a2,s0, strlen_done   # if the byte is newline character(ascii value 10), exit loop
    beq a2,s1, plus
    beq a2,s2, minus

    addi a2,a2,-48
    mul a1,a1,s0
    addi a0, a0, 1    
    add a1, a1, a2    
    j strlen_loop      
    
plus:
	li t3,1
	addi a0,a0,1
	j strlen_loop
	
minus: 
	li t3,-1
	addi a0,a0,1
	j strlen_loop

strlen_done:
	mul a1,a1,t3
    mv a0, a1          # move the counter to a0 (length of the string)
    jr ra
