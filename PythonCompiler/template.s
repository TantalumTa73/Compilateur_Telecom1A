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


