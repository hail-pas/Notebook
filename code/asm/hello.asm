; ----------------------------------------------------------------------------------------
; Writes "Hello, World" to the console using only system calls. Runs on 64-bit Linux only.
; To assemble and run:
;
;     nasm -felf64 hello.asm && ld hello.o && ./a.out
; ----------------------------------------------------------------------------------------

          global    _start

          section   .text
_start:   mov       rax, 1                  ; system call for write， sys_write = 1 => size_t sys_write(unsigned int fd, const char * buf, size_t count);
          mov       rdi, 1                  ; file handle 1 is stdout = 1
          mov       rsi, message            ; address of string to output
          mov       rdx, 12
          syscall                           ; invoke operating system to do the write
          mov       rax, 60                 ; system call for exit
          xor       rdi, rdi                ; exit code 0
          syscall                           ; invoke operating system to exit

          section   .data
message:  db        "hello, word",10,0      ; note the newline at the end
