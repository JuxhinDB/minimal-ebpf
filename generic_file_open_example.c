#include "vmlinux.h"
#include "bpf/bpf_core_read.h"
#include "bpf/bpf_endian.h"
#include "bpf/bpf_helpers.h"
#include "bpf/bpf_tracing.h"

SEC("kprobe/generic_file_open")
int generic_file_open(struct pt_regs *ctx) {
	bpf_printk("hit");
	return 0;
}
