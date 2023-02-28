LDLIBS := -lm -lvlc
DONUT := donut
DONUT_WIN := donut.exe

all: $(DONUT); ./$(DONUT)

clean:
	rm -f $(DONUT) $(DONUT_WIN)

win:
	cc main.c $(LDLIBS) -o $(DONUT_WIN)
