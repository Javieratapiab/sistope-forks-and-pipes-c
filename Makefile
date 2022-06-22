salida_out = lab2
salida_headers = disco.h validator.h reader.h writer.h
salida_source  = $(salida_headers:.h=.c) lab2.c
salida_objects = $(salida_source:.c=.o)

salida_out_vis = vis
salida_headers_vis = disco.h
salida_source_vis  = $(salida_headers_vis:.h=.c) vis.c
salida_objects_vis = $(salida_source_vis:.c=.o)

CC     = gcc
CFLAGS = -Wall

depends = .depends

build : $(salida_out_vis) $(salida_out)

$(salida_out_vis) : $(salida_objects_vis)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(salida_out) : $(salida_objects)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(objects) :
	$(CC) $(CFLAGS) -c -o $@ $*.c

$(depends) : $(salida_source) $(salida_source_vis) $(salida_headers) $(salida_headers_vis)
	@$(CC) -MM $(salida_source) $(salida_source_vis) > $@

clean :
	$(RM) $(salida_out) $(salida_out_vis) $(salida_objects) $(salida_objects_vis) $(zipfile) $(depends)

.PHONY : build zip clean

sinclude $(depends)
