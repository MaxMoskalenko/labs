bool deleting(long long key)
{

    if (count != 0)
    {
        HashNode *node = hat;
        if (node->key == key)
        {

            if (node->prev == NULL && node->next == NULL)
            { //удаление единственной ноды
                hat = node->next;
            }
            Data deleted = node->HashNode.robot;
            delete node;
            count--;
            return true;
            else
            {
                return false;
            }
        }
        while (node != NULL)
        {
            if (node->key == key)
            {
                if (node->prev == NULL && node->next != NULL) //удаление первой ноды
                {
                    hat = node->next;
                    node->next->prev = NULL;
                }
                else
                {
                    if (node->prev != NULL) //удаление средней ноды
                    {
                        node->prev->next = node->next; //предыдущая нода показывает на ту, на которую показывает наша первая нода (следующая нашей ноды)
                        node->next->prev = node->prev; //нода которая следующая после взятой показывает на то, на что показывала(<-) наша нода
                    }
                    else
                    {
                        if (node->next == NULL && node->prev != NULL)
                        {                            //УДАЛЕНИЕ ПОСЛЕДНЕЙ НОДЫ
                            node->prev->next = NULL; //предыдущая нашей ноды показывает на нулл
                        }
                    }
                }
                Data deleted = node->HashNode.robot;
                delete node;
                count--;
            }
            return true;
            node = node->next;
        }
    }
    return false;
}