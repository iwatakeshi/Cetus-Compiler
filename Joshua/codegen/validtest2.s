.text

.globl _Main
_Main:
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	pushl %esi
	pushl %edi
	subl $4, %esp
	movl $16, %ebx
	movl %ebp, %eax
	subl %ebx, %eax
	pushl %eax
	pushl $2
	popl %ebx
	popl %eax
	movl %ebx, (%eax)
	pushl $0
	popl %eax
	addl $4, %esp
	popl %edi
	popl %esi
	popl %ebx
	leave
	ret
