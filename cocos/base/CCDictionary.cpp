/****************************************************************************
 Copyright (c) 2012 - 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCDictionary.h"
#include "CCString.h"
#include "CCInteger.h"
#include "platform/CCFileUtils.h"
#include <algorithm>    // std::for_each

using namespace std;

NS_CC_BEGIN

// -----------------------------------------------------------------------
// DictElement

DictElement::DictElement(const char* pszKey, Object* pObject)
{
    CCASSERT(pszKey && strlen(pszKey) > 0, "Invalid key value.");
    _intKey = 0;
    const char* pStart = pszKey;
    
    size_t len = strlen(pszKey);
    if (len > MAX_KEY_LEN )
    {
        char* pEnd = (char*)&pszKey[len-1];
        pStart = pEnd - (MAX_KEY_LEN-1);
    }
    
    strcpy(_strKey, pStart);
    
    _object = pObject;
    memset(&hh, 0, sizeof(hh));
}

DictElement::DictElement(intptr_t iKey, Object* pObject)
{
    _strKey[0] = '\0';
    _intKey = iKey;
    _object = pObject;
    memset(&hh, 0, sizeof(hh));
}

DictElement::~DictElement()
{
    CCLOGINFO("deallocing DictElement: %p", this);
}

// -----------------------------------------------------------------------
// __Dictionary

__Dictionary::__Dictionary()
: _elements(NULL)
, _dictType(kDictUnknown)
{

}

__Dictionary::~__Dictionary()
{
    CCLOGINFO("deallocing __Dictionary: %p", this);
    removeAllObjects();
}

unsigned int __Dictionary::count()
{
    return HASH_COUNT(_elements);
}

__Array* __Dictionary::allKeys()
{
    int iKeyCount = this->count();
    if (iKeyCount <= 0) return NULL;

    __Array* array = __Array::createWithCapacity(iKeyCount);

    DictElement *pElement, *tmp;
    if (_dictType == kDictStr)
    {
        HASH_ITER(hh, _elements, pElement, tmp) 
        {
            __String* pOneKey = new __String(pElement->_strKey);
            array->addObject(pOneKey);
            CC_SAFE_RELEASE(pOneKey);
        }
    }
    else if (_dictType == kDictInt)
    {
        HASH_ITER(hh, _elements, pElement, tmp) 
        {
            __Integer* pOneKey = new __Integer(static_cast<int>(pElement->_intKey));
            array->addObject(pOneKey);
            CC_SAFE_RELEASE(pOneKey);
        }
    }
    
    return array;
}

__Array* __Dictionary::allKeysForObject(Object* object)
{
    int iKeyCount = this->count();
    if (iKeyCount <= 0) return NULL;
    __Array* array = __Array::create();

    DictElement *pElement, *tmp;

    if (_dictType == kDictStr)
    {
        HASH_ITER(hh, _elements, pElement, tmp) 
        {
            if (object == pElement->_object)
            {
                __String* pOneKey = new __String(pElement->_strKey);
                array->addObject(pOneKey);
                CC_SAFE_RELEASE(pOneKey);
            }
        }
    }
    else if (_dictType == kDictInt)
    {
        HASH_ITER(hh, _elements, pElement, tmp) 
        {
            if (object == pElement->_object)
            {
                __Integer* pOneKey = new __Integer(static_cast<int>(pElement->_intKey));
                array->addObject(pOneKey);
                CC_SAFE_RELEASE(pOneKey);
            }
        }
    }
    return array;
}

Object* __Dictionary::objectForKey(const std::string& key)
{
    // if dictionary wasn't initialized, return NULL directly.
    if (_dictType == kDictUnknown) return NULL;
    // __Dictionary only supports one kind of key, string or integer.
    // This method uses string as key, therefore we should make sure that the key type of this __Dictionary is string.
    CCASSERT(_dictType == kDictStr, "this dictionary does not use string as key.");

    Object* pRetObject = NULL;
    DictElement *pElement = NULL;
    HASH_FIND_STR(_elements, key.c_str(), pElement);
    if (pElement != NULL)
    {
        pRetObject = pElement->_object;
    }
    return pRetObject;
}

Object* __Dictionary::objectForKey(intptr_t key)
{
    // if dictionary wasn't initialized, return NULL directly.
    if (_dictType == kDictUnknown) return NULL;
    // __Dictionary only supports one kind of key, string or integer.
    // This method uses integer as key, therefore we should make sure that the key type of this __Dictionary is integer.
    CCASSERT(_dictType == kDictInt, "this dictionary does not use integer as key.");

    Object* pRetObject = NULL;
    DictElement *pElement = NULL;
    HASH_FIND_PTR(_elements, &key, pElement);
    if (pElement != NULL)
    {
        pRetObject = pElement->_object;
    }
    return pRetObject;
}

const __String* __Dictionary::valueForKey(const std::string& key)
{
    __String* pStr = dynamic_cast<__String*>(objectForKey(key));
    if (pStr == NULL)
    {
        pStr = __String::create("");
    }
    return pStr;
}

const __String* __Dictionary::valueForKey(intptr_t key)
{
    __String* pStr = dynamic_cast<__String*>(objectForKey(key));
    if (pStr == NULL)
    {
        pStr = __String::create("");
    }
    return pStr;
}

void __Dictionary::setObject(Object* pObject, const std::string& key)
{
    CCASSERT(key.length() > 0 && pObject != NULL, "Invalid Argument!");
    if (_dictType == kDictUnknown)
    {
        _dictType = kDictStr;
    }

    CCASSERT(_dictType == kDictStr, "this dictionary doesn't use string as key.");

    DictElement *pElement = NULL;
    HASH_FIND_STR(_elements, key.c_str(), pElement);
    if (pElement == NULL)
    {
        setObjectUnSafe(pObject, key);
    }
    else if (pElement->_object != pObject)
    {
        Object* pTmpObj = pElement->_object;
        pTmpObj->retain();
        removeObjectForElememt(pElement);
        setObjectUnSafe(pObject, key);
        pTmpObj->release();
    }
}

void __Dictionary::setObject(Object* pObject, intptr_t key)
{
    CCASSERT(pObject != NULL, "Invalid Argument!");
    if (_dictType == kDictUnknown)
    {
        _dictType = kDictInt;
    }

    CCASSERT(_dictType == kDictInt, "this dictionary doesn't use integer as key.");

    DictElement *pElement = NULL;
    HASH_FIND_PTR(_elements, &key, pElement);
    if (pElement == NULL)
    {
        setObjectUnSafe(pObject, key);
    }
    else if (pElement->_object != pObject)
    {
        Object* pTmpObj = pElement->_object;
        pTmpObj->retain();
        removeObjectForElememt(pElement);
        setObjectUnSafe(pObject, key);
        pTmpObj->release();
    }

}

void __Dictionary::removeObjectForKey(const std::string& key)
{
    if (_dictType == kDictUnknown)
    {
        return;
    }
    
    CCASSERT(_dictType == kDictStr, "this dictionary doesn't use string as its key");
    CCASSERT(key.length() > 0, "Invalid Argument!");
    DictElement *pElement = NULL;
    HASH_FIND_STR(_elements, key.c_str(), pElement);
    removeObjectForElememt(pElement);
}

void __Dictionary::removeObjectForKey(intptr_t key)
{
    if (_dictType == kDictUnknown)
    {
        return;
    }
    
    CCASSERT(_dictType == kDictInt, "this dictionary doesn't use integer as its key");
    DictElement *pElement = NULL;
    HASH_FIND_PTR(_elements, &key, pElement);
    removeObjectForElememt(pElement);
}

void __Dictionary::setObjectUnSafe(Object* pObject, const std::string& key)
{
    pObject->retain();
    DictElement* pElement = new DictElement(key.c_str(), pObject);
    HASH_ADD_STR(_elements, _strKey, pElement);
}

void __Dictionary::setObjectUnSafe(Object* pObject, const intptr_t key)
{
    pObject->retain();
    DictElement* pElement = new DictElement(key, pObject);
    HASH_ADD_PTR(_elements, _intKey, pElement);
}

void __Dictionary::removeObjectsForKeys(__Array* pKey__Array)
{
    Object* pObj = NULL;
    CCARRAY_FOREACH(pKey__Array, pObj)
    {
        __String* pStr = static_cast<__String*>(pObj);
        removeObjectForKey(pStr->getCString());
    }
}

void __Dictionary::removeObjectForElememt(DictElement* pElement)
{
    if (pElement != NULL)
    {
        HASH_DEL(_elements, pElement);
        pElement->_object->release();
        CC_SAFE_DELETE(pElement);
    }
}

void __Dictionary::removeAllObjects()
{
    DictElement *pElement, *tmp;
    HASH_ITER(hh, _elements, pElement, tmp) 
    {
        HASH_DEL(_elements, pElement);
        pElement->_object->release();
        CC_SAFE_DELETE(pElement);

    }
}

Object* __Dictionary::randomObject()
{
    if (_dictType == kDictUnknown)
    {
        return NULL;
    }
    
    Object* key = allKeys()->getRandomObject();
    
    if (_dictType == kDictInt)
    {
        return objectForKey( static_cast<__Integer*>(key)->getValue());
    }
    else if (_dictType == kDictStr)
    {
        return objectForKey( static_cast<__String*>(key)->getCString());
    }
    else
    {
        return NULL;
    }
}

__Dictionary* __Dictionary::create()
{
    __Dictionary* ret = new __Dictionary();
    if (ret && ret->init() )
    {
        ret->autorelease();
    }
    return ret;
}

bool __Dictionary::init()
{
    return true;
}

__Dictionary* __Dictionary::createWithDictionary(__Dictionary* srcDict)
{
    return srcDict->clone();
}

static __Array* visitArray(const ValueVector& array);

static __Dictionary* visitDict(const ValueMap& dict)
{
    __Dictionary* ret = new __Dictionary();
    ret->init();
    
    for (auto iter = dict.begin(); iter != dict.end(); ++iter)
    {
        if (iter->second.getType() == Value::Type::MAP)
        {
            const ValueMap& subDict = iter->second.asValueMap();
            auto sub = visitDict(subDict);
            ret->setObject(sub, iter->first);
            sub->release();
        }
        else if (iter->second.getType() == Value::Type::VECTOR)
        {
            const ValueVector& arr = iter->second.asValueVector();
            auto sub = visitArray(arr);
            ret->setObject(sub, iter->first);
            sub->release();
        }
        else
        {
            auto str = new __String(iter->second.asString());
            ret->setObject(str, iter->first);
            str->release();
        }
    }
    return ret;
}

static __Array* visitArray(const ValueVector& array)
{
    __Array* ret = new __Array();
    ret->init();
    
    std::for_each(array.begin(), array.end(), [&ret](const Value& value){
        if (value.getType() == Value::Type::MAP)
        {
            const ValueMap& subDict = value.asValueMap();
            auto sub = visitDict(subDict);
            ret->addObject(sub);
            sub->release();
        }
        else if (value.getType() == Value::Type::VECTOR)
        {
            const ValueVector& arr = value.asValueVector();
            auto sub = visitArray(arr);
            ret->addObject(sub);
            sub->release();
        }
        else
        {
            auto str = new __String(value.asString());
            ret->addObject(str);
            str->release();
        }
    });
    
    return ret;
}

__Dictionary* __Dictionary::createWithContentsOfFileThreadSafe(const char *pFileName)
{
    return visitDict(FileUtils::getInstance()->getValueMapFromFile(pFileName));
}

void __Dictionary::acceptVisitor(DataVisitor &visitor)
{
    return visitor.visit(this);
}

__Dictionary* __Dictionary::createWithContentsOfFile(const char *pFileName)
{
    auto ret = createWithContentsOfFileThreadSafe(pFileName);
    if (ret != nullptr)
    {
        ret->autorelease();
    }
    return ret;
}

bool __Dictionary::writeToFile(const char *fullPath)
{
    ValueMap dict;
    DictElement* element = nullptr;
    CCDICT_FOREACH(this, element)
    {
        dict[element->getStrKey()] = Value(static_cast<__String*>(element->getObject())->getCString());
    }
    
    return FileUtils::getInstance()->writeToFile(dict, fullPath);
}

__Dictionary* __Dictionary::clone() const
{
    __Dictionary* newDict = __Dictionary::create();
    
    DictElement* element = NULL;
    Object* tmpObj = NULL;
    Clonable* obj = NULL;
    if (_dictType == kDictInt)
    {
        CCDICT_FOREACH(this, element)
        {
            obj = dynamic_cast<Clonable*>(element->getObject());
            if (obj)
            {
                tmpObj = dynamic_cast<Object*>(obj->clone());
                if (tmpObj)
                {
                    newDict->setObject(tmpObj, element->getIntKey());
                }
            }
            else
            {
                CCLOGWARN("%s isn't clonable.", typeid(*element->getObject()).name());
            }
        }
    }
    else if (_dictType == kDictStr)
    {
        CCDICT_FOREACH(this, element)
        {
            obj = dynamic_cast<Clonable*>(element->getObject());
            if (obj)
            {
                tmpObj = dynamic_cast<Object*>(obj->clone());
                if (tmpObj)
                {
                    newDict->setObject(tmpObj, element->getStrKey());
                }
            }
            else
            {
                CCLOGWARN("%s isn't clonable.", typeid(*element->getObject()).name());
            }
        }
    }
    
    return newDict;
}

NS_CC_END
