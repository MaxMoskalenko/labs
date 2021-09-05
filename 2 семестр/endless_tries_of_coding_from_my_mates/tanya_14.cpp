void change()
{
    Institut pack;
    FILE *fp, *fp2;
    fp = fopen(".\\alc.dat", "r+b");
    fp2 = fopen(".\\alc.dat", "w+b");
    int institutnum;
    cout << "put in a number of string where you want change some information: ";
    cin >> institutnum;
    cout << institutnum;
    int nomer;
    string newnazva;
    string newsurname;
    int newage;
    char newmark;
    int newgroup;

    Fakultet.nazva = 1;
    Student.surname = 2;
    Student.age = 3;
    Student.mark = 4;
    Student.group = 5;

    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    long structSize = sizeof(Institut);
    int numOfStruct = fileSize / structSize;
    for (int i = 0; i < numOfStruct; i++)
    {
        fread(&pack, sizeof(Institut), 1, fp);
        if (i == institutnum)
        {
            cout << "put a number which you want to change 1 - fakultet, 2 -surname, 3 - age, 4 - mark, 5 - group ";
            cin >> nomer;
            cout << nomer;

            if (nomer == 1)
            {
                cout << "enter a new fakultet";
                cin >> newnazva;
                cout << newnazva;
                Institut[institutnum].nazva = newnazva;
            }

            else if (nomer == 2)
            {
                cout << "enter a new surname";
                cin >> newsurname;
                cout << newsurname;
                Institut[institutnum].surname = newsurname;
            }

            else if (nomer == 3)
            {
                cout << "enter new age";
                cin >> newage;
                cout << newage;
                Institut[institutnum].age = newage;
            }

            else if (nomer == 4)
            {
                cout << "enter new mark";
                cin >> newmark;
                cout << newmark;
                Institut[institutnum].mark = newmark;
            }

            else if (nomer == 5)
            {
                cout << "enter new group";
                cin >> newgroup;
                cout << newgroup;
                Institut[institutnum].group = newgroup;
            }
        }
    }

    fwrite(&pack, sizeof(Institut), 1, fp2);
}
fclose(fp);
fclose(fp2);
}