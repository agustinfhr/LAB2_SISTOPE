salida_out = lab2
salida_broker = broker
salida_worker = worker

salida_headers = 
salida_source  = $(salida_headers:.h=.c) lab2.c 
salida_objects = $(salida_source:.c=.o)

broker_headers = fbroker.h 
broker_source = $(broker_headers:.h=.c) broker.c fbroker.c
broker_objects = $(broker_source:.c=.o)

worker_headers = 
worker_source = $(worker_headers:.h=.c) worker.c
worker_objects = $(worker_source:.c=.o)


CC     = gcc
CFLAGS = -Wall

# libreria para math.h
LIBS += -lm

depends = .depends
depends2 = .depends2
depends3 = .depends3

build : $(salida_out)

$(salida_out) : $(salida_objects)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(objects) :
	$(CC) $(CFLAGS) -c -o $@ $*.c

$(depends) : $(salida_source) $(salida_headers)
	@$(CC) -MM $(salida_source) > $@


build : $(salida_broker)

$(salida_broker) : $(broker_objects)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(objects) :
	$(CC) $(CFLAGS) -c -o $@ $*.c

$(depends2) : $(broker_source) $(broker_headers)
	@$(CC) -MM $(broker_source) > $@


build : $(salida_worker)

$(salida_worker) : $(worker_objects)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(objects) :
	$(CC) $(CFLAGS) -c -o $@ $*.c

$(depends3) : $(worker_source) $(worker_headers)
	@$(CC) -MM $(worker_source) > $@


clean :
	$(RM) $(salida_out) $(salida_objects) $(zipfile) $(depends)


.PHONY : build zip clean

sinclude $(depends)

