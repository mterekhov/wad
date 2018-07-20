//
//  main.m
//  macwad
//
//  Created by Michael on 28.02.2018.
//  Copyright © 2018 Michael. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "awad.h"

void launchApplication()
{
	NSString *bundlePath = [[NSBundle mainBundle] pathForResource:@"doom" ofType:@"wad"];
	spcWAD::AWAD wad(bundlePath.UTF8String);
}

int main(int argc, const char * argv[])
{
	@autoreleasepool
	{
		launchApplication();
	}
	return 0;
}
