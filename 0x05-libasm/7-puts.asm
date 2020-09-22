; NASM code style
; Prototype when used in C: size_t asm_puts(const char *str)

	bits 64

	section .data
	str_c dq 0			; Variable to store the arg1

	section .text		; Code section
	global asm_puts		; Exporting the function name
	extern asm_strlen	; Import the function using the symbol

asm_puts:
	push rbp			; Setup stack frame
	mov rbp, rsp		; Those two lines are equivalent to 'enter'

	push rbx			; save rbx value
	mov [str_c], rdi	; store the arg1 value

	mov rax, 0			; set 0 the return value
	call asm_strlen		; call the function asm_strlen
	mov rbx, rax		; save the return value

	mov rax, 1			; Write syscall
	mov rdi, 1			; write to stdout
	mov rsi, [str_c]	; Address of the character to be printed (Address of the stack)
	mov rdx, rbx		; Write strlen bytes
	syscall				; call the syscall (Write)

	mov rax, rbx		; return value printed

	pop rbx				; set back the previos value
	mov rsp, rbp		; Restore previous stack frame
	pop rbp				; Those two lines are equivalent to 'leave'

	ret					; return
