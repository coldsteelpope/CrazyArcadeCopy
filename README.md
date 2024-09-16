# [DirectX9] CrazyArcade 모작
3일 동안 제작한 Crazy Arcade 모작 게임입니다.

![crazyArcadeMain](https://github.com/user-attachments/assets/2a1294ec-73d0-478c-98ef-1118c9d90c84)

# 구현 컨텐츠 및 기능
## 1. 클라이언트
Socket Manager를 통해 서버와 통신합니다.

통신량을 최소화하기 위해 캐릭터 이동, 물풍선 설치, 블록 파괴 등 중요한 이벤트 발생 시에만 서버로 패킷을 전송하도록 설계했습니다.

![crazyArcadeBomb](https://github.com/user-attachments/assets/07d7db4d-5d37-4a61-8165-96767c823b2b)

![crazyArcadeDeath](https://github.com/user-attachments/assets/ea2f718c-bd15-4175-945d-c171ce38c072)

## 2. 게임 서버
### 2.1. 클라이언트 접속
클라이언트가 서버에 접속하면 자동으로 게임이 실행됩니다.
![crazyArcadeServer](https://github.com/user-attachments/assets/6f8d4242-1293-407b-92a8-751432bcfc19)

![crazyArcadeMap](https://github.com/user-attachments/assets/b7c3d972-5e9a-4a1e-ab4f-c604095c3ca2)
