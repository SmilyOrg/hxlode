package hxlode;

import haxe.io.Bytes;
import haxe.io.BytesData;
import hxlode.Loader;

class PicoPNG {
	
	static var picoLoadFile:String->Image = Loader.load("hxlode", "picoLoadFile", 1);

#if neko
	static var picoDecodePNG:BytesData->Int->Image = Loader.load("hxlode", "picoDecodeStringPNG", 2);
#elseif cpp
	static var picoDecodePNG:BytesData->Int->Image = Loader.load("hxlode", "picoDecodeArrayPNG", 2);
#end

	static function main() {}
	
	public static function loadFile(fileName:String):Image {
		return picoLoadFile(fileName);
	}
	
	public static function decodePNG(data:BytesData, length:Int):Image {
		return picoDecodePNG(data, length);
	}
	
}

typedef Image = {
	width: Int,
	height: Int,
	data: BytesData
};