#include "pch.h"
#include "CppUnitTest.h"
#include "../PolygonChecker/triangleSolver.c"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(isTriangleTests)
	{
	public:
		
		TEST_METHOD(isTriangleValidInt)
		{
			float side1 = 3;
			float side2 = 4;
			float side3 = 5;

			bool result = true;

			Assert::AreEqual(result, isTriangle(side1, side2, side3));
		}
		TEST_METHOD(isTriangleInValidInt)
		{
			float side1 = 1;
			float side2 = 2;
			float side3 = 5;

			bool result = false;

			Assert::AreEqual(result, isTriangle(side1, side2, side3));
		}
		TEST_METHOD(isTriangleInValidIntZero)
		{
			float side1 = 1;
			float side2 = 0;
			float side3 = 5;

			bool result = false;

			Assert::AreEqual(result, isTriangle(side1, side2, side3));
		}
	};
}
