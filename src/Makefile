# Change this to match your zookeeper installation.
ZOOKEEPER_LIB=-lzookeeper_mt
ZOOKEEPER_LIBDIR=/usr/local/lib
ZOOKEEPER_INCDIR=/usr/local/include /usr/local/include/zookeeper

NAME=zookeeper
OBJECTS=zookeeper.cmo
XOBJECTS=$(OBJECTS:.cmo=.cmx)
C_OBJECTS=zkocaml_stubs.o

ARCHIVE=$(NAME).cma
XARCHIVE=$(ARCHIVE:.cma=.cmxa)
CARCHIVE_NAME=zookeeper
CARCHIVE=lib$(CARCHIVE_NAME).a

# Flags for the C compiler.
CFLAGS=-g -O2 -I$(ZOOKEEPER_INCDIR)

OCAMLC=ocamlc
OCAMLOPT=ocamlopt
OCAMLDEP=ocamldep
OCAMLMKLIB=ocamlmklib
OCAMLDOC=ocamldoc
OCAMLFIND=ocamlfind

.PHONY: all
all: $(ARCHIVE)
.PHONY: allopt
allopt:  $(XARCHIVE)

depend: *.c *.ml *.mli
	gcc -MM *.c > depend
	$(OCAMLDEP) *.mli *.ml >> depend

## Library creation
$(CARCHIVE): $(C_OBJECTS)
	$(OCAMLMKLIB) -oc $(CARCHIVE_NAME) $(C_OBJECTS) \
	-L$(ZOOKEEPER_LIBDIR) $(ZOOKEEPER_LIB)
$(ARCHIVE): $(CARCHIVE) $(OBJECTS)
	$(OCAMLMKLIB) -o $(NAME) $(OBJECTS) -oc $(CARCHIVE_NAME) \
	-L$(ZOOKEEPER_LIBDIR) $(ZOOKEEPER_LIB)
$(XARCHIVE): $(CARCHIVE) $(XOBJECTS)
	$(OCAMLMKLIB) -o $(NAME) $(XOBJECTS) -oc $(CARCHIVE_NAME) \
	-L$(ZOOKEEPER_LIBDIR) $(ZOOKEEPER_LIB)

## Installation
.PHONY: install
install: all
	{ test ! -f $(XARCHIVE) || extra="$(XARCHIVE) $(NAME).a"; }; \
	$(OCAMLFIND) install $(NAME) META $(NAME).cmi $(NAME).mli $(ARCHIVE) \
	dll$(CARCHIVE_NAME).so lib$(CARCHIVE_NAME).a $$extra

.PHONY: uninstall
uninstall:
	$(OCAMLFIND) remove $(NAME)

## Cleaning up
.PHONY: clean
clean::
	rm -f *~ *.cm* *.o *.a *.so depend

FORCE:

.SUFFIXES: .ml .mli .cmo .cmi .cmx

.mli.cmi:
	$(OCAMLC) -c $(COMPFLAGS) $<
.ml.cmo:
	$(OCAMLC) -c $(COMPLAGS) -nolabels $<
.ml.cmx:
	$(OCAMLOPT) -c $(COMPFLAGS) -nolabels $<
.c.o:
	$(OCAMLC) -c -ccopt "$(CFLAGS)" $<

include depend
