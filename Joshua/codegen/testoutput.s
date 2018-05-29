.text

.globl Main
Main:
	pushl %ebp
	movl %esp, %ebp
	pushl % ebx
	pushl % esi
	pushl % edi
	pushl 0
	popl %eax
	pushl % edi
	pushl % esi
	pushl % ebx
	leave
	ret
