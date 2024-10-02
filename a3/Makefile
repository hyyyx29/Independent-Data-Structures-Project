# 变量定义
CC = gcc
CFLAGS = -Wall
TARGET = graph_tester
SRCS = minheap.c graph.c graph_algos.c graph_tester.c
OBJS = $(SRCS:.c=.o)

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 编译每个源文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET)

# 运行生成的可执行文件
run: $(TARGET)
	./$(TARGET) sample_input.txt

# 使用GDB调试生成的可执行文件
debug: $(TARGET)
	gdb $(TARGET)

.PHONY: all clean run debug