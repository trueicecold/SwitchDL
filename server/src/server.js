var server = require('./file_server');
server.init({
    port:999,
    startFolder:"/Users/trueicecold/Desktop"
});
try {
    server.start();
}
catch(e) {
    console.log(e);
}
