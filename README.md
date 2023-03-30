家庭健康管理系统欢迎大佬提供宝贵意见

crontab -e 进行周期脚本

# * * * * * /home/yangyang/Pictures/webcam.sh 2>$1

树莓派与服务器间图片的传递

linux服务器---ftp服务端

树莓派---ftp客户端

这里需要注意，ftp客户端需要设置为passive即被动模式，否则会出现

# 200 PORT command successful 
# 425 Could not open data connection to port 23648: Connection timed out

的错误

解决方法：https://blog.csdn.net/quantum7/article/details/118079707?spm=a2c6h.12873639.article-detail.6.34921197jV0jsyg

设置cron定时任务

crontap -e

设置三个任务(均为树莓派平台任务)

clean_pic.sh #每周周日清理保存的照片
ftp_login.sh #每一个小时进行登录并通过ftp上传至腾讯云轻量服务器
webcam.sh #每10分钟自动进行一次照片拍摄



# 蓝牙通讯

树莓派安装了bluez蓝牙代理程序，手机用的蓝牙调试宝，进行数据收发调试
![image](https://user-images.githubusercontent.com/94435405/228773878-eaf23c07-4876-4073-9aa2-9fbf515b7327.png)

