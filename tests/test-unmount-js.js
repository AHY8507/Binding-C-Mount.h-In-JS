const { umount } = require('../mount');

console.log('=== Unmount Test ===');

const testDir = '/mnt/quick_test';
const fs = require('fs');

const umountResult = umount(testDir);
console.log('Unmount result:', umountResult);

setTimeout(() => {
    if (fs.existsSync(testDir)) {
        fs.rmdirSync(testDir);
        console.log('Directory removed');
    }
}, 3000);

