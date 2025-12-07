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
static MemBlock *last = NULL; /* 永远指向尾部 */
/** static MemBlock *tail = NULL; 尾部  TODO: 用尾部简写*/
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

static void marge_heap(MemBlock *block) {
  /* 合并后向块 */
  if (block->next && (void *)block + block->size == (void *)block->next) {
    MemBlock *next = block->next;
    block->size += next->size;
    block->next = next->next;
    if (block->next) {
      block->next->back = block;
    }
  }
  /* 合并前向块 */
  if (block->back && (void *)block->back + block->back->size == (void *)block) {
    MemBlock *back = block->back;
    back->size += block->size;
    back->next = block->next;
    if (back->next) {
      back->next->back = back;
    }
    block = back;
  }
}

void *malloc(size_t size) {
  if (size == 0)
    return NULL;
  size = (size + 7) & ~7; /* 内存对齐 */
  size_t total_size = size + sizeof(MemBlock);

  if (!head) { /* 头部指针初始化 */
    head = extend_heap(MemBlock_size);
    if (!head) {
      /* TODO: 错误处理*/
      return NULL;
    }
    head->size = 0;
    last = head->next;
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
    best = extend_heap(total_size);
    MemBlock *last = head;
    while (last->next)
      last = last->next;
    last->next = best;
    best->back = last;
  }

  /* 拆分块 */
  if (best->size - total_size >=
      MemBlock_size + 8) { // 至少能放下一个块头+8字节
    MemBlock *split = (MemBlock *)best + 1;
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
