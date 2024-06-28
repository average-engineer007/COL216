.global main
.data
prompt1 : .asciz "Name : Mohit Dua\n "
newline : .asciz"\n"

.text

main:
	li a7,5
	ecall
	mv t0,a0
	
	#li a7,1
	#add a0,t0,zero
	#ecall
	li s1,0
	li s2,1
	li t1,1
	
loop:
	addi t1, t1, 1
	add s3,s1,s2
	addi s1,s2,0
	addi s2,s3,0
	
	bne t1, t0, loop
	bne t1, zero, success
failure:
	li a0, 0
	li a7, 93 
	ecall
	
success:
	li a7,1
	addi a0,s3,0
	ecall
	li a0, 42 
	li a7, 93
	ecall