//
//  AAppDelegate.m
//  macwad
//
//  Created by Michael on 14.12.13.
//  Copyright (c) 2013 burwella. All rights reserved.
//

#import "AAppDelegate.h"
#import "awad.h"

@implementation AAppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    spcWAD::AWAD* wader = new spcWAD::AWAD("/Users/michael/Development/DOOMER/macwad/DOOM.WAD");
    spcWAD::TSequence sfxList = wader->awFilteredLumps(spcWAD::LUMPTYPES_SFX);
    for (spcWAD::TSeqIter it = sfxList.begin(); it < sfxList.end(); it++)
    {
        spcWAD::ASFX* sfx = static_cast<spcWAD::ASFX*>(*it);
        
        std::string path = "/Users/michael/Development/DOOMER/macwad/1/";
        path.append(sfx->alName());
        path.append(".midi");
        wader->awIntoMidi(path, sfx);
        printf("sfx <%s>\n", (*it)->alName().c_str());
    }
    
//    spcWAD::TSeqIter it_begin = lumpsSeq.begin();
//    spcWAD::TSeqIter it_end = lumpsSeq.end();
//    
//    int i = 0;
//    for (spcWAD::TSeqIter it = it_begin; it < it_end; it++)
//    {
//        spcWAD::ELumpTypes type = (*it)->alType();
//        std::string lumpName = (*it)->alName();
//        if (
//            (type != spcWAD::LUMPTYPES_FLATS) &&
//            (type != spcWAD::LUMPTYPES_TEXTURES) &&
//            (type != spcWAD::LUMPTYPES_PATCHES)
//            )
//        {
//            if (lumpName.find("DS") == 0)
//            {
//                i++;
//                printf("%i. sfx <%s> = %i\n", i, lumpName.c_str(), (*it)->alType());
//            }
//        }
//    }
//    
//    i = 0;
//    for (spcWAD::TSeqIter it = it_begin; it < it_end; it++)
//    {
//        spcWAD::ELumpTypes type = (*it)->alType();
//        std::string lumpName = (*it)->alName();
//        if (
//            (type != spcWAD::LUMPTYPES_FLATS) &&
//            (type != spcWAD::LUMPTYPES_TEXTURES) &&
//            (type != spcWAD::LUMPTYPES_PATCHES)
//            )
//        {
//            if (lumpName.find("DP") == 0)
//            {
//                i++;
//                printf("%i. pc <%s> = %i\n", i, lumpName.c_str(), (*it)->alType());
//            }
//        }
//    }
    
    delete wader;
}

@end
