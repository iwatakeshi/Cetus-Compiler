.text

.globl giveint
giveint:
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl $12
	popl %eax
	popl %edi
	popl %esi
	popl %ebx
	leave
	ret
.globl giveint2
giveint2:
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl $19
	popl %eax
	popl %edi
	popl %esi
	popl %ebx
	leave
	ret
.globl _Main
_Main
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	pushl %esi
	pushl %edi
	subl $12, %esp
	movl $16, %ebx
	movl %ebp, %eax
	subl %ebx, %eax
	pushl %eax
	pushl $5
	popl %ebx
	popl %eax
	movl %ebx, (%eax)
	movl $20, %ebx
	movl %ebp, %eax
	subl %ebx, %eax
	pushl %eax
	pushl $17
	popl %ebx
	popl %eax
	movl %ebx, (%eax)
	movl $24, %ebx
	movl %ebp, %eax
	subl %ebx, %eax
	pushl %eax
	pushl $27
	popl %ebx
	popl %eax
	movl %ebx, (%eax)
	pushl -16(%ebp)
	popl %eax
	addl $12, %esp
	popl %edi
	popl %esi
	popl %ebx
	leave
	ret
