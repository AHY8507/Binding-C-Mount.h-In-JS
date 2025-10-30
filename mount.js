const MountFlags = {
    MS: {
        RDONLY: 1 << 0,
        NOSUID: 1 << 1,
        NODEV: 1 << 2,
        NOEXEC: 1 << 3,
        SYNCHRONOUS: 1 << 4,
        REMOUNT: 1 << 5,
        MANDLOCK: 1 << 6,
        DIRSYNC: 1 << 7,
        NOATIME: 1 << 10,
        NODIRATIME: 1 << 11,
        MOVE: 1 << 13,
        REC: 1 << 14,
        SILENT: 1 << 15,
        POSIXACL: 1 << 16,
        UNBINDABLE: 1 << 17,
        PRIVATE: 1 << 18,
        SLAVE: 1 << 19,
        SHARED: 1 << 20,
        RELATIME: 1 << 21,
        KERNMOUNT: 1 << 22,
        I_VERSION: 1 << 23,
        STRICTATIME: 1 << 24,
        LAZYTIME: 1 << 25,
        BIND: 1 << 12
    },
    MNT: {
        FORCE: 1 << 0,
        DETACH: 1 << 1,
        EXPIRE: 1 << 2,
        NOFOLLOW: 1 << 3,
        UNUSED: 1 << 4
    }
};

const ffi = require('ffi-napi');
const ref = require('ref-napi');

const charPtr = ref.types.CString;
const ulong = ref.types.ulong;
const voidPtr = ref.types.void;
const inti = ref.types.int

const lib = ffi.Library('./CLibrary', {
    'mount': [inti, [charPtr, charPtr, charPtr, ulong, voidPtr]],
    'umount': [inti, [charPtr]],
    'umount2': [inti, [charPtr, ulong]]
});

function mount(source, target, fstype, flags, data) {
    let dataPtr = ref.NULL;
    if (data) {
        dataPtr = Buffer.from(data + '\0', 'utf8');
    }
    //const dataPtr = ref.NULL_POINTER;
    const result = lib.mount(source, target, fstype, flags, dataPtr);
    return result;
}

function umount(target) {
    const result = lib.umount(target);
    return result;
}

function umount2(target, flags) {
    const result = lib.umount2(target, flags);
    return result;
}

module.exports = {
    MountFlags,
    mount,
    umount,
    umount2
};
