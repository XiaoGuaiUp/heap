heap:heap.c
	gcc $^ -g -o $@

.PHONY:clean
	clean:
		rm -f heap
