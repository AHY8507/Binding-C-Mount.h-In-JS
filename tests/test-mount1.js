const { MountFlags, mount, umount } = require('../mount');
const fs = require('fs');

console.log('=== Quick Safe Mount Test ===');

const testDir = '/mnt/quick_test';

try {
    if (!fs.existsSync(testDir)) {
        fs.mkdirSync(testDir, { recursive: true });
    }

    console.log('Mounting tmpfs...');
    const mountResult = mount('tmpfs', testDir, 'tmpfs', MountFlags.MS.NOSUID, 'size=5M');
    
    if (mountResult === 0) {
        console.log('Mounted successfully');
        
        fs.writeFileSync(`${testDir}/hello.txt`, 'Hello from mounted tmpfs!');
        console.log('File created in mount');
        
        const content = fs.readFileSync(`${testDir}/hello.txt`, 'utf8');
        console.log('File content:', content);
        
    } else {
        console.log('Mount failed');
    }

} catch (error) {
    console.log('Error:', error.message);
} finally {
    console.log('Cleaning up...');
    try {
        umount(testDir);
        console.log('Unmounted');
        
        fs.rmdirSync(testDir);
        console.log('Directory removed');
        
    } catch (cleanupError) {
        console.log('Cleanup warning:', cleanupError.message);
    }
    
    console.log('Test finished!');
}
