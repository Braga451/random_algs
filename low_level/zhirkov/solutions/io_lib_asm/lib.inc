section .text

;rdi points to string
string_length:
    xor rax, rax
    
    .loop:
      cmp BYTE [rdi + rax], 0
      je .end
      inc rax ; i want to put this before jmp (to avoid extra labels), but, as in intel manual, the inc modifies eflags so...
      jmp .loop
    
    .end:
      ret

print_string:
    xor rax, rax
    call string_length
    mov rdx, rax
    mov rsi, rdi
    mov rdi, 0x1
    mov rax, 0x1
    syscall
    ret

print_char:
    xor rax, rax
    push rdi 
    mov rsi, rsp ; just to have a ptr
    mov rdi, 0x1
    mov rdx, 0x1
    mov rax, 0x1
    syscall
    pop rax
    xor rax, rax
    ret

print_newline:
  mov rdi, 0xA
  call print_char
  ret

; print unsgined int in rdi 
; pretty bad solution imo, but ok
print_uint:
  xor rax, rax
  mov rcx, 0xA
  push 0x0
  .loop:
    mov rax, rdi
    mov rdx, 0x0
    div rcx ; rdx -> reminder | rax quotient
    add rdx, 0x30
    push rdx
    mov rdi, rax
    cmp rdi, 0x0
    je .end_loop
    jmp .loop
    
  .end_loop:
    pop rdi
    cmp rdi, 0x0
    je .end
    call print_char
    jmp .end_loop

  .end:
    ret

print_int:
    xor rax, rax
    cmp rdi, 0x0
    jge .end
    .is_negative:
      push rdi
      mov rdi, '-'
      call print_char
      pop rdi
      neg rdi
      jmp .end
    
    .end:
      call print_uint
      ret

; rdi and rsi => str1 and str2
string_equals:
    push rbx
    push rdi
    mov rdi, rsi
    call string_length
    pop rdi
    mov rcx, rax
    call string_length
    cmp rcx, rax
    jne .not_equal
    
    cmp rcx, 0x0
    je .equal

    xor rcx, rcx

    jmp .loop_comp
    .loop_comp:
      xor rbx, rbx
      mov bl, [rdi + rcx]
      cmp BYTE bl, [rsi + rcx]
      jne .not_equal
      inc rcx
      cmp rcx, rax
      je .equal
      jmp .loop_comp

    .not_equal:
      xor rax, rax
      jmp .end

    .equal:
      mov rax, 0x1
      jmp .end
    
    .end:
      pop rbx
      ret

read_char:
    xor rax, rax
    xor rdi, rdi
    mov rdx, 0x1

    sub rsp, 0x10
    mov rsi, rsp

    syscall
    
    mov rdx, rax
    mov rax, [rsp]
    add rsp, 0x10
    ret 

; rdi points to the buffer
; rsi points to size of buffer
read_word:
    xor rax, rax
    xor rcx, rcx
    .read_loop:
      push rcx
      push rdi
      push rsi
      call read_char
      pop rsi
      pop rdi
      pop rcx
      
      cmp rdx, 0x0
      je .end_string

      cmp rax, 0x20
      je .end_string; .read_loop
      cmp rax, 0x9
      je .end_string; .read_loop
      cmp rax, 0x10
      je .end_string; .read_loop

      mov [rdi + rcx], rax
      inc rcx
      cmp rcx, rsi
      jge .bad_string
      jmp .read_loop
    
    .end_string:
      mov BYTE [rdi + rcx], 0x0
      jmp .end

    .bad_string:
      xor rdi, rdi
      xor rdx, rdx
      jmp .end

    .end:
      mov rax, rdi
      mov rdx, rcx
      ret  

; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
  push rdi
  call string_length
  pop rdi
  mov rcx, rax
  xor rax, rax
  dec rcx ; last non zero char
  mov r10, 0x1 ; To multiply
  mov r11, 0x0 ; The value
  xor rdx, rdx 

  push rdx

  .parse_loop:
    xor rax, rax 
    
    cmp rcx, 0x0
    jl .end

    mov al, [rdi + rcx]
    dec rcx

    sub al, 0x30
    
    cmp al, 0x9
    jg .parse_loop
    cmp al, 0x0
    jl .parse_loop
    
    mul r10
    add r11, rax
    
    pop rdx
    inc rdx
    push rdx

    xor rax, rax
    mov al, 0xA
    mul r10
    mov r10, rax
    jmp .parse_loop
  
  .end:
    mov rax, r11
    pop rdx
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_int:
    xor rax, rax
    push rdi
    call parse_uint
    pop rdi
    cmp BYTE [rdi], '-'
    je .is_neg
    jmp .end

    .is_neg:
      neg rax
      inc rdx
      jmp .end

    .end:
      ret 

; rdi points to string, rsi points to buffer, rdx points to buffer size
string_copy:
    call string_length
    inc rax ; string size + null byte
    cmp rax, rdx
    jne .different_sizes
    mov rcx, rax ; number of bytes to transfer
    xchg rdi, rsi ; swap rdi with rsi
    rep movsb ; copy 'rcx' bytes from rsi to rdi
    ; thanks to https://www.aldeid.com/wiki/X86-assembly/Instructions/movsb
    mov rax, rdi ; copy rdi (the original buffer ptr) ptr to rax
    jmp .end

    .different_sizes:
      xor rax, rax
      jmp .end

    .end:
      ret

