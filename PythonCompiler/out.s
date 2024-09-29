	.data
int_fmt:
	.string "%d\n"

	.text
	.globl main
main:
	push %rbp
	mov %rsp, %rbp
	
	# get argument, variable a
	mov 16(%rbp), %rax
	mov %rax, -8(%rbp)
	sub $8, %rsp
	
	# space for var b
	sub $8, %rsp
	
	# constant
	push $6
	
	# varset b
	pop -16(%rbp)
	
	# variable expr
	push -16(%rbp)
	
	# printf
	pop %rsi
	lea int_fmt(%rip), %rdi
	mov $0, %rax
	call printf
	xor %rax, %rax
	
	# constant
	push $6
	
	# constant
	push $7
	
	# mult
	pop %rax
	pop %rbx
	imul %rax, %rbx
	push %rbx
	
	# varset b
	pop -16(%rbp)
	
	# variable expr
	push -16(%rbp)
	
	# printf
	pop %rsi
	lea int_fmt(%rip), %rdi
	mov $0, %rax
	call printf
	xor %rax, %rax
	
	# constant
	push $7
	
	# constant
	push $14
	
	# division
	pop %rax
	pop %rbx
	xor %rdx, %rdx
	idivq %rbx
	mov %rax, %rbx
	push %rbx
	
	# varset b
	pop -16(%rbp)
	
	# variable expr
	push -16(%rbp)
	
	# printf
	pop %rsi
	lea int_fmt(%rip), %rdi
	mov $0, %rax
	call printf
	xor %rax, %rax
	
	# constant
	push $3
	
	# uminus
	pop %rax
	neg %rax
	push %rax
	
	# constant
	push $15
	
	# division
	pop %rax
	pop %rbx
	xor %rdx, %rdx
	idivq %rbx
	mov %rax, %rbx
	push %rbx
	
	# varset b
	pop -16(%rbp)
	
	# variable expr
	push -16(%rbp)
	
	# printf
	pop %rsi
	lea int_fmt(%rip), %rdi
	mov $0, %rax
	call printf
	xor %rax, %rax
	
	# constant
	push $1
	
	# constant
	push $3
	
	# constant
	push $3
	
	# division
	pop %rax
	pop %rbx
	xor %rdx, %rdx
	idivq %rbx
	mov %rax, %rbx
	push %rbx
	
	# constant
	push $2
	
	# constant
	push $7
	
	# plus
	pop %rax
	pop %rbx
	add %rax, %rbx
	push %rbx
	
	# constant
	push $5
	
	# mult
	pop %rax
	pop %rbx
	imul %rax, %rbx
	push %rbx
	
	# plus
	pop %rax
	pop %rbx
	add %rax, %rbx
	push %rbx
	
	# plus
	pop %rax
	pop %rbx
	add %rax, %rbx
	push %rbx
	
	# varset b
	pop -16(%rbp)
	
	# variable expr
	push -16(%rbp)
	
	# printf
	pop %rsi
	lea int_fmt(%rip), %rdi
	mov $0, %rax
	call printf
	xor %rax, %rax
	
	# just in case final return
	mov $0, %rax
	# removing all local variable
	add $16, %rsp
	mov %rbp, %rsp
	pop %rbp
	ret
	
