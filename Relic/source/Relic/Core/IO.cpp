#include "pch.h"
#include "IO.h"

namespace Relic { namespace IO
{
    bool DoesFileExist(const std::string& fileName)
    {
        FILE* file = fopen(("data/created/" + fileName).c_str(), "rb");
        if (!file)
            return false;
        
        fclose(file);
        return true;
    }

    void WriteNumberToFile(int num, const std::string& fileName)
    {
        FILE* file = fopen(("data/created/" + fileName).c_str(), "wb");
        if (!file)
        {
            RL_CORE_ERROR("Failed to write {} to {}", num, fileName);
            return;
        }
        fwrite(&num, sizeof(num), 1, file);
        fclose(file);
    }

    int ReadNumberFromFile(const std::string& fileName)
    {
        int num = 0;
        FILE* file = fopen(("data/created/" + fileName).c_str(), "rb");
        if (!file)
        {
            RL_CORE_ERROR("Failed to read {}", fileName); 
            return 0; 
        }

        fread(&num, sizeof(num), 1, file);
        fclose(file);

        return num;
    }
}}
