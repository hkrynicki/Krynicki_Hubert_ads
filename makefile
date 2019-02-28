game:
	cl main.c stack.c utils.c
	main.exe
	nmake clean
clean:
	del *.obj
	del *.exe