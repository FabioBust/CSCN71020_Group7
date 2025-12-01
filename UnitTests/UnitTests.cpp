#include "pch.h"
#include "CppUnitTest.h"
#include "../PolygonChecker/triangleSolver.c"
#include "../PolygonChecker/rectangleSolver.c"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(TriangleTests)
	{
	public:
	  /*---------------------
		Test for isTriangle()
		---------------------*/
		TEST_METHOD(isTriangle_Valid)
		{
			Assert::IsTrue(isTriangle(3, 4, 5));
			Assert::IsTrue(isTriangle(3, 3, 3));
			Assert::IsTrue(isTriangle(3, 3, 5));
			Assert::IsTrue(isTriangle(3.5f, 5.1f, 4.2f));
			Assert::IsTrue(isTriangle(5.0f, 2.0f, 2.9f));	
		}

		TEST_METHOD(isTriangle_Invalid)
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
		/*---------------------
		  Tests for Perimeter()
		  ---------------------*/
		TEST_METHOD(Perimeter_Square)
		{
			float p1[2] = { 0, 0 };
			float p2[2] = { 0, 2 };
			float p3[2] = { 2, 2 };
			float p4[2] = { 2, 0 };

			float result = Perimeter(p1, p2, p3, p4);
			Assert::AreEqual(8.0f, result, 0.01f);
		}

		TEST_METHOD(Perimeter_Rectangle)
		{
			float p1[2] = { 0, 0 };
			float p2[2] = { 0, 3 };
			float p3[2] = { 5, 3 };
			float p4[2] = { 5, 0 };

			float result = Perimeter(p1, p2, p3, p4);
			Assert::AreEqual(16.0f, result, 0.01f);
		}

		TEST_METHOD(Perimeter_NotRectangle)
		{
			float p1[2] = { 0, 0 };
			float p2[2] = { 2, 1 };
			float p3[2] = { 3, 3 };
			float p4[2] = { 1, 2 };

			float result = Perimeter(p1, p2, p3, p4);
			Assert::AreEqual(8.94427f, result, 0.01f);
		}

		TEST_METHOD(Perimeter_NotRectangleNegativePoints)
		{
			float p1[2] = { 0.5f, 0.2f };
			float p2[2] = { 3.1f, 0.7f };
			float p3[2] = { 2.6f, 4.2f };
			float p4[2] = { -0.3f, 3.8f };

			float result = Perimeter(p1, p2, p3, p4);
			Assert::AreEqual(12.8f, result, 0.01f);
		}

		TEST_METHOD(Perimeter_Rhombus)
		{
			float p1[2] = { 0, 0 };
			float p2[2] = { 2, 1 };
			float p3[2] = { 4, 0 };
			float p4[2] = { 2, -1 };

			float result = Perimeter(p1, p2, p3, p4);
			Assert::AreEqual(8.944f, result, 0.01f);
		}

		/*----------------
		  Tests for Area()
		  ----------------*/
		TEST_METHOD(Area_Rectangle)
		{
			float p1[2] = { 0, 0 };
			float p2[2] = { 0, 3 };
			float p3[2] = { 5, 3 };
			float p4[2] = { 5, 0 };

			float result = Area(p1, p2, p3, p4);
			Assert::AreEqual(15.0f, result, 0.01f);
		}

		TEST_METHOD(Area_Square)
		{
			float p1[2] = { 0, 0 };
			float p2[2] = { 0, 8 };
			float p3[2] = { 8, 8 };
			float p4[2] = { 8, 0 };

			float result = Area(p1, p2, p3, p4);
			Assert::AreEqual(64.0f, result, 0.01f);
		}

		TEST_METHOD(Area_RotatedRectangle)
		{
			float p1[2] = { 0,0 };
			float p2[2] = { 3.0f,1.732f };
			float p3[2] = { 0,6.995f };
			float p4[2] = { -3,5.196f };

			float result = Area(p1, p2, p3, p4);
			Assert::AreEqual(20.985f, result, 0.1f);
		}

	  /*----------------------
		Test for isRectangle()
		----------------------*/
		TEST_METHOD(IsRectangle_True)
		{
			float p1[2] = { 0, 0 };
			float p2[2] = { 0, 2 };
			float p3[2] = { 3, 2 };
			float p4[2] = { 3, 0 };

			bool result = isRectangle(p1, p2, p3, p4);
			Assert::IsTrue(result);
		}

		TEST_METHOD(IsRectangle_False)
		{
			float p1[2] = { 0, 0 };
			float p2[2] = { 1, 2 };
			float p3[2] = { 3, 2 };
			float p4[2] = { 3, 0 };

			bool result = isRectangle(p1, p2, p3, p4);
			Assert::IsFalse(result);
		}

		TEST_METHOD(IsRectangle_Rotated)
		{
			float p1[2] = { 1, 1 };
			float p2[2] = { 4, 2 };
			float p3[2] = { 3, 5 };
			float p4[2] = { 0, 4 };

			bool result = isRectangle(p1, p2, p3, p4);
			Assert::IsTrue(result);
		}

		TEST_METHOD(IsRectangle_NegativePoints)
		{
			float p1[2] = { -2, -1 };
			float p2[2] = { -2, 2 };
			float p3[2] = { 1, 2 };
			float p4[2] = { 1, -1 };

			bool result = isRectangle(p1, p2, p3, p4);
			Assert::IsTrue(result);
		}

		TEST_METHOD(IsRectangle_AlmostRectangle)
		{
			float p1[2] = { 0, 0 };
			float p2[2] = { 0, 2 };
			float p3[2] = { 3, 2.1f };
			float p4[2] = { 3, 0 };

			bool result = isRectangle(p1, p2, p3, p4);
			Assert::IsTrue(result);
		}

		/*----------------------
		  Test for pointSorter()
		  ----------------------*/
		TEST_METHOD(PointSorter_Clockwise)
		{
			float p1[2] = { 3.2f, 1.5f };
			float p2[2] = { 0.8f, 4.7f };
			float p3[2] = { 6.1f, 2.3f };
			float p4[2] = { 1.4f, 0.9f };

			float(*sorted)[2] = pointSorter(p1, p2, p3, p4);

			Assert::AreEqual(1.4f, sorted[0][0], 0.01f);
			Assert::AreEqual(0.9f, sorted[0][1], 0.01f);

			Assert::AreEqual(3.2f, sorted[1][0], 0.01f);
			Assert::AreEqual(1.5f, sorted[1][1], 0.01f);

			Assert::AreEqual(6.1f, sorted[2][0], 0.01f);
			Assert::AreEqual(2.3f, sorted[2][1], 0.01f);

			Assert::AreEqual(0.8f, sorted[3][0], 0.01f);
			Assert::AreEqual(4.7f, sorted[3][1], 0.01f);

			free(sorted);
		}

		TEST_METHOD(PointSorter_Collinear)
		{
			float p1[2] = { 0, 0 };
			float p2[2] = { 1, 1 };
			float p3[2] = { 2, 2 };
			float p4[2] = { 3, 3 };
		    float(*sorted)[2] = pointSorter(p1, p2, p3, p4);

			Assert::IsNotNull(sorted);
			free(sorted);
		}
	};
}
