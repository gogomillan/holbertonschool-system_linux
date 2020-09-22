; NASM code style
; Prototype when used in C: size_t asm_putc(int c)

	bits 64

	section .text	; Code section
	global asm_putc	; Exporting the function name

asm_putc:
	push rbp		; Setup stack frame
	mov rbp, rsp	; Those two lines are equivalent to 'enter'

	push rdi		; store the arg1 value

	mov rax, 1		; Write syscall
	mov rdi, 1		; write to stdout
	mov rsi, rsp	; Address of the character to be printed (Address of the stack)
	mov rdx, 1		; Write 1 byte
	syscall			; call the syscall

	pop rdi			; set back the previos value
	mov rax, 1		; return value printd

	mov rsp, rbp	; Restore previous stack frame
	pop rbp			; Those two lines are equivalent to 'leave'

	ret				; return
