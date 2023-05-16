 # Kill process (QEMU) on gdb exits
define hook-quit
  kill
end

# Connect to remote
target remote localhost:1234
file a.out
watch *0X7C00
break *0x7c00
layout src
continue
