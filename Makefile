LDLIBS := -lm -lvlc
DONUT := donut

all: $(DONUT); ./$(DONUT)

clean: 
	rm -f $(DONUT)
