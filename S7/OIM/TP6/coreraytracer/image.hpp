#pragma once

#include "color.hpp"


#include <string>

#include <ImfOutputFile.h>
#include <ImfChannelList.h>
#include <ImfFrameBuffer.h>
#include <half.h>

using namespace std;
using namespace Imf;
using namespace Imath;


/*
   at the moment, copy not safe
*/

/** @ingroup Raytracer 
 *  Image management
 */
class Image {
private:

	int m_x_res, m_y_res;

	Color * m_pixels;

public:

	Image () : m_x_res (0), m_y_res (0),
			   m_pixels (NULL) {
	}

	Image (int x_res_, int y_res_) : m_x_res (x_res_), m_y_res (y_res_) {
		m_pixels = new Color[x_res_ * y_res_];
	}

	~Image() {
		delete[] m_pixels;
	}

	const Color& pixel (int i_, int j_) const {
		return m_pixels[j_ * m_x_res + i_];
	}
	
	Color& pixel (int i_, int j_) {
		return m_pixels[j_ * m_x_res + i_];
	}

	int x_res () const {
		return m_x_res;
	}

	int y_res () const {
		return m_y_res;
	}

	void write_to_exr_file (const string& file_name_) {
		Header header (m_x_res, m_y_res);
		
		//edit the active zone.
		Box2i data_window (V2i (0, 0),
						   V2i (m_x_res - 1, m_y_res - 1));

		header.dataWindow() = data_window; //beuark.

		header.channels().insert ("R", Channel (HALF));
		header.channels().insert ("G", Channel (HALF));
		header.channels().insert ("B", Channel (HALF));	
	
		const int x_count = m_x_res;
		const int nb_pixels = m_x_res * m_y_res;
	
		half * half_rgb = new half[3 * nb_pixels];	
	
		int offset = 0;
		int num_pixel = 0;
	
		for (int y = 0; y < m_y_res; y++) {
			for (int x = 0; x < m_x_res; x++, num_pixel++) {
				Color color = pixel (x, y);
			
				for (int i = 0; i < 3; i++, offset++) {
					half_rgb[offset] = color[i];
				}			
			}
		}
	
		offset = 0;
	
		half_rgb -= 3 * offset;	

		FrameBuffer fb;
		//there are 3 * sizeof(half) bytes between two R elements.
		fb.insert ("R", Slice (HALF, (char *)half_rgb, 3 * sizeof (half),
							   3 * x_count * sizeof (half)));
		//the first element of G is sizeof(half) after the first element of R.
		fb.insert ("G", Slice (HALF, (char *)half_rgb + sizeof(half), 3 * sizeof (half),
							   3 * x_count * sizeof (half)));
		//the first B element is 2 * sizeof (half) bytes after the first element of R.
		fb.insert ("B", Slice (HALF, (char *)half_rgb + 2 * sizeof(half), 3 * sizeof (half),
							   3 * x_count * sizeof (half)));
		try {
			OutputFile file (file_name_.c_str(), header);
			file.setFrameBuffer (fb);
			//y_count() rows to write
			file.writePixels (m_y_res);
		} catch (const std::exception &e) {
			std::cerr<<"Unable to write image file "<<file_name_<<" : "<<e.what()<<std::endl;
		}

		//release the memory, but come back to the real address before.
		delete[] (half_rgb + 3 * offset);	
	}
};
