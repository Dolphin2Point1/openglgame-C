#include <AL/al.h>
#include <AL/alc.h>

ALCdevice *device;

int init(void) {
    device = alcOpenDevice(nullptr);
    if(!device) {
        return 1;
    }
}

int destroy(void) {
    alcCloseDevice(device);
    return 0;
}

