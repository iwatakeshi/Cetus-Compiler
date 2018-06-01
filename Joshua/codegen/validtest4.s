.text

.globl foo
foo:
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl 8(%ebp)
	subl $4, %esp
	pushl $2
	popl %ebx
	popl %ebx
	cdq
	imull ebx
	pushl eax
	popl %eax
	addl $8, %esp
	popl %edi
	popl %esi
	popl %ebx
	leave
	ret
.globl Main
Main:
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	pushl %esi
	pushl %edi
	subl $4, %esp
	pushl %ecx
	pushl %edx
	pushl $3
	call foo
	popl %edx
	popl %ecx
	pushl $3
	popl %ebx
	popl %ebx
	cdq
	imull ebx
	pushl eax
	pushl $2
	popl %ebx
	popl %ebx
	addl %ebx, %eax
	pushl eax
	movl %eax, %ecx
	pushl $0
	popl %eax
	addl $4, %esp
	popl %edi
	popl %esi
	popl %ebx
	leave
	ret
