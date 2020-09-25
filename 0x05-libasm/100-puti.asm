; NASM code style
; Prototype when used in C: size_t asm_puti(int n)

	bits 64

	section .data			; Variables
	str_num db 'abcdefghij', 0
	arg1 dd 0
	neg_num dd 0
	c_rcx dd 0
	c_rcxx dd 0

	section .text			; Code section
        global asm_puti			; Exporting the function name
	extern asm_putc			; Importing function

asm_puti:
       	push rbp			; Prologue
	mov rbp, rsp

	push r11
	push rdx
	push rcx
	push rdi

	mov rcx, 0
	mov [arg1], rdi
	cmp dword [arg1], 0
	jl set_neg
	je print_1

set_count:
	mov rcx, 0

get_dig:
	cmp dword [arg1], 0
	je print_num

	mov rdi, 10
	mov rdx, 0
	mov rax, 0
	mov eax, [arg1]
	div rdi
	mov [arg1], eax

	mov rdi, 0
	mov rdi, rdx
	add rdi, 48

	mov r12, str_num
	add r12, rcx
	mov [r12], dil

	inc rcx
	inc dword [neg_num]
	jmp get_dig

print_num:
	mov [c_rcx], ecx
	dec rcx
	mov [c_rcxx], ecx

print_loop:
	cmp dword [c_rcx], 0
	je ret_val

	mov r12, 0
        mov rdi, 0
        mov r12, str_num
	add r12d, [c_rcxx]
	mov dil, byte [r12]
        call asm_putc

        dec dword [c_rcx]
	dec dword [c_rcxx]

        jmp print_loop

ret_val:
	mov rax, 0
	mov rax, qword [neg_num]

end_func:				; Restore the registers
	pop rdi
	pop rcx
	pop rdx
	pop r11

	mov rsp, rbp			; Epilogue
	pop rbp

        ret				; Return

set_neg:				; Sub-rutine set_neg
	mov rdi, 45
	call asm_putc
	inc dword [neg_num]

	mov rax, 0
	mov eax, [arg1]
	neg eax
	mov [arg1], eax

	jmp set_count

print_1:				; Sub-rutine for printing
	mov rdi, 48
	call asm_putc
	jmp end_func
