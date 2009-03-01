/*
 * Cppcheck - A tool for static C/C++ code analysis
 * Copyright (C) 2007-2009 Daniel Marjamäki, Reijo Tomperi, Nicolas Le Cam,
 * Leandro Penz, Kimmo Varis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/
 */

// THIS FILE IS GENERATED BY MACHINE, SEE ../tools/errmsg.cpp !

#ifndef errorloggerH
#define errorloggerH
#include <list>
#include <string>
#include "settings.h"
class Token;
class Tokenizer;

/**
 * This is an interface, which the class responsible of error logging
 * should implement.
 */
class ErrorLogger
{
public:

    /**
     * Wrapper for error messages, provided by reportErr()
     */
    class ErrorMessage
    {
    public:
        /**
         * File name and line number.
         */
        class FileLocation
        {
        public:
            FileLocation()
            {
                line = 0;
            }
            std::string file;
            unsigned int line;
        };

        ErrorMessage(const std::list<FileLocation> &callStack, const std::string &severity, const std::string &msg, const std::string &id);
        ErrorMessage();
        std::string toXML() const;
        std::string toText() const;
        std::string serialize() const;
        bool deserialize(const std::string &data);
        std::list<FileLocation> _callStack;
        std::string _severity;
        std::string _msg;
        std::string _id;
    };

    ErrorLogger() { }
    virtual ~ErrorLogger() { }

    /**
     * Information about progress is directed here.
     * Override this to receive the progress messages.
     *
     * @param outmsg, E.g. "Checking main.cpp..."
     */
    virtual void reportOut(const std::string &outmsg) = 0;

    /**
     * Information about found errors and warnings is directed
     * here. Override this to receive the errormessages.
     *
     * @param msg Location and other information about the found.
     * error
     */
    virtual void reportErr(const ErrorLogger::ErrorMessage &msg) = 0;

    /**
     * Information about how many files have been checked
     *
     * @param index This many files have been checked.
     * @param max This many files there are in total.
     */
    virtual void reportStatus(unsigned int index, unsigned int max) = 0;

    void arrayIndexOutOfBounds(const Tokenizer *tokenizer, const std::list<const Token *> &Location)
    {
        _writemsg(tokenizer, Location, "all", "Array index out of bounds", "arrayIndexOutOfBounds");
    }
    static bool arrayIndexOutOfBounds(const Settings &s)
    {
        return s._showAll;
    }

    void bufferOverrun(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "all", "Buffer overrun", "bufferOverrun");
    }
    static bool bufferOverrun(const Settings &s)
    {
        return s._showAll;
    }

    void strncatUsage(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "all", "Dangerous usage of strncat, possible buffer overrun", "strncatUsage");
    }
    static bool strncatUsage(const Settings &s)
    {
        return s._showAll;
    }

    void outOfBounds(const Tokenizer *tokenizer, const Token *Location, const std::string &what)
    {
        _writemsg(tokenizer, Location, "error", "" + what + " is out of bounds", "outOfBounds");
    }
    static bool outOfBounds()
    {
        return true;
    }

    void stlOutOfBounds(const Tokenizer *tokenizer, const Token *Location, const std::string &what)
    {
        _writemsg(tokenizer, Location, "error", "" + what + " is out of bounds", "stlOutOfBounds");
    }
    static bool stlOutOfBounds()
    {
        return true;
    }

    void noConstructor(const Tokenizer *tokenizer, const Token *Location, const std::string &classname)
    {
        _writemsg(tokenizer, Location, "style", "The class '" + classname + "' has no constructor", "noConstructor");
    }
    static bool noConstructor(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void uninitVar(const Tokenizer *tokenizer, const Token *Location, const std::string &classname, const std::string &varname)
    {
        _writemsg(tokenizer, Location, "style", "Member variable not initialized in the constructor '" + classname + "::" + varname + "'", "uninitVar");
    }
    static bool uninitVar(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void unusedPrivateFunction(const Tokenizer *tokenizer, const Token *Location, const std::string &classname, const std::string &funcname)
    {
        _writemsg(tokenizer, Location, "style", "Unused private function '" + classname + "::" + funcname + "'", "unusedPrivateFunction");
    }
    static bool unusedPrivateFunction(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void memsetClass(const Tokenizer *tokenizer, const Token *Location, const std::string &memfunc)
    {
        _writemsg(tokenizer, Location, "error", "Using '" + memfunc + "' on class", "memsetClass");
    }
    static bool memsetClass()
    {
        return true;
    }

    void memsetStruct(const Tokenizer *tokenizer, const Token *Location, const std::string &memfunc, const std::string &classname)
    {
        _writemsg(tokenizer, Location, "error", "Using '" + memfunc + "' on struct that contains a 'std::" + classname + "'", "memsetStruct");
    }
    static bool memsetStruct()
    {
        return true;
    }

    void operatorEq(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "style", "'operator=' should return something", "operatorEq");
    }
    static bool operatorEq(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void virtualDestructor(const Tokenizer *tokenizer, const Token *Location, const std::string &Base, const std::string &Derived)
    {
        _writemsg(tokenizer, Location, "error", "Class " + Base + " which is inherited by class " + Derived + " does not have a virtual destructor", "virtualDestructor");
    }
    static bool virtualDestructor()
    {
        return true;
    }

    void unusedFunction(const std::string &filename, const std::string &funcname)
    {
        _writemsg("[" + filename + "]: The function '" + funcname + "' is never used", "unusedFunction");
    }
    static bool unusedFunction(const Settings &s)
    {
        return s._checkCodingStyle || s._showAll;
    }

    void mismatchAllocDealloc(const Tokenizer *tokenizer, const std::list<const Token *> &Location, const std::string &varname)
    {
        _writemsg(tokenizer, Location, "error", "Mismatching allocation and deallocation: " + varname + "", "mismatchAllocDealloc");
    }
    static bool mismatchAllocDealloc()
    {
        return true;
    }

    void memleak(const Tokenizer *tokenizer, const Token *Location, const std::string &varname)
    {
        _writemsg(tokenizer, Location, "error", "Memory leak: " + varname + "", "memleak");
    }
    static bool memleak()
    {
        return true;
    }

    void memleakall(const Tokenizer *tokenizer, const Token *Location, const std::string &varname)
    {
        _writemsg(tokenizer, Location, "all", "Memory leak: " + varname + "", "memleakall");
    }
    static bool memleakall(const Settings &s)
    {
        return s._showAll;
    }

    void resourceLeak(const Tokenizer *tokenizer, const Token *Location, const std::string &varname)
    {
        _writemsg(tokenizer, Location, "error", "Resource leak: " + varname + "", "resourceLeak");
    }
    static bool resourceLeak()
    {
        return true;
    }

    void deallocDealloc(const Tokenizer *tokenizer, const Token *Location, const std::string &varname)
    {
        _writemsg(tokenizer, Location, "error", "Deallocating a deallocated pointer: " + varname + "", "deallocDealloc");
    }
    static bool deallocDealloc()
    {
        return true;
    }

    void deallocuse(const Tokenizer *tokenizer, const Token *Location, const std::string &varname)
    {
        _writemsg(tokenizer, Location, "error", "Using '" + varname + "' after it is deallocated / released", "deallocuse");
    }
    static bool deallocuse()
    {
        return true;
    }

    void mismatchSize(const Tokenizer *tokenizer, const Token *Location, const std::string &sz)
    {
        _writemsg(tokenizer, Location, "error", "The given size " + sz + " is mismatching", "mismatchSize");
    }
    static bool mismatchSize()
    {
        return true;
    }

    void cstyleCast(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "style", "C-style pointer casting", "cstyleCast");
    }
    static bool cstyleCast(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void redundantIfDelete0(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "style", "Redundant condition. It is safe to deallocate a NULL pointer", "redundantIfDelete0");
    }
    static bool redundantIfDelete0(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void redundantIfRemove(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "style", "Redundant condition. The remove function in the STL will not do anything if element doesn't exist", "redundantIfRemove");
    }
    static bool redundantIfRemove(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void dangerousUsageStrtol(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "error", "Invalid radix in call to strtol or strtoul. Must be 0 or 2-36", "dangerousUsageStrtol");
    }
    static bool dangerousUsageStrtol()
    {
        return true;
    }

    void ifNoAction(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "style", "Found redundant if condition - 'if (condition);'", "ifNoAction");
    }
    static bool ifNoAction(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void sprintfOverlappingData(const Tokenizer *tokenizer, const Token *Location, const std::string &varname)
    {
        _writemsg(tokenizer, Location, "error", "Overlapping data buffer " + varname + "", "sprintfOverlappingData");
    }
    static bool sprintfOverlappingData()
    {
        return true;
    }

    void udivError(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "error", "Unsigned division. The result will be wrong.", "udivError");
    }
    static bool udivError()
    {
        return true;
    }

    void udivWarning(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "all style", "Warning: Division with signed and unsigned operators", "udivWarning");
    }
    static bool udivWarning(const Settings &s)
    {
        return s._checkCodingStyle || s._showAll;
    }

    void unusedStructMember(const Tokenizer *tokenizer, const Token *Location, const std::string &structname, const std::string &varname)
    {
        _writemsg(tokenizer, Location, "style", "struct or union member '" + structname + "::" + varname + "' is never used", "unusedStructMember");
    }
    static bool unusedStructMember(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void passedByValue(const Tokenizer *tokenizer, const Token *Location, const std::string &parname)
    {
        _writemsg(tokenizer, Location, "style", "Function parameter '" + parname + "' is passed by value. It could be passed by reference instead.", "passedByValue");
    }
    static bool passedByValue(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void constStatement(const Tokenizer *tokenizer, const Token *Location, const std::string &type)
    {
        _writemsg(tokenizer, Location, "style", "Redundant code: Found a statement that begins with " + type + " constant", "constStatement");
    }
    static bool constStatement(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void charArrayIndex(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "style", "Warning - using char variable as array index", "charArrayIndex");
    }
    static bool charArrayIndex(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void charBitOp(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "style", "Warning - using char variable in bit operation", "charBitOp");
    }
    static bool charBitOp(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void variableScope(const Tokenizer *tokenizer, const Token *Location, const std::string &varname)
    {
        _writemsg(tokenizer, Location, "never", "The scope of the variable " + varname + " can be limited", "variableScope");
    }
    static bool variableScope()
    {
        return false;
    }

    void conditionAlwaysTrueFalse(const Tokenizer *tokenizer, const Token *Location, const std::string &truefalse)
    {
        _writemsg(tokenizer, Location, "style", "Condition is always " + truefalse + "", "conditionAlwaysTrueFalse");
    }
    static bool conditionAlwaysTrueFalse(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void strPlusChar(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "error", "Unusual pointer arithmetic", "strPlusChar");
    }
    static bool strPlusChar()
    {
        return true;
    }

    void returnLocalVariable(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "error", "Returning pointer to local array variable", "returnLocalVariable");
    }
    static bool returnLocalVariable()
    {
        return true;
    }

    void dangerousFunctionmktemp(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "style", "Found 'mktemp'. You should use 'mkstemp' instead", "dangerousFunctionmktemp");
    }
    static bool dangerousFunctionmktemp(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void dangerousFunctiongets(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "style", "Found 'gets'. You should use 'fgets' instead", "dangerousFunctiongets");
    }
    static bool dangerousFunctiongets(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void dangerousFunctionscanf(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "style", "Found 'scanf'. You should use 'fgets' instead", "dangerousFunctionscanf");
    }
    static bool dangerousFunctionscanf(const Settings &s)
    {
        return s._checkCodingStyle;
    }

    void iteratorUsage(const Tokenizer *tokenizer, const Token *Location, const std::string &container1, const std::string &container2)
    {
        _writemsg(tokenizer, Location, "error", "Same iterator is used with both " + container1 + " and " + container2 + "", "iteratorUsage");
    }
    static bool iteratorUsage()
    {
        return true;
    }

    void erase(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "error", "Dangerous usage of erase", "erase");
    }
    static bool erase()
    {
        return true;
    }

    void pushback(const Tokenizer *tokenizer, const Token *Location, const std::string &iterator_name)
    {
        _writemsg(tokenizer, Location, "error", "After push_back or push_front, the iterator '" + iterator_name + "' may be invalid", "pushback");
    }
    static bool pushback()
    {
        return true;
    }

    void unvalidatedInput(const Tokenizer *tokenizer, const Token *Location)
    {
        _writemsg(tokenizer, Location, "security", "Unvalidated input", "unvalidatedInput");
    }
    static bool unvalidatedInput(const Settings &s)
    {
        return s._security;
    }


    static std::string callStackToString(const std::list<ErrorLogger::ErrorMessage::FileLocation> &callStack);

private:
    void _writemsg(const Tokenizer *tokenizer, const Token *tok, const char severity[], const std::string &msg, const std::string &id);
    void _writemsg(const Tokenizer *tokenizer, const std::list<const Token *> &callstack, const char severity[], const std::string &msg, const std::string &id);
    void _writemsg(const std::string &msg, const std::string &id);
};
#endif
