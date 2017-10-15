#include <iostream>
#include "Maingame.h"

#ifdef __cplusplus
extern "C"
#endif

using namespace std;

namespace Ishankingen {
	extern C_LINKAGE int SDL_main(int argc, char* argv[]) {
		Maingame maingame;
		maingame.run();
		return 0;
	}
}