extern printf
global main

section .data
    str: db "Clock ticks: %llu", 10, 0

section .text
main:
    push ebp
    mov ebp, esp

    ; 1. call rdtscp. Take into account what registers it changes
    ; Moved 'rdtscp' before initializing 'ecx' to avoid overwriting it
    rdtscp

    ; 2. save the values from 'edx' and 'eax' to other registers
    mov edi, edx
    mov esi, eax

    ; Number of cycles
    mov ecx, 1000 * 1000 * 1000

    ; 3. implement a simple loop using 'loop', then using a jump instruction
repeat:
    mov ebx, 0
    loop repeat
    ;dec ecx
    ;jnz repeat

    ; 4. call rdtscp again
    rdtscp

    ; 5. subtract from 'eax' the former value of 'eax', then from 'edx' the
    ; former value of 'edx'. Use 'sbb' to account for an underflow in 'eax'
    sub eax, esi
    sbb edx, edi

    push edx
    push eax
    push str
    call printf
    add esp, 12

    xor eax, eax
    mov esp, ebp
    pop ebp
    ret
