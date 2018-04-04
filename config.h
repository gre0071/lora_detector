/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define to 1 if you have the `getopt' function. */
#define HAVE_GETOPT 1

/* Define to 1 if you have the <getopt.h> header file. */
#define HAVE_GETOPT_H 1

/* Define to 1 if you have the `getopt_long' function. */
#define HAVE_GETOPT_LONG 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unirec/inline.h> header file. */
/* #undef HAVE_UNIREC_INLINE_H */

/* Define to 1 if you have the <unirec/ipaddr_cpp.h> header file. */
/* #undef HAVE_UNIREC_IPADDR_CPP_H */

/* Define to 1 if you have the <unirec/ipaddr.h> header file. */
/* #undef HAVE_UNIREC_IPADDR_H */

/* Define to 1 if you have the <unirec/links.h> header file. */
/* #undef HAVE_UNIREC_LINKS_H */

/* Define to 1 if you have the <unirec/unirec.h> header file. */
/* #undef HAVE_UNIREC_UNIREC_H */

/* Define to 1 if you have the <unirec/ur_time.h> header file. */
/* #undef HAVE_UNIREC_UR_TIME_H */

/* Define to 1 if you have the <unirec/ur_values.h> header file. */
/* #undef HAVE_UNIREC_UR_VALUES_H */

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Name of package */
#define PACKAGE "lora_detector"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "gre0071@vsb.cz"

/* Define to the full name of this package. */
#define PACKAGE_NAME "lora_detector"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "lora_detector 1.0.0"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "lora_detector"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.0.0"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Trap getopt macro. Argc and argv are number and values of arguments, optstr
   is a string containing legitimate option characters, longopts is the array
   of option structures (unused for on system without getopt_long()) */
#define TRAP_GETOPT(argc, argv, optstr, longopts) getopt_long(argc, argv, optstr, longopts, NULL)

/* Version number of package */
#define VERSION "1.0.0"

/* Define for Solaris 2.5.1 so the uint32_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT32_T */

/* Define to the type of an unsigned integer type of width exactly 16 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint16_t */

/* Define to the type of an unsigned integer type of width exactly 32 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint32_t */
