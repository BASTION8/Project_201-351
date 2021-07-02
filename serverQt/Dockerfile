FROM ubuntu

COPY . ./serverQt

WORKDIR ./serverQt

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update
RUN apt-get install qt5-default -y
#RUN apt-get -y install qtcreator
RUN apt-get install qtbase5-dev -y
RUN apt-get install qt5-qmake
RUN apt-get install build-essential -y 

# ТУТ УКАЗАТЬ НОРМАЛЬНЫЙ ПУТЬ ДО СТАРТОГО ФАЙЛА
RUN qmake echoServer_351.pro
RUN make
CMD ["./echoServer_351"]