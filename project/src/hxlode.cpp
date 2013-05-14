#ifndef STATIC_LINK
	#define IMPLEMENT_API
#endif
#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif
#include <hx/CFFI.h>

//#include <stdio.h>
//#include <stdlib.h>
//#include <stdarg.h>
//#include <string.h>
//#include <iostream>
//#include <sstream>
//#include <vector>

#include "picopng.cpp"

using namespace std;

extern "C" {
	
	value picoDecode(vector<unsigned char> buf) {
		vector<unsigned char> image;
		
		unsigned long w, h;
		int error = decodePNG(image, w, h, buf.empty() ? 0 : &buf[0], (unsigned long)buf.size());
		
		// If there's an error, display it
		if(error != 0) {
			cerr << "Error reading PNG: " << error << std::endl;
			return val_null;
		}
		
		//if(image.size() > 4) cout << "Width: " << w << endl << "Height: " << h << endl << "First pixel: " << hex << int(image[0]) << int(image[1]) << int(image[2]) << int(image[3]) << endl;
		
		//cout << "Allocating buffer..." << endl;
		
		//buffer data = alloc_buffer_len(image.size());
		//buffer data = alloc_buffer(NULL);
		//memcpy(buffer_data(data), image.data(), image.size());
		//buffer_append_sub(data, reinterpret_cast<const char*>(image.data()), image.size());
		//value imgData = buffer_val(data);
		
		value imgData = copy_string(reinterpret_cast<const char*>(image.data()), image.size());
		
		//cout << "Allocating object..." << endl;
		
		value img;
		img = alloc_empty_object();
		alloc_field(img, val_id("width"), alloc_int(w));
		alloc_field(img, val_id("height"), alloc_int(h));
		alloc_field(img, val_id("data"), imgData);
		
		//cout << "Done" << endl;
		
		return img;
	}
	
	value picoDecodePNG(value file) {
		if (!val_is_string(file)) return val_null;
		const char* bytes = val_string(file);
		vector<unsigned char> buf(bytes, bytes+val_strlen(file));
		return picoDecode(buf);
	}
	DEFINE_PRIM(picoDecodePNG, 1);
	
	value picoLoadFile(value path) {
		if (!val_is_string(path)) return val_null;
		
		vector<unsigned char> buf;
		loadFile(buf, val_string(path));
		return picoDecode(buf);
	}
	DEFINE_PRIM(picoLoadFile, 1);
}

