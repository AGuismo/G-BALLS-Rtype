## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



CONSUMER	?=	testConsumer
EVENT		?=	testEvent
EVENT_TIMEOUT	?=	testEventTimeout
THREAD_POOL     ?=	testThreadPool


F.C	     +=	-W -Wall  -fPIC
F.I	     +=	-I $(DIR.H)
F.L	     += -lpthread -shared
F.D	     += -DNDEBUG


all:		$(CONSUMER) $(EVENT) $(THREAD_POOL) $(EVENT_TIMEOUT)

$(CONSUMER):
	g++ -o $(CONSUMER) -g3 -Dlinux -I ../Threads/include/ -I../deps/Bind/include -std=c++0x test_Consumer.cpp -lpthread -L../Threads/ -lThread

$(EVENT):
	g++ -o $(EVENT) -g3 -Dlinux -I ../Threads/include/  -I../deps/Bind/include -std=c++0x test_Event.cpp -lpthread -L../Threads/ -lThread

$(EVENT_TIMEOUT):
	g++ -o $(EVENT_TIMEOUT) -g3 -Dlinux -I ../Threads/include/  -I../deps/Bind/include -std=c++0x test_Event2.cpp -lpthread -L../Threads/ -lThread

$(THREAD_POOL):
	g++ -o $(THREAD_POOL) -g3 -Dlinux -I ../Threads/include/ -I../deps/Bind/include -std=c++0x test_ThreadPool.cpp -lpthread -L../Threads/ -lThread

clean:
	rm -f	$(CONSUMER)
	rm -f	$(EVENT)
	rm -f	$(EVENT_TIMEOUT)
	rm -f	$(THREAD_POOL)

fclean:

re:		all






















































