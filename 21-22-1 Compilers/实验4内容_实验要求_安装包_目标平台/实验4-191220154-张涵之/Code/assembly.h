#ifndef _ASSEMBLY_H
#define _ASSEMBLY_H

#include "lib.h"

void assembly(char* filename);
void assembleCode(FILE* p, InterCode code);
void assembleLabel(FILE* p, InterCode code);
void assembleFunc(FILE* p, InterCode code);
void assembleAssign(FILE* p, InterCode code);
void assembleBinary(FILE* p, InterCode code);
void assembleGoto(FILE* p, InterCode code);
void assembleIfgoto(FILE* p, InterCode code);
void assembleReturn(FILE* p, InterCode code);
void assembleDec(FILE* p, InterCode code);
void assembleArg(FILE* p, InterCode code);
void assembleCall(FILE* p, InterCode code);
void assembleParam(FILE* p, InterCode code);
void assembleRead(FILE* p, InterCode code);
void assembleWrite(FILE* p, InterCode code);

#endif