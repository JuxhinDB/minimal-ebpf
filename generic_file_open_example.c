#include "vmlinux.h"
#include "bpf/bpf_core_read.h"
#include "bpf/bpf_endian.h"
#include "bpf/bpf_helpers.h"
#include "bpf/bpf_tracing.h"

char LICENSE[] SEC("license") = "GPL";

struct generic_file_open_args {
	struct file *filp;
	struct inode *inode;
};

SEC("kprobe/generic_file_open")
int generic_file_open(struct generic_file_open_args *ctx) {
	int pid = bpf_get_current_pid_tgid() >> 32;
	const char fmt_str[] = "detected file open - pid: %d, file: %s, uid: %d\n";

	// Read data over from kernel space
	struct inode *inode;
	struct file *filp;

	bpf_probe_read(&inode, sizeof(inode), &ctx->inode);
	bpf_probe_read(&filp, sizeof(filp), &ctx->filp);

	// Read data over from user space
	struct path *path;
	struct dentry *dentry;
	struct qstr d_name = {};

	bpf_probe_read(&path, sizeof(path), &filp->f_path);
	bpf_probe_read(&dentry, sizeof(dentry), &path->dentry);
	bpf_probe_read(&d_name, sizeof(d_name), &dentry->d_name);

	bpf_trace_printk(fmt_str, 
			sizeof(fmt_str), 
			pid, 
			d_name.name,
			&inode
	);

	return 0;
}
