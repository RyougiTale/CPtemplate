#include <bits/stdc++.h>
using namespace std;

bool compareOutputs(FILE *fp1, FILE *fp2)
{
    const int bufferSize = 1024;
    char buffer1[bufferSize];
    char buffer2[bufferSize];

    while (!feof(fp1) && !feof(fp2))
    {
        size_t bytesRead1 = fread(buffer1, 1, bufferSize, fp1);
        size_t bytesRead2 = fread(buffer2, 1, bufferSize, fp2);
        buffer1[bytesRead1] = '\0';
        buffer2[bytesRead2] = '\0';

        cout << buffer1;
        cout << buffer2;

        if (bytesRead1 != bytesRead2 || memcmp(buffer1, buffer2, bytesRead1) != 0)
        {
            return false;
        }
    }

    // Check if one of the files has more content
    if (!feof(fp1) || !feof(fp2))
    {
        return false;
    }

    return true;
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());                          //  Mersenne Twister
    std::uniform_int_distribution<> distrib(1, 100); // 均匀分布

    for (int fk = 0; fk < 1000; fk++)
    {
        freopen("input.txt", "w", stdout);
        int cases = 50;
        cout << cases << endl;
        for (int i = 0; i < cases; i++)
        {
            cout << distrib(gen) << " " << distrib(gen) << endl;
        }

        FILE *fp1 = popen("test.exe", "r");
        FILE *fp2 = popen("ans.exe", "r");

        if (!fp1 || !fp2)
        {
            std::cerr << "Failed to open programs." << std::endl;
            return 1;
        }

        bool areOutputsEqual = compareOutputs(fp1, fp2);

        pclose(fp1);
        pclose(fp2);

        if (areOutputsEqual)
        {
            std::cout << "Outputs are equal." << std::endl;
            fclose(stdout);
        }
        else
        {
            std::cout << "Outputs are NOT equal." << std::endl;
            break;
        }
    }
    return 0;
}