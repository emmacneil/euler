; Project Euler - Problem 001
; Multiples of 3 and 5
;
; Assembly code for Intel x86-64, 64-bit mode, Linux, with NASM compiler.

global main
extern atoi
extern printf
section .text



; T takes one argument, n, and returns the n-th triangular number, T(n).
; E.g. T(0) = 0, T(1) = 1, T(2) = 3, T(3) = 6, ..., T(100) = 5050, ...
T:
        mov     rax, rdi
        add     rdi, 1
        mul     rdi
        shr     rax, 1
        ret



; f takes two arguments, n and k (in that order) and returns the sum of all positive multiples
; of k that are less than n.
; E.g. f(10, 3)  = 18 = 3 + 6 + 9
;      f(10, 5)  = 5
;      f(10, 15) = 0
; This calculation is performed via the formula f(n, k) = k*T((n - 1)/k).
f:
        push    rbp
        mov     rbp, rsp

        ; Compute (n - 1)/k
        sub     rdi, 1
        xor     rdx, rdx
        mov     rax, rdi
        div     rsi             ; rax <== (n - 1)/k
        
        ; Compute T((n - 1)/k)
        mov     rdi, rax
        call    T               ; rax <== T((n - 1)/k)
        
        mul     rsi             ; rax <== k*T((n - 1)/k)
        
        mov     rsp, rbp
        pop     rbp
        ret



main:
        push    rbp
        mov     rbp, rsp

        ; Assume we are solving the problem for N = 1000
        mov     r12, 1000
        
        ; If a command line argument was given, use that value for N instead.
        cmp     rdi, 2
        jne     L0
        mov     rdi, [rsi+8]
        call    atoi
        mov     r12, rax
L0:
        ; Now compute f(N, 3) + f(N, 5) - f(N, 15), storing result in r13.
        mov     rdi, r12
        mov     rsi, 3
        call    f
        mov     r13, rax        ; r13 = f(N, 3)
        
        mov     rdi, r12
        mov     rsi, 5
        call    f
        add     r13, rax        ; r13 += f(N, 5)
        
        mov     rdi, r12
        mov     rsi, 15
        call    f
        sub     r13, rax        ; r13 -= f(N, 15)
        
        ; Print result of calculation
        mov     rdi, fmt
        mov     rsi, r13
        call    printf

        mov     rax, 0
        mov     rsp, rbp
        pop     rbp
        ret

section .data
fmt     db      "%d", 10, 0
fmtlen  equ     $ - fmt
