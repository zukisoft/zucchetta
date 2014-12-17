//-----------------------------------------------------------------------------
// Copyright (c) 2014 Michael G. Brehm
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "syscalls.h"
#include "LinuxException.h"

#pragma warning(push, 4)

// g_rpccontext (main.cpp)
//
// RPC context handle
extern sys32_context_t g_rpccontext;

// REMOTE_SYSCALL_X
//
// Remote system call implementations; each argument must be valid to be passed directly
// into the RPC interface or require any RPC memory allocation/release operations, otherwise
// there needs to be a LOCAL_SYSCALL_X function defined for it
#define REMOTE_SYSCALL_0(_syscall) \
[](PCONTEXT context) -> uapi::long_t { UNREFERENCED_PARAMETER(context); return _syscall(g_rpccontext); }

#define REMOTE_SYSCALL_1(_syscall, _type_0) \
[](PCONTEXT context) -> uapi::long_t { return _syscall(g_rpccontext, (_type_0)(context->Ebx)); }

#define REMOTE_SYSCALL_2(_syscall, _type_0, _type_1) \
[](PCONTEXT context) -> uapi::long_t { return _syscall(g_rpccontext, (_type_0)(context->Ebx), (_type_1)(context->Ecx)); }

#define REMOTE_SYSCALL_3(_syscall, _type_0, _type_1, _type_2) \
[](PCONTEXT context) -> uapi::long_t { return _syscall(g_rpccontext, (_type_0)(context->Ebx), (_type_1)(context->Ecx), (_type_2)(context->Edx)); }

#define REMOTE_SYSCALL_4(_syscall, _type_0, _type_1, _type_2, _type_3) \
[](PCONTEXT context) -> uapi::long_t { return _syscall(g_rpccontext, (_type_0)(context->Ebx), (_type_1)(context->Ecx), (_type_2)(context->Edx), (_type_3)(context->Esi)); }

#define REMOTE_SYSCALL_5(_syscall, _type_0, _type_1, _type_2, _type_3, _type_4) \
[](PCONTEXT context) -> uapi::long_t { return _syscall(g_rpccontext, (_type_0)(context->Ebx), (_type_1)(context->Ecx), (_type_2)(context->Edx), (_type_3)(context->Esi), (_type_4)(context->Edi)); }

#define REMOTE_SYSCALL_6(_syscall, _type_0, _type_1, _type_2, _type_3, _type_4, _type_5) \
[](PCONTEXT context) -> uapi::long_t { return _syscall(g_rpccontext, (_type_0)(context->Ebx), (_type_1)(context->Ecx), (_type_2)(context->Edx), (_type_3)(context->Esi), (_type_4)(context->Edi), (_type_5)(context->Ebp)); }

// CONTEXT_SYSCALL
//
// System call implementation that operates against the raw CONTEXT structure
#define CONTEXT_SYSCALL(_syscall) _syscall

// LOCAL_SYSCALL_X
//
// Local system call implementations
#define LOCAL_SYSCALL_0(_syscall) \
[](PCONTEXT context) -> uapi::long_t { UNREFERENCED_PARAMETER(context); return _syscall(); }

#define LOCAL_SYSCALL_1(_syscall, _type_0) \
[](PCONTEXT context) -> uapi::long_t { return _syscall((_type_0)(context->Ebx)); }

#define LOCAL_SYSCALL_2(_syscall, _type_0, _type_1) \
[](PCONTEXT context) -> uapi::long_t { return _syscall((_type_0)(context->Ebx), (_type_1)(context->Ecx)); }

#define LOCAL_SYSCALL_3(_syscall, _type_0, _type_1, _type_2) \
[](PCONTEXT context) -> uapi::long_t { return _syscall((_type_0)(context->Ebx), (_type_1)(context->Ecx), (_type_2)(context->Edx)); }

#define LOCAL_SYSCALL_4(_syscall, _type_0, _type_1, _type_2, _type_3) \
[](PCONTEXT context) -> uapi::long_t { return _syscall((_type_0)(context->Ebx), (_type_1)(context->Ecx), (_type_2)(context->Edx), (_type_3)(context->Esi)); }

#define LOCAL_SYSCALL_5(_syscall, _type_0, _type_1, _type_2, _type_3, _type_4) \
[](PCONTEXT context) -> uapi::long_t { return _syscall((_type_0)(context->Ebx), (_type_1)(context->Ecx), (_type_2)(context->Edx), (_type_3)(context->Esi), (_type_4)(context->Edi)); }

#define LOCAL_SYSCALL_6(_syscall, _type_0, _type_1, _type_2, _type_3, _type_4, _type_5) \
[](PCONTEXT context) -> uapi::long_t { return _syscall((_type_0)(context->Ebx), (_type_1)(context->Ecx), (_type_2)(context->Edx), (_type_3)(context->Esi), (_type_4)(context->Edi), (_type_5)(context->Ebp)); }

//-----------------------------------------------------------------------------
// sys_noentry
//
// Stub system call entry for ordinals that aren't implemented
uapi::long_t sys_noentry(PCONTEXT context) 
{ 
	UNREFERENCED_PARAMETER(context);
	_RPT1(_CRT_WARN, "sys_noentry: system call number %d requested\r\n", context->Eax);

	return -LINUX_ENOSYS; 
}

//-----------------------------------------------------------------------------
// g_syscalls
//
// Table of all system calls arranged by ordinal
syscall_t g_syscalls[512] = {

/* 000 */	sys_noentry,
/* 001 */	sys_noentry,
/* 002 */	sys_noentry,
/* 003 */	REMOTE_SYSCALL_3(sys32_read, sys32_int_t, sys32_uchar_t*, sys32_size_t),
/* 004 */	REMOTE_SYSCALL_3(sys32_write, sys32_int_t, const sys32_uchar_t*, sys32_size_t),
/* 005 */	REMOTE_SYSCALL_3(sys32_open, const sys32_char_t*, sys32_int_t, sys32_mode_t),
/* 006 */	REMOTE_SYSCALL_1(sys32_close, sys32_int_t),
/* 007 */	sys_noentry,
/* 008 */	REMOTE_SYSCALL_2(sys32_creat, const sys32_char_t*, sys32_mode_t),
/* 009 */	sys_noentry,
/* 010 */	sys_noentry,
/* 011 */	sys_noentry,
/* 012 */	sys_noentry,
/* 013 */	sys_noentry,
/* 014 */	REMOTE_SYSCALL_3(sys32_mknod, const sys32_char_t*, sys32_mode_t, sys32_dev_t),
/* 015 */	sys_noentry,
/* 016 */	sys_noentry,
/* 017 */	sys_noentry,
/* 018 */	sys_noentry,
/* 019 */	sys_noentry,
/* 020 */	REMOTE_SYSCALL_0(sys32_getpid),
/* 021 */	REMOTE_SYSCALL_5(sys32_mount, const sys32_char_t*, const sys32_char_t*, const sys32_char_t*, sys32_ulong_t, sys32_addr_t),
/* 022 */	sys_noentry,
/* 023 */	sys_noentry,
/* 024 */	sys_noentry,
/* 025 */	sys_noentry,
/* 026 */	sys_noentry,
/* 027 */	sys_noentry,
/* 028 */	sys_noentry,
/* 029 */	sys_noentry,
/* 030 */	sys_noentry,
/* 031 */	sys_noentry,
/* 032 */	sys_noentry,
/* 033 */	REMOTE_SYSCALL_2(sys32_access, const sys32_char_t*, sys32_mode_t),
/* 034 */	sys_noentry,
/* 035 */	sys_noentry,
/* 036 */	sys_noentry,
/* 037 */	sys_noentry,
/* 038 */	sys_noentry,
/* 039 */	REMOTE_SYSCALL_2(sys32_mkdir, const sys32_char_t*, sys32_mode_t),
/* 040 */	sys_noentry,
/* 041 */	sys_noentry,
/* 042 */	sys_noentry,
/* 043 */	sys_noentry,
/* 044 */	sys_noentry,
/* 045 */	REMOTE_SYSCALL_1(sys32_brk, sys32_addr_t),
/* 046 */	sys_noentry,
/* 047 */	sys_noentry,
/* 048 */	sys_noentry,
/* 049 */	sys_noentry,
/* 050 */	sys_noentry,
/* 051 */	sys_noentry,
/* 052 */	sys_noentry,
/* 053 */	sys_noentry,
/* 054 */	sys_noentry,
/* 055 */	sys_noentry,
/* 056 */	sys_noentry,
/* 057 */	sys_noentry,
/* 058 */	sys_noentry,
/* 059 */	REMOTE_SYSCALL_1(sys32_olduname, linux_oldold_utsname*),
/* 060 */	REMOTE_SYSCALL_1(sys32_umask, sys32_mode_t),
/* 061 */	sys_noentry,
/* 062 */	sys_noentry,
/* 063 */	sys_noentry,
/* 064 */	REMOTE_SYSCALL_0(sys32_getppid),
/* 065 */	sys_noentry,
/* 066 */	sys_noentry,
/* 067 */	sys_noentry,
/* 068 */	sys_noentry,
/* 069 */	sys_noentry,
/* 070 */	sys_noentry,
/* 071 */	sys_noentry,
/* 072 */	sys_noentry,
/* 073 */	sys_noentry,
/* 074 */	REMOTE_SYSCALL_2(sys32_sethostname, sys32_char_t*, sys32_size_t),
/* 075 */	sys_noentry,
/* 076 */	sys_noentry,
/* 077 */	sys_noentry,
/* 078 */	sys_noentry,
/* 079 */	sys_noentry,
/* 080 */	sys_noentry,
/* 081 */	sys_noentry,
/* 082 */	sys_noentry,
/* 083 */	sys_noentry,
/* 084 */	sys_noentry,
/* 085 */	REMOTE_SYSCALL_3(sys32_readlink, const sys32_char_t*, sys32_char_t*, sys32_size_t),
/* 086 */	sys_noentry,
/* 087 */	sys_noentry,
/* 088 */	sys_noentry,
/* 089 */	sys_noentry,
/* 090 */	LOCAL_SYSCALL_6(sys_old_mmap, void*, uapi::size_t, int, int, int, uapi::off_t),
/* 091 */	REMOTE_SYSCALL_2(sys32_munmap, sys32_addr_t, sys32_size_t),
/* 092 */	sys_noentry,
/* 093 */	sys_noentry,
/* 094 */	sys_noentry,
/* 095 */	sys_noentry,
/* 096 */	sys_noentry,
/* 097 */	sys_noentry,
/* 098 */	sys_noentry,
/* 099 */	REMOTE_SYSCALL_2(sys32_statfs, const sys32_char_t*, linux_statfs32*),
/* 100 */	REMOTE_SYSCALL_2(sys32_fstatfs, sys32_int_t, linux_statfs32*),
/* 101 */	sys_noentry,
/* 102 */	sys_noentry,
/* 103 */	sys_noentry,
/* 104 */	sys_noentry,
/* 105 */	sys_noentry,
/* 106 */	sys_noentry,
/* 107 */	sys_noentry,
/* 108 */	sys_noentry,
/* 109 */	REMOTE_SYSCALL_1(sys32_uname, linux_old_utsname*),
/* 110 */	sys_noentry,
/* 111 */	sys_noentry,
/* 112 */	sys_noentry,
/* 113 */	sys_noentry,
/* 114 */	sys_noentry,
/* 115 */	sys_noentry,
/* 116 */	sys_noentry,
/* 117 */	sys_noentry,
/* 118 */	sys_noentry,
/* 119 */	sys_noentry,
/* 120 */	CONTEXT_SYSCALL(sys_clone),
/* 121 */	REMOTE_SYSCALL_2(sys32_setdomainname, sys32_char_t*, sys32_size_t),
/* 122 */	REMOTE_SYSCALL_1(sys32_newuname, linux_new_utsname*),
/* 123 */	sys_noentry,
/* 124 */	sys_noentry,
/* 125 */	REMOTE_SYSCALL_3(sys32_mprotect, sys32_addr_t, sys32_size_t, sys32_int_t),
/* 126 */	sys_noentry,
/* 127 */	sys_noentry,
/* 128 */	sys_noentry,
/* 129 */	sys_noentry,
/* 130 */	sys_noentry,
/* 131 */	sys_noentry,
/* 132 */	sys_noentry,
/* 133 */	sys_noentry,
/* 134 */	sys_noentry,
/* 135 */	sys_noentry,
/* 136 */	sys_noentry,
/* 137 */	sys_noentry,
/* 138 */	sys_noentry,
/* 139 */	sys_noentry,
/* 140 */	sys_noentry,
/* 141 */	sys_noentry,
/* 142 */	sys_noentry,
/* 143 */	sys_noentry,
/* 144 */	sys_noentry,
/* 145 */	sys_noentry,
/* 146 */	REMOTE_SYSCALL_3(sys32_writev, sys32_int_t, sys32_iovec_t*, sys32_int_t),
/* 147 */	sys_noentry,
/* 148 */	sys_noentry,
/* 149 */	sys_noentry,
/* 150 */	sys_noentry,
/* 151 */	sys_noentry,
/* 152 */	sys_noentry,
/* 153 */	sys_noentry,
/* 154 */	sys_noentry,
/* 155 */	sys_noentry,
/* 156 */	sys_noentry,
/* 157 */	sys_noentry,
/* 158 */	sys_noentry,
/* 159 */	sys_noentry,
/* 160 */	sys_noentry,
/* 161 */	sys_noentry,
/* 162 */	sys_noentry,
/* 163 */	sys_noentry,
/* 164 */	sys_noentry,
/* 165 */	sys_noentry,
/* 166 */	sys_noentry,
/* 167 */	sys_noentry,
/* 168 */	sys_noentry,
/* 169 */	sys_noentry,
/* 170 */	sys_noentry,
/* 171 */	sys_noentry,
/* 172 */	REMOTE_SYSCALL_5(sys32_prctl, sys32_int_t, sys32_ulong_t, sys32_ulong_t, sys32_ulong_t, sys32_ulong_t),
/* 173 */	sys_noentry,
/* 174 */	REMOTE_SYSCALL_5(sys32_rt_sigaction, sys32_int_t, sys32_addr_t, sys32_addr_t, sys32_size_t, sys32_addr_t),
/* 175 */	REMOTE_SYSCALL_4(sys32_rt_sigprocmask, sys32_int_t, const sys32_sigset_t*, sys32_sigset_t*, sys32_size_t),
/* 176 */	sys_noentry,
/* 177 */	sys_noentry,
/* 178 */	sys_noentry,
/* 179 */	sys_noentry,
/* 180 */	sys_noentry,
/* 181 */	sys_noentry,
/* 182 */	sys_noentry,
/* 183 */	REMOTE_SYSCALL_2(sys32_getcwd, sys32_char_t*, sys32_ulong_t),
/* 184 */	sys_noentry,
/* 185 */	sys_noentry,
/* 186 */	sys_noentry,
/* 187 */	sys_noentry,
/* 188 */	sys_noentry,
/* 189 */	sys_noentry,
/* 190 */	sys_noentry,
/* 191 */	sys_noentry,
/* 192 */	LOCAL_SYSCALL_6(sys_mmap, void*, uapi::size_t, int, int, int, uapi::off_t),
/* 193 */	sys_noentry,
/* 194 */	sys_noentry,
/* 195 */	REMOTE_SYSCALL_2(sys32_stat64, const sys32_char_t*, linux_stat3264*),
/* 196 */	REMOTE_SYSCALL_2(sys32_lstat64, const sys32_char_t*, linux_stat3264*),
/* 197 */	REMOTE_SYSCALL_2(sys32_fstat64, sys32_int_t, linux_stat3264*),
/* 198 */	sys_noentry,
/* 199 */	REMOTE_SYSCALL_0(sys32_getuid),
/* 200 */	REMOTE_SYSCALL_0(sys32_getgid),
/* 201 */	sys_noentry,
/* 202 */	sys_noentry,
/* 203 */	sys_noentry,
/* 204 */	sys_noentry,
/* 205 */	sys_noentry,
/* 206 */	sys_noentry,
/* 207 */	sys_noentry,
/* 208 */	sys_noentry,
/* 209 */	sys_noentry,
/* 210 */	sys_noentry,
/* 211 */	sys_noentry,
/* 212 */	sys_noentry,
/* 213 */	sys_noentry,
/* 214 */	sys_noentry,
/* 215 */	sys_noentry,
/* 216 */	sys_noentry,
/* 217 */	sys_noentry,
/* 218 */	sys_noentry,
/* 219 */	REMOTE_SYSCALL_3(sys32_madvise, sys32_addr_t, sys32_size_t, sys32_int_t),
/* 220 */	sys_noentry,
/* 221 */	REMOTE_SYSCALL_3(sys32_fcntl64, sys32_int_t, sys32_int_t, sys32_addr_t),
/* 222 */	sys_noentry,
/* 223 */	sys_noentry,
/* 224 */	sys_noentry,
/* 225 */	sys_noentry,
/* 226 */	sys_noentry,
/* 227 */	sys_noentry,
/* 228 */	sys_noentry,
/* 229 */	sys_noentry,
/* 230 */	sys_noentry,
/* 231 */	sys_noentry,
/* 232 */	sys_noentry,
/* 233 */	sys_noentry,
/* 234 */	sys_noentry,
/* 235 */	sys_noentry,
/* 236 */	sys_noentry,
/* 237 */	sys_noentry,
/* 238 */	sys_noentry,
/* 239 */	sys_noentry,
/* 240 */	sys_noentry,
/* 241 */	sys_noentry,
/* 242 */	sys_noentry,
/* 243 */	LOCAL_SYSCALL_1(sys_set_thread_area, uapi::user_desc*),
/* 244 */	sys_noentry,
/* 245 */	sys_noentry,
/* 246 */	sys_noentry,
/* 247 */	sys_noentry,
/* 248 */	sys_noentry,
/* 249 */	sys_noentry,
/* 250 */	sys_noentry,
/* 251 */	sys_noentry,
/* 252 */	sys_noentry,
/* 253 */	sys_noentry,
/* 254 */	sys_noentry,
/* 255 */	sys_noentry,
/* 256 */	sys_noentry,
/* 257 */	sys_noentry,
/* 258 */	REMOTE_SYSCALL_1(sys32_set_tid_address, sys32_addr_t),
/* 259 */	sys_noentry,
/* 260 */	sys_noentry,
/* 261 */	sys_noentry,
/* 262 */	sys_noentry,
/* 263 */	sys_noentry,
/* 264 */	sys_noentry,
/* 265 */	sys_noentry,
/* 266 */	sys_noentry,
/* 267 */	sys_noentry,
/* 268 */	REMOTE_SYSCALL_3(sys32_statfs64, const sys32_char_t*, sys32_size_t, linux_statfs3264*),
/* 269 */	REMOTE_SYSCALL_3(sys32_fstatfs64, sys32_int_t, sys32_size_t, linux_statfs3264*),
/* 270 */	REMOTE_SYSCALL_3(sys32_tgkill, sys32_pid_t, sys32_pid_t, sys32_int_t),
/* 271 */	sys_noentry,
/* 272 */	sys_noentry,
/* 273 */	sys_noentry,
/* 274 */	sys_noentry,
/* 275 */	sys_noentry,
/* 276 */	sys_noentry,
/* 277 */	sys_noentry,
/* 278 */	sys_noentry,
/* 279 */	sys_noentry,
/* 280 */	sys_noentry,
/* 281 */	sys_noentry,
/* 282 */	sys_noentry,
/* 283 */	sys_noentry,
/* 284 */	sys_noentry,
/* 285 */	sys_noentry,
/* 286 */	sys_noentry,
/* 287 */	sys_noentry,
/* 288 */	sys_noentry,
/* 289 */	sys_noentry,
/* 290 */	sys_noentry,
/* 291 */	sys_noentry,
/* 292 */	sys_noentry,
/* 293 */	sys_noentry,
/* 294 */	sys_noentry,
/* 295 */	REMOTE_SYSCALL_4(sys32_openat, sys32_int_t, const sys32_char_t*, sys32_int_t, sys32_mode_t),
/* 296 */	REMOTE_SYSCALL_3(sys32_mkdirat, sys32_int_t, const sys32_char_t*, sys32_mode_t),
/* 297 */	REMOTE_SYSCALL_4(sys32_mknodat, sys32_int_t, const sys32_char_t*, sys32_mode_t, sys32_dev_t),
/* 298 */	sys_noentry,
/* 299 */	sys_noentry,
/* 300 */	REMOTE_SYSCALL_4(sys32_fstatat64, sys32_int_t, const sys32_char_t*, linux_stat3264*, sys32_int_t),
/* 301 */	sys_noentry,
/* 302 */	sys_noentry,
/* 303 */	sys_noentry,
/* 304 */	sys_noentry,
/* 305 */	sys_noentry,
/* 306 */	sys_noentry,
/* 307 */	sys_noentry,
/* 308 */	sys_noentry,
/* 309 */	sys_noentry,
/* 310 */	sys_noentry,
/* 311 */	sys_noentry,
/* 312 */	sys_noentry,
/* 313 */	sys_noentry,
/* 314 */	sys_noentry,
/* 315 */	sys_noentry,
/* 316 */	sys_noentry,
/* 317 */	sys_noentry,
/* 318 */	sys_noentry,
/* 319 */	sys_noentry,
/* 320 */	sys_noentry,
/* 321 */	sys_noentry,
/* 322 */	sys_noentry,
/* 323 */	sys_noentry,
/* 324 */	sys_noentry,
/* 325 */	sys_noentry,
/* 326 */	sys_noentry,
/* 327 */	sys_noentry,
/* 328 */	sys_noentry,
/* 329 */	sys_noentry,
/* 330 */	sys_noentry,
/* 331 */	sys_noentry,
/* 332 */	sys_noentry,
/* 333 */	sys_noentry,
/* 334 */	sys_noentry,
/* 335 */	sys_noentry,
/* 336 */	sys_noentry,
/* 337 */	sys_noentry,
/* 338 */	sys_noentry,
/* 339 */	sys_noentry,
/* 340 */	sys_noentry,
/* 341 */	sys_noentry,
/* 342 */	sys_noentry,
/* 343 */	sys_noentry,
/* 344 */	sys_noentry,
/* 345 */	sys_noentry,
/* 346 */	sys_noentry,
/* 347 */	sys_noentry,
/* 348 */	sys_noentry,
/* 349 */	sys_noentry,
/* 350 */	sys_noentry,
/* 351 */	sys_noentry,
/* 352 */	sys_noentry,
/* 353 */	sys_noentry,
/* 354 */	sys_noentry,
/* 355 */	sys_noentry,
/* 356 */	sys_noentry,
/* 357 */	sys_noentry,
/* 358 */	sys_noentry,
/* 359 */	sys_noentry,
/* 360 */	sys_noentry,
/* 361 */	sys_noentry,
/* 362 */	sys_noentry,
/* 363 */	sys_noentry,
/* 364 */	sys_noentry,
/* 365 */	sys_noentry,
/* 366 */	sys_noentry,
/* 367 */	sys_noentry,
/* 368 */	sys_noentry,
/* 369 */	sys_noentry,
/* 370 */	sys_noentry,
/* 371 */	sys_noentry,
/* 372 */	sys_noentry,
/* 373 */	sys_noentry,
/* 374 */	sys_noentry,
/* 375 */	sys_noentry,
/* 376 */	sys_noentry,
/* 377 */	sys_noentry,
/* 378 */	sys_noentry,
/* 379 */	sys_noentry,
/* 380 */	sys_noentry,
/* 381 */	sys_noentry,
/* 382 */	sys_noentry,
/* 383 */	sys_noentry,
/* 384 */	sys_noentry,
/* 385 */	sys_noentry,
/* 386 */	sys_noentry,
/* 387 */	sys_noentry,
/* 388 */	sys_noentry,
/* 389 */	sys_noentry,
/* 390 */	sys_noentry,
/* 391 */	sys_noentry,
/* 392 */	sys_noentry,
/* 393 */	sys_noentry,
/* 394 */	sys_noentry,
/* 395 */	sys_noentry,
/* 396 */	sys_noentry,
/* 397 */	sys_noentry,
/* 398 */	sys_noentry,
/* 399 */	sys_noentry,
/* 400 */	sys_noentry,
/* 401 */	sys_noentry,
/* 402 */	sys_noentry,
/* 403 */	sys_noentry,
/* 404 */	sys_noentry,
/* 405 */	sys_noentry,
/* 406 */	sys_noentry,
/* 407 */	sys_noentry,
/* 408 */	sys_noentry,
/* 409 */	sys_noentry,
/* 410 */	sys_noentry,
/* 411 */	sys_noentry,
/* 412 */	sys_noentry,
/* 413 */	sys_noentry,
/* 414 */	sys_noentry,
/* 415 */	sys_noentry,
/* 416 */	sys_noentry,
/* 417 */	sys_noentry,
/* 418 */	sys_noentry,
/* 419 */	sys_noentry,
/* 420 */	sys_noentry,
/* 421 */	sys_noentry,
/* 422 */	sys_noentry,
/* 423 */	sys_noentry,
/* 424 */	sys_noentry,
/* 425 */	sys_noentry,
/* 426 */	sys_noentry,
/* 427 */	sys_noentry,
/* 428 */	sys_noentry,
/* 429 */	sys_noentry,
/* 430 */	sys_noentry,
/* 431 */	sys_noentry,
/* 432 */	sys_noentry,
/* 433 */	sys_noentry,
/* 434 */	sys_noentry,
/* 435 */	sys_noentry,
/* 436 */	sys_noentry,
/* 437 */	sys_noentry,
/* 438 */	sys_noentry,
/* 439 */	sys_noentry,
/* 440 */	sys_noentry,
/* 441 */	sys_noentry,
/* 442 */	sys_noentry,
/* 443 */	sys_noentry,
/* 444 */	sys_noentry,
/* 445 */	sys_noentry,
/* 446 */	sys_noentry,
/* 447 */	sys_noentry,
/* 448 */	sys_noentry,
/* 449 */	sys_noentry,
/* 450 */	sys_noentry,
/* 451 */	sys_noentry,
/* 452 */	sys_noentry,
/* 453 */	sys_noentry,
/* 454 */	sys_noentry,
/* 455 */	sys_noentry,
/* 456 */	sys_noentry,
/* 457 */	sys_noentry,
/* 458 */	sys_noentry,
/* 459 */	sys_noentry,
/* 460 */	sys_noentry,
/* 461 */	sys_noentry,
/* 462 */	sys_noentry,
/* 463 */	sys_noentry,
/* 464 */	sys_noentry,
/* 465 */	sys_noentry,
/* 466 */	sys_noentry,
/* 467 */	sys_noentry,
/* 468 */	sys_noentry,
/* 469 */	sys_noentry,
/* 470 */	sys_noentry,
/* 471 */	sys_noentry,
/* 472 */	sys_noentry,
/* 473 */	sys_noentry,
/* 474 */	sys_noentry,
/* 475 */	sys_noentry,
/* 476 */	sys_noentry,
/* 477 */	sys_noentry,
/* 478 */	sys_noentry,
/* 479 */	sys_noentry,
/* 480 */	sys_noentry,
/* 481 */	sys_noentry,
/* 482 */	sys_noentry,
/* 483 */	sys_noentry,
/* 484 */	sys_noentry,
/* 485 */	sys_noentry,
/* 486 */	sys_noentry,
/* 487 */	sys_noentry,
/* 488 */	sys_noentry,
/* 489 */	sys_noentry,
/* 490 */	sys_noentry,
/* 491 */	sys_noentry,
/* 492 */	sys_noentry,
/* 493 */	sys_noentry,
/* 494 */	sys_noentry,
/* 495 */	sys_noentry,
/* 496 */	sys_noentry,
/* 497 */	sys_noentry,
/* 498 */	sys_noentry,
/* 499 */	sys_noentry,
/* 500 */	sys_noentry,
/* 501 */	sys_noentry,
/* 502 */	sys_noentry,
/* 503 */	sys_noentry,
/* 504 */	sys_noentry,
/* 505 */	sys_noentry,
/* 506 */	sys_noentry,
/* 507 */	sys_noentry,
/* 508 */	sys_noentry,
/* 509 */	sys_noentry,
/* 510 */	sys_noentry,
/* 511 */	sys_noentry
};

//-----------------------------------------------------------------------------

#pragma warning(pop)
