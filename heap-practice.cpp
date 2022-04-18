#include <bits/stdc++.h>
using namespace std;

class page
{
public:
    page *prevPage = NULL;
    page *nextPage = NULL;
    int start_add = 0;
    int count_records = 0;
    vector<int> records;
};

class HeapFile
{
private:
    int numberOfPages;
    int pageSize;
    page *start = NULL;

public:
    HeapFile(int size)
    {
        pageSize = size;
        numberOfPages = 0;
    }

    // For iterating through pages
    page *curr;

    void insertData(int record_size, int primaryKey)
    {
        if (start == NULL)
        {
            start = new page();
            (start->records).push_back(primaryKey);
            (start->count_records)++;
            (start->start_add) += record_size;
            ++numberOfPages;
            return;
        }

        else
        {
            curr = start;
            int ans = 0;
            while (curr->nextPage != NULL)
            {
                if ((pageSize - (curr->start_add)) >= record_size)
                {
                    ans = 1;
                    break;
                }

                curr = curr->nextPage;
            }

            if (ans == 0)
            {
                if ((pageSize - (curr->start_add)) >= record_size)
                {
                    ans = 1;
                }

                else
                {
                    ++numberOfPages;
                    page *new_page = new page();
                    new_page->prevPage = curr;
                    curr->nextPage = new_page;
                    curr = new_page;
                }
            }
        }

        (curr->records).push_back(primaryKey);
        (curr->count_records)++;
        curr->start_add += record_size;
        return;
    }

    void search(int primaryKey)
    {
        curr = start;
        int page_no = 0;
        while (curr != NULL)
        {
            for (int i = 0; i < (curr->records).size(); ++i)
            {
                if ((curr->records)[i] == primaryKey)
                {
                    cout << page_no << " " << i << endl;
                    return;
                }
            }

            ++page_no;
            curr = curr->nextPage;
        }

        cout << -1 << " " << -1 << endl;
        return;
    }

    void show()
    {
        cout << numberOfPages << " ";

        curr = start;
        for (int i = 0; i < numberOfPages; ++i)
        {
            cout << curr->count_records << " ";

            curr = curr->nextPage;
        }

        cout << endl;
        return;
    }
};

int main()
{
    int size, opCode;
    cin >> size >> opCode;

    HeapFile *file = new HeapFile(size - 16);

    while (opCode != 4)
    {
        if (opCode == 1)
        {
            int recordSize, primaryKey;
            cin >> recordSize >> primaryKey;
            (*file).insertData(recordSize + 4, primaryKey);
        }

        if (opCode == 2)
        {
            (*file).show();
        }

        if (opCode == 3)
        {
            int primaryKey;
            cin >> primaryKey;
            (*file).search(primaryKey);
        }

        cin >> opCode;
    }

    return 0;
}
