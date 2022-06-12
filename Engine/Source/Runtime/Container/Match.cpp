#include "Match.h"
#include "Platform/Timer.h"

using namespace Matrix::Container;

MMatch::MMatch()
{
    Clear();
}
MMatch::~MMatch()
{
}
void MMatch::Clear()
{
    b_index = -1;
    p_index = -1;
    num_pstrings = 0;
    pfloats.Clear();
    pints.Clear();
    Core::MXMemset(pstrings, 0, sizeof(pstrings));
}
bool MMatch::Open(TCHAR *filename)
{
    if (File.Open(filename, Core::File::OM_RB))
        return true;
    return false;
}
bool MMatch::Getline()
{

    int index = 0;  // general index
    int length = 0; // general length

    Core::MXMemset(buffer, 0, sizeof(buffer));
    while (1)
    {
        //读取一行数据，如果一行数据超过maxlength，则读取maxlength长度，文件指针移动
        // maxlength单位，如果一行数据小于maxlength，则文件指针移动到下一行！
        index = 0;
        if (!File.GetLine(buffer, BUFFER_SIZE))
        {
            Core::MXMemset(buffer, 0, sizeof(buffer));
            return false;
        }
        //读取这一行实际长度
        length = Core::MXStrLen(buffer);
        //测试本行遇到文本前的空格数
        while (_istspace(buffer[index]))
            index++;

        //空行或注释则继续
        if (index >= length)
            continue;
        Core::MXMemcpy((void *)buffer, (void *)(buffer + index), ((length - index) + 1) * sizeof(TCHAR));
        length = length - 1;
        while (buffer[length] == 10 || buffer[length] == 13)
        {
            buffer[length] = 0;
            length--;
            if (length == -1)
            {
                break;
            }
        }

        break;
    }

    return 1;
}
bool MMatch::PatternMatch(TCHAR *_pattern)
{
    pattern = _pattern;
    return Begin();
}
bool MMatch::Begin()
{
    Clear();
    return (Fun1());
}
bool MMatch::Fun1()
{
    p_index++;
    if (pattern[p_index] == _T('\0'))
        return 1;
    else if (pattern[p_index] == _T('['))
        if (buffer[b_index + 1] == _T('\0'))
            return 0;
        else
            return (Fun2());
    else
        return 0;
}
bool MMatch::Fun2()
{
    p_index++;
    if (pattern[p_index] == _T('\''))
        return FunStrMatch();
    else if (pattern[p_index] == _T('s'))
        return FunStr_I_Match();
    else if (pattern[p_index] == _T('i'))
        return FunIntMatch();
    else if (pattern[p_index] == _T('f'))
        return FunFloMatch();
    else
        return 0;
}
bool MMatch::FunStrMatch()
{
    b_index++;
    while (buffer[b_index] == _T(' '))
    {
        b_index++;
        continue;
    }
    b_index--;
    while (1)
    {
        b_index++;
        p_index++;
        if ((buffer[b_index] == _T(' ') || buffer[b_index] == _T('\0')) && pattern[p_index] == _T('\''))
        {
            p_index++;
            if (pattern[p_index] == _T(']'))
                return Fun1();
            else
                return 0;
        }
        else if (buffer[b_index] == pattern[p_index])
            continue;
        else
            return 0;
    }
}
bool MMatch::FunStr_I_Match()
{
    p_index++;
    int len = 0;
    int flag = 0;

    if (pattern[p_index] == _T('='))
        flag = 1;
    else if (pattern[p_index] == _T('<'))
        flag = 2;
    else if (pattern[p_index] == _T('>'))
        flag = 3;
    if (flag != 0)
    {
        p_index++;
        if (pattern[p_index] >= 48 && pattern[p_index] <= 57)
        {
            len = FunIntMatch_D();

            int _b_index = 0;
            b_index++;
            while (buffer[b_index] == ' ')
            {
                b_index++;
                continue;
            }
            b_index--;
            while (1)
            {
                b_index++;
                if (buffer[b_index] == _T('\0') || buffer[b_index] == _T(' '))
                {
                    if (flag == 1)
                    {
                        if (_b_index != len)
                            return 0;
                    }
                    if (flag == 3)
                    {
                        if (_b_index <= len)
                            return 0;
                    }
                    if (flag == 2)
                    {
                        if (_b_index >= len)
                            return 0;
                    }
                    Core::MXMemcpy((void *)pstrings[num_pstrings],
                                   (void *)(buffer + b_index - _b_index), _b_index * sizeof(TCHAR));
                    pstrings[num_pstrings][_b_index] = _T('\0');
                    num_pstrings++;
                    break;
                }
                else
                {
                    _b_index++;
                }
            }
            if (pattern[p_index] == _T(']'))
                return Fun1();
            else
                return 0;
        }
        else
            return 0;
    }
    else
        return 0;
}
int MMatch::FunIntMatch_D()
{
    int _p_index = p_index;
    int result;
    while (1)
    {
        p_index++;
        if (pattern[p_index] >= 48 && pattern[p_index] <= 57)
            continue;
        else
            break;
    }
    TCHAR *num = MX_NEW TCHAR[p_index - _p_index + 1];
    Core::MXMemcpy((void *)num, (void *)(pattern + _p_index), (p_index - _p_index) * sizeof(TCHAR));
    num[p_index - _p_index] = _T('\0');
    result = Math::MXstoi(num);
    ENGINE_DELETEA(num);
    return result;
}
bool MMatch::FunIntMatch()
{
    int num_len = 0;
    b_index++;
    while (buffer[b_index] == _T(' '))
    {
        b_index++;
        continue;
    }
    b_index--;
    b_index++;
    if (buffer[b_index] == _T('+') || buffer[b_index] == _T('-') || Core::MXIstalnum(buffer[b_index]))
    {
        num_len++;
    }
    else
        return 0;
    while (1)
    {
        b_index++;
        if (buffer[b_index] == _T(' ') || buffer[b_index] == _T('\0'))
        {
            TCHAR *num = MX_NEW TCHAR[num_len + 1];
            Core::MXMemcpy((void *)num, (void *)(buffer + b_index - num_len), num_len * sizeof(TCHAR));
            num[num_len] = _T('\0');
            pints.AddElement(Math::MXstoi(num));
            ENGINE_DELETEA(num);
            p_index++;
            if (pattern[p_index] == _T(']'))
                return Fun1();
            else
                return 0;
        }
        else if (Core::MXIstalnum(buffer[b_index]))
        {
            num_len++;
            continue;
        }
        else
            return 0;
    }
}
bool MMatch::FunFloMatch()
{

    int num_len = 0;
    b_index++;
    while (buffer[b_index] == _T(' '))
    {
        b_index++;
        continue;
    }
    b_index--;
    b_index++;
    if (buffer[b_index] == _T('+') || buffer[b_index] == _T('-') || Core::MXIstalnum(buffer[b_index]))
    {
        num_len++;

        b_index++;
        while (Core::MXIstalnum(buffer[b_index]))
        {
            num_len++;
            b_index++;
        }
        if (buffer[b_index] == _T('.'))
        {
            num_len++;
            b_index++;
            if (Core::MXIstalnum(buffer[b_index]))
            {
                while (Core::MXIstalnum(buffer[b_index]))
                {
                    num_len++;
                    b_index++;
                }
            }
            else
            {
                return 0;
            }
            if (buffer[b_index] == _T(' ') || buffer[b_index] == _T('\0'))
            {
                TCHAR *num = MX_NEW TCHAR[num_len + 1];
                Core::MXMemcpy((void *)num, (void *)(buffer + b_index - num_len), num_len * sizeof(TCHAR));
                num[num_len] = '\0';
                pfloats.AddElement(Math::MXstof(num));
                ENGINE_DELETEA(num);
                p_index++;
                if (pattern[p_index] == _T(']'))
                    return Fun1();
                else
                    return 0;
            }
            else
            {
                return 0;
            }
        }
        else if (buffer[b_index] == _T(' ') || buffer[b_index] == _T('\0'))
        {
            TCHAR *num = MX_NEW TCHAR[num_len + 1];
            Core::MXMemcpy((void *)num, (void *)(buffer + b_index - num_len), num_len * sizeof(TCHAR));
            num[num_len] = _T('\0');
            pfloats.AddElement(Math::MXstof(num));
            ENGINE_DELETEA(num);
            p_index++;
            if (pattern[p_index] == _T(']'))
                return Fun1();
            else
                return 0;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}