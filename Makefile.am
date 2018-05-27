ACLOCAL_AMFLAGS = -I m4
bin_PROGRAMS=lora_detector
lora_detector_SOURCES=lora_detector.c fields.c fields.h lora_packet.c lora_packet.h black_list.c black_list.h aes/aes.c aes/aes.h
lora_detector_LDADD=-lunirec -ltrap -lm
include ./aminclude.am
