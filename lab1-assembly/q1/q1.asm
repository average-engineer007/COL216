.data
prompt1 : .asciz "Name : Mohit Dua\n "
prompt2 : .asciz "Entry Number : 2022CS51745"

.text
.global main
main: 
	#allocate space for the input string 
	#addi sp sp 63
	li a7,4
	la a0,prompt1
	ecall

	li a7,4
	la a0,prompt2
	ecall
	li a0,0
	li a7,93
	ecall
