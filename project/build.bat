@echo off
:: g++-3 src/hxlode.cpp -shared -o bin/hxlode.ndll -Iinclude -L /cygdrive/c/haxe/neko/ -lneko

::@cd cpp
haxelib run hxcpp build.xml

::@cd ..
::haxe -lib hxlode -main hxlode.PicoPNG -cpp bin
::bin\PicoPNG.exe
::cd project


:: cp ndll/Windows/hxlode.ndll bin/hxlode.ndll

:: haxe -cp neko/lodepng -main LodePNG -neko bin/LodePNG.n
:: @cd bin
:: neko LodePNG
:: @cd ..