#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* for read and write Buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command Chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/*for convert number */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

extern char **env;

/**
 * struct liststring
 *@num:the num field
 *@str: a string to define
 *@next_index: it points to the next node
 */
typedef struct liststring
{
	int num;
	char *str;
	struct liststring *next_index;
} list_t;

/**
 *struct pass - containes arguments to pass into function ,
 *allowing uniform prototype for function pointer struct
 *@argm:a string generate from function getline
 *@argvm:an array of strings generated from argm
 *@paths:a string path for current command
 *@linesCount:number of count error
 *@lines_flag:if on count this line input
 *@argcm:the argument count
 *@errors:the error code count
 *@@file_name: the program filename
 *@linkedenv: linked list local copy of environ
 *@env: custom modified copy of environ from LL env
 *@hist: the history node
 *@neigb_node: the alias node
 *@changed_env: on if environ was changed
 *@last_command: the return status of the last exec'd command
 *@cmd_buf_pointer: address of pointer to cmd_buf, on if chaining
 *@cmd_type: CMD_type ||, &&, ;
 *@read_dict: the fd to read line input
 *@hist_num_counts: the history lines count
 */

typedef struct pass
{
	char *argm;
	char **argvm;
	char *paths;
	int argcm;
	unsigned int linesCount;
	int errors;
	int lines_flag;
	char file_Name;
	list_t linkedenv;
	list_t hist;
	list_t neigb_node;
	char **env;
	int changed_env;
	int last_command;
	char cmd_buf_pointer;
	int cmd_types;
	int read_dict;
	int hist_num_count;
} infom_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct built_funcs - containe bultin functions string and related one
 * @typeF:built int command flag
 * @funcs:the function
 */

typedef struct built_funcs
{
	char *typeF;
	int (*funcs)(infom_t *);
} built_funcs_table

/* shell Loops.c */
int hsh(infom_t *, char **);
int find_builtFunc(infom_t *);
void find_cmd(infom_t *);
void fork_exec_command(infom_t *);

/* parser.c */
int is_cmd_Valid(infom_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_executable_path(infom_t, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void _P_error_string(char *);
int _errputchar(char);
int _putfdict(char c, int fd);
int _putsfdict(char *str, int fd);

/*string.c */
int _getstrlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string1.c */
char *_strcpy(char *, char *);
char *_dublicate_string(const char *);
void _puts(char *);
int _putchar(char);

/* exit.c */
char *_strcopy(char *, char *, int);
char *_strcat(char *, char *, int);
char *_find_strchr(char *, char);

/* updated_toem_tokenizer.c */
char **split_string(char *, char *);
char **split_string_by_space(char *, char);

/* reallocate.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_reallocate(void *, unsigned int, unsigned int);

/* memory.c */
int free_block(void **);

