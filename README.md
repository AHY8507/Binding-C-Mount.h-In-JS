# Node.js Linux Mount/Unmount Library

A Node.js library for mounting and unmounting filesystems on Linux systems using native system calls through FFI.

---

## Prerequisites

* Node.js and npm must be installed
* Linux operating system (this library is Linux-specific)
* **Root privileges required** for mount operations
* GCC compiler for building the native addon

---

## Installation

1. **Install global dependencies:**
```bash
npm install -g node-gyp
```
2. **Install project dependencies:**
```bash
npm install ffi-napi ref-napi
```
3. **Compile the C library:**
```bash
gcc -shared -o CLibrary.so addon.c
```
## Important Security Note
*Root privileges are REQUIRED for mount operations. Switch to root before running:*
```bash
sudo su
# or
sudo -s
```
## API Reference
### MountFlags Constants

```javascript
const { MountFlags } = require('./mount');

// MS flags (for mount operations)
console.log(MountFlags.MS.RDONLY);    // Read-only mount: 1
console.log(MountFlags.MS.NOSUID);    // Ignore suid and sgid bits: 2
console.log(MountFlags.MS.NODEV);     // Disallow device access: 4
console.log(MountFlags.MS.NOEXEC);    // Disallow program execution: 8
console.log(MountFlags.MS.BIND);      // Create a bind mount: 4096
// ... and many more

// MNT flags (for unmount operations)
console.log(MountFlags.MNT.FORCE);    // Force unmount: 1
console.log(MountFlags.MNT.DETACH);   // Lazy unmount: 2
```
### Core Functions

#### `mount(source, target, filesystemtype, flags, data)`

Mounts a filesystem.

**Parameters:**

| Parameter         | Type     | Description |
|-------------------|----------|-------------|
| `source`          | `string` | Source device or filesystem (e.g., `'/dev/sda1'`, `'tmpfs'`) |
| `target`          | `string` | Mount point directory (e.g., `'/mnt/my_mount'`) |
| `filesystemtype`  | `string` | Filesystem type (e.g., `'tmpfs'`, `'ext4'`, `'none'`) |
| `flags`           | `number` | Mount flags (use `MountFlags.MS.*`, combined with `|`) |
| `data`            | `string` | Mount options string. Use `''` for `NULL`/no options |

**Returns:**  
`0` on success, `-1` on error

#### `umount(target)`

Unmounts a filesystem.

**Parameters:**

| Parameter | Type     | Description                  |
|----------|----------|------------------------------|
| `target` | `string` | Mount point to unmount       |

**Returns:**  
`0` on success, `-1` on error

---

#### `umount2(target, flags)`

Unmounts a filesystem with additional flags.

**Parameters:**

| Parameter | Type     | Description                         |
|----------|----------|-------------------------------------|
| `target` | `string` | Mount point to unmount              |
| `flags`  | `number` | Unmount flags (use `MountFlags.MNT`) |

**Returns:**  
`0` on success, `-1` on error
### Quick Start Tutorial
1. **Basic Setup**
```javascript
const { MountFlags, mount, umount } = require('./mount');
const fs = require('fs');

// Always run as root!
console.log('Current user should be root for mount operations');
```
2. **Simple tmpfs Mount Example**
```javascript
const testDir = '/mnt/my_test_mount';

try {
    if (!fs.existsSync(testDir)) {
        fs.mkdirSync(testDir, { recursive: true });
    }

    const result = mount('tmpfs', testDir, 'tmpfs', MountFlags.MS.NOEXEC, 'size=10M');
    
    if (result === 0) {
        console.log('Successfully mounted tmpfs!');
        fs.writeFileSync(`${testDir}/test.txt`, 'Hello from mounted filesystem!');
        console.log('File created in mounted filesystem');
    } else {
        console.log('Mount failed');
    }

} finally {
    try {
        umount(testDir);
        if (fs.existsSync(testDir)) {
            fs.rmdirSync(testDir);
        }
    } catch (e) {
        console.log('Cleanup warning:', e.message);
    }
}
```
3. **Advanced Example with Multiple Flags**
```javascript
const combinedFlags = MountFlags.MS.NOSUID | MountFlags.MS.NODEV | MountFlags.MS.NOEXEC;

const result = mount(
    '/dev/sdb1', 
    '/mnt/external', 
    'ext4', 
    combinedFlags, 
    ''
);
```
4. **Bind Mount Example**
```javascript
const bindResult = mount(
    '/home/user/data',
    '/mnt/bound_data', 
    'none', 
    MountFlags.MS.BIND, 
    ''
);
```
5. **Unmount Examples**
```javascript
umount('/mnt/my_mount');

umount2('/mnt/stuck_mount', MountFlags.MNT.FORCE);

umount2('/mnt/busy_mount', MountFlags.MNT.DETACH);
```
## Important Notes
### Data Parameter Handling
```javascript
// Correct - empty string for NULL
mount('tmpfs', '/mnt/test', 'tmpfs', MountFlags.MS.RDONLY, '');

// Incorrect - don't use null or undefined
mount('tmpfs', '/mnt/test', 'tmpfs', MountFlags.MS.RDONLY, null);
```
### Error Handling
```javascript
const result = mount('tmpfs', '/mnt/test', 'tmpfs', MountFlags.MS.RDONLY, '');
if (result === -1) {
    console.error('Mount operation failed');
}
```
### Testing
```bash
sudo su

node test-full-js1.js
node test-full-js2.js
node test-full-flags.js
```
## Common Filesystem Types

| Filesystem | Description                     |
|------------|---------------------------------|
| `tmpfs`    | Temporary filesystem in memory  |
| `ext4`     | Linux extended filesystem       |
| `vfat`     | FAT32 filesystem                |
| `ntfs`     | Windows NT filesystem           |
| `none`     | For bind mounts                 |

---

## Troubleshooting

| Issue                   | Solution                                      |
|-------------------------|-----------------------------------------------|
| `Permission denied`     | Run as **root** (`sudo su` or `sudo -s`)      |
| `Mount failed`          | Check if mount point directory exists         |
| `Invalid argument`      | Verify filesystem type and flags              |
| `Library not found`     | Ensure `CLibrary.so` is in the same directory |

## License
This library is intended for educational and administrative purposes on systems where you have appropriate permissions.
