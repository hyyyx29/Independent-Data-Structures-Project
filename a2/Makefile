# 变量定义
CC = gcc
CFLAGS = -Wall
TARGETS = minheap_tester minheap_measure
SRCS_T = minheap.c minheap_tester.c
SRCS_M = minheap.c minheap_measure.c
OBJS_T = $(SRCS_T:.c=.o)
OBJS_M = $(SRCS_M:.c=.o)

# 默认目标
all: $(TARGETS)

# 链接目标文件生成可执行文件
minheap_tester: $(OBJS_T)
	$(CC) $(CFLAGS) -o $@ $^

minheap_measure: $(OBJS_M)
	$(CC) $(CFLAGS) -o $@ $^

# 编译每个源文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJS_T) $(OBJS_M) $(TARGETS)

# 运行生成的可执行文件
run: minheap_tester
	./minheap_tester sample_input.txt

# 使用GDB调试生成的可执行文件
debug: minheap_tester
	gdb minheap_tester

.PHONY: all clean run debug
