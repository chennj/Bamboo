#pragma once

#include "Event.h"

namespace BAMBOO
{
	class BAMBOO_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return _KeyCode; }

	public:
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int keyCode) : _KeyCode(keyCode) {}
		int _KeyCode;
	};

	class BAMBOO_API KeyPressedEvent : public KeyEvent
	{
	private:
		int _RepeatCount;

	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			:
			KeyEvent(keyCode), _RepeatCount(repeatCount) {}

	public:
		inline int GetRepeatCount() const { return _RepeatCount; }
		
		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << _KeyCode << " (" << _RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class BAMBOO_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			:
			KeyEvent(keyCode) {}

	public:
		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << _KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class BAMBOO_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keyCode)
			:
			KeyEvent(keyCode) {}

	public:
		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << _KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}