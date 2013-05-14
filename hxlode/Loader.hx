package hxlode;

#if cpp
import cpp.Lib;
#elseif neko
import neko.Lib;
#end

class Loader
{
	private static var init = false;

	public static function load(lib:String, s:String, n:Int):Dynamic
	{

		if (!init) {
#if neko
			loadNekoAPI();
#end
			//Lib.load("hxlode","hxlode_init",0)();
			init = true;
		}

		return Lib.load(lib,s,n);
	}

#if neko
	public static function loadNekoAPI()
	{
		//var i = Lib.load("hxlode","neko_init", 5);
		//if (i != null)
		//{
			//i(function(s) return new String(s), function(len:Int) { var r = []; if (len > 0) r[len - 1] = null; return r; }, null, true, false);
		//}
	}
#end
}
