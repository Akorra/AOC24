int main()
{
    std::ifstream input("data/input.txt");
    if(!input.is_open())
    {
        std::cerr << "[ERROR] " << "Opening File";
        return -1;
    }

    std::vector<int> block, empty;

    int  i=0;
    char ch;
    while(input >> ch)
    {
        if(i%2)
            empty.push_back((int)(ch-'0'));
        else
            block.push_back((int)(ch-'0'));
        i++;
    }

    input.close();

    int sum=0, pos=0, f=0, l=block.size()-1;
    while(f<block.size())
    {  
        while(block[f]>0)
        {
            sum += f * pos;
            block[f]--;
            pos++;
        }

        while(empty[f]>0 && f<l)
        {
            while(block[l]<=0 && f<l)
                l--;
            
            if(f>=l)
                break;

            sum += l * pos;
            block[l]--;
            empty[f]--;
            pos++;
        }
        f++;
    }
    
    {
        ScopedTimer timer("Part 1");


    }
    std::cout << sum << std::endl;

    {
        ScopedTimer timer("Part 2");
 
    }
    
    return 0;
}