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
	NSString *bundlePath = [[NSBundle mainBundle] pathForResource:@"doom1" ofType:@"wad"];
	spcWAD::AWAD wad(bundlePath.UTF8String);
	
//	spcWAD::TSequence lumpsList = wad.awLumps();
//	int counter = 1;
//	for (spcWAD::TSequence::iterator iter = lumpsList.begin(); iter < lumpsList.end(); iter++)
//	{
//		spcWAD::ALump* lump = static_cast<spcWAD::ALump *>(*iter);
//		printf("%i. %s\t\t%s\n", counter, lump->alName().c_str(), lumpTypeName(lump).c_str());
//		counter++;
//	}
//
//	lumpsList = wad.awFilteredLumps(spcWAD::LUMPTYPES_TEXTURES);
//	counter = 1;
//	for (spcWAD::TSequence::iterator iter = lumpsList.begin(); iter < lumpsList.end(); iter++)
//	{
//		spcWAD::ALump* lump = static_cast<spcWAD::ALump *>(*iter);
//		printf("%i. %s\n", counter, lump->alName().c_str());
//		counter++;
//	}
}

int main(int argc, const char * argv[])
{
	@autoreleasepool
	{
		launchApplication();
	}
	return 0;
}
