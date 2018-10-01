#include "endPage.h"

void endPage::setup()
{
	typo1.setup();

	shader.load("defaultShader/defaultShader");
}

void endPage::draw(bool kicked)
{
	shaderColor1 = ofFloatColor(0.0f, 0.921f, 0.705f);
	shaderColor1.lerp(ofFloatColor(1.0f, 0.117f, 0.176f), (sinf(ofGetElapsedTimef()*2.1f) + 1) / 2);

	shaderColor2 = ofFloatColor(0.0f, 0.313f, 1.0f);
	shaderColor2.lerp(ofFloatColor(1.0f, 1.0f, 0.0f), (sinf(ofGetElapsedTimef()*2.1f) + 1) / 2);

	shader.begin();
	shader.setUniform4f("inputColor1", shaderColor1);
	shader.setUniform4f("inputColor2", shaderColor2);
	typo1.draw();
	shader.end();
}
