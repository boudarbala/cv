const { exec } = require('child_process');

// Path to the built C++ executable
const executablePath = './crud-exe';


// Run the executable
const child = exec(executablePath, (error, stdout, stderr) => {
  if (error) {
    console.error(`Error executing ${executablePath}:`, error);
    return;
  }

  if (stderr) {
    console.error(`Standard error: ${stderr}`);
  }

  console.log(`Standard output: ${stdout}`);
});

// Optionally handle events from the child process
child.on('exit', (code) => {
  console.log(`Child process exited with code ${code}`);
});

child.on('error', (error) => {
  console.error('Child process error:', error);
});
