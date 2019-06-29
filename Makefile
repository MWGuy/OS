GCCPARAMS = -m32 -Iinclude -fcheck-new -fno-stack-protector -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = obj/loader.o \
          obj/libc.o \
		  obj/tty.o \
		  obj/vga.o \
		  obj/memory.o \
		  obj/kernel.o

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	c++ $(GCCPARAMS) -c -o $@ $<

obj/%.o: src/%.c
	mkdir -p $(@D)
	c++ $(GCCPARAMS) -c -o $@ $<

obj/%.o: src/%.h
	mkdir -p $(@D)
	c++ $(GCCPARAMS) -c -o $@ $<

obj/%.o: src/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

kernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

install: kernel.bin
	sudo cp $< /boot/kernel.bin

os.iso: kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp kernel.bin iso/boot/kernel.bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "OS" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/kernel.bin'      >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=os.iso iso
	rm -rf iso

qemu: os.iso
	qemu-system-x86_64 -cdrom os.iso
	
clean:
	rm -rf obj kernel.bin os.iso
