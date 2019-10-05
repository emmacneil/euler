; Project Euler - Problem 001
; Multiples of 3 and 5
;
; Assembly code for Intel x86-64, 64-bit mode, Linux, with NASM compiler.

global main
extern atoi
section .text

; T returns the n-th triangular number, T(n) = n(n+1)/2
T:
; f returns the sum of all multiples of k less than n.
; this is f(n, k) = k*T(n/k)
f:
        push    rbp
        mov     rbp, rsp
        mov     rsp, rbp
        pop     rbp
        ret

main:
        push    rbp
        mov     rbp, rsp

        mov     r12, 1000
        ; argc is in rdi, argv in rsi
        
        ; If there are two command line arguments, get the second one.
        ; convert it to an integer, store it in r12
        cmp     rdi, 2
        jne     L0
        mov     rdi, [rsi+8]
        call    atoi
        mov     r12, rax
L0:

        mov     rax, 0
        mov     rsp, rbp
        pop     rbp
        ret

