
.data
.code
PUBLIC Close
Close PROC
    ; Params:
    ; RCX = imageBase
    ; RDX = ExitThreadAddr
    ; R8  = VirtualFreeAddr
 
    ; Allocate shadow space and align stack
    sub rsp, 28h
    ;i dont actually know how much i should align it here, but 28h (40) is aligned to 16h(10) and works
    ;if anyone proficient enough could explain - would be great.
    
    mov [rsp+20h], rdx         ; save ExitThreadAddr on stack
    mov [rsp+18h], r8          ; save virtualFreeAddr on stack
    
    ; Set up the parameters for VirtualFree
    ;rcx was untouched so it still contains imageBase
    mov rdx, 0                 ;rdx dwSize (2nd parameter)
    mov r8, 8000h            ;r8 dwFreeType (3rd parameter)
    
    ;stack now
    ;+18 - virtualFreeAddr
    ;+20 - exitThreadAddr
    
  
    mov rax, [rsp+18h]; ; [rsp+18h] contains virtualfreeaddr on stack now, move it to rax  
    push qword ptr[rsp+20h]; push ExitThreadAddr to TOP of the stack (so it would be ret address for VirtualFree)
 
    ;top of stack = ExitThreadAddr
    ;params for VirtualFree:
    ;rcx - ImageBase
    ;rdx - 0 (dwSize)
    ;r8 - 8000h (MEM_RELEASE)
 
    jmp rax;rax = virtualFreeAddr
Close ENDP
END