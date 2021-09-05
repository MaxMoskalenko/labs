void insert(long long key, Data value)
{
    long index = Hash(key);

    do
    {
        if (bucketsArray[index].key == key && bucketsArray[index].is_deleted == false)
        {
            return;
        }
        else if (bucketsArray[index].is_deleted == true || (bucketsArray[index].is_deleted == false && bucketsArray[index].data == nullptr))
        {
            bucketsArray[index].data = new Data;
            *(bucketsArray[index].data) = value;
            bucketsArray[index].key = key;
            bucketsArray[index].is_deleted = false;
            amountOfElemets++;
            break;
        }
        else
        {
            index = (index + 1) % M;
        }
    } while (true);

    if (amountOfElemets >= loadFactor * M)
    {
        M *= 2;
        amountOfElemets = 0;
        Data_Container *oldBucketsArray = bucketsArray;
        bucketsArray = new Data_Container[M];
        for (int i = 0; i < M / 2; i++)
        {
            if (oldBucketsArray[i].is_deleted == false && oldBucketsArray[i].data != nullptr)
            {
                (*this).insert(oldBucketsArray[i].key, *(oldBucketsArray[i].data));
            }
        }
        delete[] oldBucketsArray;
    }
}

void insert(long long key, Data data)
{
    int position = hash(key);

    while (true)
    {
        if (bucketArray[position].isEmpty)
        {
            bucketArray[position].data = data;
            bucketArray[position].key = key;
            bucketArray[position].isEmpty = false;
            isize++;
            break;
        }
        if (bucketArray[position].key == key)
        {
            bucketArray[position].data = data;
            bucketArray[position].key = key;
            bucketArray[position].isEmpty = false;
            break;
        }
        position = (position + 1) % m;
    }
    if (isize >= maxLoadFactor * m)
        increaseSize();
}