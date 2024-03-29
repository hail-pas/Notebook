# ssh 隧道端口转发    本地地址端口:远程地址端口
ssh -L 0.0.0.0:8000:127.0.0.1:8000 root@10.211.55.3

# lsof
lsof -i -n | grep ssh  # 查看ssh隧道
lsof -i tcp:3000  # 查看端口占用
lsof -i tcp:8000 | grep Python | awk '{print $2}' | xargs kill -9  # 关闭所有占用8000的程序

# http server
python3 -m http.server 8000 --bind 127.0.0.1

# http test
max=10
for i in `seq 1 $max`
do
    echo `curl -o /dev/null -s -w %{http_code}:%{time_namelookup}:%{time_connect}:%{time_appconnect}:%{time_pretransfer}:%{time_starttransfer}:%{time_total} https://sf.jmc.com.cn:8081/`
done
