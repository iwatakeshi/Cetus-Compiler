.text

.globl proc
proc:
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl 8(%ebp)
	subl $4, %esp
	pushl -16(%ebp)
	popl %eax
	addl $8, %esp
	popl %edi
	popl %esi
	popl %ebx
	leave
	ret
.globl _Main
_Main:
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	pushl %esi
	pushl %edi
	subl $8, %esp
	movl $20, %ebx
	movl %ebp, %eax
	subl %ebx, %eax
	pushl %eax
	pushl $15
	popl %ebx
	popl %eax
	movl %ebx, (%eax)
	movl $16, %ebx
	movl %ebp, %eax
	subl %ebx, %eax
	pushl %eax
	pushl %ecx
	pushl %edx
	pushl -20(%ebp)
	call proc
	addl $4, %esp
	popl %edx
	popl %ecx
	popl %ebx
	movl %eax, (%ebx)
	pushl -16(%ebp)
	popl %eax
	addl $8, %esp
	popl %edi
	popl %esi
	popl %ebx
	leave
	ret
