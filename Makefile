LDLIBS := -w -lm -lvlc
DONUT := donut

all: $(DONUT)

clean: 
	rm -f $(DONUT)
