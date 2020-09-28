; NASM code style
; Prototype when used in C: size_t asm_puti_base(int n, const char *base);
;	n(argument) -> rdi(register)
;	base(argument) -> rsi(register)

	bits 64

	section .data		; Data section, initialized variables
fmt_d:	db "%d", 0		; The printf format, "\n",'0'
fmt_px:	db "%x", 0		; The printf format, "\n",'0'
fmt_nx:	db "-%x", 0		; The printf format, "\n",'0'

	section .text
	global asm_puti_base
	extern printf		; the C function, to be called
	extern asm_strlen	; my own strlen function

asm_puti_base:
	push rbp		; prolog
	mov rbp, rsp

	push r8			; save r8 value in stack

	mov r8, rdi		; get the first argument

	mov rdi, rsi		; set the base as parameter for strlen
	xor rax, rax		; clean the return register
	call asm_strlen		; call my function

	cmp rax, 10		; according to the strlen return
	je set_fmt_d		; sub-routone if is decimal
	cmp rax, 16		; according to the strlen return
	je set_fmt_x		; sub-routine if is exadecimal
	mov rdi, fmt_d		; set the format for the printf by default

print_f:
	mov rsi, r8		; set the value to print
	xor rax, rax		; clean the return register
	call printf		; call C function

	pop r8			; restore r8 from stack

	mov rsp, rbp		; epilogue
	pop rbp

	mov rax, 0		; normal, no error, return value
	ret

set_fmt_d:
	mov rdi, fmt_d		; set the format for the printf
	jmp print_f

set_fmt_x:
	mov rax, r8		; the value
	test eax, eax		; check sign
	js set_fmt_nx
	mov rdi, fmt_px		; set the format for the printf
	jmp print_f

set_fmt_nx:
	mov rdi, fmt_nx		; set the format for the printf
	jmp print_f
