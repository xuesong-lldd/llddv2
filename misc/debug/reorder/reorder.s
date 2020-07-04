	.file	"reorder.c"
	.text
	.p2align 4,,15
	.globl	foo
	.type	foo, @function
foo:
.LFB0:
	.cfi_startproc
	movl	b(%rip), %eax
	movl	$0, c(%rip)
	movl	$0, b(%rip)
	addl	$1, %eax
	movl	%eax, a(%rip)
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
	.comm	c,4,4
	.comm	b,4,4
	.comm	a,4,4
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
