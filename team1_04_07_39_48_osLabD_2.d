#!/usr/sbin/dtrace -s

syscall::open:entry
/ execname == "main" /
{
	printf("%s %s %d %d", execname, copyinstr(arg0), uid, gid);
}

proc:::exec-success
{
	trace(curpsinfo->pr_psargs);
}

syscall::read:entry
/ execname == "main" /
{
	@[execname] = quantize(arg2);
}
