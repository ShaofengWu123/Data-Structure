#pragma once

//由一个字符串表达式产生逆波兰式
void generate_poland(char expression[], SqList* ppoland);

//计算逆波兰式
double calcualate_poland(SqList poland);