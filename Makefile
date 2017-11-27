BINDIR = bin
SRCDIR = src
INCLUDEDIR = include
APPDIR = application
OBJDIR = build
TESTDIR = test
LIBDIR  = lib

CC = g++
CFLAGS = -O3 -Wall -std=c++11 -pedantic -I. -I $(INCLUDEDIR)
LDFLAGS =
AR = ar

BIN = ${BINDIR}/prog
APP = ${APPDIR}/main.cpp
LIBSTATIC = ${LIBDIR}/portfowarding.a
LIBDINAMIC = ${LIBDIR}/portfowarding.so

SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
APPOBJ = $(patsubst $(APPDIR)/%.cpp,$(OBJDIR)/%.o,$(APP))

_TESTS = $(wildcard $(TESTDIR)/*.cpp)
TESTS = $(patsubst %.cpp,%,$(_TESTS))

$(BIN): $(OBJS) $(APPOBJ)
	$(CC) -o $(BIN) $(APPOBJ) $(OBJS) $(CFLAGS) $(LDFLAGS)

$(APPOBJ): $(APP)
	$(CC) -c -o $@ $< $(CFLAGS)

${OBJDIR}/%.o: $(SRCDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(TESTS)
	$(info ************  Testes concluídos com sucesso! ************)

$(TESTDIR)/t_%: $(TESTDIR)/t_%.cpp $(OBJS)
	$(CC) -o $@ $< $(OBJS) $(CFLAGS) $(LDFLAGS)
	$@

clean:
	rm -f $(BIN) $(OBJS) $(APPOBJ) $(LIBDIR)/*
	rm -f $(TESTS)

$(LIBSTATIC): $(OBJS) $(APPOBJ)
	$(AR) rcs $@ $(OBJS)

$(LIBDINAMIC): $(SRCDIR)/*.cpp
	$(CC) -fPIC -c -o $(OBJS) $< $(CFLAGS)
	$(CC) -shared -fPIC -o $@ $(OBJS)

static: $(OBJS) $(APPOBJ)
	make $(LIBSTATIC)
	$(CC) -o $(BIN) $(LIBSTATIC) $(APPOBJ) $(OBJS) $(CFLAGS) $(LDFLAGS)

dinamic: $(OBJS) $(APPOBJ)
	make $(LIBDINAMIC)
	$(CC) -o $(BIN) $(LIBDINAMIC) $(APPOBJ) $(OBJS) $(CFLAGS) $(LDFLAGS)
