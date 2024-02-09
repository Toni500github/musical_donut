LDLIBS := `pkg-config --libs portaudiocpp sndfile`
DONUT := donut
DONUT_WIN := donut.exe

all:
	cc donut.c -o $(DONUT) $(LDLIBS)

clean:
	rm -f $(DONUT) $(DONUT_WIN)

win:
	cc donut.c $(LDLIBS) -o $(DONUT_WIN)
