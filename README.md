# SmartHome_FinalProject
Hệ thống Smart Home - TTV, dùng bộ xử lý trung tâm là ESP32 đọc và nhận dữ liệu thông qua Firebase, kết nối với trang Web được tạo bởi HTML - CSS - JavaScript.
## Chi tiết về hệ thống
### 1. Trang Web
![Các phần của trang Web](https://github.com/ThienHuynh2605/SmartHome_FinalProject/assets/129538825/8db3a8b8-0219-4918-b72f-5f747c650eac)
- Trang Web gồm có Phòng khách, Phòng ngủ và Nhà bếp.
- Mỗi phòng đều có chung nhiệt độ, độ ẩm và khí gas.
- Phòng khách có Quạt, Ti Vi, Loa. Phòng ngủ có Đèn, Ti Vi, Loa. Nhà bếp có Quạt, Cửa bếp, Máy thông gió.
### 2. Google Firebase
Dùng Realtime Database đề đồng bộ các giá trị thời gian thực với Web và ESP32 
![Realtime Database của Google Firebase](https://github.com/ThienHuynh2605/SmartHome_FinalProject/assets/129538825/98a93e94-bbbf-438a-8be1-f077bcc1d8b8)
Cách lấy code cấu hình kết nối Realtime Database:
- Chọn Project setting
  ![image](https://github.com/ThienHuynh2605/SmartHome_FinalProject/assets/129538825/fc775936-cf2e-40e3-9445-756f0e2aed18)
- Kéo xuống đến mục "Installing and configuring the SDK" -> chọn vào "Configuration"
  ![image](https://github.com/ThienHuynh2605/SmartHome_FinalProject/assets/129538825/7574d713-0742-4211-805d-9d03a06a920e)
### 3. Phần cứng và sơ đồ kết nối
Phần cứng gồm:
- Bộ xử lý trung tâm ESP32.
- Nút nhấn (9 cái - mỗi phòng 3 cái).
- Các led đơn là các thiết bị (6 thiết bị - mỗi phòng 2 thiết bị).
- Màn hình LCD1602 dùng để hiển thị giá trị của loa Phòng khách, loa Phòng ngủ và máy thông gió.
- Cảm biến nhiệt độ, độ ẩm DHT11; cảm biến khí Gas MQ2.

Sơ đồ kết nối
![Sơ đồ kết nối](https://github.com/ThienHuynh2605/SmartHome_FinalProject/assets/129538825/e33d1489-f7ea-4663-81a1-e044aa1403d4)

Kết nối trên phần cứng
<img src="https://github.com/ThienHuynh2605/SmartHome_FinalProject/assets/129538825/f7821cdd-5bd4-44ab-9c58-6353eb195423" alt="Kết nối của phần cứng" width="1000" height="750">

[Video Ket Qua He Thong](https://www.youtube.com/watch?v=ODe7xbFddnY)

## Vấn đề của hệ thống
Hệ thống hoạt động trong một thời gian ngắn thì sẽ bị đứng (có thể do việc truyền nhận dữ liệu từ Firebase) nên cần Reset ESP32 để hoạt động lại.

## Các thành viên thực hiện
1. Huỳnh Văn Thiện
2. Nguyễn Thành Trung
3. Đặng Đình Long Vũ





