#include "Cursor.h"
#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>





Cursor::~Cursor()
{
}

void Cursor::init() {
	initShader();
	spritesheet.loadFromFile("images/cursor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	cursor = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.5,0.5), &spritesheet, &simpleTexProgram);
	cursor->setNumberAnimations(2);
	setCursor();
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	changeCursor(false);
}

void Cursor::render(){
	glm::mat4 modelview;
	simpleTexProgram.use();
	simpleTexProgram.setUniformMatrix4f("projection", projection);
	simpleTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	simpleTexProgram.setUniformMatrix4f("modelview", modelview);
	cursor->render();
}

void Cursor::update(int x, int y)
{	
	cursor->setPosition(glm::vec2(x-8, y-8));
}

void Cursor::initShader() {
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	simpleTexProgram.init();
	simpleTexProgram.addShader(vShader);
	simpleTexProgram.addShader(fShader);
	simpleTexProgram.link();
	if (!simpleTexProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << simpleTexProgram.log() << endl << endl;
	}
	simpleTexProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void Cursor::setCursor() {
	cursor->setAnimationSpeed(SELECTED, 0);
	cursor->addKeyframe(SELECTED, glm::vec2(0, 0));
	cursor->setAnimationSpeed(NORMAL, 0);
	cursor->addKeyframe(NORMAL, glm::vec2(0.5, 0));
}

void Cursor::changeCursor(bool overLemming) {
	if (overLemming) {
		cursor->changeAnimation(SELECTED);
		//currentCursorType = 0;
	}
	else {
		cursor->changeAnimation(NORMAL);
		//currentCursorType = 1;
	}
}

void Cursor::lemmingInside(bool overLemming) {
	changeCursor(overLemming);
}