var parseArgs = require('minimist')(process.argv.slice(2));
var server = require('./file_server');
var fs = require('fs');
try {
    if (!parseArgs.f) {
        console.log("");
        console.log("SwitchDL Usage:");
        console.log("---------------");
        console.log("");
        console.log("node server.js -f <start folder>             Start SwitchDL in the specified folder on port 3333");
        console.log("node server.js -f <start folder> -p <port>   Start SwitchDL in the specified folder and port");
    }
    else {
        parseArgs.p = parseArgs.p || 3333;
        if (fs.existsSync(parseArgs.f)) {
            if (!isNaN(parseArgs.p)) {
                server.init({
                    startFolder:parseArgs.f,
                    port:parseArgs.p
                });
                server.start();
            }
            else {
                console.log("Invalid Port");
            }
        }
        else {
            console.log("Invalid Path");
        }
    }
}
catch(e) {
    console.log(e);
}
