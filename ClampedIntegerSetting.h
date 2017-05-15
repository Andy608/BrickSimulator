#pragma once
#ifndef BOUNTIVE_CLAMPEDINTEGERSETTING_H_
#define BOUNTIVE_CLAMPEDINTEGERSETTING_H_

#include "IntegerSetting.h"

namespace Bountive
{
	class ClampedIntegerSetting : public IntegerSetting
	{
	public:
		ClampedIntegerSetting(std::wstring settingName, const GLint DEFAULT_INTEGER, const GLint MIN_INTEGER, const GLint MAX_INTEGER);
		virtual ~ClampedIntegerSetting();

		virtual void setCustomInteger(GLint customInteger);

		virtual const GLint& getMinInteger() const;
		virtual const GLint& getMaxInteger() const;

		GLint& clamp(GLint& customInteger) const;

	private:
		const GLint mMIN_INTEGER;
		const GLint mMAX_INTEGER;
	};
}

#endif