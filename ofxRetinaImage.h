//
//  ofxRetinaImage.h
//
//  Created by Oriol Ferrer Mesià on 26/10/12.
//
//

#ifndef ofxRetinaImage_h
#define ofxRetinaImage_h

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"

class ofxRetinaImage : public ofImage{

	public:

	float getWidth(){
		return scale * width;
	}

	float getHeight(){
		return scale * height;
	}

	float getTexWidth(){
		return width;
	}

	float getTexHeight(){
		return height;
	}

	float getScale(){
		return scale;
	}


	void draw(float x, float y, float w, float h){
		drawSubsection(x, y, 0,
					   w, h,
					   0,0,
					   getWidth() / scale, getHeight() / scale);
	}

	void draw(float x, float y){
		drawSubsection(x, y, 0,
					   getWidth() / scale, getHeight() / scale,
					   0,0,
					   getWidth() / scale, getHeight() / scale);
	}

	bool loadImage(string fileName){

		scale = 1.f;
		isRetina = false;
		if( ofxiPhoneGetOFWindow()->isRetinaSupportedOnDevice() ){

			NSString *tmp = ofxStringToNSString(fileName);
			NSArray * separated = [tmp componentsSeparatedByString:@"."];
			if ( [separated count] > 1){

				NSString * firstBit = [separated objectAtIndex:0];
				NSString * lastBit = [separated objectAtIndex: [separated count]-1 ];
				
				for(int i = 1; i < [separated count] - 1; i++){
					NSString * t = [NSString stringWithFormat:@".%@", [separated objectAtIndex:i]];
					firstBit = [firstBit stringByAppendingString: t];
				}

				NSString * fullPath = [NSString stringWithFormat:@"%@%@%@", firstBit, @"@2x.", lastBit];

				bool loadedRetina = ofImage::loadImage(ofxNSStringToString(fullPath));
				if (!loadedRetina){
					ofLog(OF_LOG_ERROR, "ofxRetinaImage can't find retina version for image >> " + fileName + ". Will Try loading standard version.");
					return ofImage::loadImage(fileName);
				}else{
					isRetina = true;
					scale = 0.5;
					//cout << "ofxRetinaImage loaded >> " + ofxNSStringToString(fullPath) << endl ;
					return true;
				}
			}else{
				ofLog(OF_LOG_ERROR, "ofxRetinaImage can't load standard version of image >> " + fileName);
				return false;
			}

		}else{
			return ofImage::loadImage(fileName);
		}
	}

	private:

	bool isRetina;
	float scale;
};

#endif
