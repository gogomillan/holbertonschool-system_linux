; NASM code style
; Prototype when used in C: int asm_strcmp(const char *s1, const char *s2)
;	s1(argument) -> rdi(register)
;	s2(argument) -> rsi(register)

	bits 64

	section .text			; Code section
	global asm_strcmp		; Exporting the function name

asm_strcmp:				; The symbol or function label
	push rbp			; prologue
	mov rbp, rsp
					; save registers posibly used by the caller
	push rbx			; save rbx value in stack
	push rcx			; save rcx value in stack
	push rdx			; save rdx value in stack
	push r8				; save r8 value in stack

	mov rbx, rdi			; copy the argument(s1) to rbx register
	mov rcx, rsi			; copy the argument(s2) to rcx register
	mov rdx, 0			; rdx register will be the iterator and starts in 0
	jmp entry_i			; jump into this loop's part for the firt time

iter_i:					; for statement
	inc rdx				; increment the iterator
entry_i:				; this entry point avoid the first time increment
	mov r8b, byte [rcx + rdx]	; check if the char in s1
	cmp r8b, byte 0x00		; is not a null char
	je finally_i			; if it is go out of for loop
	mov r8b, byte [rbx + rdx]	; check if the char in s2
	cmp r8b, byte 0x00		; is not a null char
	je finally_i			; if it is go out of for loop
	cmp r8b, byte [rcx + rdx]	; check if char in s1 is eql to char in s2
	je iter_i			; if it is, continue in the for loop

finally_i:				; finally lopp
	mov rax, 0			; set the return value to 0
	push qword [rbx + rdx]		; push the last char s1 compared before on stack
	push qword [rcx + rdx]		; push the last char s2 compared before on stack
	mov rbx, 0			; set the reg to 0
	mov rcx, 0			; set the reg to 0
	mov bl, byte [rsp + 8]		; set the last char value s1 in a variable
	mov cl, byte [rsp]		; set the last char value s2 in a variable
	cmp rbx, rcx			; compare the previous variables
	je ret_eq			; if are the same set return value to 0
	jl ret_lt			; if rbx is less than rcx set the return value to -1
	jg ret_gt			; if rbx is greater than rcx set the return value to 1

ret_eq:					; set the return value to 0
	mov rax, 0
	jmp end_func			; jump to the end

ret_lt:					; set the return value to -1
	mov rax, -1
	jmp end_func			; jump to the end

ret_gt:					; set the return value to 1
	mov rax, 1
	jmp end_func			; jump to the end

end_func:
					; restore registers for the caller
	pop r8				; restore r8 from stack
	pop rdx				; restore rdx from stack
	pop rcx				; restore rcx from stack
	pop rbx				; restore rbx from stack

	mov rsp, rbp			; epilogue
	pop rbp

	ret				; return the cmp value
