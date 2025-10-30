#include <stdio.h>

int mount(const char *source, const char *target,
          const char *filesystemtype, unsigned long mountflags,
          const void *data) {
    return 0;
        
}

int unmount(const char *target) {
    return 0;
}

int unmount2(const char *target, unsigned long flags) {
    return 0;
}

int mounting(const char *source, const char *target,
    const char *filesystemtype, unsigned long mountflags,
    const void *data) {
    int mount_result = mount(source, target, filesystemtype, mountflags, data);
    if(mount_result == -1) {
        perror("Mount failed.");
        return -1;
    }
    return mount_result;
}
    
int unmounting2(const char *target, unsigned long flags) {
    int unmount2_result = unmount2(target, flags);
    if(unmount2_result == -1) {
        perror("Unmount failed.");
        return -1;
    }
    return unmount2_result;
    
}

int unmounting(const char *target) {
    int unmount_result = unmount(target);
    if(unmount_result == -1) {
        perror("Unmount failed.");
        return -1;
    }
    return unmount_result;
    
}
