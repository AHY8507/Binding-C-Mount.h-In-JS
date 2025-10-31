// include necessary headers
#include <stdio.h>
#include <sys/mount.h>

// Function to mount a filesystem
int mounting(const char *source, const char *target,
    const char *filesystemtype, unsigned long mountflags,
    const char *data) {
    if(data == "") {
        data = NULL;
    }
    int mount_result = mount(source, target, filesystemtype, mountflags, data);
    if(mount_result == -1) {
        perror("ADDON.C: Mount failed.");
        return -1;
    }
    return mount_result;
}
    
// Function to unmount a filesystem with flags
int umounting2(const char *target, unsigned long flags) {
    int umount2_result = umount2(target, flags);
    if(umount2_result == -1) {
        perror("ADDON.C: Umount2 failed.");
        return -1;
    }
    return umount2_result;
    
}

// Function to unmount a filesystem without flags
int umounting(const char *target) {
    int umount_result = umount(target);
    if(umount_result == -1) {
        perror("ADDON.C: Umount failed.");
        return -1;
    }
    return umount_result;
    
}
