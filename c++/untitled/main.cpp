#include <iostream>
#include <fstream>

//char replace(char ch)
//{
//    switch (int(ch)) {
//    case -62:
//        //	    if (
//        ch = ' ';
//        break;
//    default:
//        break;
//    }
//    return ch;
//}
void process(std::ifstream &in, std::ofstream &out)
{
    char ch;
    while (in.get(ch)) {
        //	out << replace(ch);
        switch (int(ch)) {
        case -62: {
            char tmp = in.get();
            if ((int)tmp == -96)
            {
                ch = ' ';
            }
            break;
        }
        default:
            break;
        }

        out << ch;
        std::cout << (int)ch;
    }
}

int main(int arc, char *argv[])
{
    std::string fileName;

    if (arc < 2)
    {
        std::cout << "enter the file name: ";
        std::cin >> fileName;
    }
    else {
        fileName = argv[1];
    }

    std::ifstream in(fileName.c_str());
    if (!in)
        std::cout << "cannot read file: " << fileName << std::endl;

    std::ofstream out((fileName + "01").c_str());
    if (!out)
        std::cout << "cannot write file: " << fileName + "01";
    process(in, out);

    in.close();
    out.close();
    std::cout << "done" << std::endl;

    return 0;
}

