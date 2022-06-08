use aya::programs::{CgroupSkb, CgroupSkbAttachType};
use aya::Bpf;
use std::convert::TryInto;
use std::fs::File;

fn main() {
    // load the BPF code
    let mut bpf = Bpf::load_file("../generic_file_open_example.o").unwrap();

    // get the `ingress_filter` program compiled into `bpf.o`.
    let ingress: &mut CgroupSkb = bpf
        .program_mut("generic_file_open")
        .unwrap()
        .try_into()
        .unwrap();

    // load the program into the kernel
    ingress.load().unwrap();

    // attach the program to the root cgroup. `ingress_filter` will be called for all
    // incoming packets.
    let cgroup = File::open("/sys/fs/cgroup/unified").unwrap();
    ingress
        .attach(cgroup, CgroupSkbAttachType::Ingress)
        .unwrap();
}
