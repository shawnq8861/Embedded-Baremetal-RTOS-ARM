target remote localhost:3333
show remotetimeout
set remotetimeout 180
monitor arm7_9 dcc_downloads enable
monitor arm7_9 fast_memory_access enable
monitor reset init
monitor wait_halt
monitor poll
monitor flash probe 0
monitor flash erase_sector 0 0 26
monitor reset init
monitor wait_halt
monitor poll
monitor flash write_image erase C:/UWScratch/embsys100a05_sln/embsys100a05.hex 0 ihex
symbol-file embsys100a05.elf
monitor soft_reset_halt
set remotetimeout 10
break main
continue