const { umount } = require('../mount');

const testDir = '/mnt/quick_test';

const umountResult = umount(testDir);
console.log('Unmount result:', umountResult);