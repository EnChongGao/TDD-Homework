// BudgetInquiryTest.cpp : Defines the entry point for the console application.
//
#include "gmock/gmock.h"
#include "BudgetInquiry.h"

TEST( CBudgetInquiry, GetTotalBudget_GetHalfMonthBudget_ReturnFifteen )
{
    CBudgetInquiry kBudgetInquiry;
    kBudgetInquiry.SetYearMonthBudget( "2019/01", 31 );//ex: "2019/01", 31
    ASSERT_EQ( kBudgetInquiry.GetTotalBudget( "2019/01/01", "2019/01/15" ), 15 );
}

TEST( CBudgetInquiry, GetTotalBudget_GetHalfMonthBudgetAndCrossingAnotherMonth_ReturnFour )
{
    CBudgetInquiry kBudgetInquiry;
    kBudgetInquiry.SetYearMonthBudget( "2019/02", 28 );
    ASSERT_EQ( kBudgetInquiry.GetTotalBudget( "2019/02/15", "2019/03/15" ), 14 );
}

TEST( CBudgetInquiry, GetTotalBudget_GetAllMonthBudget_ReturnThirtyOne )
{
    CBudgetInquiry kBudgetInquiry;
    kBudgetInquiry.SetYearMonthBudget( "2019/01", 31 );//ex: "2019/01", 31
    ASSERT_EQ( kBudgetInquiry.GetTotalBudget( "2019/01/01", "2019/01/31" ), 31 );
}

TEST( CBudgetInquiry, GetTotalBudget_GetOnlyOneDayBudget_ReturnOne )
{
    CBudgetInquiry kBudgetInquiry;
    kBudgetInquiry.SetYearMonthBudget( "2019/01", 31 );//ex: "2019/01", 31
    ASSERT_EQ( kBudgetInquiry.GetTotalBudget( "2019/01/01", "2019/01/01" ), 1 );
}

TEST( CBudgetInquiry, GetTotalBudget_GetOneDayBudgetByDoubleBudget_ReturnTwo )
{
    CBudgetInquiry kBudgetInquiry;
    kBudgetInquiry.SetYearMonthBudget( "2019/01", 62 );//ex: "2019/01", 62
    ASSERT_EQ( kBudgetInquiry.GetTotalBudget( "2019/01/01", "2019/01/01" ), 2 );
}

TEST( CBudgetInquiry, GetTotalBudget_GetDifferentDateBudget_ReturnZero )
{
    CBudgetInquiry kBudgetInquiry;
    kBudgetInquiry.SetYearMonthBudget( "2019/01", 62 );//ex: "2019/01", 62
    ASSERT_EQ( kBudgetInquiry.GetTotalBudget( "2019/02/01", "2019/02/01" ), 0 );
}

TEST( CBudgetInquiry, GetTotalBudget_SetBudgetWithCrossingYear_ReturnSixtyTwo )
{
    CBudgetInquiry kBudgetInquiry;
    kBudgetInquiry.SetYearMonthBudget( "2019/01", 31 );//ex: "2019/01", 31
    kBudgetInquiry.SetYearMonthBudget( "2020/01", 31 );
    ASSERT_EQ( kBudgetInquiry.GetTotalBudget( "2019/01/01", "2020/01/31" ), 62 );
}

TEST( CBudgetInquiry, GetTotalBudget_GetAllDateBudget_Return271 )
{
    CBudgetInquiry kBudgetInquiry;
    kBudgetInquiry.SetYearMonthBudget( "2019/01", 31 );//ex: "2019/01", 31
    kBudgetInquiry.SetYearMonthBudget( "2019/02", 56 );
    kBudgetInquiry.SetYearMonthBudget( "2019/03", 93 );
    kBudgetInquiry.SetYearMonthBudget( "2019/04", 60 );
    kBudgetInquiry.SetYearMonthBudget( "2019/05", 31 );
    ASSERT_EQ( kBudgetInquiry.GetTotalBudget( "2019/01/01", "2019/06/01" ), 271 );
}

TEST( CBudgetInquiry, GetTotalBudget_AllDateBudgetWithCrossingYear_Return121 )
{
    CBudgetInquiry kBudgetInquiry;
    kBudgetInquiry.SetYearMonthBudget( "2019/01", 31 );//ex: "2019/01", 31
    kBudgetInquiry.SetYearMonthBudget( "2020/01", 31 );
    kBudgetInquiry.SetYearMonthBudget( "2020/02", 28 );
    kBudgetInquiry.SetYearMonthBudget( "2020/03", 31 );
    ASSERT_EQ( kBudgetInquiry.GetTotalBudget( "2019/01/01", "2020/03/31" ), 121 );
}

TEST( CBudgetInquiry, GetTotalBudget_AllDateBudgetWithOtherYear_ReturnZero )
{
    CBudgetInquiry kBudgetInquiry;
    kBudgetInquiry.SetYearMonthBudget( "2019/01", 31 );//ex: "2019/01", 31
    ASSERT_EQ( kBudgetInquiry.GetTotalBudget( "2018/01/01", "2018/03/31" ), 0 );
}

TEST( CBudgetInquiry, GetTotalBudget_SetBudgetAfterGetBudget_ReturnZero )
{
    CBudgetInquiry kBudgetInquiry;
    kBudgetInquiry.SetYearMonthBudget( "2019/01", 31 );//ex: "2019/01", 31
    ASSERT_EQ( kBudgetInquiry.GetTotalBudget( "2018/01/01", "2018/03/31" ), 0 );

    kBudgetInquiry.SetYearMonthBudget( "2018/02", 28 );
    ASSERT_EQ( kBudgetInquiry.GetTotalBudget( "2018/02/15", "2019/01/01" ), 15 );
}

TEST( CBudgetInquiry, GetTotalBudget_SetSameMonthTwice_ReturnSixtyTwo )
{
    CBudgetInquiry kBudgetInquiry;
    kBudgetInquiry.SetYearMonthBudget( "2019/01", 31 );//ex: "2019/01", 31
    kBudgetInquiry.SetYearMonthBudget( "2019/01", 62 );
    ASSERT_EQ( kBudgetInquiry.GetTotalBudget( "2019/01/01", "2019/01/31" ), 62 );
}

TEST( CBudgetInquiry, GetTotalBudget_SetMonthZeroBudget_ReturnZero )
{
    CBudgetInquiry kBudgetInquiry;
    kBudgetInquiry.SetYearMonthBudget( "2019/01", 0 );//ex: "2019/01", 0
    ASSERT_EQ( kBudgetInquiry.GetTotalBudget( "2019/01/01", "2019/03/31" ), 0 );
}

TEST( CBudgetInquiry, GetTotalBudget_SetCrossingThreeYearsBudget_Return93 )
{
    CBudgetInquiry kBudgetInquiry;
    kBudgetInquiry.SetYearMonthBudget( "2019/01", 31 );//ex: "2019/01", 0
    kBudgetInquiry.SetYearMonthBudget( "2020/01", 31 );//ex: "2019/01", 0
    kBudgetInquiry.SetYearMonthBudget( "2021/01", 31 );//ex: "2019/01", 0
    ASSERT_EQ( kBudgetInquiry.GetTotalBudget( "2019/01/01", "2021/01/31" ), 93 );
}