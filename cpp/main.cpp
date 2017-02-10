#include <unistd.h>
#include <MetabotV2.h>

using namespace Metabot;

int main()
{
    MetabotV2 metabot("/dev/ttyACM0");

    metabot.setLeds("yellow");
    sleep(1);
    metabot.setLeds("cyan");
    sleep(1);
    metabot.setLeds("magenta");
    sleep(1);
    metabot.setLeds("off");
    sleep(1);

    return 0;
}
