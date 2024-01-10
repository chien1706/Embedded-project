# Giới thiệu về project
Project là một sản phẩm áp dụng hệ thống nhúng có khả năng bật tắt đèn tự động sử dụng cảm biến ánh sáng, cảm biến âm thanh, 
cảm biến siêu âm (cảm biến khoảng cách) và hẹn giờ thời gian thực.
## Hệ thống tự động bật/tắt đèn dựa vào cảm biến ánh sáng
Sản phẩm sử dụng quang trở để có thể nhận biết được ánh sáng xung quanh từ đó đưa ra quyết định về việc bật, tắt đèn. Nếu 
xung quanh tối hệ thống sẽ nhận biết và tự động bật đèn và ngược lại
## Hệ thống tự động bật/tắt đèn dựa vào cảm biến âm thanh
Sản phẩm sử dụng một cảm biến âm thanh được tích hợp vào, khi có âm thanh lớn (được mô phỏng là có người đi đến) thì hệ thống
sẽ phát hiện ra và tự động bật đèn trong một khoảng thời gian sau đó (đang setup là 3 giây) nếu sau đấy vẫn phát hiện ra âm 
thanh thì đèn vẫn tiếp tục sáng còn nếu không phát hiện ra (mô phỏng người đã đi qua) thì đèn sẽ tắt để tiết kiệm năng lượng (điện)
## Hệ thống bật tắt đèn dựa vào cảm biến siêu âm (cảm biến khoảng cách)
Sản phẩm sử dụng một cảm biến âm thanh để phát hiện có vật thể (người) lại gần, khi có vật thể (người) lại gần, cảm biến siêu 
âm sẽ truyền tín hiệu về và đèn sẽ được bật lên, ngược lại khi không có vật thể (người) gần đó thì đèn sẽ tắt đi để tiết kiệm 
năng lượng (điện)
## Hệ thống bật tắt đèn hẹn giờ theo thời gian thực:
Sản phẩm được tích hợp Tiny RTC để có thể cập nhật thời gian thực, kết hợp cùng 8 nút điều chỉnh thời gian (gồm tăng giảm giờ, 
phút thời gian bắt đầu, tăng giảm giờ, phút thời gian kết thúc). Khi thời gian hiện tại nằm trong khoảng thời gian được hẹn giờ 
thì đèn sẽ được bật và ngược lại
# Hướng dẫn cài đặt thư viện
## Arduno IDE
 - Truy cập https://www.arduino.cc/en/software và download phiên bản phù hợp với hệ điều hành
 - Repo có sử dụng một thư viện ngoài là LiquidCrystal_I2C đã được đóng zip đi kèm trong repo trong file: "LidquidCrystal_I2C-1.1.2.zip
# Báo cáo cụ thể của project
Tổng hợp trong file Embedded_project_report.pdf
