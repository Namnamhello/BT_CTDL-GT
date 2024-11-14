#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// Cấu trúc cho một node trong danh sách liên kết
struct FileNode {
    string fileName;       // Tên file
    long fileSize;         // Kích thước file (bytes)
    time_t timeAdded;      // Thời gian thêm vào danh sách
    FileNode* next;        // Con trỏ đến node tiếp theo
};

// Danh sách liên kết đơn
struct LinkedList {
    FileNode* head; // Con trỏ đầu danh sách

    LinkedList() { // Hàm khởi tạo cơ bản
        head = nullptr;
    }

    // Hàm thêm file vào danh sách
    void addFile(string fileName, long fileSize) {
        FileNode* newNode = new FileNode; // Tạo node mới
        newNode->fileName = fileName;
        newNode->fileSize = fileSize;
        newNode->timeAdded = time(nullptr); // Lấy thời gian hiện tại
        newNode->next = nullptr;

        // Nếu danh sách rỗng hoặc file mới có thời gian nhỏ hơn node đầu tiên
        if (!head || newNode->timeAdded < head->timeAdded) {
            newNode->next = head; // Chèn vào đầu
            head = newNode;
        } else {
            FileNode* temp = head;
            // Tìm vị trí thích hợp để chèn
            while (temp->next && temp->next->timeAdded <= newNode->timeAdded) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode; // Chèn vào giữa hoặc cuối
        }
    }

    // Hàm tính tổng kích thước file trong danh sách
    long calculateTotalSize() {
        long totalSize = 0;
        FileNode* temp = head;
        while (temp) {
            totalSize += temp->fileSize;
            temp = temp->next;
        }
        return totalSize;
    }

    // Hàm hiển thị danh sách các file
    void displayFiles() {
        FileNode* temp = head;
        while (temp) {
            cout << "File: " << temp->fileName 
                 << ", Size: " << temp->fileSize << " bytes"
                 << ", Time Added: " << temp->timeAdded << endl;
            temp = temp->next;
        }
    }

    // Hàm loại bỏ file để tổng kích thước không vượt quá 32GB
    void trimToFitUSB(long maxSize) {
        while (calculateTotalSize() > maxSize) {
            if (head) {
                FileNode* temp = head;
                head = head->next; // Xóa node đầu tiên
                delete temp;       // Giải phóng bộ nhớ
            }
        }
    }
};
int main() {
    LinkedList fileList;

    // Thêm các file vào danh sách
    fileList.addFile("File1.txt", 1048576);  // 1MB
    fileList.addFile("File2.txt", 5242880); // 5MB
    fileList.addFile("File3.txt", 1073741824); // 1GB
    fileList.addFile("File4.txt", 17179869184); // 16GB

    cout << "Danh sach file truoc khi loai bo:" << endl;
    fileList.displayFiles();

    // Tính tổng kích thước file
    cout << "Tong kich thuoc file: " << fileList.calculateTotalSize() << " bytes" << endl;

    // Loại bỏ file để vừa với USB 32GB (32 * 1024 * 1024 * 1024 bytes)
    fileList.trimToFitUSB(32L * 1024 * 1024 * 1024);

    cout << "\nDanh sach file sau khi loai bo de vua voi USB 32GB:" << endl;
    fileList.displayFiles();

    return 0;
}
