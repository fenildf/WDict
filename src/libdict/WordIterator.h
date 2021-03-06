#ifndef _WORDITERATOR_H_
#define _WORDITERATOR_H_

#include <string>

/// 单词迭代器接口
class WordIterator
{
public:
    virtual ~WordIterator() = default;
    virtual std::string Next() = 0;
    virtual bool HasNext() = 0;
};

#endif // _WORDITERATOR_H_
