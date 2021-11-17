global runAssemblyCode

extern printf

section .data
    str: db "%d",10,13

section .text
runAssemblyCode:
    push ebp
    mov ebp, esp

    mov eax, [ebp+8]
    mov ecx, [ebp+12]
    xor edx, edx
    xor esi, esi
    xor edi, edi

repeat:
    add edi, [eax + esi*4]
    add edi, [eax + (esi + 1)*4]
    add edi, [eax + (esi + 2)*4]
    add edi, [eax + (esi + 3)*4]
    add esi, 4
    cmp esi, ecx
    jl repeat

    mov eax, edi
    mov esp, ebp
    pop ebp
    ret
