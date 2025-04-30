
	.file	1 "c.sil"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module fp=32
	.module nooddspreg
	.abicalls
	.text
# MIPS code for variable declarations
	.globl	arr
	.section		.bss,"aw",@nobits
	.align	2
	.type	arr, @object
	.size	arr, 64
arr:
	.space	64
	.globl	len
	.align	2
	.type	len, @object
	.size	len, 4
len:
	.space	4
	.globl	i
	.align	2
	.type	i, @object
	.size	i, 4
i:
	.space	4
	.rdata
	.align	2
$LC0:
	.ascii	"%d\000"
	.align	2
$LC1:
	.ascii	"%d\n\000"
	.text
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,32,$31		# vars= 0, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	.cprestore	16
# MIPS code for READ
	la $4, $LC0
	la $5, len
	jal __isoc99_scanf
# MIPS code for FOR_STMT
	# MIPS code for ASSIGNMENT
	li $2, 0
	la $10, i
	sw $2, 0($10)
FOR_START_0:
	la $10, i
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	la $10, len
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	slt $2, $3, $2
	beqz $2, FOR_END_0
# MIPS code for READ
	la $4, $LC0
	la $10, i
	lw $2, 0($10)
	sll $8, $2, 2
	la $9, arr
	addu $5, $9, $8
	jal __isoc99_scanf
	# MIPS code for ASSIGNMENT
	la $10, i
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	li $2, 1
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	addu $2, $3, $2
	la $10, i
	sw $2, 0($10)
	j FOR_START_0
FOR_END_0:
# MIPS code for FOR_STMT
	# MIPS code for ASSIGNMENT
	li $2, 0
	la $10, i
	sw $2, 0($10)
FOR_START_1:
	la $10, i
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	la $10, len
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	li $2, 2
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	div $3, $2
	mflo $2
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	slt $2, $3, $2
	beqz $2, FOR_END_1
	# MIPS code for ASSIGNMENT
	# Compute index for array access: array[i]
	la $10, len
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	la $10, i
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	subu $2, $3, $2
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	li $2, 1
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	subu $2, $3, $2
	sll $2, $2, 2
	la $10, arr
	add $10, $10, $2
	lw $2, 0($10)
	move $12, $2
	la $10, i
	lw $2, 0($10)
	sll $2, $2, 2
	la $10, arr
	add $10, $10, $2
	sw $12, 0($10)
	# MIPS code for ASSIGNMENT
	la $10, i
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	li $2, 1
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	addu $2, $3, $2
	la $10, i
	sw $2, 0($10)
	j FOR_START_1
FOR_END_1:
# MIPS code for FOR_STMT
	# MIPS code for ASSIGNMENT
	li $2, 0
	la $10, i
	sw $2, 0($10)
FOR_START_2:
	la $10, i
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	la $10, len
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	slt $2, $3, $2
	beqz $2, FOR_END_2
# MIPS code for WRITE
	la $4, $LC1
	la $10, i
	lw $2, 0($10)
	sll $8, $2, 2
	la $9, arr
	addu $9, $9, $8
	lw $5, 0($9)
	jal printf
	# MIPS code for ASSIGNMENT
	la $10, i
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	li $2, 1
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	addu $2, $3, $2
	la $10, i
	sw $2, 0($10)
	j FOR_START_2
FOR_END_2:
	move $2, $0
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	j	$31
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 10.3.0-1ubuntu1) 10.3.0"
	.section	.note.GNU-stack,"",@progbits