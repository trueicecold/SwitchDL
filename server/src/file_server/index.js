const path = require('path');
const fs = require('fs');
const express = require('express');
const app = express();
const port = 3000;

module.exports = {
    init:function(opts) {
        this.opts = (opts) || {
            port:3000
        };
    },
    start:function() {
        if (this.opts) {
            if (!this.opts.startFolder) {
                throw "NO_PATH_SPECIFIED";
            }
            if (isNaN(this.opts.port)) {
                throw "INVALID_PORT";
            }
            try {
                var stats = fs.statSync(this.opts.startFolder);
                if (!stats.isDirectory()) {
                    throw "NOT_A_DIR";
                }
            }
            catch(e) {
                throw "INVALID_PATH";
            }
            this.startServer();
        }
        else {
            throw "NO_OPTS";
        }
    },
    stop:function() {
        if (this.express_server)
            this.express_server.close();
        this.express_server = null;
    },
    startServer:function() {
        this.stop();
        app.use('/download', express.static(this.opts.startFolder));
        app.get('/ping', function(req, res) {res.send("pong")});
        app.get('/list:folderPath(*)', function(req, res) {
            if (req.params.folderPath != null) {
                if (req.params.folderPath.charAt(0) != "/") {
                    req.params.folderPath = "/" + req.params.folderPath;
                }
                req.params.folderPath = req.params.folderPath.replace(/\/{2,100}/ig, "/");
            }
            else {
                req.params.folderPath = "/";
            }
            var files = {status:1, path:req.params.folderPath, backPath:req.params.folderPath.substr(0, req.params.folderPath.lastIndexOf("/")), items:[]};
            try {
                fs.readdirSync(path.join(this.opts.startFolder, req.params.folderPath)).forEach(file => {
                    if (file.indexOf(".") == 0) return;
                    var item = {name:file};
                    var fstat = fs.statSync(path.join(this.opts.startFolder, req.params.folderPath, file));
                    item.type = fstat.isDirectory() ? "folder" : "file";
                    item.size = (item.type == "folder") ? "" : fstat.size;
                    files.items.push(item);
                });
                files.items.sort(function(a,b) {
                    if (a.type == "file" && b.type == "folder") return 1;
                    if (a.type == "folder" && b.type == "folder") return (a.name < b.name) ? -1 : 1;
                    if (a.type == "file" && b.type == "file") return (a.name < b.name) ? -1 : 1;
                    return 0;
                });
            }
            catch(e) {
                files.status = 0;
                files.error = e.code;
            }
            res.send(JSON.stringify(files, null, "\t"));
        }.bind(this));

        this.express_server = app.listen(this.opts.port, () => console.log(`SwitchDL server is listening on port ${this.opts.port}!`));
  },
  isStarted:function() {
    return this.express_server != null;
  }
};