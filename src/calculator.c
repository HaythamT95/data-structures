#include <stdio.h> /*fprintf*/
#include <assert.h> /*assert*/
#include <string.h> /*strlen*/

#include "stack.h"
#include "calculator.h"

#define EVENTS 7
#define STATES 8
#define NAN 0.0/0.0

typedef enum
{
	CANT_CALC,
	CAN_CALC,
	EQUAL,
	END,
	ERROR,
	SPACE_AFTER_DIGIT,
	FLOAT_INDICATOR,
	DIGIT_AFTER_FLOAT_INDICATOR
}state_ty;

typedef enum
{
	DIGIT,
	OPERATOR,
	EQ,
	SPACE,
	ENTER,
	OTHER,
	DOT
}event_ty;

typedef struct
{
	stack_ty *digits_stack;
	stack_ty *operators_stack;
	double accumulated_digits;
	double accumulated_float_digits;
	int count_floating_digits;
}calc_ty;

typedef struct
{
    char ascii_value;
    int precedence;
    double (*operation_func)(double num1, double num2);
}operator_ty;

typedef int (*state_function)(calc_ty* calc_, char ch_);

typedef struct
{
	state_ty state;
	state_function state_func;
}state_machine;

static int OnDigit(calc_ty *calc_ ,char ch_);
static int OnFloatDigit(calc_ty *calc_ ,char ch_);
static int OnError(calc_ty *calc_ ,char ch_);
static int OnOperator(calc_ty *calc_ ,char ch_);
static int OnEqual(calc_ty *calc_ ,char ch_);
static int Empty(calc_ty *calc_ ,char ch_);
static int CharToEvent(char ch_);
static int OnEnd(calc_ty *calc_, char ch_);
static int IsOperationStronger(const operator_ty* op1_, const operator_ty* op2_);
static int CalculateIMP(calc_ty *calc_, const operator_ty* op_);
static operator_ty* CharToOperator(char c_);
static double AddOperation(double num1, double num2);
static double SubtractOperation(double num1, double num2);
static double MultiplyOperation(double num1, double num2);
static double DivideOperation(double num1, double num2);
static double FakeFunction(double num1, double num2);

static void ResetStats(calc_ty *calc_);

static const state_machine func_states[EVENTS][STATES] =
{                /*CANT CALC*/    		 /*CAN_CALC*/          		   /*EQUAL*/           /*END*/            /*ERROR*/			  /*SPACE_AFTER_DIGIT*/			/*FLOAT_INDICATOR*/								/*DIGIT_AFTER_FLOAT_INDICATOR*/
/*DIGIT,   */  { { CAN_CALC, OnDigit  }, { CAN_CALC, OnDigit        }, { ERROR, OnError }, { ERROR, OnError }, { ERROR, OnError }, {ERROR, OnError},			{ DIGIT_AFTER_FLOAT_INDICATOR, OnFloatDigit}, 	{DIGIT_AFTER_FLOAT_INDICATOR, OnFloatDigit}},				
/*OPERATOR,*/  { { ERROR, OnError     }, { CANT_CALC, OnOperator	}, { ERROR, OnError }, { ERROR, OnError }, { ERROR, OnError }, {CANT_CALC, OnOperator},		{ ERROR, OnError     },							{ CANT_CALC, OnOperator	}},
/*EQUAL,  */   { { ERROR, OnError     }, { EQUAL, OnEqual           }, { ERROR, OnError }, { ERROR, OnError }, { ERROR, OnError }, {EQUAL, OnEqual }, 			{ ERROR, OnError     },							{ EQUAL, OnEqual           }},
/*SPACE,  */   { { CANT_CALC, Empty   }, { SPACE_AFTER_DIGIT, Empty }, { EQUAL, Empty 	}, { ERROR, Empty 	}, { ERROR, OnError }, {SPACE_AFTER_DIGIT, Empty},  { ERROR, OnError     },							{ SPACE_AFTER_DIGIT, Empty }},
/*ENTER,    */ { { ERROR, OnError     }, { ERROR, OnError        	}, { END, OnEnd     }, { ERROR, OnError }, { ERROR, OnError }, {ERROR, OnError},			{ ERROR, OnError     },							{ ERROR, OnError     }},
/*OTHER    */  { { ERROR, OnError     }, { ERROR, OnError        	}, { ERROR, OnError }, { ERROR, OnError }, { ERROR, OnError }, {ERROR, OnError},			{ ERROR, OnError     },							{ ERROR, OnError     }},
/*POINT 	*/ { { ERROR, OnError     }, { FLOAT_INDICATOR, Empty   }, { ERROR, OnError }, { ERROR, OnError }, { ERROR, OnError }, {ERROR, OnError},			{ ERROR, OnError     },							{ ERROR, OnError     }},
};

static operator_ty operators[] =
    {
        {'+', 1, AddOperation},
        {'-', 1, SubtractOperation},
        {'*', 2, MultiplyOperation},
        {'/', 2, DivideOperation},
        {'=', 0, FakeFunction},
    };

double Calculate(const char *expression)
{
	calc_ty calc;
	size_t stack_capacity = 0;
	char *exp = NULL;
	int state = 0;
	int event = 0;
	int err_code = 0;
	state_function func;
	double result = 0;

	/*assert*/
	assert(NULL != expression);

	/*create num stack*/
	/*return if failed*/
	stack_capacity = strlen(expression);

	calc.digits_stack = StackCreate(stack_capacity, sizeof(double));
	if(NULL == calc.digits_stack)
	{
		fprintf(stderr, "ERROR OCCURED DURING MAKING CALCULATOR\n");
		return NAN;
	}

	/*create operator stack*/
		/*if failed*/
	calc.operators_stack = StackCreate(stack_capacity, sizeof(double));
	if(NULL == calc.operators_stack)
	{
		/*destroy number stack*/
		/*return failure*/
		fprintf(stderr, "ERROR OCCURED DURING MAKING CALCULATOR\n");
		StackDestroy(calc.digits_stack);
		return NAN;
	}

	ResetStats(&calc);

	exp = (char*)expression;
	/*state = CharToEvent(*exp);*/

	/*while state != END && state != ERROR && O == err_code*/
	while(END != state && ERROR != state && 0 == err_code)
	{
		/*event = CharToEvent (char)*/
		event = CharToEvent(*exp);

		/*state = states[event][state].state*/
		func = func_states[event][state].state_func;

		/*state_func = calculator states[event][state].func*/
		state = func_states[event][state].state;

		/*err_code=state_func()*/
		err_code = func(&calc, *exp);
		++exp;
	}

	/*assert operator stack empty*/
	assert(0 != StackIsEmpty(calc.operators_stack));

	/*assert number stack size is 1*/
	assert(1 == StackSize(calc.digits_stack));

	/* ret = top of number stack */
	result = *(double*)StackPeek(calc.digits_stack);

	/*destroy stacks*/
	StackDestroy(calc.digits_stack);
	StackDestroy(calc.operators_stack);

	calc.digits_stack = NULL;
	calc.operators_stack = NULL;

	return result;
}	

int OnDigit(calc_ty *calc_ ,char ch_)
{
	double digit = ch_ - '0';
	int mul10 = 10;

	assert(NULL != calc_);

	calc_->accumulated_digits *= mul10;
	calc_->accumulated_digits += digit;

	return 0;
}


int OnFloatDigit(calc_ty *calc_ ,char ch_)
{
	double digit = ch_ - '0';
	int mul10 = 10;

	assert(NULL != calc_);

	calc_->accumulated_float_digits *= mul10;
	calc_->accumulated_float_digits += digit;
	calc_->count_floating_digits *= mul10;

	return 0;
}

int OnOperator(calc_ty *calc_ ,char ch_)
{
	operator_ty *operation = NULL;
	double whole_number = 0;

	assert(NULL != calc_);

	calc_->accumulated_float_digits = (calc_->accumulated_float_digits)/calc_->count_floating_digits;
	
	whole_number = calc_->accumulated_digits + calc_->accumulated_float_digits;

	StackPush(calc_->digits_stack, &whole_number);
	ResetStats(calc_);

	/*op = charToOp(ch)*/
	operation = CharToOperator(ch_);
	/*CalculateIMP(cal,op)*/
	CalculateIMP(calc_, operation);
	/*ret if failed*/

	/*add to op stack*/
	StackPush(calc_->operators_stack, operation);
	/*ret if failed*/

	return 0;
}

int CharToEvent(char ch_)
{	
	static const int eventLookup[256] = 
	{
        END, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, ENTER, OTHER, OTHER,
        OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
        SPACE, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OPERATOR, OPERATOR, OTHER, OPERATOR, DOT, OPERATOR,
        DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT,
        OTHER, OTHER, OTHER, EQ, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
        OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
        OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
        OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,OTHER, OTHER,
        OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,OTHER, OTHER,
        OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,OTHER, OTHER,
        OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,OTHER, OTHER, 
        OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
        OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,OTHER
    };

    /*return characterEventsLUT[]*/
    return eventLookup[(int)ch_];
}

int OnError(calc_ty *calc_, char ch_)
{
	/*assert*/
	assert (NULL != calc_);
	(void)ch_;

	fprintf(stderr, "ERROR OCCURED DURING CALCULATION\n");
	return ERROR;
}

int OnEnd(calc_ty *calc_, char ch_)
{
	/*assert*/
	assert(NULL != calc_);
	(void)ch_;

	/*Return end*/
	return END; 
}

int Empty(calc_ty *calc_, char ch_)
{
	/*assert*/
	assert(NULL != calc_);
	(void)ch_;

	return 0;
}

int OnEqual(calc_ty *calc_, char ch_)
{
	double whole_number = 0;
	/*assert*/
	assert(NULL != calc_);
	(void)ch_;

	calc_->accumulated_float_digits = calc_->accumulated_float_digits/calc_->count_floating_digits;

	whole_number = calc_->accumulated_digits + calc_->accumulated_float_digits;

	StackPush(calc_->digits_stack, &whole_number);
	ResetStats(calc_);

	/*CalculateIMP(calc, op_lowest_priority)*/
	CalculateIMP(calc_, &operators[4]);
	return 1;
}

int IsOperationStronger(const operator_ty* op1_, const operator_ty* op2_)
{
	/*assert*/
	assert(NULL != op1_);
	assert(NULL != op2_);

	/*Compare ops*/
	return op1_->precedence < op2_->precedence;
}

int CalculateIMP(calc_ty *calc_, const operator_ty* op_)
{
	operator_ty* operation = NULL;
	double *num1 = NULL;
	double *num2 = NULL;
	double result_of_op = 0;
	size_t i = 0;
	/*assert*/
	assert(NULL != calc_);
	assert(NULL != op_);

	operation = StackPeek(calc_->operators_stack);


	/*while operators not empty AND stack-top priority is stronger than op*/
	while ((!StackIsEmpty(calc_->operators_stack)) &&
           ((!IsOperationStronger(StackPeek(calc_->operators_stack), op_)) || ('=' == op_->ascii_value)))
	{
		operation = StackPeek(calc_->operators_stack);

		/*pop operators*/
		StackPop(calc_->operators_stack);

		/*pop 2 numbers*/
		num1 = StackPeek(calc_->digits_stack);
		StackPop(calc_->digits_stack);
		num2 = StackPeek(calc_->digits_stack);
		StackPop(calc_->digits_stack);

		/*push calculated result to numbers*/	
		
		for (i = 0; i < 5; ++i)
		{
			if(operators[i].ascii_value == operation->ascii_value)
			{
				result_of_op = operators[i].operation_func(*num1,*num2);
			}
		}

		StackPush(calc_->digits_stack, &result_of_op);
		
	}

	return 0;
}

operator_ty* CharToOperator(char c_)
{
	size_t i = 0;

	for(i = 0; i < 5; ++i)
	{
		if(operators[i].ascii_value == c_)
		{
			return &operators[i];
		}
	}
	return &operators[4];
}

double AddOperation(double num1, double num2)
{
	return num1 + num2;
}

double SubtractOperation(double num1, double num2)
{
	return num2 - num1;
}

double MultiplyOperation(double num1, double num2)
{
	return num1 * num2;
}

double DivideOperation(double num1, double num2)
{
	assert(0 != num1);
	return num2 / num1;
}

double FakeFunction(double num1, double num2)
{
	(void)num1;
	(void)num2;

	return 0;
}

void ResetStats(calc_ty *calc_)
{
	calc_->accumulated_digits = 0;
	calc_->accumulated_float_digits = 0;
	calc_->count_floating_digits = 1;
}