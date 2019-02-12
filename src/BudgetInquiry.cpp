#include "BudgetInquiry.h"
#include <sstream>
#include <string>

#define POSITIVE_SLASH "/"
vector< int > CBudgetInquiry::ms_MonthDaysVector = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
CBudgetInquiry::CBudgetInquiry()
{
}

CBudgetInquiry::~CBudgetInquiry()
{

}

void CBudgetInquiry::SetYearMonthBudget( string strYearMonth, int nBudget )
{
    vector< string > kStringVector = GetDateVector( strYearMonth );
    if( kStringVector.size() == 2 )
    {
        string strTransformYearMonth = kStringVector[ 0 ] + POSITIVE_SLASH + kStringVector[ 1 ];
        m_kBudgetMap[ strTransformYearMonth ] = nBudget;
    }
}

int CBudgetInquiry::GetTotalBudget( string strStartDate, string strEndDate )
{
    vector< string > kStartDateVector  = GetDateVector( strStartDate );
    vector< string > kEndDateVector = GetDateVector( strEndDate );
    if( kStartDateVector.size() != 3 || kEndDateVector.size() != 3 )
    {
        return 0;
    }

    int nStartYear = stoi( kStartDateVector[ 0 ] );
    int nEndYear = stoi( kEndDateVector[ 0 ] );
    int nStartMonth = stoi( kStartDateVector[ 1 ] );
    int nEndMonth = stoi( kEndDateVector[ 1 ] );
    int nStartDay = stoi( kStartDateVector[ 2 ] );
    int nEndDay = stoi( kEndDateVector[ 2 ] );
    int nTotalYears = nEndYear - nStartYear;
    int nTotalMonths = nEndMonth - nStartMonth;
    //�p���Y��
    int nStartMonthDays = ms_MonthDaysVector[ nStartMonth - 1 ];//index�q0�}�l�A����q1�}�l�A�ҥH-1
    int nStartRemainDays = 0;
    if ( nTotalMonths == 0 && nTotalYears == 0 )//�Y���P�~�P��
    {
        nStartRemainDays = nEndDay - nStartDay + 1; 
    }
    else
    {
        nStartRemainDays = nStartMonthDays - nStartDay + 1; // ex. 1�릳31�ѡA1���}�l�� = 31 -1 = 30�A�ҥH�n�b + 1
    }
    string strStartYearMonth = kStartDateVector[ 0 ] + POSITIVE_SLASH + CleanStartWithZeroString( kStartDateVector[ 1 ] );
    int nStartMonthBudget = m_kBudgetMap[ strStartYearMonth ];
    int nStartResultBudget = nStartMonthBudget / nStartMonthDays * nStartRemainDays;

    //�p����� (������P�~�P��)
    int nEndResultBudget = 0;
    if( nTotalMonths != 0 || nTotalYears != 0 )
    {
        int nEndMonthDays = ms_MonthDaysVector[ nEndMonth - 1 ];
        int nEndRemainDays = nEndDay;
        string strEndYearMonth = kEndDateVector[ 0 ] + POSITIVE_SLASH + CleanStartWithZeroString( kEndDateVector[ 1 ] );
        int nEndMonthBudget = m_kBudgetMap[ strEndYearMonth ];
        nEndResultBudget = nEndMonthBudget / nEndMonthDays * nEndRemainDays;
    }

    //�p�⤤���������,�@�~��12�Ӥ�
    nTotalMonths = nTotalYears * 12 + nEndMonth; //�N�~���t���ഫ����ơA�æ����Y����Ӥ���ӧO�p��
    int nBudget = 0;
    if( nTotalMonths > 0 )
    {
        int nTempYear = stoi( kStartDateVector[ 0 ] );
        for( int i = nStartMonth + 1; i < nTotalMonths; i++ )
        {
            string strYearMonthBudget;
            int nTempMonth = i % 12;
            if ( nTempMonth == 1 )
            {
                ++nTempYear;
            }
            else if ( nTempMonth == 0 )
            {
                nTempMonth = 12;
            }

            strYearMonthBudget = to_string( nTempYear ) + POSITIVE_SLASH + to_string( nTempMonth );
            nBudget += m_kBudgetMap[ strYearMonthBudget ];
        }
    }

    return nStartResultBudget + nEndResultBudget + nBudget;
}

std::vector< string > CBudgetInquiry::GetDateVector( string strDate )
{
    vector< string > kStringVector;
    istringstream kStringStream( strDate );
    string strStartTemp, strEndTemp;
    
    while( getline( kStringStream, strStartTemp, '/' ) )
    {
        kStringVector.push_back( strStartTemp );
    }

    if( kStringVector.size() == 2 )
    {
        kStringVector[ 1 ] = CleanStartWithZeroString( kStringVector[ 1 ] );
    }
    if( kStringVector.size() == 3 )
    {
        kStringVector[ 2 ] = CleanStartWithZeroString( kStringVector[ 2 ] );
    }

    return kStringVector;
}

string CBudgetInquiry::CleanStartWithZeroString( string strMonthOrDay )
{
    int nTranformNum = stoi( strMonthOrDay );
    return to_string( nTranformNum );
}
