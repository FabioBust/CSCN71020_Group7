#include "pch.h"
#include "CppUnitTest.h"
#include "../PolygonChecker/triangleSolver.c"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(TriangleTests)
	{
	public:
	  /*---------------------
		Test for isTriangle()
		---------------------*/
		TEST_METHOD(isTriangleValid)
		{
			Assert::IsTrue(isTriangle(3, 4, 5));
			Assert::IsTrue(isTriangle(3, 3, 3));
			Assert::IsTrue(isTriangle(3, 3, 5));
			Assert::IsTrue(isTriangle(3.5f, 5.1f, 4.2f));
			Assert::IsTrue(isTriangle(5.0f, 2.0f, 2.9f));	
		}

		TEST_METHOD(isTriangleInvalid)
		{
			Assert::IsFalse(isTriangle(1, 2, 5));
			Assert::IsFalse(isTriangle(0, 5, 5));
			Assert::IsFalse(isTriangle(-1, 2, 3));
			Assert::IsFalse(isTriangle(3, 3, 6));
		}

	  /*---------------------------
		Tests for analyzeTriangle()
		---------------------------*/
		TEST_METHOD(AnalyzeTriangle_Equilateral) 
		{

			char* type = analyzeTriangle(3, 3, 3);
			Assert::AreEqual("Equilateral triangle", type);
		}

		TEST_METHOD(AnalyzeTriangle_Isosceles)
		{
			char* type1 = analyzeTriangle(3, 3, 5);
			char* type2 = analyzeTriangle(5, 3, 3);
			char* type3 = analyzeTriangle(3, 5, 3);

			Assert::AreEqual("Isosceles triangle", type1);
			Assert::AreEqual("Isosceles triangle", type2);
			Assert::AreEqual("Isosceles triangle", type3);
		}

		TEST_METHOD(AnalyzeTriangle_Scalene) {
			char* type = analyzeTriangle(3, 4, 5);
			Assert::AreEqual("Scalene triangle", type);
		}

		TEST_METHOD(AnalyzeTriangle_NotTriangle)
		{
			char* type = analyzeTriangle(3, 2, 8);
			Assert::AreEqual("Not a triangle", type);
		}

      /*---------------------------
		Tests for angleCalculator()
		---------------------------*/
		TEST_METHOD(AngleCalculator_Equilateral)
		{
			TriangleAngles t = angleCalculator(1, 1, 1);
			Assert::AreEqual(60.0, t.a1, 0.01);
			Assert::AreEqual(60.0, t.a2, 0.01);
			Assert::AreEqual(60.0, t.a3, 0.01);
		}

		TEST_METHOD(AngleCalculator_Isosceles)
		{
			TriangleAngles t = angleCalculator(3, 3, 5);
			Assert::AreEqual(33.5573, t.a1, 0.01);
			Assert::AreEqual(33.5573, t.a2, 0.01);
			Assert::AreEqual(112.885, t.a3, 0.01);
		}

		TEST_METHOD(AngleCalculator_Scalene)
		{
			TriangleAngles t = angleCalculator(3, 4, 5);
			Assert::AreEqual(36.87, t.a1, 0.01);
			Assert::AreEqual(53.13, t.a2, 0.01);
			Assert::AreEqual(90.0, t.a3, 0.01);
		}
	};

	TEST_CLASS(RectangleTests)
	{
		TEST_METHOD(Perimeter_Square)
		{

		}
	};
}
