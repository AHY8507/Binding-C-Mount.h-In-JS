const { MountFlags, mount } = require('../mount');

const testDir = '/mnt/quick_test';

const mountResult = mount('tmpfs', testDir, 'tmpfs', MountFlags.MS.NOSUID, 'size=5M');

console.log('Mount result:', mountResult);