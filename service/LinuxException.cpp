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
#include "LinuxException.h"

#pragma warning(push, 4)

const LinuxException::ErrorMapEntry LinuxException::s_map[] = {
	
	{ LINUX_EPERM,           "EPERM",           "Operation not permitted" },
	{ LINUX_ENOENT,          "ENOENT",          "No such file or directory" },
	{ LINUX_ESRCH,           "ESRCH",           "No such process" },
	{ LINUX_EINTR,           "EINTR",           "Interrupted system call" },
	{ LINUX_EIO,             "EIO",             "I/O error" },
	{ LINUX_ENXIO,           "ENXIO",           "No such device or address" },
	{ LINUX_E2BIG,           "E2BIG",           "Argument list too long" },
	{ LINUX_ENOEXEC,         "ENOEXEC",         "Exec format error" },
	{ LINUX_EBADF,           "EBADF",           "Bad file number" },
	{ LINUX_ECHILD,          "ECHILD",          "No child processes" },
	{ LINUX_EAGAIN,          "EAGAIN",          "Try again" },
	{ LINUX_ENOMEM,          "ENOMEM",          "Out of memory" },
	{ LINUX_EACCES,          "EACCES",          "Permission denied" },
	{ LINUX_EFAULT,          "EFAULT",          "Bad address" },
	{ LINUX_ENOTBLK,         "ENOTBLK",         "Block device required" },
	{ LINUX_EBUSY,           "EBUSY",           "Device or resource busy" },
	{ LINUX_EEXIST,          "EEXIST",          "File exists" },
	{ LINUX_EXDEV,           "EXDEV",           "Cross-device link" },
	{ LINUX_ENODEV,          "ENODEV",          "No such device" },
	{ LINUX_ENOTDIR,         "ENOTDIR",         "Not a directory" },
	{ LINUX_EISDIR,          "EISDIR",          "Is a directory" },
	{ LINUX_EINVAL,          "EINVAL",          "Invalid argument" },
	{ LINUX_ENFILE,          "ENFILE",          "File table overflow" },
	{ LINUX_EMFILE,          "EMFILE",          "Too many open files" },
	{ LINUX_ENOTTY,          "ENOTTY",          "Not a typewriter" },
	{ LINUX_ETXTBSY,         "ETXTBSY",         "Text file busy" },
	{ LINUX_EFBIG,           "EFBIG",           "File too large" },
	{ LINUX_ENOSPC,          "ENOSPC",          "No space left on device" },
	{ LINUX_ESPIPE,          "ESPIPE",          "Illegal seek" },
	{ LINUX_EROFS,           "EROFS",           "Read-only file system" },
	{ LINUX_EMLINK,          "EMLINK",          "Too many links" },
	{ LINUX_EPIPE,           "EPIPE",           "Broken pipe" },
	{ LINUX_EDOM,            "EDOM",            "Math argument out of domain of func" },
	{ LINUX_ERANGE,          "ERANGE",          "Math result not representable" },
	{ LINUX_EDEADLK,         "EDEADLK",         "Resource deadlock would occur" },
	{ LINUX_ENAMETOOLONG,    "ENAMETOOLONG",    "File name too long" },
	{ LINUX_ENOLCK,          "ENOLCK",          "No record locks available" },
	{ LINUX_ENOSYS,          "ENOSYS",          "Function not implemented" },
	{ LINUX_ENOTEMPTY,       "ENOTEMPTY",       "Directory not empty" },
	{ LINUX_ELOOP,           "ELOOP",           "Too many symbolic links encountered" },
	{ LINUX_ENOMSG,          "ENOMSG",          "No message of desired type" },
	{ LINUX_EIDRM,           "EIDRM",           "Identifier removed" },
	{ LINUX_ECHRNG,          "ECHRNG",          "Channel number out of range" },
	{ LINUX_EL2NSYNC,        "EL2NSYNC",        "Level 2 not synchronized" },
	{ LINUX_EL3HLT,          "EL3HLT",          "Level 3 halted" },
	{ LINUX_EL3RST,          "EL3RST",          "Level 3 reset" },
	{ LINUX_ELNRNG,          "ELNRNG",          "Link number out of range" },
	{ LINUX_EUNATCH,         "EUNATCH",         "Protocol driver not attached" },
	{ LINUX_ENOCSI,          "ENOCSI",          "No CSI structure available" },
	{ LINUX_EL2HLT,          "EL2HLT",          "Level 2 halted" },
	{ LINUX_EBADE,           "EBADE",           "Invalid exchange" },
	{ LINUX_EBADR,           "EBADR",           "Invalid request descriptor" },
	{ LINUX_EXFULL,          "EXFULL",          "Exchange full" },
	{ LINUX_ENOANO,          "ENOANO",          "No anode" },
	{ LINUX_EBADRQC,         "EBADRQC",         "Invalid request code" },
	{ LINUX_EBADSLT,         "EBADSLT",         "Invalid slot" },
	{ LINUX_EBFONT,          "EBFONT",          "Bad font file format" },
	{ LINUX_ENOSTR,          "ENOSTR",          "Device not a stream" },
	{ LINUX_ENODATA,         "ENODATA",         "No data available" },
	{ LINUX_ETIME,           "ETIME",           "Timer expired" },
	{ LINUX_ENOSR,           "ENOSR",           "Out of streams resources" },
	{ LINUX_ENONET,          "ENONET",          "Machine is not on the network" },
	{ LINUX_ENOPKG,          "ENOPKG",          "Package not installed" },
	{ LINUX_EREMOTE,         "EREMOTE",         "Object is remote" },
	{ LINUX_ENOLINK,         "ENOLINK",         "Link has been severed" },
	{ LINUX_EADV,            "EADV",            "Advertise error" },
	{ LINUX_ESRMNT,          "ESRMNT",          "Srmount error" },
	{ LINUX_ECOMM,           "ECOMM",           "Communication error on send" },
	{ LINUX_EPROTO,          "EPROTO",          "Protocol error" },
	{ LINUX_EMULTIHOP,       "EMULTIHOP",       "Multihop attempted" },
	{ LINUX_EDOTDOT,         "EDOTDOT",         "RFS specific error" },
	{ LINUX_EBADMSG,         "EBADMSG",         "Not a data message" },
	{ LINUX_EOVERFLOW,       "EOVERFLOW",       "Value too large for defined data type" },
	{ LINUX_ENOTUNIQ,        "ENOTUNIQ",        "Name not unique on network" },
	{ LINUX_EBADFD,          "EBADFD",          "File descriptor in bad state" },
	{ LINUX_EREMCHG,         "EREMCHG",         "Remote address changed" },
	{ LINUX_ELIBACC,         "ELIBACC",         "Can not access a needed shared library" },
	{ LINUX_ELIBBAD,         "ELIBBAD",         "Accessing a corrupted shared library" },
	{ LINUX_ELIBSCN,         "ELIBSCN",         ".lib section in a.out corrupted" },
	{ LINUX_ELIBMAX,         "ELIBMAX",         "Attempting to link in too many shared libraries" },
	{ LINUX_ELIBEXEC,        "ELIBEXEC",        "Cannot exec a shared library directly" },
	{ LINUX_EILSEQ,          "EILSEQ",          "Illegal byte sequence" },
	{ LINUX_ERESTART,        "ERESTART",        "Interrupted system call should be restarted" },
	{ LINUX_ESTRPIPE,        "ESTRPIPE",        "Streams pipe error" },
	{ LINUX_EUSERS,          "EUSERS",          "Too many users" },
	{ LINUX_ENOTSOCK,        "ENOTSOCK",        "Socket operation on non-socket" },
	{ LINUX_EDESTADDRREQ,    "EDESTADDRREQ",    "Destination address required" },
	{ LINUX_EMSGSIZE,        "EMSGSIZE",        "Message too long" },
	{ LINUX_EPROTOTYPE,      "EPROTOTYPE",      "Protocol wrong type for socket" },
	{ LINUX_ENOPROTOOPT,     "ENOPROTOOPT",     "Protocol not available" },
	{ LINUX_EPROTONOSUPPORT, "EPROTONOSUPPORT", "Protocol not supported" },
	{ LINUX_ESOCKTNOSUPPORT, "ESOCKTNOSUPPORT", "Socket type not supported" },
	{ LINUX_EOPNOTSUPP,      "EOPNOTSUPP",      "Operation not supported on transport endpoint" },
	{ LINUX_EPFNOSUPPORT,    "EPFNOSUPPORT",    "Protocol family not supported" },
	{ LINUX_EAFNOSUPPORT,    "EAFNOSUPPORT",    "Address family not supported by protocol" },
	{ LINUX_EADDRINUSE,      "EADDRINUSE",      "Address already in use" },
	{ LINUX_EADDRNOTAVAIL,   "EADDRNOTAVAIL",   "Cannot assign requested address" },
	{ LINUX_ENETDOWN,        "ENETDOWN",        "Network is down" },
	{ LINUX_ENETUNREACH,     "ENETUNREACH",     "Network is unreachable" },
	{ LINUX_ENETRESET,       "ENETRESET",       "Network dropped connection because of reset" },
	{ LINUX_ECONNABORTED,    "ECONNABORTED",    "Software caused connection abort" },
	{ LINUX_ECONNRESET,      "ECONNRESET",      "Connection reset by peer" },
	{ LINUX_ENOBUFS,         "ENOBUFS",         "No buffer space available" },
	{ LINUX_EISCONN,         "EISCONN",         "Transport endpoint is already connected" },
	{ LINUX_ENOTCONN,        "ENOTCONN",        "Transport endpoint is not connected" },
	{ LINUX_ESHUTDOWN,       "ESHUTDOWN",       "Cannot send after transport endpoint shutdown" },
	{ LINUX_ETOOMANYREFS,    "ETOOMANYREFS",    "Too many references: cannot splice" },
	{ LINUX_ETIMEDOUT,       "ETIMEDOUT",       "Connection timed out" },
	{ LINUX_ECONNREFUSED,    "ECONNREFUSED",    "Connection refused" },
	{ LINUX_EHOSTDOWN,       "EHOSTDOWN",       "Host is down" },
	{ LINUX_EHOSTUNREACH,    "EHOSTUNREACH",    "No route to host" },
	{ LINUX_EALREADY,        "EALREADY",        "Operation already in progress" },
	{ LINUX_EINPROGRESS,     "EINPROGRESS",     "Operation now in progress" },
	{ LINUX_ESTALE,          "ESTALE",          "Stale file handle" },
	{ LINUX_EUCLEAN,         "EUCLEAN",         "Structure needs cleaning" },
	{ LINUX_ENOTNAM,         "ENOTNAM",         "Not a XENIX named type file" },
	{ LINUX_ENAVAIL,         "ENAVAIL",         "No XENIX semaphores available" },
	{ LINUX_EISNAM,          "EISNAM",          "Is a named type file" },
	{ LINUX_EREMOTEIO,       "EREMOTEIO",       "Remote I/O error" },
	{ LINUX_EDQUOT,          "EDQUOT",          "Quota exceeded" },
	{ LINUX_ENOMEDIUM,       "ENOMEDIUM",       "No medium found" },
	{ LINUX_EMEDIUMTYPE,     "EMEDIUMTYPE",     "Wrong medium type" },
	{ LINUX_ECANCELED,       "ECANCELED",       "Operation Canceled" },
	{ LINUX_ENOKEY,          "ENOKEY",          "Required key not available" },
	{ LINUX_EKEYEXPIRED,     "EKEYEXPIRED",     "Key has expired" },
	{ LINUX_EKEYREVOKED,     "EKEYREVOKED",     "Key has been revoked" },
	{ LINUX_EKEYREJECTED,    "EKEYREJECTED",    "Key was rejected by service" },
	{ LINUX_EOWNERDEAD,      "EOWNERDEAD",      "Owner died" },
	{ LINUX_ENOTRECOVERABLE, "ENOTRECOVERABLE", "State not recoverable" },
	{ LINUX_ERFKILL,         "ERFKILL",         "Operation not possible due to RF-kill" },
	{ LINUX_EHWPOISON,       "EHWPOISON",       "Memory page has hardware error" },
	{ 0, nullptr, nullptr },
};

//-----------------------------------------------------------------------------

#pragma warning(pop)