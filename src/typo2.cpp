#include "typo2.h"

void typo2::setup()
{
	

	this->font_size = 40;
	this->font.loadFont("senndmit.TTF", this->font_size, true, true, true);
	charactors = { 'B', 'A', 'L', 'A', 'N', 'C', 'E','D' };
}

void typo2::draw()
{
	ofSetColor(239);
	int sample_count = 180;
	for (int charactor_index = 0; charactor_index < charactors.size(); charactor_index++) {

		ofPath path = this->font.getCharacterAsPoints(charactors[charactor_index], true, false);
		vector<ofPolyline> outline = path.getOutline();

		ofPoint location = ofPoint(charactor_index %8 * this->font_size * 1.2 + this->font_size * 0.7, charactor_index / 8 * this->font_size * 1.4 + this->font_size * 0.7);
		ofPushMatrix();
		ofTranslate(location);

		ofNoFill();
		this->font.drawStringAsShapes(string{ charactors[charactor_index] }, this->font_size * -0.5, this->font_size * 0.5);

		ofFill();
		ofBeginShape();
		for (int outline_index = 0; outline_index < (int)outline.size(); outline_index++) {

			if (outline_index != 0) {

				ofNextContour(true);
			}

			outline[outline_index] = outline[outline_index].getResampledByCount(sample_count);
			vector<ofVec3f> vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < (int)vertices.size(); vertices_index++) {

				ofPoint point(vertices[vertices_index].x - this->font_size * 0.5, vertices[vertices_index].y + this->font_size * 0.5, vertices[vertices_index].z);

				int noise_x = ofMap(ofNoise((location.y + point.y) * 0.01 + ofGetFrameNum() * 0.03), 0, 1, -50, 50);
				noise_x /= 10;
				noise_x *= 10;
				if (noise_x > -10 && noise_x < 10) {

					noise_x = 0;
				}

				ofVertex(point + ofPoint(noise_x, 0));
			}
		}
		ofEndShape();
		ofPopMatrix();
	}
}
