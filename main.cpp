#include "View/GuiBuilder.h"

int
main(int, char**)
{
    GuiBuilder builder;

    while(true){
        builder.loop();
    }

    return 0;
}