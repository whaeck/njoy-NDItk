
static std:: vector<double> read(std::istream& in, std::size_t size, const std::string& keyword){

    std::vector<double> data;
    data.reserve(size);
    double temp;
    std::string key;

    in >> key;
    if (key != keyword)
    {
        throw std::runtime_error("Error! Unexpected keyword.");
    }

    for(unsigned int i=0;i<size;++i)
    {
        in >> temp;
     //    std:: cout << temp << std::endl;

        if(in.fail())
        {
            throw std::runtime_error("Error! Bad input in stream.");
        }

        data.push_back(temp);
        
    }

    


    return data;


}
