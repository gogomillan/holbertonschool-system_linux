; NASM code style
; Prototype when used in C: size_t asm_strlen(const char *str)
; 	str(argument) -> rdi(register)

	bits 64

	section .text			; Code section
	global asm_strlen		; Exporting the function name

asm_strlen:				; The symbol or function name label
	push rbp			; prologue
	mov rbp, rsp
					; save registers posibly used by the caller
	push rbx			; save rbx value in stack
	push rcx			; save rcx value in stack

	mov rbx, rdi			; copy the argument(str) in rbx register
	mov rcx, 0			; rcx register will be the iterator and starts in 0
	jmp entry_i			; jump into this loop's part for the firt time

iter_i:					; loop iter_i ->  while (*str != '\0')
	inc rcx				; increment the iterator
entry_i:				; this entry point avoid the first time increment
	cmp byte [rbx + rcx ], 0x00	; compare character of iterator position with caracter null
	jne iter_i			; if not null jump loop

end:
	mov rax, rcx			; set the lenght in the return register
					; restore registers for the caller
	pop rcx				; restore rcx register from stack
	pop rbx				; restore rbx register from stack

	mov rsp, rbp			; epilogue
	pop rbp

	ret				; return
