.section .data
int_fmt:
    .string "%d\n"           # Format string for printing integers
int_fmt_scan:
    .string "%d"

.section .text
.globl print
.extern printf               # Declare printf as an external function
.globl main

print:
        # Prologue
        push %rbp                
        mov %rsp, %rbp           
        
        # Pop the last element from the stack into rsi (argument for printf)
        mov 16(%rbp), %rsi                 
    
        # Align the stack for printf
        mov %rsp, %rax           
        and $15, %rax            
        jnz .align_stack_printf         
    
.call_printf:
        # Load the format string into rdi (first argument for printf)
        lea int_fmt(%rip), %rdi  
        mov $0, %rax             
    
        # Call printf
        call printf              

        # Epilogue
        mov %rbp, %rsp
        pop %rbp                   
        ret                      

.align_stack_printf:
        sub $8, %rsp       
        jmp .call_printf


scan:
        # Prologue
        push %rbp                
        mov %rsp, %rbp           
        
        # Pop the last element from the stack into rsi (argument for printf)
        ; mov 16(%rbp), %rsi     
        sub $8, %rsp            
    
        # Align the stack for printf
        mov %rsp, %rax           
        and $15, %rax            
        jnz .align_stack_scanf         
    
.call_scanf:
        # Load the format string into rdi (first argument for printf)
        leaq 8(%rsp), %rsi
        leaq int_fmt_scan(%rip), %rdi  
        movq $0, %rax             
    
        # Call printf
        call scanf
        
        mov 8(%rsp), %rax 

        # Epilogue
        mov %rbp, %rsp
        popq %rbp                   
        ret                      

.align_stack_scanf:
        sub $8, %rsp       
        jmp .call_scanf



	.bss
u: .quad

	.text
g:
	push %rbp
	mov %rsp, %rbp
	
	# get argument, variable bg
	mov 16(%rbp), %rax
	mov %rax, -8(%rbp)
	sub $8, %rsp
	
	# variable expr bg
	push -8(%rbp)
	
	# constant
	push $1
	
	# plus
	pop %rbx
	pop %rax
	add %rax, %rbx
	push %rbx
	
	# return
	pop %rax
	
	mov %rbp, %rsp
	pop %rbp
	ret
	
	# just in case final return
	mov $0, %rax
	mov %rbp, %rsp
	pop %rbp
	ret
	
f:
	push %rbp
	mov %rsp, %rbp
	
	# get argument, variable bf
	mov 16(%rbp), %rax
	mov %rax, -8(%rbp)
	sub $8, %rsp
	
	# constant
	push $2
	
	# variable expr bf
	push -8(%rbp)
	
	push %rax
	call g
	add $8, %rsp
	push %rax
	
	# mult
	pop %rbx
	pop %rax
	imul %rax, %rbx
	push %rbx
	
	# return
	pop %rax
	
	mov %rbp, %rsp
	pop %rbp
	ret
	
	# just in case final return
	mov $0, %rax
	mov %rbp, %rsp
	pop %rbp
	ret
	
h:
	push %rbp
	mov %rsp, %rbp
	
	# get argument, variable vh
	mov 16(%rbp), %rax
	mov %rax, -8(%rbp)
	sub $8, %rsp
	
	# space for var bh
	sub $8, %rsp
	
	# constant
	push $12
	
	# varset of var bh
	pop -16(%rbp)
	
	# variable expr bh
	push -16(%rbp)
	
	# print value
	call print
	
	# constant
	push $5
	
	# varset of var vh
	pop -8(%rbp)
	
	# variable expr vh
	push -8(%rbp)
	
	# print value
	call print
	
	# variable expr vh
	push -8(%rbp)
	
	# return
	pop %rax
	
	mov %rbp, %rsp
	pop %rbp
	ret
	
	# just in case final return
	mov $0, %rax
	mov %rbp, %rsp
	pop %rbp
	ret
	
main:
	push %rbp
	mov %rsp, %rbp
	
	# get argument, variable amain
	mov 16(%rbp), %rax
	mov %rax, -8(%rbp)
	sub $8, %rsp
	
	# constant
	push $18
	
	# varset of var umain
	pop %rax
	mov %rax, u(%rip)
	
	# constant
	push $0
	
	# varset of var amain
	pop -8(%rbp)
	
	# variable expr amain
	push -8(%rbp)
	
	# print value
	call print
	
	# variable expr glob u
	push u(%rip)
	
	# print value
	call print
	
	# space for var bmain
	sub $8, %rsp
	
	# constant
	push $42
	
	# varset of var bmain
	pop -16(%rbp)
	
	# variable expr amain
	push -8(%rbp)
	
	# function call, no varset
	call h
	add $8, %rsp
	
	# variable expr bmain
	push -16(%rbp)
	
	# print value
	call print
	
	# constant
	push $2
	
	push %rax
	call f
	add $8, %rsp
	push %rax
	
	# varset of var umain
	pop %rax
	mov %rax, u(%rip)
	
	# variable expr glob u
	push u(%rip)
	
	# print value
	call print
	
	# just in case final return
	mov $0, %rax
	mov %rbp, %rsp
	pop %rbp
	ret
	
