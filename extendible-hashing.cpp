#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;

int global_depth;
int bucket_capacity;
bool allow_duplicates = false;

class Bucket
{
public:
    int local_depth;
    int count = 0;
    int capacity = 4;
    vector<int> container;
    Bucket(int size, int depth)
    {
        local_depth = depth;
        capacity = size;
        container.resize(size);
    }
    Bucket(int depth)
    {
        local_depth = depth;
        capacity = bucket_capacity;
        container.resize(bucket_capacity);
    }
    Bucket()
    {
        local_depth = global_depth;
        capacity = bucket_capacity;
        container.resize(capacity);
    }
    int insert(int key, bool ignore = allow_duplicates)
    {
        if (count >= capacity)
        {
            cout << "ERROR 500: Bucket full, insert not allowed.\n";
            return 0;
        }
        int res = search(key);
        if (res == 1 && !ignore)
        {
            // while (true)
            // {
            //     char instruction;
            //     cout << "WARNING : Duplicate key entry detected.\nEnter 'y' if you want to insert it anyways or 'n' to cancel the operation: ";
            //     cin>>ws;
            //     cin >> instruction;
            //     if (instruction == 'n')
            //         return 0;
            //     break;
            // }
            cout<<"ERROR: Duplicate key entry detected, insertion terminated\n";
            return 0;
        }
        container[count] = key;
        count++;
        return 1;
        // sort(container.begin(), container.begin() + count); //or maybe a O(n) insert // or use a multiset
    }
    int search(int key)
    {
        for (int i = 0; i < count; i++)
        {
            if (container[i] == key)
            {
                return 1;
            }
        }
        return 0;
    }
    int remove(int key)
    {
        int idx = -1;
        for (int i = 0; i < count; i++)
        {
            if (container[i] == key)
            {
                idx = i;
                break;
            }
        }
        if (idx == -1)
            return 2;
        else if (count == 1)
        {
            // do something
            count--;
            return 0;
        }
        else
        {
            swap(container[count - 1], container[idx]);
            count--;
            return 1;
        }
    }
};

class Directory
{
public:
    int global_depth;
    int capacity;
    int max_depth = 20;
    vector<Bucket *> dirc;
    map<int, Bucket*> creation_index;
    int current_index = 0;
    Directory()
    {
        capacity = 2;
        global_depth = 1;
        dirc.resize(2);
        initialize_dirc();
    }
    Directory(int depth)
    {
        capacity = (1 << depth);
        global_depth = depth;
        dirc.resize(capacity);
        initialize_dirc();
    }
    int insert(int key)
    {
        int idx = hash_function(key);
        Bucket *ref = dirc[idx];
        if (ref->count < ref->capacity)
        {
            return (*ref).insert(key);
        }
        else
        {
            if (ref->local_depth < global_depth)
            {
                int new_idx = (1 << ref->local_depth) + hash_function(key, ref->local_depth);
                dirc[new_idx] = new Bucket(ref->local_depth + 1);
                creation_index[current_index++] = dirc[new_idx];
                ref->local_depth++;
                redistribute(ref, dirc[new_idx]);
                return insert(key);
            }
            else
            {
                if (global_depth == max_depth)
                {
                    cout << "ERROR : Max depth reached for directory(" << max_depth << "), insertion terminated.\n";
                    return 0;
                }
                global_depth++;
                int old_capacity = capacity;
                capacity *= 2;
                dirc.resize(capacity);
                for (int i = 0; i < old_capacity; i++)
                {
                    dirc[old_capacity + i] = dirc[i];
                }
                return insert(key);
            }
        }
        return 0;
    }

    int search(int key)
    {
        int idx = hash_function(key);
        Bucket *ref = dirc[idx];
        int res = (*ref).search(key);
        if (res)
            cout << "FOUND(" << key << ") \n";
        else
            cout << "NOT FOUND(" << key << ") \n";
        return res;
    }

    void remove(int key)
    {
        int idx = hash_function(key);
        Bucket *ref = dirc[idx];
        int res = (*ref).remove(key);
        if (res == 2)
            cout << "Key doesn't exist\n";
        if (res == 1)
            cout << "Key removed\n";
        if (res == 0)
            cout << "Key removed (last key from its bucket)\n";
    }

    void show(bool full = false)
    {
        if(full)
        cout << "Global depth: "; 
        cout<< global_depth << "\n";
        if(full)
        cout << "Number of buckets: ";
        cout << creation_index.size() << "\n";
        for (int i=0; i < creation_index.size(); i++)
        {
            if(full)
                cout<<i+1<<". ";
            cout<<creation_index[i]->count<<" "<<creation_index[i]->local_depth<<"\n";
        }
    }

private:
    void initialize_dirc()
    {
        for (auto &x : dirc)
        {
            x = new Bucket(global_depth);
            creation_index[current_index++] = x;
        }
    }
    int hash_function(int key, int depth = -1)
    {
        depth = (depth == -1) ? global_depth : depth;
        int mod = 1 << depth;
        return (key % mod);
    }
    void redistribute(Bucket *src, Bucket *dst)
    {
        vector<int> s = src->container;
        int s_size = src->count;
        vector<int> d = dst->container;
        int d_size = dst->count;

        src->count = 0;
        dst->count = 0;
        for (int i = 0; i < s_size; i++)
        {
            insert(s[i]);
        }
        for (int i = 0; i < d_size; i++)
        {
            insert(d[i]);
        }
    }
};

/*
First two lines describe the initialization parameters for your extendible hash table.
Line 1: Global depth
Line 2: Bucket capacity
Remaining lines of the input file describe the operations to be performed on the hash table.
2: Insert new value
3: Search a value
4: Delete a value
5: Display status of the hash table
6: Quit
*/

int main()
{
    cout << "Hello World!" << endl;
    cin >> global_depth >> bucket_capacity;
    Directory hash_table(global_depth);
    bool flag = false;

    while (true)
    {
        if (flag)
        {
            cout << "Exiting ... \n";
            break;
        }
        cout << "\n";
        int instruction;
        cin >> instruction;
        switch (instruction)
        {
        case 2:
        {
            // insert a new value
            int value;
            cin >> value;
            int res = hash_table.insert(value);
            if (res == 1)
            {
                cout << "Key Inserted\n";
            }
            break;
        }
        case 3:
        {
            int value;
            cin >> value;
            hash_table.search(value);
            break;
        }
        case 4:
        {
            int value;
            cin >> value;
            hash_table.remove(value);
            break;
        }
        case 5:
        {
            hash_table.show(!true);
            break;
        }
        case 6:
        {
            flag = true;
            break;
        }
        // case 7:
        // {
        //     allow_duplicates = !allow_duplicates;
        //     cout<<"Duplicate key entry are now ";
        //     (allow_duplicates)? cout<<"enabled\n" : cout<<"disabled, if you try to insert duplicates the program may remove earlier stored duplicate keys.\n";
        //     break;
        // }
        default:
        {
            cout << "Not a valid input. Please try again\n";
        }
        }
    }

    return 0;
}