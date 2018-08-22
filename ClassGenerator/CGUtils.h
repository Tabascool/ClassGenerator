//
//  CGUtils.h
//  Programme2
//
//  Created by Arnaud Le Bourblanc on 01/06/2015.
//  Copyright (c) 2015 ESGI. All rights reserved.
//

#ifndef __Programme2__CGUtils__
#define __Programme2__CGUtils__

#include <string>
#include <utility>

using namespace std;

namespace CGUtils {

    static const char *dataTypes[] = { "bool", "char", "int", "float", "double", "void", "wchar_t" };

    enum visibility { PRIVATE, PROTECTED, PUBLIC };

    typedef pair<bool,string> ResultCode;
}



#endif /* defined(__Programme2__CGUtils__) */
