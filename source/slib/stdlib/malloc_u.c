/*
 * stdlib: malloc_u.c
 * t_clibs
 * Apache License 2.0
 *
 * */

/* ISO C99 Standard */
/* Non-standard incomplete implementation */

#if linux

#include "slib/stdlib.h"

#include <unistd.h>

#define NULL_p ((void *)-1)

/* #include "slib/stddef.h" */

typedef struct MemBlock {
  size_t size; /* 算上结构体本身的大小 */
  struct MemBlock *next;
  struct MemBlock *back;
} MemBlock; /* Full size: 24Bit */

static size_t MemBlock_size = sizeof(MemBlock);

static MemBlock *head = NULL; /* 头指针不可分配 */
/** static MemBlock *tail = NULL; /* 尾部  TODO: 用尾部简写*/
/* Extend Heap */
static void *extend_heap(size_t size) { /*TODO: Use MMAP*/
  void *heap = sbrk(0);
  if (sbrk(size + MemBlock_size) == NULL_p) /* 算上结构体本身大小 */
    return NULL;
  MemBlock *block = (MemBlock *)heap;
  block->size = size + MemBlock_size;
  block->next = block->back = NULL;
  return block;
}

// static void marge_heap(MemBlock *block) {
//   if (block->next) {
//     if ((void *)block + block->size ==
//         (void *)block->next) /* 连续，合并这个块 */
//     {
//       block->size += block->next->size;
//       block->back = block->next->back;
//       block->next = block->next->next;
//     }
//   }
//   if (block->back) {
//     if ((void *)block - block->size ==
//         (void *)block->back) /* 连续，合并这个快 */
//     {
//       block->size += block->back->size;
//       block->back = block->back->back;
//       block->next = block->back->next;
//     }
//   }
//
//   if (block->next)
//     marge_heap(block->next);
//   if (block->back)
//     marge_heap(block->back);
// }

// void *malloc(size_t size) {
//   if (size == 0)
//     return NULL;
//   if (!head) /* 如果头指针为空 */
//   {
//     head = extend_heap(MemBlock_size);
//     if (head == NULL_p) {
//       /* TODO: 记录问题*/
//       return NULL;
//     }
//     head->size = 0; /* Full size */
//   }
//   size = (size + 7) & ~7; /* 向上对齐*/
//   MemBlock *p = NULL;     /* 待分配块 */
//   if (!head->size) {      /* 已经没有内存了，申请内存*/
//     p = head->next;
//     while (p->next) {
//       p = p->next;
//     }
//     p->next = extend_heap(size + MemBlock_size);
//     if (p->next == NULL_p) {
//       /* TODO: 记录问题*/
//       return NULL;
//     }
//     return (void *)p + MemBlock_size;
//   }
//   if (head->size - 16 <= size) { /* 不够分配块，申请内存 */
//     p = head->next;              /* 在这块内存之后补充即可 */
//     while (p->next) {
//       p = p->next;
//     }
//     head->size -= p->size;
//     MemBlock *tmp = extend_heap(size - p->size + MemBlock_size);
//     if (tmp == NULL_p) {
//       /* TODO: 记录问题*/
//       return NULL;
//     }
//     return (void *)p + MemBlock_size;
//   }
//   /* 先查询有没有比较大的块然后拆分，或者分配内存。
//    * 最佳适配算法：
//    * 	目前算法时间复杂度： O(k)，k 是链表长度
//    * */
//
//   p = head->next;
//   MemBlock *tmp = NULL;
//   while (p->next != NULL) {
//     if (p->size - MemBlock_size == size) {
//       tmp = p;
//       break;
//     }
//     if (p->size - MemBlock_size > size) {
//       if (!tmp)
//         tmp = p;
//       else if (tmp->size > p->size)
//         tmp = p;
//     }
//   }
//   if (!tmp) { /* 块不够了，在尾部扩展内存 */
//     p->next = extend_heap(size + MemBlock_size);
//     p->next->back = p;
//     return (void *)p->next + MemBlock_size;
//   }
//
//   /* 直接分配这块内存 */
//
//   head->size -= size;
//   MemBlock *ts = (MemBlock *)((void *)tmp + MemBlock_size + size);
//   /* 插入新的块，返回tmp */
//   ts->back = tmp;
//   ts->next = tmp->next;
//   tmp->next = ts;
//   return (void *)tmp + MemBlock_size;
// }

static void marge_heap(MemBlock *block) {
    /* 合并后向块 */
    if (block->next && (char*)block + block->size == (char*)block->next) {
        MemBlock *next = block->next;
        block->size += next->size;
        block->next = next->next;
        if (block->next) {
            block->next->back = block;
        }
    }
    /* 合并前向块 */
    if (block->back && (char*)block->back + block->back->size == (char*)block) {
        MemBlock *back = block->back;
        back->size += block->size;
        back->next = block->next;
        if (back->next) {
            back->next->back = back;
        }
        block = back;  // 合并后当前块变为前向块
    }
}


void *malloc(size_t size) {
  if (size == 0)
    return NULL;
  size = (size + 7) & ~7;                      /* 内存对齐 */
  size_t total_size = size + sizeof(MemBlock); /* 总大小 */

  if (!head) { /* 头部指针初始化 */
		head = extend_heap(MemBlock_size);
		if(!head)
		{
			/* TODO: 错误处理*/
			return NULL;
		}
    head->size = 0;
  }

  /* Bast-Fit */
  MemBlock *best = NULL;
  MemBlock *p = head->next;
  while (p) {
    if (p->size >= total_size && (!best || p->size < best->size)) {
      best = p;
    }
    p = p->next;
  }

  /* 没有合适的块，拓展堆 */
  if (!best) {
    best = sbrk(total_size);
    if (best == (void *)-1)
      return NULL;
    best->size = total_size;
    best->back = NULL;
    best->next = NULL;
    // 插入到链表尾部（简化处理）
    MemBlock *last = head;
    while (last->next)
      last = last->next;
    last->next = best;
    best->back = last;
  }

  /* 拆分块 */
  if (best->size - total_size >=
      MemBlock_size + 8) { // 至少能放下一个块头+8字节
    MemBlock *split = (MemBlock *)((void *)best + total_size);
    split->size = best->size - total_size;
    split->back = best;
    split->next = best->next;
    if (split->next)
      split->next->back = split;
    best->next = split;
    best->size = total_size;
  }

  /* 移除块 */
  if (best->back)
    best->back->next = best->next;
  if (best->next)
    best->next->back = best->back;
  return (void *)best + MemBlock_size;
}

void free(void *ptr) {
  if (!ptr)
    return;                              /* 此处应该Abrt */
  MemBlock *block = (MemBlock *)ptr - 1; /* 得到原始指针 */
                                         /* 合并这个块 */
  block->next = head->next;
  block->back = head;
  if (head->next)
    head->next->back = block;
  head->next = block;

  marge_heap(block);
}

#endif
