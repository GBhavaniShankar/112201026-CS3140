
	.file	1 "sample2.sil"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module fp=32
	.module nooddspreg
	.abicalls
	.text
# MIPS code for variable declarations
	.globl	array
	.section		.bss,"aw",@nobits
	.align	2
	.type	array, @object
	.size	array, 20
array:
	.space	20
	.globl	filter
	.align	2
	.type	filter, @object
	.size	filter, 12
filter:
	.space	12
	.globl	convolution
	.align	2
	.type	convolution, @object
	.size	convolution, 12
convolution:
	.space	12
	.globl	sum
	.align	2
	.type	sum, @object
	.size	sum, 4
sum:
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
	# MIPS code for ASSIGNMENT
	li $2, -1
	move $12, $2
	li $2, 0
	sll $2, $2, 2
	la $10, filter
	add $10, $10, $2
	sw $12, 0($10)
	# MIPS code for ASSIGNMENT
	li $2, 0
	move $12, $2
	li $2, 1
	sll $2, $2, 2
	la $10, filter
	add $10, $10, $2
	sw $12, 0($10)
	# MIPS code for ASSIGNMENT
	li $2, 1
	move $12, $2
	li $2, 2
	sll $2, $2, 2
	la $10, filter
	add $10, $10, $2
	sw $12, 0($10)
# MIPS code for READ
	la $4, $LC0
	li $2, 0
	sll $8, $2, 2
	la $9, array
	addu $5, $9, $8
	jal __isoc99_scanf
# MIPS code for READ
	la $4, $LC0
	li $2, 1
	sll $8, $2, 2
	la $9, array
	addu $5, $9, $8
	jal __isoc99_scanf
# MIPS code for READ
	la $4, $LC0
	li $2, 2
	sll $8, $2, 2
	la $9, array
	addu $5, $9, $8
	jal __isoc99_scanf
# MIPS code for READ
	la $4, $LC0
	li $2, 3
	sll $8, $2, 2
	la $9, array
	addu $5, $9, $8
	jal __isoc99_scanf
# MIPS code for READ
	la $4, $LC0
	li $2, 4
	sll $8, $2, 2
	la $9, array
	addu $5, $9, $8
	jal __isoc99_scanf
	# MIPS code for ASSIGNMENT
	# Compute index for array access: array[i]
	li $2, 0
	sll $2, $2, 2
	la $10, array
	add $10, $10, $2
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 0
	sll $2, $2, 2
	la $10, filter
	add $10, $10, $2
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	mul $2, $3, $2
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 1
	sll $2, $2, 2
	la $10, array
	add $10, $10, $2
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 1
	sll $2, $2, 2
	la $10, filter
	add $10, $10, $2
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	mul $2, $3, $2
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	addu $2, $3, $2
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 2
	sll $2, $2, 2
	la $10, array
	add $10, $10, $2
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 2
	sll $2, $2, 2
	la $10, filter
	add $10, $10, $2
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	mul $2, $3, $2
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	addu $2, $3, $2
	move $12, $2
	li $2, 0
	sll $2, $2, 2
	la $10, convolution
	add $10, $10, $2
	sw $12, 0($10)
	# MIPS code for ASSIGNMENT
	# Compute index for array access: array[i]
	li $2, 1
	sll $2, $2, 2
	la $10, array
	add $10, $10, $2
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 0
	sll $2, $2, 2
	la $10, filter
	add $10, $10, $2
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	mul $2, $3, $2
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 2
	sll $2, $2, 2
	la $10, array
	add $10, $10, $2
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 1
	sll $2, $2, 2
	la $10, filter
	add $10, $10, $2
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	mul $2, $3, $2
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	addu $2, $3, $2
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 3
	sll $2, $2, 2
	la $10, array
	add $10, $10, $2
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 2
	sll $2, $2, 2
	la $10, filter
	add $10, $10, $2
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	mul $2, $3, $2
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	addu $2, $3, $2
	move $12, $2
	li $2, 1
	sll $2, $2, 2
	la $10, convolution
	add $10, $10, $2
	sw $12, 0($10)
	# MIPS code for ASSIGNMENT
	# Compute index for array access: array[i]
	li $2, 2
	sll $2, $2, 2
	la $10, array
	add $10, $10, $2
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 0
	sll $2, $2, 2
	la $10, filter
	add $10, $10, $2
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	mul $2, $3, $2
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 3
	sll $2, $2, 2
	la $10, array
	add $10, $10, $2
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 1
	sll $2, $2, 2
	la $10, filter
	add $10, $10, $2
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	mul $2, $3, $2
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	addu $2, $3, $2
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 4
	sll $2, $2, 2
	la $10, array
	add $10, $10, $2
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 2
	sll $2, $2, 2
	la $10, filter
	add $10, $10, $2
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	mul $2, $3, $2
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	addu $2, $3, $2
	move $12, $2
	li $2, 2
	sll $2, $2, 2
	la $10, convolution
	add $10, $10, $2
	sw $12, 0($10)
	# MIPS code for ASSIGNMENT
	# Compute index for array access: array[i]
	li $2, 0
	sll $2, $2, 2
	la $10, convolution
	add $10, $10, $2
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 1
	sll $2, $2, 2
	la $10, convolution
	add $10, $10, $2
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	addu $2, $3, $2
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	# Compute index for array access: array[i]
	li $2, 2
	sll $2, $2, 2
	la $10, convolution
	add $10, $10, $2
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	addu $2, $3, $2
	la $10, sum
	sw $2, 0($10)
# MIPS code for WRITE
	la $4, $LC1
	# Compute index for array access: array[i]
	li $2, 0
	sll $2, $2, 2
	la $10, convolution
	add $10, $10, $2
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	la $10, sum
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	div $3, $2
	mflo $2
	move $5, $2
	jal printf
# MIPS code for WRITE
	la $4, $LC1
	# Compute index for array access: array[i]
	li $2, 1
	sll $2, $2, 2
	la $10, convolution
	add $10, $10, $2
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	la $10, sum
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	div $3, $2
	mflo $2
	move $5, $2
	jal printf
# MIPS code for WRITE
	la $4, $LC1
	# Compute index for array access: array[i]
	li $2, 2
	sll $2, $2, 2
	la $10, convolution
	add $10, $10, $2
	lw $2, 0($10)
	addiu $sp, $sp, -4
	sw $2, 0($sp)
	la $10, sum
	lw $2, 0($10)
	lw $3, 0($sp)
	addiu $sp, $sp, 4
	div $3, $2
	mflo $2
	move $5, $2
	jal printf
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