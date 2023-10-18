#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Will manage the buffer */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Will execute mulitiple commands */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Will manage the conveting num */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* getline.c */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the numberic field
 * @str: cahracter string
 * @next: points to the following node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - for passing arguments
 *@arg: the argument
 *@argv: an array of strings
 *@path: string representing the command path
 *@argc: argument count
 *@lin_cnt:  handles error count
 *@error_num: will return on exit fail
 *@lincnt_flag: indicates if counting this line of input
 *@file_name: name of prgram file
 *@env: a copy of environ
 *@environ:a  local copy of  environ
 *@history: node for history
 *@alias: node for alias
 *@env_changed: indicates change in environment
 *@status: return status
 *@cmd_buffer: pointer address to the command buffer
 *@cmd_buffer_type: handles ||, &&, ;
 *@readfd: the file descriptor to read line input
 *@histcnt: counts number of line
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int lin_cnt;
	int error_num;
	int lincnt_flag;
	char *file_name;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buffer;
	int cmd_buffer_type;
	int readfd;
	int histcnt;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - a string
 *@type: command flag
 *@func: a function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* shs.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* handle_patts.c */
int _rcmd(info_t *, char *);
char *char_duplicate(char *, int, int);
char *_fpath(info_t *, char *, char *);

/* loop */
int loophsh(char **);

/* errors.c */
void _eputs(char *);
int _eputchar(char);
int _putffd(char c, int fd);
int _putsffd(char *str, int fd);

/* str_copy2.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* str_copy.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* str_copy1.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* handle_str2.c */
char **_str_split(char *, char *);
char **_str_split2(char *, char);

/* handle_mem.c */
char *setmemos(char *, char, unsigned int);
void string_free(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* handle_mem0.c */
int isfreed(void **);

/* interactive_shell.c*/
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* convert_str.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *conv_num(long int, int, int);
void remove_comments(char *);

/* builltin.c */
int copy_exit(info_t *);
int copy_cdd(info_t *);
int _help(info_t *);

/* builltin0.c */
int copy_histories(info_t *);
int copy_alias(info_t *);

/* mygetlines.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/*myin_info.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* mysetenv.c*/
char *_getenv(info_t *, const char *);
int _myenvirons(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* setenv1.c */
char **get_environs(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* history.c */
char *history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int list_history(info_t *info, char *buf, int linecount);
int renum_history(info_t *info);

/* handle_str.c*/
list_t *_anode(list_t **, const char *, int);
list_t *end_anode(list_t **, const char *, int);
size_t print_lstr(const list_t *);
int d_ind(list_t **, unsigned int);
void _flist(list_t **);

/* handle_str1.c */
size_t l_length(const list_t *);
char **l_str(list_t *);
size_t _plist(const list_t *);
list_t *_snode(list_t *, char *, char);
ssize_t getn_ind(list_t *, list_t *);

/* check_chain.c */
int _chain(info_t *, char *, size_t *);
void chain_check(info_t *, char *, size_t *, size_t, size_t);
int rep_alias(info_t *);
int rep_var(info_t *);
int rep_str(char **, char *);

#endif
