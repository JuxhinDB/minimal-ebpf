use aya::programs::KProbe;
use aya::Bpf;
use std::convert::TryInto;
use std::fs::File;

fn main() {
    // load the BPF code
    let mut bpf = Bpf::load_file("../generic_file_open_example.o").unwrap();

    // get the program compiled into `bpf.o`.
    let program: &mut KProbe = bpf
        .program_mut("generic_file_open")
        .unwrap()
        .try_into()
        .unwrap();

    // load the program into the kernel
    program.load().unwrap();

    program.attach("generic_file_open", 0).unwrap();

    loop {}
}
