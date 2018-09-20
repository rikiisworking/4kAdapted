#include "typo3.h"

void typo3::setup()
{
	this->font_size = 40;
	this->font.loadFont("senndmit.ttf", this->font_size, true, true, true);
	charactors = { 'P', 'L', 'E', 'A', 'S', 'U',
		'R', 'A', 'B', 'L', 'E'};
}

void typo3::draw()
{
	ofNoFill();
	ofSetColor(239);
	ofSetLineWidth(2);
	ofTranslate(20, this->font_size + 20);
	int sample_count = 90;
	for (int charactor_index = 0; charactor_index < charactors.size(); charactor_index++) {

		ofPath path = this->font.getCharacterAsPoints(charactors[charactor_index], true, false);
		vector<ofPolyline> outline = path.getOutline();

		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			outline[outline_index] = outline[outline_index].getResampledByCount(sample_count);
			vector<ofVec3f> vertices = outline[outline_index].getVertices();

			ofBeginShape();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				ofPoint point(vertices[vertices_index].x, vertices[vertices_index].y, vertices[vertices_index].z);

				if (ofGetFrameNum() % (sample_count * 2) < sample_count) {

					if (vertices_index < ofGetFrameNum() % sample_count) {
						ofVertex(point);
					}
				}
				else {

					if (vertices_index > ofGetFrameNum() % sample_count) {
						ofVertex(point);
					}
				}

			}
			ofEndShape();
		}

		if ((charactor_index + 1) % 8 == 0) {
			ofTranslate(this->font_size * -6, this->font_size * 1.4);
		}
		else {
			ofTranslate(this->font_size * 1.2, 0);
		}
	}
}
