#pragma once

#include <cstdlib>
#include <vector>
#include <algorithm>

#include "Environment.h"
#include "GuiRenderer.h"
#include "Types.h"

namespace GUInterface
{

class Widget
{
private:
	int32 mX, mY, mWidth, mHeight;
	Widget* mParent;
	std::vector<Widget*> mChildren;

public:
	virtual ~Widget() {}

	Widget() : mX(0),mY(0),mWidth(0),mHeight(0),mParent(nullptr),mChildren(std::vector<Widget*>()) {}
	Widget(int32 x, int32 y, int32 width, int32 height) : mX(x),mY(y),mWidth(width),mHeight(height),mParent(nullptr),mChildren(std::vector<Widget*>()) {}
	Widget(int32 x, int32 y, int32 width, int32 height, Widget* parent) : mX(x),mY(y),mWidth(width),mHeight(height),mParent(parent),mChildren(std::vector<Widget*>()) {}

	bool OnMouseClick(int32 x, int32 y, int32 button, bool down)
	{
		for(uint32 i = 0; i < mChildren.size(); i++)
		{
			std::cout << "Child " << i << " OnMouseButton\n";
			if(GetChild(i)->OnMouseClick(x+mX,y+mY,button,down))
			{
				std::cout << "Child " << i << " Clicked\n";
				GetChild(i)->SetColor((float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX);
				return true;
			}
		}
		std::cout << "OnMouseButton: " << InBounds(x,y) << "\n";
		return InBounds(x,y);
	}

	void Draw(Video::IGraphicsDevice* graphics, Video::GuiRenderer* g)
	{
		OnDraw(graphics, g);

		//g->Translate(mX, mY);
		for (uint32 i = 0; i < GetChildCount(); i++)
		{
			GetChild(GetChildCount() - i - 1)->Draw(graphics, g);
		}
		//g->Translate(-mX, -mY);
	}

	void OnDraw(Video::IGraphicsDevice* graphics, Video::GuiRenderer* g)
	{
		int32 x, y;
		Widget* p = GetParent();
		if(p != nullptr)
		{
			x = graphics->GetWidth() - GetX() + p->GetX();
			y = graphics->GetHeight() - GetY() + p->GetY();
		}
		else
		{
			x = mX;
			y = mY;
		}
		g->SetColor(mR, mG, mB);
		g->FillRect(x, y, mWidth - 1, mHeight - 1);
	}

	void Focus() {
		Widget* w = this;

		while (w->GetParent() != nullptr)
		{
			w->GetParent()->AddChild(w, 0);
			w = w->GetParent();
		}
	}

	void AddChild(Widget* w)
	{
		AddChild(w, GetChildCount());
	}

	void AddChild(Widget* w, uint32 index) {
		Widget* parent = w->GetParent();

		if (parent != nullptr)
		{
			parent->RemoveChild(w);
		}

		mChildren.insert(mChildren.begin() + index, w);
		w->SetParent(this);
	}

	void RemoveChild(Widget* w)
	{
		mChildren.erase(std::remove(mChildren.begin(), mChildren.end(), w), mChildren.end());
	}

	void SetParent(Widget* parent)
	{
		mParent = parent;
	}

	void SetSize(int32 w, int32 h)
	{
		mWidth = w;
		mHeight = h;
	}

	void SetPosition(int32 x, int32 y)
	{
		mX = x;
		mY = y;
	}

	void SetBounds(int32 x, int32 y, int32 w, int32 h)
	{
		SetPosition(x, y);
		SetSize(w, h);
	}

	void SetColor(float64 r, float64 g, float64 b)
	{
		mR = r;
		mG = g;
		mB = b;
	}

	bool InBounds(int32 x, int32 y)
	{
		x = x - GetX();
		y = y - GetY();

		std::cout << "X: " << x << ", Y: " << y << std::endl;

		if (x < 0 || x >= GetWidth()) return false;
		if (y < 0 || y >= GetHeight()) return false;

		return true;
	}

	int GetX()
	{
		Widget* p = GetParent();
		if(p == nullptr)
			return mX;
		else
			return p->GetX() + mX;
	}
	int GetY()
	{
		Widget* p = GetParent();
		if(p == nullptr)
			return mY;
		else
			return p->GetY() + mY;
	}
	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }
	Widget* GetParent() { return mParent; }
	Widget* GetChild(uint32 i) { return mChildren[i]; }
	uint32 GetChildCount() { return mChildren.size(); }

	virtual void OnUpdate(float dt) {}

private:
	float64 mR = 0, mG = 0, mB = .5;
};


}