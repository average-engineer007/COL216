.data
newline: .asciz "\n "
prompt1 : .asciz "M"

.text
.global main
main: 
	#allocate space for the input string 
	addi sp,sp,-11
	li a7,8
	mv a0,sp
	li a1,11
	ecall
	
	li a7,4
	la a0,newline
	ecall

	
	lb a0, 0(sp)   # Load the first byte (character) from the string
	li a7, 11
    	ecall
    	li a7, 4
	la a0,prompt1
	ecall

    	
	li a0,0
	li a7,93
	ecall