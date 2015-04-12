
#include "tbs.h"

int main(){
    LOG_INIT("log.txt");
    LOG_F_TRACE(GAME_LOG_PATH, "log test trace");
    LOG_F_INFO(GAME_LOG_PATH, "log test info");
    LOG_F_WARNING(GAME_LOG_PATH, "log test warning");
    LOG_F_ERROR(GAME_LOG_PATH, "log test error");

    return 0;
}
