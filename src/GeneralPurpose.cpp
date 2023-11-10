#include "GeneralPurpose.h"

std::vector<std::string> split(std::string str, char separator)
{
    int lastSeparatorPosition = -1;
    std::vector<std::string> words;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == separator) {
            if (i - lastSeparatorPosition > 1)
                words.push_back(std::string(str.begin() + (lastSeparatorPosition + 1), str.begin() + i));
            lastSeparatorPosition = i;
        }
    }

    if (lastSeparatorPosition < (int)str.size() - 1)
        words.push_back(std::string(str.begin() + (lastSeparatorPosition + 1), str.end()));

    return words;
}
