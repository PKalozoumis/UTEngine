#pragma once
class Menu
{
	private:
		bool active = false;

	public:
		void switchState(void);
		bool isActive(void) const;
		void draw(void) const;
};

