#include <iostream>
#include <fstream>
using namespace std;

// RAII Example 1: File handling with Resource class
class FileHandler {
private:
    ifstream file;
    
public:
    FileHandler(const string& filename) {
        cout << "Acquiring resource: Opening file " << filename << endl;
        file.open(filename);
        if (!file.is_open()) {
            throw runtime_error("Failed to open file");
        }
    }
    
    ~FileHandler() {
        cout << "Releasing resource: Closing file" << endl;
        if (file.is_open()) {
            file.close();
        }
    }
    
    void readContent() {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
    }
};

// RAII Example 2: Memory management with smart pointer wrapper
class MemoryBlock {
private:
    int* data;
    size_t size;
    
public:
    MemoryBlock(size_t sz) : size(sz) {
        cout << "Allocating " << size << " integers" << endl;
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = i;
        }
    }
    MemoryBlock(const MemoryBlock&) = delete;
    MemoryBlock& operator=(const MemoryBlock&) = delete;
    ~MemoryBlock() {
        cout << "Deallocating memory" << endl;
        delete[] data;
    }
    
    int getValue(size_t index) {
        if (index < size) return data[index];
        return -1;
    }
};

// RAII Example 3: Locking mechanism
class Mutex {
public:
    void lock() {
        cout << "Lock acquired" << endl;
    }
    void unlock() {
        cout << "Lock released" << endl;
    }
};

class ScopedLock {
private:
    Mutex& mutex;
    
public:
    ScopedLock(Mutex& m) : mutex(m) {
        mutex.lock();
    }
    
    ~ScopedLock() {
        mutex.unlock();
    }
};

int main() {
    cout << "=== RAII Concept in C++ ===" << endl;
    try {
    FileHandler file("example.txt");
    file.readContent();
} catch (const runtime_error& error) {
    cerr << error.what() << endl;
}
    // Example 1: Memory management
    cout << "\n--- Memory Management ---" << endl;
    {
        MemoryBlock block(5);
        cout << "Value at index 2: " << block.getValue(2) << endl;
    } // Resource automatically released here
    
    // Example 2: Scoped Lock
    cout << "\n--- Scoped Lock ---" << endl;
    Mutex m;
    {
        ScopedLock lock(m);
        cout << "Critical section" << endl;
    } // Lock automatically released here
    
    cout << "\n=== All resources cleaned up ===" << endl;
    return 0;
}
