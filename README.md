# minimal-ebpf

Tiny repository containing work related to eBPF and Rust. The medium to long term objective
is to use this repository to learn more about eBPF and how to use it with Rust.

For the time being this is mostly a scratchpad.

### generic_file_open_example

Simple eBPF program that uses [bpftrace](https://github.com/iovisor/bpftrace) to hook to the
[generic_file_open](https://elixir.bootlin.com/linux/latest/source/include/linux/fs.h#L3036)
kprobe and print out details regarding which file was opened and by who. This currently filters
by `uid` being `1000` which generally refers to the current user.

```
Attaching 2 probes...
uid, gid, filename 
1000, 1000, HEAD
```


