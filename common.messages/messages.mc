;//-----------------------------------------------------------------------------
;// Copyright (c) 2016 Michael G. Brehm
;// 
;// Permission is hereby granted, free of charge, to any person obtaining a copy
;// of this software and associated documentation files (the "Software"), to deal
;// in the Software without restriction, including without limitation the rights
;// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
;// copies of the Software, and to permit persons to whom the Software is
;// furnished to do so, subject to the following conditions:
;// 
;// The above copyright notice and this permission notice shall be included in all
;// copies or substantial portions of the Software.
;// 
;// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
;// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
;// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
;// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
;// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
;// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
;// SOFTWARE.
;//-----------------------------------------------------------------------------

;//--------------------------------------------------------------------------
;// Facility Codes
FacilityNames=(
			Generic=0:FACILITY_GENERIC
			Common=1:FACILITY_COMMON
			Linux=2:FACILITY_LINUX
			Elf=3:FACILITY_ELF
			Executable=4:FACILITY_EXECUTABLE
			TaskState=5:FACILITY_TASKSTATE
			Process=6:FACILITY_PROCESS
			Thread=7:FACILITY_THREAD
			Service=8:FACILITY_SERVICE
			)

;//--------------------------------------------------------------------------
;// Language Codes
LanguageNames=(English=0x0409:MSG00409)

;//--------------------------------------------------------------------------
;// Error Definitions
;//--------------------------------------------------------------------------

MessageIdTypedef=HRESULT

;//--------------------------------------------------------------------------
;// GENERIC Error Codes

MessageId=1
Severity=Informational
Facility=Generic
SymbolicName=GENERIC_INFORMATIONAL
Language=English
%1
.

MessageId=
Severity=Warning
SymbolicName=GENERIC_WARNING
Language=English
%1
.

MessageId=
Severity=Error
SymbolicName=GENERIC_ERROR
Language=English
%1
.

MessageId=0x4
Severity=Error
SymbolicName=GENERIC_WIN32_ERROR
Language=English
%1.  Error Code %2 - %3
.

MessageId=
;//ExceptionName=ArgumentNullException,paramname
Severity=Error
SymbolicName=E_ARGUMENTNULL
Language=English
Parameter %1 value cannot be null.
.

MessageId=
;//ExceptionName=ArgumentOutOfRangeException,paramname
Severity=Error
SymbolicName=E_ARGUMENTOUTOFRANGE
Language=English
Parameter %1 was out of the range of valid values.
.

;//----------------------------------------------------------------------------
;// Common
;//
;// Messages for custom exceptions thrown by common code

MessageId=1
Severity=Error
Facility=Common
SymbolicName=E_INDEXPOOL_EXHAUSTED
Language=English
The index pool has been exhausted; no more sequential index values can be allocated
.

MessageId=
Severity=Error
SymbolicName=E_DECOMPRESS_INIT
Language=English
The decompression stream cannot be initialized (method: %1)
.

MessageId=
Severity=Error
SymbolicName=E_DECOMPRESS_BADMAGIC
Language=English
The decompression stream magic number is invalid (method: %1)
.

MessageId=
Severity=Error
SymbolicName=E_DECOMPRESS_BADHEADER
Language=English
The decompression stream header is corrupt (method: %1)
.

MessageId=
Severity=Error
SymbolicName=E_DECOMPRESS_TRUNCATED
Language=English
The decompression stream ended prematurely (method: %1)
.

MessageId=
Severity=Error
SymbolicName=E_DECOMPRESS_CORRUPT
Language=English
The decompression stream data is corrupt (method: %1)
.

MessageId=
Severity=Error
SymbolicName=E_DECOMPRESS_TOOBIG
Language=English
The decompressed stream data is too big for this library (method: %1)
.

MessageId=
Severity=Error
SymbolicName=E_COMPRESSION_FORMAT
Language=English
Compressed file format %1 is not supported 
.

;//----------------------------------------------------------------------------
;// Linux
;//
;// Messages specific to the Linux environment

MessageId=1
Severity=Error
Facility=Linux
SymbolicName=E_LINUX_EPERM 
Language=English
EPERM: Operation not permitted
.

MessageId=2
Severity=Error
SymbolicName=E_LINUX_ENOENT
Language=English
ENOENT: No such file or directory
.

MessageId=3
Severity=Error
SymbolicName=E_LINUX_ESRCH
Language=English
ESRCH: No such process
.

MessageId=4
Severity=Error
SymbolicName=E_LINUX_EINTR
Language=English
EINTR: Interrupted system call
.

MessageId=5
Severity=Error
SymbolicName=E_LINUX_EIO
Language=English
EIO: I/O error
.

MessageId=6
Severity=Error
SymbolicName=E_LINUX_ENXIO
Language=English
ENXIO: No such device or address
.

MessageId=7
Severity=Error
SymbolicName=E_LINUX_E2BIG           
Language=English
E2BIG: Argument list too long
.

MessageId=8
Severity=Error
SymbolicName=E_LINUX_ENOEXEC         
Language=English
ENOEXEC: Exec format error
.

MessageId=9
Severity=Error
SymbolicName=E_LINUX_EBADF           
Language=English
EBADF: Bad file number
.

MessageId=10
Severity=Error
SymbolicName=E_LINUX_ECHILD          
Language=English
ECHILD: No child processes
.

MessageId=11
Severity=Error
SymbolicName=E_LINUX_EAGAIN          
Language=English
EAGAIN: Try again
.

MessageId=12
Severity=Error
SymbolicName=E_LINUX_ENOMEM          
Language=English
ENOMEM: Out of memory
.

MessageId=13
Severity=Error
SymbolicName=E_LINUX_EACCES          
Language=English
EACCES: Permission denied
.

MessageId=14
Severity=Error
SymbolicName=E_LINUX_EFAULT          
Language=English
EFAULT: Bad address
.

MessageId=15
Severity=Error
SymbolicName=E_LINUX_ENOTBLK         
Language=English
ENOTBLK: Block device required
.

MessageId=16
Severity=Error
SymbolicName=E_LINUX_EBUSY           
Language=English
EBUSY: Device or resource busy
.

MessageId=17
Severity=Error
SymbolicName=E_LINUX_EEXIST          
Language=English
EEXIST: File exists
.

MessageId=18
Severity=Error
SymbolicName=E_LINUX_EXDEV           
Language=English
EXDEV: Cross-device link
.

MessageId=19
Severity=Error
SymbolicName=E_LINUX_ENODEV          
Language=English
ENODEV: No such device
.

MessageId=20
Severity=Error
SymbolicName=E_LINUX_ENOTDIR         
Language=English
ENOTDIR: Not a directory
.

MessageId=21
Severity=Error
SymbolicName=E_LINUX_EISDIR          
Language=English
EISDIR: Is a directory
.

MessageId=22
Severity=Error
SymbolicName=E_LINUX_EINVAL          
Language=English
EINVAL: Invalid argument
.

MessageId=23
Severity=Error
SymbolicName=E_LINUX_ENFILE          
Language=English
ENFILE: File table overflow
.

MessageId=24
Severity=Error
SymbolicName=E_LINUX_EMFILE          
Language=English
EMFILE: Too many open files
.

MessageId=25
Severity=Error
SymbolicName=E_LINUX_ENOTTY          
Language=English
ENOTTY: Not a typewriter
.

MessageId=26
Severity=Error
SymbolicName=E_LINUX_ETXTBSY         
Language=English
ETXTBSY: Text file busy
.

MessageId=27
Severity=Error
SymbolicName=E_LINUX_EFBIG           
Language=English
EFBIG: File too large
.

MessageId=28
Severity=Error
SymbolicName=E_LINUX_ENOSPC          
Language=English
ENOSPC: No space left on device
.

MessageId=29
Severity=Error
SymbolicName=E_LINUX_ESPIPE          
Language=English
ESPIPE: Illegal seek
.

MessageId=30
Severity=Error
SymbolicName=E_LINUX_EROFS           
Language=English
EROFS: Read-only file system
.

MessageId=31
Severity=Error
SymbolicName=E_LINUX_EMLINK          
Language=English
EMLINK: Too many links
.

MessageId=32
Severity=Error
SymbolicName=E_LINUX_EPIPE          
Language=English
EPIPE: Broken pipe
.

MessageId=33
Severity=Error
SymbolicName=E_LINUX_EDOM            
Language=English
EDOM: Math argument out of domain of func
.

MessageId=34
Severity=Error
SymbolicName=E_LINUX_ERANGE          
Language=English
ERANGE: Math result not representable
.

MessageId=35
Severity=Error
SymbolicName=E_LINUX_EDEADLK         
Language=English
EDEADLK: Resource deadlock would occur
.

MessageId=36
Severity=Error
SymbolicName=E_LINUX_ENAMETOOLONG    
Language=English
ENAMETOOLONG: File name too long
.

MessageId=37
Severity=Error
SymbolicName=E_LINUX_ENOLCK          
Language=English
ENOLCK: No record locks available
.

MessageId=38
Severity=Error
SymbolicName=E_LINUX_ENOSYS          
Language=English
ENOSYS: Function not implemented
.

MessageId=39
Severity=Error
SymbolicName=E_LINUX_ENOTEMPTY       
Language=English
ENOTEMPTY: Directory not empty
.

MessageId=40
Severity=Error
SymbolicName=E_LINUX_ELOOP           
Language=English
ELOOP: Too many symbolic links encountered
.

MessageId=42
Severity=Error
SymbolicName=E_LINUX_ENOMSG          
Language=English
ENOMSG: No message of desired type
.

MessageId=43
Severity=Error
SymbolicName=E_LINUX_EIDRM           
Language=English
EIDRM: Identifier removed
.

MessageId=44
Severity=Error
SymbolicName=E_LINUX_ECHRNG          
Language=English
ECHRNG: Channel number out of range
.

MessageId=45
Severity=Error
SymbolicName=E_LINUX_EL2NSYNC        
Language=English
EL2NSYNC: Level 2 not synchronized
.

MessageId=46
Severity=Error
SymbolicName=E_LINUX_EL3HLT          
Language=English
EL3HLT: Level 3 halted
.

MessageId=47
Severity=Error
SymbolicName=E_LINUX_EL3RST          
Language=English
EL3RST: Level 3 reset
.

MessageId=48
Severity=Error
SymbolicName=E_LINUX_ELNRNG          
Language=English
ELNRNG: Link number out of range
.

MessageId=49
Severity=Error
SymbolicName=E_LINUX_EUNATCH         
Language=English
EUNATCH: Protocol driver not attached
.

MessageId=50
Severity=Error
SymbolicName=E_LINUX_ENOCSI          
Language=English
ENOCSI: No CSI structure available
.

MessageId=51
Severity=Error
SymbolicName=E_LINUX_EL2HLT          
Language=English
EL2HLT: Level 2 halted
.

MessageId=52
Severity=Error
SymbolicName=E_LINUX_EBADE           
Language=English
EBADEL: Invalid exchange
.

MessageId=53
Severity=Error
SymbolicName=E_LINUX_EBADR           
Language=English
EBADR: Invalid request descriptor
.

MessageId=54
Severity=Error
SymbolicName=E_LINUX_EXFULL          
Language=English
EXFULL: Exchange full
.

MessageId=55
Severity=Error
SymbolicName=E_LINUX_ENOANO          
Language=English
ENOANO: No anode
.

MessageId=56
Severity=Error
SymbolicName=E_LINUX_EBADRQC         
Language=English
EBADRQC: Invalid request code
.

MessageId=57
Severity=Error
SymbolicName=E_LINUX_EBADSLT         
Language=English
EBADSLT: Invalid slot
.

MessageId=59
Severity=Error
SymbolicName=E_LINUX_EBFONT          
Language=English
EBFONT: Bad font file format
.

MessageId=60
Severity=Error
SymbolicName=E_LINUX_ENOSTR          
Language=English
ENOSTR: Device not a stream
.

MessageId=61
Severity=Error
SymbolicName=E_LINUX_ENODATA         
Language=English
ENODATA: No data available
.

MessageId=62
Severity=Error
SymbolicName=E_LINUX_ETIME           
Language=English
ETIME: Timer expired
.

MessageId=63
Severity=Error
SymbolicName=E_LINUX_ENOSR           
Language=English
ENOSR: Out of streams resources
.

MessageId=64
Severity=Error
SymbolicName=E_LINUX_ENONET          
Language=English
ENONET: Machine is not on the network
.

MessageId=65
Severity=Error
SymbolicName=E_LINUX_ENOPKG          
Language=English
ENOPKG: Package not installed
.

MessageId=66
Severity=Error
SymbolicName=E_LINUX_EREMOTE         
Language=English
EREMOTE: Object is remote
.

MessageId=67
Severity=Error
SymbolicName=E_LINUX_ENOLINK        
Language=English
ENOLINK: Link has been severed
.

MessageId=68
Severity=Error
SymbolicName=E_LINUX_EADV            
Language=English
EADV: Advertise error
.

MessageId=69
Severity=Error
SymbolicName=E_LINUX_ESRMNT          
Language=English
ESRMNT: Srmount error
.

MessageId=70
Severity=Error
SymbolicName=E_LINUX_ECOMM           
Language=English
ECOMM: Communication error on send
.

MessageId=71
Severity=Error
SymbolicName=E_LINUX_EPROTO          
Language=English
EPROTO: Protocol error
.

MessageId=72
Severity=Error
SymbolicName=E_LINUX_EMULTIHOP       
Language=English
EMULTIHOP: Multihop attempted
.

MessageId=73
Severity=Error
SymbolicName=E_LINUX_EDOTDOT         
Language=English
EDOTDOT: RFS specific error
.

MessageId=74
Severity=Error
SymbolicName=E_LINUX_EBADMSG         
Language=English
EBADMSG: Not a data message
.

MessageId=75
Severity=Error
SymbolicName=E_LINUX_EOVERFLOW       
Language=English
EOVERFLOW: Value too large for defined data type
.

MessageId=76
Severity=Error
SymbolicName=E_LINUX_ENOTUNIQ        
Language=English
ENOTUNIQ: Name not unique on network
.

MessageId=77
Severity=Error
SymbolicName=E_LINUX_EBADFD          
Language=English
EBADFD: File descriptor in bad state
.

MessageId=78
Severity=Error
SymbolicName=E_LINUX_EREMCHG         
Language=English
EREMCHG: Remote address changed
.

MessageId=79
Severity=Error
SymbolicName=E_LINUX_ELIBACC         
Language=English
ELIBACC: Can not access a needed shared library
.

MessageId=80
Severity=Error
SymbolicName=E_LINUX_ELIBBAD         
Language=English
ELIBBAD: Accessing a corrupted shared library
.

MessageId=81
Severity=Error
SymbolicName=E_LINUX_ELIBSCN         
Language=English
ELIBSCN: .lib section in a.out corrupted
.

MessageId=82
Severity=Error
SymbolicName=E_LINUX_ELIBMAX         
Language=English
ELIBMAX: Attempting to link in too many shared libraries
.

MessageId=83
Severity=Error
SymbolicName=E_LINUX_ELIBEXEC        
Language=English
ELIBEXEC: Cannot exec a shared library directly
.

MessageId=84
Severity=Error
SymbolicName=E_LINUX_EILSEQ          
Language=English
EILSEQ: Illegal byte sequence
.

MessageId=85
Severity=Error
SymbolicName=E_LINUX_ERESTART        
Language=English
ERESTART: Interrupted system call should be restarted
.

MessageId=86
Severity=Error
SymbolicName=E_LINUX_ESTRPIPE        
Language=English
ESTRPIPE: Streams pipe error
.

MessageId=87
Severity=Error
SymbolicName=E_LINUX_EUSERS          
Language=English
EUSERS: Too many users
.

MessageId=88
Severity=Error
SymbolicName=E_LINUX_ENOTSOCK        
Language=English
ENOTSOCK: Socket operation on non-socket
.

MessageId=89
Severity=Error
SymbolicName=E_LINUX_EDESTADDRREQ    
Language=English
EDESTADDRREQ: Destination address required
.

MessageId=90
Severity=Error
SymbolicName=E_LINUX_EMSGSIZE        
Language=English
EMSGSIZE: Message too long
.

MessageId=91
Severity=Error
SymbolicName=E_LINUX_EPROTOTYPE      
Language=English
EPROTOTYPE: Protocol wrong type for socket
.

MessageId=92
Severity=Error
SymbolicName=E_LINUX_ENOPROTOOPT     
Language=English
ENOPROTOOPT: Protocol not available
.

MessageId=93
Severity=Error
SymbolicName=E_LINUX_EPROTONOSUPPORT 
Language=English
EPROTONOSUPPORT: Protocol not supported
.

MessageId=94
Severity=Error
SymbolicName=E_LINUX_ESOCKTNOSUPPORT 
Language=English
ESOCKTNOSUPPORT: Socket type not supported
.

MessageId=95
Severity=Error
SymbolicName=E_LINUX_EOPNOTSUPP      
Language=English
EOPNOTSUPP: Operation not supported on transport endpoint
.

MessageId=96
Severity=Error
SymbolicName=E_LINUX_EPFNOSUPPORT    
Language=English
EPFNOSUPPORT: Protocol family not supported
.

MessageId=97
Severity=Error
SymbolicName=E_LINUX_EAFNOSUPPORT    
Language=English
EAFNOSUPPORT: Address family not supported by protocol
.

MessageId=98
Severity=Error
SymbolicName=E_LINUX_EADDRINUSE      
Language=English
EADDRINUSE: Address already in use
.

MessageId=99
Severity=Error
SymbolicName=E_LINUX_EADDRNOTAVAIL   
Language=English
EADDRNOTAVAIL: Cannot assign requested address
.

MessageId=100
Severity=Error
SymbolicName=E_LINUX_ENETDOWN        
Language=English
ENETDOWN: Network is down
.

MessageId=101
Severity=Error
SymbolicName=E_LINUX_ENETUNREACH     
Language=English
ENETUNREACH: Network is unreachable
.

MessageId=102
Severity=Error
SymbolicName=E_LINUX_ENETRESET       
Language=English
ENETRESET: Network dropped connection because of reset
.

MessageId=103
Severity=Error
SymbolicName=E_LINUX_ECONNABORTED    
Language=English
ECONNABORTED: Software caused connection abort
.

MessageId=104
Severity=Error
SymbolicName=E_LINUX_ECONNRESET      
Language=English
ECONNRESET: Connection reset by peer
.

MessageId=105
Severity=Error
SymbolicName=E_LINUX_ENOBUFS         
Language=English
ENOBUFS: No buffer space available
.

MessageId=106
Severity=Error
SymbolicName=E_LINUX_EISCONN         
Language=English
EISCONN: Transport endpoint is already connected
.

MessageId=107
Severity=Error
SymbolicName=E_LINUX_ENOTCONN        
Language=English
ENOTCONN: Transport endpoint is not connected
.

MessageId=108
Severity=Error
SymbolicName=E_LINUX_ESHUTDOWN       
Language=English
ESHUTDOWN: Cannot send after transport endpoint shutdown
.

MessageId=109
Severity=Error
SymbolicName=E_LINUX_ETOOMANYREFS    
Language=English
ETOOMANYREFS: Too many references: cannot splice
.

MessageId=110
Severity=Error
SymbolicName=E_LINUX_ETIMEDOUT       
Language=English
ETIMEDOUT: Connection timed out
.

MessageId=111
Severity=Error
SymbolicName=E_LINUX_ECONNREFUSED    
Language=English
ECONNREFUSED: Connection refused
.

MessageId=112
Severity=Error
SymbolicName=E_LINUX_EHOSTDOWN       
Language=English
EHOSTDOWN: Host is down
.

MessageId=113
Severity=Error
SymbolicName=E_LINUX_EHOSTUNREACH    
Language=English
EHOSTUNREACH: No route to host
.

MessageId=114
Severity=Error
SymbolicName=E_LINUX_EALREADY        
Language=English
EALREADY: Operation already in progress
.

MessageId=115
Severity=Error
SymbolicName=E_LINUX_EINPROGRESS     
Language=English
EINPROGRESS: Operation now in progress
.

MessageId=116
Severity=Error
SymbolicName=E_LINUX_ESTALE         
Language=English
ESTALE: Stale file handle
.

MessageId=117
Severity=Error
SymbolicName=E_LINUX_EUCLEAN         
Language=English
EUCLEAN: Structure needs cleaning
.

MessageId=118
Severity=Error
SymbolicName=E_LINUX_ENOTNAM         
Language=English
ENOTNAM: Not a XENIX named type file
.

MessageId=119
Severity=Error
SymbolicName=E_LINUX_ENAVAIL         
Language=English
ENAVAIL: No XENIX semaphores available
.

MessageId=120
Severity=Error
SymbolicName=E_LINUX_EISNAM          
Language=English
EISNAM: Is a named type file
.

MessageId=121
Severity=Error
SymbolicName=E_LINUX_EREMOTEIO       
Language=English
EREMOTEIO: Remote I/O error
.

MessageId=122
Severity=Error
SymbolicName=E_LINUX_EDQUOT          
Language=English
EDQUOT: Quota exceeded
.

MessageId=123
Severity=Error
SymbolicName=E_LINUX_ENOMEDIUM       
Language=English
ENOMEDIUM: No medium found
.

MessageId=124
Severity=Error
SymbolicName=E_LINUX_EMEDIUMTYPE     
Language=English
EMEDIUMTYPE: Wrong medium type
.

MessageId=125
Severity=Error
SymbolicName=E_LINUX_ECANCELED       
Language=English
ECANCELED: Operation Canceled
.

MessageId=126
Severity=Error
SymbolicName=E_LINUX_ENOKEY          
Language=English
ENOKEY: Required key not available
.

MessageId=127
Severity=Error
SymbolicName=E_LINUX_EKEYEXPIRED     
Language=English
EKEYEXPIRED: Key has expired
.

MessageId=128
Severity=Error
SymbolicName=E_LINUX_EKEYREVOKED     
Language=English
EKEYREVOKED: Key has been revoked
.

MessageId=129
Severity=Error
SymbolicName=E_LINUX_EKEYREJECTED    
Language=English
EKEYREJECTED: Key was rejected by service
.

MessageId=130
Severity=Error
SymbolicName=E_LINUX_EOWNERDEAD      
Language=English
EOWNERDEAD: Owner died
.

MessageId=131
Severity=Error
SymbolicName=E_LINUX_ENOTRECOVERABLE 
Language=English
ENOTRECOVERABLE: State not recoverable
.

MessageId=132
Severity=Error
SymbolicName=E_LINUX_ERFKILL         
Language=English
ERFKILL: Operation not possible due to RF-kill
.

MessageId=133
Severity=Error
SymbolicName=E_LINUX_EHWPOISON       
Language=English
EHWPOISON: Memory page has hardware error
.

;//----------------------------------------------------------------------------
;// Elf
;//
;// Messages specific to the parsing and loading of an ELF image

MessageId=1
;//ExceptionName=ElfInvalidMagicException
Severity=Error
Facility=Elf
SymbolicName=E_ELFINVALIDMAGIC
Language=English
ELF image header does not contain the required magic number.
.

MessageId=
;//ExceptionName=ElfTruncatedHeaderException
Severity=Error
SymbolicName=E_ELFTRUNCATEDHEADER
Language=English
ELF image header has been truncated.
.

MessageId=
;//ExceptionName=ElfInvalidClassException,imageclass
Severity=Error
SymbolicName=E_ELFINVALIDCLASS
Language=English
ELF image class %1!d! is not valid for execution on this platform.
.

MessageId=
;//ExceptionName=ElfUnexpectedArchitectureException,architecture
Severity=Error
SymbolicName=E_ELFUNEXPECTEDARCHITECTURE
Language=English
Executable architecture code %1!d! was unexpected, the ELF image cannot be loaded.
.

MessageId=
;//ExceptionName=ElfInvalidTypeException,imagetype
Severity=Error
SymbolicName=E_ELFINVALIDTYPE
Language=English
Elf image type %1!d! is not valid for execution on this platform.
.

MessageId=
;//ExceptionName=ElfImageTruncatedException
Severity=Error
SymbolicName=E_ELFIMAGETRUNCATED
Language=English
ELF image metadata indicates a source data offset that lies beyond the end of the file.
.

MessageId=
;//ExceptionName=ElfCommitSegmentException
Severity=Error
SymbolicName=E_ELFCOMMITSEGMENT
Language=English
Unable to commit the virtual memory required to load an ELF image segment.
.

MessageId=
;//ExceptionName=ElfInvalidEncodingException,encoding
Severity=Error
SymbolicName=E_ELFINVALIDENCODING
Language=English
ELF image encoding %1!d! is not valid for execution on this platform.
.

MessageId=
;//ExceptionName=ElfInvalidVersionException,imageversion
Severity=Error
SymbolicName=E_ELFINVALIDVERSION
Language=English
ELF image format version %1!d! is not supported.
.

MessageId=
;//ExceptionName=ElfInvalidMachineTypeException,machinetype
Severity=Error
SymbolicName=E_ELFINVALIDMACHINETYPE
Language=English
Elf image machine type %1!d! is not valid for execution on this platform.
.

MessageId=
;//ExceptionName=ElfHeaderFormatException
Severity=Error
SymbolicName=E_ELFHEADERFORMAT
Language=English
ELF image header format is not supported.
.

MessageId=
;//ExceptionName=ElfProgramHeaderFormatException
Severity=Error
SymbolicName=E_ELFPROGHEADERFORMAT
Language=English
ELF image program header format is not supported.
.

MessageId=
;//ExceptionName=ElfSectionHeaderFormatException
Severity=Error
SymbolicName=E_ELFSECTHEADERFORMAT
Language=English
ELF image section header format is not supported.
.

MessageId=
;//ExceptionName=ElfInvalidInterpreterException
Severity=Error
SymbolicName=E_ELFINVALIDINTERPRETER
Language=English
ELF image interpreter path is invalid or corrupt.
.

;//----------------------------------------------------------------------------
;// Executable
;//
;// Messages specific to the parsing and loading of executable images

MessageId=1
;//ExceptionName=ExecutableInvalidFormatException
Severity=Error
Facility=Executable
SymbolicName=E_EXECUTABLEINVALIDFORMAT
Language=English
Unrecognized or unsupported executable format.
.

MessageId=
;//ExceptionName=ExecutableInterpreterBinaryException
Severity=Error
SymbolicName=E_EXECUTABLEINTERPRETERBINARY
Language=English
Interpreter script does not specify a path to a target executable.
.

;//----------------------------------------------------------------------------
;// TaskState
;//
;// Messages specific to hosted process/thread task state

MessageId=1
Severity=Error
Facility=TaskState
SymbolicName=E_TASKSTATEUNSUPPORTEDCLASS
Language=English
The specified thread architecture class (%1!d!) is not supported.
.

MessageId=
Severity=Error
SymbolicName=E_TASKSTATEOVERFLOW
Language=English
The specified value (%1!d!) would overflow a 32-bit context task register.
.

MessageId=
Severity=Error
SymbolicName=E_TASKSTATEINVALIDLENGTH
Language=English
The length of the specified existing task state (%1!d! bytes) does not match the expected length for the thread architecture class (%2!d!).
.

MessageId=
Severity=Error
SymbolicName=E_TASKSTATEWRONGCLASS
Language=English
The specified thread architecture class (%1!d!) does not match that from which a task state was created (%2!d!).  This task state cannot be applied to the specified thread.
.

;//----------------------------------------------------------------------------
;// Process
;//
;// Messages specific to hosted process management

MessageId=1
Severity=Error
Facility=Process
SymbolicName=E_PROCESSINVALIDX86HOST
Language=English
The configured host application for 32-bit x86 processes is not a 32-bit application.
.

MessageId=
Severity=Error
SymbolicName=E_PROCESSINVALIDX64HOST
Language=English
The configured host application for 64-bit x86_64 processes is not a 64-bit application.
.

MessageId=
Severity=Error
SymbolicName=E_PROCESSINVALIDTHREADPROC
Language=English
The remote thread entry point provided for a hosted process is invalid.
.

MessageId=
Severity=Error
SymbolicName=E_PROCESSINVALIDSTACKSIZE
Language=English
The thread stack size virtual machine property is invalid.
.

MessageId=
Severity=Error
SymbolicName=E_PROCESSINVALIDTHREADTIMEOUT
Language=English
The thread attach timeout virtual machine property is invalid.
.

MessageId=
Severity=Error
SymbolicName=E_PROCESSDUPLICATEPID
Language=English
The provided pid (%1!d!) cannot be inserted as a child for process (%2!d!); the pid has already been added.
.

MessageId=
Severity=Error
SymbolicName=E_PROCESSTHREADTIMEOUT
Language=English
Process (%1!d!) timed out waiting for a newly created native OS thread to become attached.
.

;//----------------------------------------------------------------------------
;// Thread
;//
;// Messages specific to hosted thread management

MessageId=1
Severity=Error
Facility=Thread
SymbolicName=E_THREADINVALIDSIGALTSTACK
Language=English
The pointer provided for a thread signal alternate stack is invalid.
.

;//----------------------------------------------------------------------------
;// Service
;//
;// Messages specific to the virtual machine service

MessageId=1
Severity=Error
Facility=Service
SymbolicName=E_INITRAMFSNOTFOUND
Language=English
The specified initial RAM file system (initramfs) archive %1 cannot be found or is not a file object
.

MessageId=
Severity=Error
SymbolicName=E_INITRAMFSEXTRACT
Language=English
An error occurred extracting the contents of the initial RAM file system (initramfs) archive %1: %2
.
