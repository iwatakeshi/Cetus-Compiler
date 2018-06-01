.text

.globl Main
Main:
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	pushl %esi
	pushl %edi
	subl $4, %esp
	pushl $2
	movl %eax, %ecx
	pushl $0
	popl %eax
	addl $4, %esp
	popl %edi
	popl %esi
	popl %ebx
	leave
	ret
