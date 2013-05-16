hxlode
======

PNG image decoder haxelib for neko/cpp using LodePNG / PicoPNG


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
