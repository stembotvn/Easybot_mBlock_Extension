# Easybot_mBlock_Extension

Mblock là phần mềm cho phép lập trình Scratch cho Robot do hãng MakeBlock phát triển được kế thừa từ Scratch 2.0 của MIT.
Extension là tập hợp file cho phép cài đặt các Block cho các loại robot khác nhau để có thể chạy trên môi trường Mblock. 

Easybot Extension do STEMbot phát triển để có thể lập trình ngôn ngữ Scratch cho các Robot thuộc dòng Easybot để có thể chạy trên môi trường Mblock. 
Tài liệu bắt đầu lập trình Robot với Scratch: https://github.com/stembotvn/ZowiVbot-Mblock-Doccument 



## Cách cài đặt

 ### Cài đặt nhanh:
 Mở mBlock, vào Tab Extension/Manage Extension -> Search: "Easybot" by Hien Phan and download 
 ### Cài đặt thủ công: 
* Dowload Extension với định dạng nén .Zip file về máy tính. 
* Mở phần mềm Mblock, vào tab Extensions/Manage Extensions -> Bấm "Add Extension" -> Chọn đường dẫn tới file Zip vừa download, chú ý chọn loại file là Zip để Extension xuất hiện trên màn hình tìm kiếm Extension. 
* Test chương trình 
## Hoạt động
### Kết nối
Easybot hỗ trợ 2 chế độ kết nối với Mblock là Serial via USB và Bluetooth
1. Serial Connection:
   * Bật nguồn cho Robot, đảm bảo Pin đầy để hoạt động
   * Cắm dây nối USB từ máy tính đến robot, chú ý, sử dụng dây Mini USB với chiều dài ít nhất 40 cm để Robot có thể hoạt động không bị vướng. 
   * Trên phần mềm Mblock, vào Connect/Serial Port: chọn cổng kết nối với Robot, nếu kết nối thành công sẽ được thông báo (Serial Connected)
   * Các Block liên quan đến hoạt động của robot thì vào mục Robot, Zowi Vbot hỗ trợ 3 loại Block: Move, Gesture và Sing với rất nhiều thuộc tính liên quan.
   
 2. Bluetooth Connection: 
 * Máy tính bắt buộc phải có chức năng Bluetooth, nếu không có thì sử dụng Bluetooth USB Dongle. 
 * Bật Bluetooth lên và Pair với Robot, chú ý, tên Device hiển thị là tên Robot hoặc tên module Bluetooth, các bạn có thể Pair lần đầu và sau đó đổi tên tùy ý, mật khẩu để Pair là 1234
 * Vào Connect/Bluetooth: chọn device vừa Pair là (Tên module bluetooth với địa chỉ kèm theo dạng aa:bb:cc:dd:ee:ff) và bấm connect 
 * Nếu kết nối thành công, lập trình giống như với Serial Connection. 
 ### Chạy chương trình
    Extension hiện tại chỉ hỗ trợ Arduino Mode
    
 #### Scratch Mode 
   Scratch Mode là chế độ chạy chương trình Robot ngay trên máy tính, Robot sẽ nhận lệnh từng từ Scratch và thực thi gần như song song: 
   - Ưu điểm là chạy chương trình ngay lập tức mà không phải biên dịch
   - Nhược điểm là Robot chỉ hoạt động khi phần mềm mBlock chạy và phải đảm bảo Robot và máy tính luôn được kết nối  
     Để sử dụng Scratch Mode, Robot phải được nạp trước Firmware thích hợp từ Phần mềm Arduino

 #### Arduino Mode
 Chế độ Arduino mode ta vào mBlock-> Edit/Arduino Mode, Các lệnh Scratch sẽ được dịch qua Arduino code.
   - Chọn Connect/Serial -> Chọn đúng cổng Serial của Robot
   - Chọn Board/Nano 328 
   - Bấm Upload Code to Arduinno để chạy chương trình, lúc này Robot có thể tự hoạt động mà không cần máy tính.
   - Lưu ý: Khi Upload Code to Arduino, Chức năng Scratch Mode sẽ không thể hoạt động trở lại cho đến khi sử dụng Arduino IDE upload lại Firmware tương thích Scratch Mode cho Robot
 ## Note
   Khuyến nghị các bạn lập trình Scratch trên môi trường Mblock nên sử dụng cáp Serial, phiên bản Bluetooth hiện chưa được ổn đinh, nếu bị mất kết nối hoặc không thể kết nối trở lại, phải Restart mBLock software.
   
   Chúc các bạn thực hành vui vẻ với chú robot này
 
 

