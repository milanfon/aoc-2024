CC = clang

1st-a:
	$(CC) 1st.c -o 1st -DVARIANT_A

1st-b:
	$(CC) 1st.c -o 1st -DVARIANT_B

2nd:
	$(CC) 2nd.c common/files.c -o 2nd

clean:
	rm -f 1st 2nd
