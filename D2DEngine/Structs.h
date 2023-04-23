#pragma once
#include <glm/glm.hpp>

namespace D2D
{
	struct BoxColliderBounds
	{
		BoxColliderBounds() = default;
		BoxColliderBounds(float xValue, float yValue, float offsetXValue, float offsetYValue, float widthValue, float heightValue)
		{
			x = xValue;
			y = yValue;
			offsetX = offsetXValue;
			offsetY = offsetYValue;
			width = widthValue;
			height = heightValue;
		}

		bool IsPointInBounds(const glm::vec2& point)
		{
			return point.x > x && point.x < x + width && point.y > y && point.y < y + height;
		}

		float x{};
		float y{};
		float offsetX{};
		float offsetY{};
		float width{};
		float height{};
	};

	struct Rect
	{
		Rect() = default;
		Rect(float xValue, float yValue, float wValue, float hValue)
		{
			x = xValue;
			y = yValue;
			w = wValue;
			h = hValue;
		}

		Rect(const BoxColliderBounds& bounds)
		{
			x = bounds.x + bounds.offsetX;
			y = bounds.y + bounds.offsetY;
			w = bounds.width;
			h = bounds.height;
		}

		bool IsPointInBounds(const glm::vec2& point)
		{
			return point.x > x && point.x < x + w && point.y > y && point.y < y + h;
		}

		float x, y, w, h;
	};
}
