global _start

extern print

section .data

message: db  "Heell",0xa,0

section .text

_start:
        mov rdi, message
		call print

		mov rax, 60
		mov rdi, 0
		syscall
