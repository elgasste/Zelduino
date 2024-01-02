#if !defined( INPUT_READER_H )
#define INPUT_READER_H

#include "input_state.h"

#if defined( __cplusplus )
extern "C" {
#endif

void zInputReader_Init();
void zInputReader_ReadInput();

#if defined( __cplusplus )
}
#endif

#endif // INPUT_READER_H
