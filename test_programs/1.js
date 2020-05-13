const readline = require("readline");
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question("", function(a) {
    rl.question("", function(b) {
        a = parseInt(a);
        b = parseInt(b);
        console.log(a+b);
        rl.close();
    });
});

rl.on("close", function() {
    process.exit(0);
});

