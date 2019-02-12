#ifndef BUDGETINQUIRY_H
#define BUDGETINQUIRY_H
#include <map>
#include <vector>
#include <string>

using namespace std;
class CBudgetInquiry
{
public:
    CBudgetInquiry();
    ~CBudgetInquiry();
    void SetYearMonthBudget( string strYearMonth, int nBudget );
    int GetTotalBudget( string strStartDate, string strEndDate );
private:
    vector< string > GetDateVector( string strDate );
    string CleanStartWithZeroString( string strMonthOrDay );
private:
    map< string, int > m_kBudgetMap;
    static vector< int > ms_MonthDaysVector;
};


#endif // BUDGETINQUIRY_H
