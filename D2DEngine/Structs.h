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
			x = bounds.x + bounds.offsetX - bounds.width/2;
			y = bounds.y + bounds.offsetY - bounds.height/2;
			w = bounds.width;
			h = bounds.height;
		}

		bool IsPointInBox(const glm::vec2& point)
		{
			return point.x > x && point.x < x + w && point.y > y && point.y < y + h;
		}

		float x, y, w, h;
	};

	struct Capsule
	{
	public:
		Capsule() = default;
		Capsule(const glm::vec2& centerValue, const glm::vec2& offsetValue, float heightValue, float radiusValue)
		{
			center = centerValue;
			offset = offsetValue;
			height = heightValue;
			radius = radiusValue;
		}

		Rect& GetRect()
		{
			rect.x = center.x - radius;
			rect.y = center.y - height / 2 + radius;
			rect.w = 2 * radius;
			rect.h = height - 2 * radius;

			return rect;
		}

		glm::vec2& GetTopCenter()
		{
			topCenter.x = center.x;
			topCenter.y = center.y - height / 2 + radius;

			return topCenter;
		}

		glm::vec2& GetBotCenter()
		{
			botCenter.x = center.x;
			botCenter.y = center.y + height / 2 - radius;

			return botCenter;
		}

		glm::vec2 center{};
		glm::vec2 offset{};
		float height{};
		float radius{};

	private:
		Rect rect{};
		glm::vec2 topCenter{};
		glm::vec2 botCenter{};
	};
}
