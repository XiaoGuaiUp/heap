#pragma once

#define HeapMaxSize 1024
typedef char HeapType;
typedef int (*Compare)(HeapType a,HeapType b);

typedef struct Heap{
    HeapType data[HeapMaxSize];
    size_t size;//元素个数
    Compare cmp;
} Heap;

//在对堆进行初始化时，决定是大堆还是小堆
void HeapInit(Heap* heap,Compare cmp);
//销毁
void HeapDestroy(Heap* heap);
//往堆中插入元素
void HeapInsert(Heap* heap,HeapType value);
//取堆顶元素
int HeapRoot(Heap* heap,HeapType* value);
//删除堆顶元素
void HeapErase(Heap* heap);
//创建一个堆
void HeapCreate(Heap* heap,HeapType array[],size_t size);
//堆排序  假设升序，大堆
void HeapSort(HeapType array[],size_t size);

