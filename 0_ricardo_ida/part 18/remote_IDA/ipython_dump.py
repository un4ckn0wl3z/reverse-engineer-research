import idaapi
import idc
import struct

bin=""

file=open("raw__.bin", "wb")

for ea in range (0x920000,0x92B000,4):
    bin+=struct.pack("<L",idc.Dword(ea))

    
file.write(bin)
file.close()