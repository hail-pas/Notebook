mbr.img: mbr.S
	gcc -ggdb -c $<
	ld mbr.o -Ttext 0x7c00
	objcopy -S -O binary -j .text a.out $@

run: mbr.img
	qemu-system-x86_64 $<

debug: mbr.img
	qemu-system-x86_64 -s -S $< &  # Run QEMU in background then bind to ::1234
	gdb -x init.gdb  # RTFM: gdb (1) target remote :1234

clean:
	rm -f *.img *.o a.out
