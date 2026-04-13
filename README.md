# Travel-Route-Optimization (TSP)

**Bài toán:** Tối ưu hóa lộ trình du lịch (Traveling Salesman Problem)

## 1. Mô tả bài toán

Một công ty du lịch cần lên kế hoạch hành trình ngắn nhất để đi qua **n thành phố** khác nhau:
- Xuất phát từ thành phố **0** (cố định)
- Đi qua tất cả các thành phố **đúng 1 lần**
- Trở về điểm xuất phát
- **Mục tiêu:** Tìm chi phí tối thiểu

## 2. Cách chạy chương trình

### **Biên dịch:**
```bash
g++ -std=c++17 -o TSP TSP.cpp
```

### **Chạy:**
```bash
./TSP
```

### **Hoặc một lệnh:**
```bash
g++ -std=c++17 -o TSP TSP.cpp && ./TSP
```

## 3. Input / Output

### **Input (input.txt):**
```
5                    # Số test case
4                    # Số thành phố (n)
0 20 42 35           # Ma trận chi phí C[i][j]
20 0 30 34
42 30 0 12
35 34 12 0
...
```

### **Output (output.txt):**
```
========== TEST CASE 1 (n=4) ==========
====BACKTRACKING====
Chi phi toi thieu: 97
Lo trinh: 0 1 2 3 0
Thoi gian: 0 ms

====BITMASK DP====
Chi phi toi thieu: 97
Lo trinh: 0 1 2 3 0
Thoi gian: 0 ms

====GREEDY====
Chi phi: 97
Lo trinh: 0 1 2 3 0
Thoi gian: 0 ms
```

## 4. Ba thuật toán

### **1. Backtracking**
- **Ý tưởng:** Duyệt tất cả hoán vị, cắt nhánh khi vượt chi phí hiện tại
- **Độ phức tạp:** O(n!)
- **Ưu điểm:** Đảm bảo tìm được kết quả optimal
- **Nhược điểm:** Chậm với n lớn (n > 12)

### **2. Bitmask DP (Dynamic Programming)**
- **Ý tưởng:** `dp[mask][i]` = chi phí min để thăm tập đỉnh `mask`, kết thúc tại `i`
- **Độ phức tạp:** O(2^n × n²)
- **Ưu điểm:** Nhanh hơn Backtracking, tìm được optimal
- **Nhược điểm:** Tốn bộ nhớ với n lớn (n > 15)

### **3. Greedy (Tham lam)**
- **Ý tưởng:** Mỗi bước chọn thành phố gần nhất chưa thăm
- **Độ phức tạp:** O(n²)
- **Ưu điểm:** Rất nhanh, đơn giản
- **Nhược điểm:** Không đảm bảo optimal

## 5. Kết quả test

| Test | n | BT | DP | Greedy | Thời gian |
|------|---|----|----|--------|-----------|
| 1 | 4 | 97 | 97 | 97 | 0 ms |
| 2 | 5 | 80 | 80 | 80 | 0 ms |
| 3 | 6 | 109 | 109 | 109 | 0 ms |
| 4 | 7 | 85 | 85 | 85 | 0 ms |
| 5 | 8 | 212 | 212 | 212 | 0 ms |

## 6. Cấu trúc file

```
TSP.cpp          # Source code (chứa 3 thuật toán)
input.txt        # 5 test case
output.txt       # Kết quả chạy
README.md        # Hướng dẫn này
```

## 7. Ghi chú

- **Chuẩn C++:** C++17 trở lên
- **Max n:** 20 (giới hạn mảng)
- **Thư viện:** iostream, fstream, cstring, climits, ctime
- Chương trình ghi output vào file theo **append mode** (có thể chạy nhiều lần)
