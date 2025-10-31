#include <stdio.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

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

int create_directory(const char *path) {
    struct stat st;
    if (stat(path, &st) == -1) {
        if (mkdir(path, 0755) == -1) {
            perror("Failed to create directory");
            return -1;
        }
        printf("Created directory: %s\n", path);
    }
    return 0;
}

int test_mount_tmpfs() {
    printf("=== Testing tmpfs mount ===\n");
    
    const char *test_dir = "/mnt/c_test_tmpfs";
    
    if (create_directory(test_dir) == -1) {
        return -1;
    }
    
    printf("Mounting tmpfs...\n");
    int result = mounting("tmpfs", test_dir, "tmpfs", MS_NOSUID | MS_NODEV, "size=10M");
    
    if (result == 0) {
        printf("Tmpfs mount successful\n");
        
        sleep(2);
        
        printf("Unmounting...\n");
        if (umounting(test_dir) == 0) {
            printf("Unmount successful\n");
        }
    }
    
    rmdir(test_dir);
    return result;
}

int test_bind_mount() {
    printf("\n=== Testing bind mount ===\n");
    
    const char *source_dir = "/tmp/c_test_source";
    const char *target_dir = "/tmp/c_test_bind";
    
    if (create_directory(source_dir) == -1) return -1;
    if (create_directory(target_dir) == -1) return -1;
    
    FILE *fp = fopen("/tmp/c_test_source/test.txt", "w");
    if (fp) {
        fprintf(fp, "Test bind mount\n");
        fclose(fp);
    }
    
    printf("Creating bind mount...\n");
    int result = mounting(source_dir, target_dir, NULL, MS_BIND, NULL);
    
    if (result == 0) {
        printf("Bind mount successful\n");
        
        sleep(1);
        
        printf("Unmounting bind mount...\n");
        if (umounting(target_dir) == 0) {
            printf("Unmount successful\n");
        }
    }
    
    rmdir(target_dir);
    rmdir(source_dir);
    return result;
}

int test_umount2_flags() {
    printf("\n=== Testing umount2 with flags ===\n");
    
    const char *test_dir = "/mnt/c_test_umount2";
    
    if (create_directory(test_dir) == -1) {
        return -1;
    }
    
    printf("Mounting tmpfs for umount2 test...\n");
    if (mounting("tmpfs", test_dir, "tmpfs", MS_NOSUID, "size=5M") == 0) {
        printf("Testing umount2 with MNT_DETACH...\n");
        int result = umounting2(test_dir, MNT_DETACH);
        
        if (result == 0) {
            printf("Umount2 with MNT_DETACH successful\n");
        } else {
            printf("Umount2 with MNT_DETACH failed\n");
        }
    }
    
    rmdir(test_dir);
    return 0;
}

void test_error_handling() {
    printf("\n=== Testing error handling ===\n");
    
    printf("Testing mount with invalid target...\n");
    mounting("tmpfs", "/invalid/path", "tmpfs", MS_NOSUID, NULL);
    
    printf("Testing umount with invalid target...\n");
    umounting("/invalid/mountpoint");
    
    printf("Testing umount2 with invalid target...\n");
    umounting2("/invalid/mountpoint", MNT_FORCE);
}

int main() {
    printf("Starting C mount function tests\n\n");
    
    if (geteuid() != 0) {
        printf("Warning: Not running as root. Some tests may fail.\n");
        printf("Run with sudo for full functionality.\n\n");
    }
    
    test_mount_tmpfs();
    test_bind_mount();
    test_umount2_flags();
    test_error_handling();
    
    printf("\n=== All tests completed ===\n");
    
    return 0;
}