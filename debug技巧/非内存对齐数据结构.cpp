struct SmallNode
{
    int l;
    int r;
    unsigned short exist;
} __attribute__((packed));

// 注意这种手法无法传参数引用, 会被编译器拒绝, 可以直接传, 应该也可以传指针