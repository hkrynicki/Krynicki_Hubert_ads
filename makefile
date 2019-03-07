game:
	cl main.c stack.c utils.c input-gathering.c
	main.exe
	nmake clean
clean:
	del *.obj
	del *.exe