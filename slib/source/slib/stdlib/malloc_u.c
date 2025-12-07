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
  if (sbrk(size) == NULL_p) /* 算上结构体本身大小 */
    return NULL;
  MemBlock *block = (MemBlock *)heap;
  block->size = size;
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

  size = (size + 7) & ~7;
  size_t total_size = size + sizeof(MemBlock);

  /* 初始化 head（哨兵节点）*/
  if (!head) {
    // 注意：head 不需要从堆分配，我们可以直接使用静态变量
    static MemBlock head_node;
    head = &head_node;
    head->size = 0; // 哨兵节点大小为 0
    head->next = NULL;
    head->back = NULL;
    last = head; // 初始化 last 指向 head
  }

  // Best-Fit 搜索
  MemBlock *best = NULL;
  MemBlock *p = head->next;
  while (p) {
    if (p->size >= total_size && (!best || p->size < best->size)) {
      best = p;
    }
    p = p->next;
  }

  // 没有合适的块，扩展堆
  if (!best) {
    best = extend_heap(total_size);
    if (!best)
      return NULL;

    // 插入到链表末尾（保持地址有序）
    best->back = last;
    best->next = NULL;
    if (last)
      last->next = best;
    last = best;
  }

  /* 分割块（如果剩余空间足够大）*/
  if (best->size - total_size >= sizeof(MemBlock) + 8) {
    MemBlock *split = (MemBlock *)((void *)best + total_size);

    split->size = best->size - total_size;
    split->next = best->next;
    split->back = best;

    if (best->next)
      best->next->back = split;
    best->next = split;

    /* 如果分割的块是最后一个，更新 last */
    if (last == best) last = split;

    best->size = total_size;
  }

	/* 移除块 */
  if (best->back)
    best->back->next = best->next;
  if (best->next)
    best->next->back = best->back;

  /* 如果移除的是最后一个节点，更新 last */
  if (last == best)
    last = best->back;

  return (void *)best + MemBlock_size;
}

void free(void *ptr) {
  if (!ptr)
    return;                              /* 此处应该Abrt */
  MemBlock *block = (MemBlock *)((void*)(ptr) - MemBlock_size); /* 得到原始指针 */
                                         /* 合并这个块 */

	/*
	 * 如果元数据是好的，那么不必管他
	 * 如果元数据被篡改，Ub，不必管他
	 * */

  block->next = head->next;
  block->back = head;
  if (head->next)
    head->next->back = block;
  head->next = block;

  /* marge_heap(block); */ /* 限于设计的问题，无法合并，临时决定不合并 */
}

#endif
