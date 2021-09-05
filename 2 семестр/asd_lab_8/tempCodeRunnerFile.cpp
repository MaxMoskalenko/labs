while (true)
    {
        std::cout << "Input: ";
        std::cin >> word;

        std::cout << "Output: ";
        std::vector<std::string> result = tree.findByPrefix(word);
        printVector(result);
        std::cout << std::endl;

        char isContinue;
        std::cout << "Do you want to continue (y|n): ";
        std::cin >> isContinue;
        if (isContinue == 'n')
            break;
    }