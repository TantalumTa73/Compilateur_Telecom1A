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
        
        # set space for an intern variable    
        sub $8, %rsp            
    
        # Align the stack for printf
        mov %rsp, %rax           
        and $15, %rax            
        jnz .align_stack_scanf         
    
.call_scanf:
        # Load the format string into rdi (first argument for printf)
        # pushq $0
        movq $0, %rax             
        leaq (%rsp), %rsi
        leaq int_fmt_scan(%rip), %rdi  
    
        # Call printf
        call scanf
        
        # save value in rax
        mov (%rsp), %rax 

        # Epilogue
        mov %rbp, %rsp
        popq %rbp                   
        ret                      

.align_stack_scanf:
        sub $8, %rsp       
        jmp .call_scanf



	.bss
	.align 8
	.type u, @object
	.size u, 8
u:
	.zero 8
	.align 8
	.type v, @object
	.size v, 8
v:
	.zero 8

	.text
main:
	push %rbp
	mov %rsp, %rbp
	
	# get argument, variable amain
	mov 16(%rbp), %rax
	mov %rax, -8(%rbp)
	sub $8, %rsp
	
	# constant
	push $5
	
	# varset of var umain
	pop %rax
	mov %rax, u(%rip)
	
	# constant
	push $7
	
	# varset of var vmain
	pop %rax
	mov %rax, v(%rip)
	
	# variable expr glob u
	push u(%rip)
	
	# print value
	call print
	
	# just in case final return
	mov $0, %rax
	mov %rbp, %rsp
	pop %rbp
	ret
	
