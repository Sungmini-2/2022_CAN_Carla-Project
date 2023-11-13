# 2022_CAN_Carla-Project
#Carla 시뮬레이터를 이용하여 자율주행 차량을 통해 CAN DATA를 받아옴. #HONDA CANDB 을 통해 CAN Message Frame 설정하였음 #calra에서 받아오는 can data를 아두이노와 라즈베리파이 그리고 PCAN을 통해 HOST PC와의 CAN Interface 구축 #아두이노는 각 제어기 역할 #공격자가 PCAN을 통해 CAN Message공격을 하면 Carla시뮬레이터 차량의 제어에 문제가 생김. #이를 보완할 방법으로 parity check, HIGHT 알고리즘으로 데이터암호화하여 평문을 가려 리버싱 막기위함
