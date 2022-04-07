#!/usr/sbin/dtrace -s

dtrace:::BEGIN
{
	printf("              UID        GID\n");
}

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
