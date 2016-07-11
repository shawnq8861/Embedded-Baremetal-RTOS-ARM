target remote localhost:3333
monitor arm7_9 dcc_downloads enable
monitor arm7_9 fast_memory_access enable
monitor reset init
monitor wait_halt
monitor poll
symbol-file embsys100a05.elf
monitor soft_reset_halt
set remotetimeout 10
break main
continue