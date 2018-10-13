const path = require('path');
const fs = require('fs');
const express = require('express');
const app = express();
const port = 3000;

var startFolder = '/Users/trueicecold/Desktop/ttt';

app.use('/download', express.static(startFolder));
app.get('/list/:folderPath?', function(req, res) {
    req.params.folderPath = (req.params.folderPath != null) ? req.params.folderPath : '/';
    var files = {status:1, path:req.params.folderPath, items:[]};
    try {
        fs.readdirSync(path.join(startFolder, req.params.folderPath)).forEach(file => {
            if (file.indexOf(".") == 0) return;
            var item = {name:file};
            var fstat = fs.statSync(path.join(startFolder, req.params.folderPath, file));
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
});

app.listen(port, () => console.log(`SwitchDL server is listening on port ${port}!`));