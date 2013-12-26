hxlode
======

PNG image decoder haxelib for neko/cpp using LodePNG / PicoPNG.

Official binaries provided for Windows. Binaries for Mac / Mac64 by [Alex Koz](https://github.com/fzzrr). Binaries for Linux / Linux64 by [zaynyatyi](https://github.com/zaynyatyi).


Usage
-----

Decode PNG directly from a file
```haxe
var img:Image = PicoPNG.loadFile("hello.png");
```

Decode PNG from BytesData
```haxe
var file = File.read("hello.png");
var fileBytes = file.readAll();
var img:Image = PicoPNG.decodePNG(fileBytes.getData(), fileBytes.length);
```

Using the returned image data
```haxe
var bytes = Bytes.ofData(img.data);
var width = img.width;
var height = img.height;

log('Processing $path | $width x $height | '+bytes.length+" bytes");
log("First RGBA pixel: "+bytes.get(0)+" "+bytes.get(1)+" "+bytes.get(2)+" "+bytes.get(3));
```
