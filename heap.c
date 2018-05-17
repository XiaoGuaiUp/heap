#include <stdio.h>
#include <stdlib.h>

#include "heap.h"


//在对堆进行初始化时，决定是大堆还是小堆
void HeapInit(Heap* heap,Compare cmp)
{
    if(heap==NULL)
    {
        return;
    }
    heap->size=0;
    heap->cmp=cmp;
    return;
}
//销毁
void HeapDestroy(Heap* heap)
{
    if(heap==NULL)
    {
        return;
    }
    heap->size=0;
    heap->cmp=NULL;
}

//交换函数
void Swap(HeapType* a,HeapType* b)
{
    HeapType tmp=*a;
    *a=*b;
    *b=tmp;
}

//对堆进行上浮调整
void AdjustUp(Heap* heap,size_t index)
{
    //一个变量只做一件事情
    size_t child=index;
    size_t parent=(child-1)/2;
    while(child>0)
    {
        if(!heap->cmp(heap->data[parent],heap->data[child]))
        {
            Swap(&heap->data[parent],&heap->data[child]);
        }
        else
        {
            break;
        }
        child=parent;
        parent=(child-1)/2;
    }
}
//往堆中插入元素
void HeapInsert(Heap* heap,HeapType value)
{
    if(heap==NULL)
    {
        return;
    }
    if(heap->size>=HeapMaxSize)
    {
        //满了
        return;
    }
    heap->data[heap->size++]=value;
    //插入之后，对堆进行上浮调整，必须保证堆里的元素是有序的
    //调整的起始位置是size-1;
    AdjustUp(heap,heap->size-1);
    return;
}
//取堆顶元素
int HeapRoot(Heap* heap,HeapType* value)
{
    if(heap==NULL)
    {
        return 0;
    }
    *value=heap->data[0];
    return 1;
}

//下沉操作
void AdjustDown(Heap* heap,size_t index)
{
    size_t parent=index;
    size_t child=2*index+1;
    while(child<heap->size)
    {
        if(((child+1)<heap->size) && heap->cmp(heap->data[child+1],heap->data[child]))
        {
            child=child+1;
        }
        //指向子树中更小的一个
        if(heap->cmp(heap->data[child],heap->data[parent]))
        {
            Swap(&heap->data[child],&heap->data[parent]);
        }
        else
        {
            break;
        }
        parent=child;
        child=2*parent+1;
    }

}

//删除堆顶元素
void HeapErase(Heap* heap)
{
    if(heap==NULL)
    {
        return;
    }
    if(heap->size==0)
    {
        //空堆
        return;
    }
    //交换堆顶元素和最后一个元素
    Swap(&heap->data[0],&heap->data[heap->size-1]);
    //进行层删
    --heap->size;
    //从根节点出发，进行下沉调整
    AdjustDown(heap,heap->data[0]);
}

//////////////////////////////////////////////////////////////////
//以下为测试函数
/////////////////////////////////////////////////////////////////

//定义cmp的值，为大堆还是小堆
int Greater(HeapType a,HeapType b)
{
    return a>b?0:1;  //1为小堆
}

int Less(HeapType a,HeapType b)
{
    return a>b?1:0;  //1为大堆
}

void HeapPrintf(Heap* heap,const char* msg)
{
    printf("%s\n",msg);
    int i=0;
    for(;i<heap->size;++i)
    {
        printf("%c ",heap->data[i]);
    }
    printf("\n");
}
//测试堆的初始化
void TestInit()
{
    printf("=========== %s ============\n",__FUNCTION__);
    Heap heap;
    HeapInit(&heap,Greater); //小堆
    printf("size 理论值为 0，实际为 ：%lu\n",heap.size);
    printf("cmp实际值：%d\n",Greater);
}

//测试插入
void TestInsert()
{
    printf("============ %s ===========\n",__FUNCTION__);
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'a');
    HeapPrintf(&heap,"插入两个值");
}

//测试堆顶元素
void TestRoot()
{
    printf("============ %s ===========\n",__FUNCTION__);
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'a');
    HeapPrintf(&heap,"插入两个值");
    HeapType top;
    int ret=HeapRoot(&heap,&top);
    printf("ret 理论为1，实际为 %d\n",ret);
    printf("堆顶元素理论为a,实际为: %c\n",top);
}

//测试删除堆顶元素
void TestErase()
{
    printf("============ %s ===========\n",__FUNCTION__);
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'s');
    HeapInsert(&heap,'e');
    HeapPrintf(&heap,"插入五个值");
    HeapType top;
    int ret=HeapRoot(&heap,&top);
    printf("ret 理论为1，实际为 %d\n",ret);
    printf("堆顶元素理论为a,实际为: %c\n",top);
    HeapErase(&heap);
    printf("============ 删了堆顶元素 =========\n");
    HeapPrintf(&heap,"删除堆顶元素");

}

int main()
{
    TestInit();
    TestInsert();
    TestRoot();
    TestErase();
}




