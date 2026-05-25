//link github: https://github.com/QuanPM2006/Project-lttt.git

*MÔ TẢ CHUNG VỀ PROJECT
- Một chương trình C++ được thiết kế để giải quyết bài toán trọng tâm trong Lý thuyết thông tin: Tính toán khoảng cách Hamming nhỏ nhất d_min của một mã khối tuyến tính dựa trên ma trận kiểm tra H.
- Trình bày lời giải chi tiết: In ra từng bước duyệt tổ hợp, minh họa trực quan phép cộng XOR của các vector cột phụ thuộc tuyến tính để chứng minh kết quả d_min.
- Đánh giá năng lực mã: Tự động tính toán và kết luận khả năng phát hiện lỗi e và khả năng sửa lỗi t của bộ mã.
- Tối ưu hiệu năng: Ứng dụng kỹ thuật đệ quy quay lui kết hợp Cắt tỉa nhánh để xử lý nhanh 
các ma trận kích thước lớn.

*THIẾT KẾ HỆ THỐNG

Lớp Bit:
    + Đóng vai trò là đơn vị dữ liệu nhỏ nhất.
    + Tính năng: Nạp chồng toán tử cộng operator+ bằng phép XOR (^), đảm bảo quy tắc toán học 1 + 1 = 0.
Lớp BinaryVector:
    + Là một mảng động std::vector chứa các đối tượng Bit.
    + Tính năng: Nạp chồng toán tử operator+ để cộng XOR hai vector. Cung cấp hàm laVectorKhong() để kiểm tra xem tổng các vector có bằng không gian không hay không.
Lớp BinaryMatrix:
    + Là mảng 2 chiều chứa các BinaryVector.
    + Tính năng: Nạp chồng luồng cin/cout để nhập/xuất ma trận dễ dàng. Quan trọng nhất là hàm rutMotCotRa() giúp trích xuất dữ liệu dọc thành vector ngang để phục vụ thuật toán.
Lớp LinearBlockCode:
    + Lớp quản lý ma trận $H$ và thực thi thuật toán.
    + Thuật toán cốt lõi: Sử dụng Backtracking trong hàm thuChonCot().
                           Thuật toán vét cạn từ w = 1 -> n để tìm tổ hợp cột có tổng XOR bằng Vector 0.
                           Áp dụng kỹ thuật Cắt tỉa nhánh sớm giúp tối ưu triệt để thời gian chạy.

* HƯỚNG DẪN CÀI ĐẶT
  Dự án được viết hoàn toàn bằng C++ tiêu chuẩn.

  Yêu cầu hệ thống:

  Trình biên dịch C++ 
  IDE: Visual Studio Code, Dev-C++, hoặc Code::Blocks.

  Cách thức cài đặt:
  main.cpp: Chứa toàn bộ mã nguồn chương trình.
  test.in: File chứa các testcase đầu vào.


* CÁCH THỨC TRIỂN KHAI VÀ KIỂM TRA TÍNH ĐÚNG ĐẮN
Chương trình được thiết kế để đọc luồng dữ liệu chuẩn, tương thích hoàn hảo với các hệ thống chấm điểm tự động (ICPC).

Bước 1: Chuẩn bị dữ liệu Test 
Cấu trúc dữ liệu trong file test.in cho mỗi bộ test như sau:
Dòng 1: Ghi 2 số nguyên r và c (Số hàng và Số cột của ma trận H).
r dòng tiếp theo: Mỗi dòng ghi c số (chỉ gồm 0 và 1), cách nhau bởi dấu cách.


Ví dụ một testcase (Mã Hamming 7,4):


3 7
1 0 1 1 1 0 0
1 1 1 0 0 1 0
0 1 1 1 0 0 1
Bước 2: Biên dịch và Chạy
Mở Terminal tại thư mục chứa file main.cpp và thực hiện các lệnh sau:

1. Biên dịch mã nguồn:

Bash
g++ main.cpp -o main.exe
2. Chạy chương trình và cấp dữ liệu từ file:

Bash
.\main.exe < test.in > test.out
Bước 3: Đánh giá kết quả
Mở file test.out để kiểm tra tính đúng đắn.


Xác nhận ma trận $H$ đầu vào.
Quá trình tìm kiếm $d_{min}$ (Báo cáo các tổ hợp không thành công).
Minh họa chi tiết phép cộng XOR các cột vừa tìm được để chứng minh chúng thực sự tạo ra Vector Không
Kết luận d_min, năng lực phát hiện và sửa lỗi của hệ thống
