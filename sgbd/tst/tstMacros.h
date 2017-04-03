#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>   

#ifndef TST_FILES_PATH
  #define TST_FILES_PATH "."
#endif

#ifndef TST_OUT_PATH
  #define TST_OUT_PATH "."
#endif

#define S_OUTPATH(name) (OUTPUT_PATH + name)
#define C_OUTPATH(name) S_OUTPATH(name).c_str()

#define S_OUTDIR OUTPUT_PATH
#define C_OUTDIR OUTPUT_PATH.c_str()

#define S_INPATH(name) (INPUT_PATH + name)
#define C_INPATH(name) S_INPATH(name).c_str()

#define S_INDIR INPUT_PATH
#define C_INDIR INPUT_PATH.c_str()

#define INIT_OUTPATH(filename) static const std::string OUTPUT_PATH = std::string(TST_OUT_PATH) + "/" + filename + "/";
#define INIT_INPATH(filename) static const std::string INPUT_PATH = std::string(TST_FILES_PATH) + "/" + filename + "/";

#define CREATE_OUTPATH if (mkdirat(AT_FDCWD, C_OUTDIR, S_IFDIR | S_IRWXU) == -1 && errno != EEXIST) \
                          std::cerr << "ERROR: impossible to create the output directory " + S_OUTDIR << std::endl;

