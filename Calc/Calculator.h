// Calculator.h: interface for the Calculator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(CALCULATOR_H__INCLUDED_)
#define CALCULATOR_H__INCLUDED_

#if !defined(MAX_CALC_STRING)
#define MAX_CALC_STRING 308
#endif //MAX_CALC_STRING

class Calculator  
{
public:
	int GetError();
	void CalcResult();
	double GetResultN(double *res=NULL);
	char * GetResultS(char *res=NULL);
	char * GetExpression(char *res=NULL);
	void SetExpression(const char *exp);
	Calculator operator =(Calculator calc);
	Calculator(const Calculator &calc);
	Calculator(const char *exp=NULL);

protected:
	unsigned int ne(long double n,unsigned int radix=10);
	double fact(double n);
	char * p;
	int CalcError;
	double ResN;
	char ResS[MAX_CALC_STRING];
	char Exp[MAX_CALC_STRING];

	double level1();
	double level2();
	double level3();

};

#endif // !defined(CALCULATOR_H__INCLUDED_)

#if !defined(skipspaces)
#define skipspaces(p) while(isspace(*p)) p++;
#endif //skipspaces