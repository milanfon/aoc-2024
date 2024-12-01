CC = clang

1st-a:
	$(CC) 1st.c -o 1st -DVARIANT_A

1st-b:
	$(CC) 1st.c -o 1st -DVARIANT_B

clean:
	rm -f 1st
