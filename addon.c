#include <stdio.h>
#include <sys/mount.h>
//gcc -shared -o CLibrary.so addon.c

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
    

int umounting2(const char *target, unsigned long flags) {
    int umount2_result = umount2(target, flags);
    if(umount2_result == -1) {
        perror("Umount failed.");
        return -1;
    }
    return umount2_result;
    
}


int umounting(const char *target) {
    int umount_result = umount(target);
    if(umount_result == -1) {
        perror("Umount failed.");
        return -1;
    }
    return umount_result;
    
}
