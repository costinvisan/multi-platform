#define EMPTY_STRING ""
#define DEFINE_ARG "-D"
#define DIR_ARG "-I"
#define OUT_ARG "-O"
#define DELIM_ARGS "="
#define DELIM_FILE " "
#define TERMINATOR "\0"
#define NEW_LINE "\n"
#define MULTI_LINE_DEF "\\\n"
#define DELIM_CODE "\t []{}<>=+-*/%!&|^.,:;()\\"
#define KEY_WORD_DEFINE "#define"
#define KEY_WORD_UNDEFINE "#undef"
#define KEY_WORD_INCLUDE "#include"
#define DEF_ARG_CODE 0
#define DEF_ARG_CODE_U 1
#define DIR_ARG_CODE 2
#define DIR_ARG_CODE_U 3
#define IN_FILE_CODE 4
#define OUT_FILE_CODE 5
#define OUT_FILE_CODE_U 6
#define DEFINE_CODE 7
#define IGNORE_CODE -1
#define BUFFER_LENGTH 255