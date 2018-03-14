/*
 * Copyright (c) 1995-2009, 2014-2016, 2018 Paul Mattes.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the names of Paul Mattes nor the names of his contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY PAUL MATTES "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL PAUL MATTES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *	task.h
 *		Global declarations for task.c.
 */

/* macro definition */
struct macro_def {
    char		*name;
    char		**parents;
    char		*action;
    struct macro_def	*next;
};
extern struct macro_def *macro_defs;
typedef void *task_cbh;

void abort_script(void);
void login_macro(char *s);
void macros_init(void);
void macro_command(struct macro_def *m);
void peer_script_init(void);
void connect_error(const char *fmt, ...);
void connect_errno(int e, const char *fmt, ...);
void ps_set(char *s, bool is_hex);
void push_keymap_action(char *);
void push_macro(char *);
void push_stack_macro(char *);
bool task_active(void);
bool task_can_kbwait(void);
void task_connect_wait(void);
bool run_tasks(void);
void task_error(const char *msg);
void task_host_output(void);
void task_info(const char *fmt, ...) printflike(1, 2);
bool task_ifield_can_proceed(void);
void task_kbwait(void);
void task_passthru_done(const char *tag, bool success, const char *result);
bool task_redirect(void);
const char *task_set_passthru(task_cbh **ret_cbh);
void task_store(unsigned char c);

typedef void (*task_data_cb)(task_cbh handle, const char *buf, size_t len);
typedef bool (*task_done_cb)(task_cbh handle, bool success, bool abort);
typedef bool (*task_run_cb)(task_cbh handle, bool *success);
typedef void (*task_closescript_cb)(task_cbh handle);
typedef struct {
    const char *shortname;
    enum iaction ia;
    unsigned flags;
    task_data_cb data;
    task_done_cb done;
    task_run_cb run;
    task_closescript_cb closescript;
} tcb_t;
#define CB_UI		0x1	/* came from the UI */
#define CB_NEEDS_RUN	0x2	/* needs its run method called */
#define CB_NEW_TASKQ	0x4	/* creates a new task queue */
char *push_cb(const char *buf, size_t len, const tcb_t *cb,
	task_cbh handle);
void task_activate(task_cbh handle);
void task_register(void);
char *task_cb_prompt(task_cbh handle);
unsigned long task_cb_msec(task_cbh handle);