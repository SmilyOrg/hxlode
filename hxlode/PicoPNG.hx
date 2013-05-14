package hxlode;

import haxe.io.Bytes;
import haxe.io.BytesData;
import hxlode.Loader;

class PicoPNG {
	static var picoLoadFile:String->Image = Loader.load("hxlode", "picoLoadFile", 1);
	static var picoDecodePNG:BytesData->Image = Loader.load("hxlode", "picoDecodePNG", 1);
    
	static function main() {}
	
	public static function loadFile(fileName:String):Image {
		return picoLoadFile(fileName);
	}
	
	public static function decodePNG(data:BytesData):Image {
		return picoDecodePNG(data);
	}
	
}

typedef Image = {
	width: Int,
	height: Int,
	data: BytesData
};