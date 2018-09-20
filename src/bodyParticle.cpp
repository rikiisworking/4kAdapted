#include "bodyParticle.h"

void bodyParticle::update()
{
	lifeTime = lifeTime - 1.0f;
}

void bodyParticle::draw()
{
	thePath.setStrokeColor(ofColor(bodyColor, ofMap(lifeTime, 0, 50, 0, 60)));
	thePath.setFillColor(ofColor(bodyColor, ofMap(lifeTime, 0,50, 0, 60)));
	thePath.draw();
}

void bodyParticle::draw(ofPoint drawPosition)
{
	thePath.setStrokeColor(ofColor(bodyColor));
	thePath.setFillColor(ofColor(bodyColor));
	ofGetGLRenderer()->draw(thePath,drawPosition.x,drawPosition.y);
}

bodyParticle::bodyParticle(ofPath path, ofColor color, float life)
{
	thePath = path;
	bodyColor = color;
	lifeTime = life;
	thePath.setFilled(true);

}

