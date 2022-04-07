#!/usr/sbin/dtrace -s

/* 1. Tracing open system call and printing the id's with function name. */
syscall::open:entry
{
	printf("%s %s", execname, copyinstr(arg0));
}

/* 2.Tracing read system call */
syscall::read:entry
{
	printf("%s", stringof(copyin(arg1, arg2)));
}

/* 3. Summarizes return value of read() syscalls, printing it as a histogram */
syscall::read:return
{
	@ = quantize(arg0);
}

/* 4. Tracing write system call */
syscall::write:entry
{
	printf("%s", stringof(copyin(arg1, arg2)));
}

/* 5. Display probes that are available with the proc provider */
/* dtrace -l -P proc */

/* 6. Shows which system calls are happening most often */
syscall:::entry
{
	@syscalls[probefunc] = count();
}

/* 7. Shows the number of times a particular system call is happening(ioctl in nthis case) */
syscall::ioctl:entry
{
	@syscalls[probefunc] = count();
}

/* 8. Print a message */
dtrace:::BEGIN
{
	printf("Hello world!\n");
}

/* 9. Count kernel stacks that led to blocking (off-CPU) evnts. */
/*
sched:::off-cpu
{
	@[stack(8)] = count();
}
*/

/* 10. TCP passive opens by remote IP address */
/*
tcp:::accept-established
{
	@[args[3]->tcps_raddr] = count();
}
*/

/* 11. Summary on kernel vmem_alloc() calls. */
/*
fbt::vmem_alloc:entry
{
	@[curthread->td_name, args[0]->vm_name] = sum(arg1);
}
*/

/* 12. D-script that tells distribution of function calls that are made to libc by a particular subject process. */
/* dtrace -s libc.d -c date > output.txt */
