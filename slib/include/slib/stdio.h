/*
 * stdio.h
 * t_clibs
 * Apache License 2.0
 *
 * */

/* ISO C99 Standard */
/* Non-standard incomplete implementation */

#include "stddef.h"

#ifndef T_CLIBS_SLIB_STDIO_H
#define T_CLIBS_SLIB_STDIO_H

/* #define NULL ((void*)0)*/
#define EOF (-1)

#define SEEK_SET 0 /* Seek from beginning of file.  */
#define SEEK_CUR 1 /* Seek from current position.  */
#define SEEK_END 2 /* Seek from end of file.  */
/* For GNU, No implement */

typedef struct FILE {

} FILE;

typedef struct fpos_t {

} fpos_t;

int fgetc(FILE *stream);                  /* Read a character from stream*/
int fputc(unsigned char c, FILE *stream); /* Write a character for stream */

char *fgets(
    char *s, int n,
    FILE *stream); /* Read n-1 characters from stream and append '\0' in end */
int fputs(const char *s,
          FILE *stream); /* Write string for stream, if failed return EOF, else
                            return not negative*/

/*
"r" 	读取 	打开文件进行读取 	从头开始读取 	打开失败
"w" 	写入 	创建文件进行写入 	销毁内容 	创建新文件
"a" 	追加 	追加到文件 	写入到末尾 	创建新文件
"r+" 	读取扩展 	打开文件进行读/写 	从头开始读取 	错误
"w+" 	写入扩展 	创建文件进行读/写 	销毁内容 	创建新文件
"a+" 	追加扩展 	打开文件进行读/写 	写入到末尾 	创建新文件
 * */
FILE *fopen(const char *filename, const char *mode); /* Open a file */
int fclose(FILE *stream);                            /* Close file */

int fflush(FILE *stream); /* flush stream*/

int fseek(FILE *stream, long offset, int whence); /* Move file pointer */
long ftell(FILE *stream);  // 返回当前文件指针偏移（相对于起始）
void rewind(FILE *stream); // 等价于 fseek(stream, 0L, SEEK_SET)，清除错误标志

int printf(const char *restrict format,
           ...); // 格式化输出到 stdout（支持 C99 格式符如 %zd/%ju）
int fprintf(FILE *restrict stream, const char *restrict format, ...);
int scanf(const char *restrict format, ...); // 格式化输入从 stdin
int fscanf(FILE *restrict stream, const char *restrict format, ...);
int sprintf(char *restrict s, const char *restrict format,
            ...); // 格式化输出到字符串
int snprintf(char *restrict s, size_t n, const char *restrict format,
             ...); // C99 新增：限制长度，安全版

int ferror(FILE *stream);    // 检查流是否有错误，返回非零为真
int feof(FILE *stream);      // 检查流是否到 EOF，返回非零为真
void clearerr(FILE *stream); // 清除流的错误和 EOF 标志

#define getchar() fgetc(stdin)
#define putchar(c) fputc((int)(unsigned char)(c), stdout)

#endif
