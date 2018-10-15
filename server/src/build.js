const packager = require('electron-packager');

packager({
    dir:".",
    out:"../dist/packages/osx",
    arch:"x64",
    platform:"darwin",
    overwrite:true
});

packager({
    dir:".",
    out:"../dist/packages/linux",
    arch:"x64",
    platform:"linux",
    overwrite:true
});

packager({
    dir:".",
    out:"../dist/packages/win",
    arch:"x64",
    platform:"win32",
    overwrite:true
});