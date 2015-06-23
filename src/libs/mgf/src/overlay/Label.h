/*
**	Author:		Martin Schwarz
**	Name:		Label.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_LABEL_H
#define MGF_LABEL_H

#include "../Include.h"
#include "Moveable.h"
#include "../data/Texture.h"

namespace mgf{

class Label : public Moveable{
public:
	Label(const std::string &name);
	virtual ~Label();

	virtual bool render(std::shared_ptr<Renderer> renderer);

	virtual bool setText(const std::string &text);
	virtual bool setFont(const std::string &font);
	virtual bool setFont(TTF_Font *font);
	virtual bool setColor(glm::vec3 color);
	virtual bool setTextSize(float size);
	virtual bool setBackground(const std::string &path);
	virtual bool setBackground(std::shared_ptr<Texture> texture);

	virtual std::string getText();
	virtual std::shared_ptr<Texture> getBackground();

protected:
	bool textToTexture();
	int nextPow2(int num);

	std::string mText;
	glm::vec3 mColor;
	float mSize;
	TTF_Font *mFont;

	std::shared_ptr<OverlayNode> mTop;
	std::shared_ptr<Material> mTopMat;
};

} // mgf

#endif // MGF_LABEL_H











