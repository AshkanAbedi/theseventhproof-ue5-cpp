// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable CppMemberFunctionMayBeStatic

#include "UI/ExampleWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SExampleWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(STextBlock)
		.Text(NSLOCTEXT("Ex", "HelloWorld" , "Hello World!"))
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
