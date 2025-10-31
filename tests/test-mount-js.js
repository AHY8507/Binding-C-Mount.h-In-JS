const { MountFlags, mount } = require('../mount');

console.log('=== Mount Test ===');

const testDir = '/mnt/quick_test';
const fs = require('fs');

setTimeout(() => {
    if (!fs.existsSync(testDir)) {
        console.log('Creating directory:', testDir);
        fs.mkdirSync(testDir, { recursive: true });
    }
}, 3000);

console.log('Attempting mount...');

const mountResult = mount('tmpfs', testDir, 'tmpfs', MountFlags.MS.NOSUID, 'size=5M');

console.log('Mount result:', mountResult);