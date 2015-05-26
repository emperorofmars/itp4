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
	virtual bool setBackground(const std::string &path);
	virtual bool setBackground(std::shared_ptr<Texture> texture);

	virtual std::string getText();
	virtual std::shared_ptr<Texture> getBackground();

protected:
	bool textToTexture(const std::string &text);

	std::string mText;
	std::shared_ptr<Texture> mTextImage;
	std::shared_ptr<Texture> mBackground;
};

} // mgf

#endif // MGF_LABEL_H











