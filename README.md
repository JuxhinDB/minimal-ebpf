# minimal-ebpf

Tiny repository containing work related to eBPF and Rust. The medium to long term objective
is to use this repository to learn more about eBPF and how to use it with Rust.

For the time being this is mostly a scratchpad.

### generic_file_open_example

Simple eBPF program that uses [bpftrace](https://github.com/iovisor/bpftrace)
to hook to the [generic_file_open](https://elixir.bootlin.com/linux/latest/source/include/linux/fs.h#L3036)
kprobe and print out details regarding which file was opened and by who. This 
currently filters by `uid` being `1000` which generally refers to the current 
user.

```
Attaching 2 probes...
uid, gid, filename 
1000, 1000, HEAD
```

#### Moving away from bpftrace

Decided to start recreating the program without using `bpftrace` in order to 
get a better understanding of the internal representations of eBPF programs.

We recreate the [`generic_file_open`](generic_file_open_example.c) example 
in C and compile it to byte-code using `clang`.

```
clang -target bpf -Wall -O2 -c generic_file_open_example.c -o generic_file_open_example.o
```

We can now use the Rust library, [aya](https://github.com/aya-rs/aya) to load
our program.

#### Using [aya](https://github.com/aya-rs/aya)

Extended the [generic_file_open](generic-file-open/) example to now use Aya to 
load our program into the kernel.

```
cargo b
sudo ./target/debug/generic-file-open
```

We can then use `bpftool prog` to validate that our program has loaded.

```
❯ sudo bpftool prog
2: cgroup_skb  name egress  tag b9d9f7a5d9d7e087  gpl
        loaded_at 2022-06-08T13:03:02+0100  uid 0
        xlated 360B  jited 206B  memlock 4096B  map_ids 6,4,3
```
