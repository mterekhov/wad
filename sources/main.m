//
//  main.m
//  macwad
//
//  Created by Michael on 28.02.2018.
//  Copyright © 2018 Michael. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "awad.h"
#include "alevel.h"
#include "types.h"

void launchApplication()
{
	NSString *bundlePath = [[NSBundle mainBundle] pathForResource:@"doom" ofType:@"wad"];
	spcWAD::AWAD wad(bundlePath.UTF8String);
    spcWAD::ALevel e1m8 = wad.readLevel("e1m8");
    const spcWAD::TThingList& levelItemsList = e1m8.levelItemsList();
    int c = 0;
    printf("THINGS\n");
    for (spcWAD::TThingListConstIter iter = levelItemsList.begin(); iter != levelItemsList.end(); iter++)
    {
        printf("%i. <%s>\n", ++c, iter->spritePrefix().c_str());
    }
    
    const spcWAD::ASprite& sprite = e1m8.findSprite(*levelItemsList.begin());
    printf("sprite <%s>\n", sprite.spritesPrefix.c_str());
}

int main(int argc, const char * argv[])
{
	@autoreleasepool
	{
		launchApplication();
	}
	return 0;
}
