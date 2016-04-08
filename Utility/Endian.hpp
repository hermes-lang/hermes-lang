/* 
 * File:   Endian.hpp
 * Author: Konstantin
 *
 * Created on March 30, 2016, 11:19 AM
 */

#ifndef ENDIAN_HPP
#define	ENDIAN_HPP

namespace hermes
{
    namespace util
    {
        namespace endian
        {           
            struct Endian
            {
                static size_t endianLength()
                {
                    volatile union
                    {
                        volatile uintmax_t integral;
                        volatile unsigned char array [sizeof(decltype(integral))];
                    } memoryTester;
                    memoryTester.integral = 1;
                    size_t length = 0;
                    while (length < sizeof(decltype(memoryTester.integral)) && memoryTester.array[length] != 1) ++length;
                    return (sizeof(decltype(memoryTester.integral)) - length);
                }
                static size_t value;
            };
            
            size_t Endian::value = Endian::endianLength();
            
            template <typename T>
            union Serializable
            {
                template <typename U>
                Serializable(U&& x) : value(std::forward<U>(x)) {}
                static constexpr size_t size = sizeof(T);
                void serialize() noexcept
                {
                    const size_t high = Endian::value - 1;
                    const size_t frames = size / Endian::value;
                    for (size_t i = 0; i < frames; ++i)
                        for (size_t j = 0, h = high; j < h; ++j, --h)
                        {
                            char temp = c_str[j];
                            c_str[j] = c_str[h];
                            c_str[h] = temp;
                        }
                }
                T value;
                char c_str [size];
            };
        }
    }
}

#endif	/* ENDIAN_HPP */

