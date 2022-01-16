// Calculator.cpp: implementation of the Calculator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Calculator.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// Construction
//////////////////////////////////////////////////////////////////////

Calculator::Calculator(const char *exp)
{
	if(exp!=NULL)
	{
		lstrcpy(Exp,exp);
		CalcResult();
	}
	else
		lstrcpy(Exp,"");
}

Calculator::Calculator(const Calculator &calc)
{
	lstrcpy(Exp,calc.Exp);
	CalcResult();
}

//////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////

Calculator Calculator::operator =(Calculator calc)
{
	lstrcpy(Exp,calc.Exp);
	CalcResult();
	return *this;
}

//////////////////////////////////////////////////////////////////////
//	Functions
//////////////////////////////////////////////////////////////////////

void Calculator::SetExpression(const char *exp)
{
	if(exp!=NULL)
	{
		lstrcpy(Exp,exp);
		CalcResult();
	}
}

char * Calculator::GetExpression(char *exp)
{
	if(exp!=NULL)
		lstrcpy(exp,Exp);
	return Exp;
}

char * Calculator::GetResultS(char *res)
{
	if(res!=NULL)
		lstrcpy(res,Exp);
	return ResS;
}

int Calculator::GetError()
{
	return CalcError;
}

double Calculator::GetResultN(double *res)
{
	if(res!=NULL)
		*res=ResN;
	return ResN;
}


double Calculator::fact(double n)
{
	double d;
	double m;
	if(n<0||modf(n,&m)!=0)
		return 0;
	if(n==1||n==0)
		return 1;
	d=fact(n-1)*n;
	return d;
}

unsigned int Calculator::ne(long double n, unsigned int radix)
{
	unsigned int i;
	long double bt,at;
	if(radix>36||radix<2)
		return 0;
	if(n<0)
		n=-n;
	bt=modfl(n,&at);
	for(i=1;at>radix;i++)
		at/=10;
	return i;
}


void Calculator::CalcResult()
{
	if(Exp!=NULL&&*Exp!='\0')
	{
		CalcError=0;
		p=Exp;
		ResN=level1();
		if(!CalcError)
			CalcError=(*p!='\0');
		if(!CalcError)
			if(ResN>1e16)
				sprintf(ResS,"%e",ResN);
			else
				sprintf(ResS,"%16.10f",ResN);
		else
		{
			ResN=0;
			lstrcpy(ResS,"");
		}
	}
	else
		CalcError=1;
}

double Calculator::level1()
{
	double result=level2();
	while(!CalcError)
	{
		skipspaces(p);
		if(*p=='+')
		{
			p++;
			result+=level2();
		}
		else
		if(*p=='-')
		{
			p++;
			result-=level2();
		}
		else
			break;
	}
	return result;
}

double Calculator::level2()
{
	double result=level3();
	while(!CalcError)
	{
		skipspaces(p);
		if(*p=='*')
		{
			p++;
			result*=level3();
		}
		else
		if(*p=='/')
		{
			p++;
			double divider=level3();
			if(divider)
				result/=divider;
			else
				CalcError=1;
		}
		else
		if(*p=='^')
		{
			p++;
			result=pow(result,level3());
		}
		else
		if(*p=='!')
		{
			p++;
			result=fact(result);
			if(result==0)
				CalcError=1;
		}
		else
			break;
	}
	return result;

}

double Calculator::level3()
{
	double result=0;
	skipspaces(p);
	if(*p=='(')
	{
		p++;
		result=level1();
		skipspaces(p);
		if(*p++!=')')
			CalcError=1;
	}
	else
	if(*p=='-')
	{
		p++;
		result=-level1();
	}
	else
	if(*p=='+')
	{
		p++;
		result=level1();
	}
	else
	if(isdigit(*p)||*p=='.')
	{
		result=strtod(p,&p);
	}
	else
		CalcError=1;
	return result;
}

